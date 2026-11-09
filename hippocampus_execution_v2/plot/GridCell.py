import numpy as np
from scipy.optimize import fsolve
import warnings

class GridCell:
    def __init__(self, ID, location, tau_refractory, coef_a, coef_d):
        # Create random number generator
        self.ranGen = np.random.default_rng(seed=ID)

        # Set cell ID
        self.ID = ID

        # Set cell location within medial entorhinal cortex
        self.location = location

        # Set time constant for refractory period
        self.tau = tau_refractory
        
        # Set parameters to generate grid field
        self.coef_a = coef_a
        self.coef_d = coef_d
    
    # Equation for sigmoidal function
    def sig(self, x, A, K, B, M, v):
        numerator = K - A
        denominator = (1 + np.exp(-B * (x - M)))
        return A + numerator / denominator**(1 / v)
    
    # Mapping grid map properties to grid map parameters
    def map_grid_param(self, position, A, d):
        x, y = position
        x = np.abs(x)
        y = np.abs(y)
        a = np.array([1, x, y, x**2, y**2, x**2*y, x**2*y**2, y**2, x*y**2, x*y])
        a1 = a * self.coef_a
        a2 = a * self.coef_d
        return (sum(a1) - A, sum(a2) - d)
    
    # Create grid map using topographic grid field properties
    def make_gridmap_topographic(self, position, gridCoeffs):
        min_y = 0
        max_y = 2.4080397823282595 # 2.4080397823282595 or 10
        y = max_y - self.location[1]
        
        ## --- Use sigmoid function to generate uniform size of grid field, but biological it is not necessary to make grid field size uniform --- ##
        # ysig = self.sig(y, min_y-0.32560712688527405, max_y, 2.15, -1.7858005014930183, 0.01) 
        # self.dist = gridCoeffs['slope']['gridSpacing'] * (ysig - min_y) + gridCoeffs['intercept']['gridSpacing']
        # self.area = 0.8 * (gridCoeffs['slope']['fieldSizes'] * (ysig - min_y) + gridCoeffs['intercept']['fieldSizes'])
        ## --- Use sigmoid function to generate uniform size of grid field, but biological it is not necessary to make grid field size uniform --- ##
        
        ## --- Disable sigmoid function  --- ##
        self.dist = gridCoeffs['slope']['gridSpacing'] * (y - min_y) + gridCoeffs['intercept']['gridSpacing']
        self.area = 0.8 * (gridCoeffs['slope']['fieldSizes'] * (y - min_y) + gridCoeffs['intercept']['fieldSizes'])
        ## --- Disable sigmoid function  --- ##
        
        self.theta = 2 * (self.dist - gridCoeffs['intercept']['orientationSpacing']) / gridCoeffs['slope']['orientationSpacing']
        self.theta += self.ranGen.normal(0, 15.49)

        # Given grid map properties, find grid map parameters
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            self.a, self.d = fsolve(self.map_grid_param, (0.01, 150), args=(self.area, self.dist))	

        self.a = np.abs(self.a)
        self.d = np.abs(self.d)

        ## -------------------------------------------------------------------------------##
        ## In grid cell model, each cell’s grid field (hexagonal pattern) is not “anchored” at a universal origin.
        ## Instead, each cell has a random phase offset—its grid pattern is shifted in space.
        ## x0 and y0 are random phase offset of grid field for this cell's grid in x and y
        ## This ensures that, even if two cells have the same grid spacing and orientation, their fields don’t exactly overlap
        
        # self.x0 = self.ranGen.uniform(-self.d, self.d) # -d to d is too small
        # self.y0 = self.ranGen.uniform(-self.d, self.d) # -d to d is too small
        
        ## Modify, multiply d by 10
        self.y0 = self.ranGen.uniform(-self.d * 10, self.d * 10) # -d to d is too small, 5 could be correct, >=10 could large 
        self.x0 = self.ranGen.uniform(-self.d * 10, self.d * 10) # -d to d is too small, 5 could be correct, >=10 could large 
        ## -------------------------------------------------------------------------------##
        
        self.c = np.array([[self.x0], [self.y0]])
    
    # Create grid map by manually setting grid field properties
    def make_gridmap(self, dist, area, theta):
        self.dist = dist
        self.area = area
        self.theta = theta
        
        # Given grid map properties, find grid map parameters
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            self.a, self.d = fsolve(self.map_grid_param, (0.01, 150), args=(self.area, self.dist))	

        self.a = np.abs(self.a)
        self.d = np.abs(self.d)

        self.x0 = self.ranGen.uniform(-self.d, self.d)
        self.y0 = self.ranGen.uniform(-self.d, self.d)
        self.c = np.array([[self.x0], [self.y0]])
        
    
    # Create firing rate profile from rat position and grid map
    def calc_firing_rate(self, position, firingrate_max):
        x = position["x"]
        y = position["y"]
        
        #thetak = np.array([-30*np.pi/180, 30*np.pi/180, 90*np.pi/180]) + self.theta # vertex angles, old wrong!
        thetak = np.array([-30*np.pi/180, 30*np.pi/180, 90*np.pi/180]) + self.theta * np.pi/180 # vertex angles, converted from degrees to radians, modified (2025.6.18)
        cossin = np.array( [np.cos(thetak), np.sin(thetak)] ).T
        
        coeff = 4 * np.pi / np.sqrt(3) / self.d
        r = np.array([x, y])
        r = r.reshape((2, np.prod(r.shape[1:])))
        
        summation = np.cos(coeff * np.dot(cossin, r - self.c))
        summation = summation.sum(axis=0)
        summation = summation.reshape(x.shape)
        
        self.firing_rates = np.exp((self.a * summation) + 1.5) - 1
        
        # Map firing rates between 0.1 and the maximum firing rate
        self.firing_rates -= np.min(self.firing_rates)
        self.firing_rates /= np.max(self.firing_rates)
        self.firing_rates *= firingrate_max
        self.firing_rates[self.firing_rates==0] = 0.1 # 0.1, maybe too low?
    
    def hetero_poisson(self, tstop, tres):
        # Generate spikes
        self.spike_times = []
        init_refract = -1e9
        t = 0
        while t < tstop:
            #ind = int(t / tres) # original
            ind = min(int(t / tres), len(self.firing_rates) - 1)# modify
            roll = self.ranGen.uniform(0, 1)
            refract = 1 - np.exp(-(t - init_refract) / self.tau)
            # Divide by 1000 to convert Hz from 1/s to 1/ms
            if (roll <= self.firing_rates[ind] * tres * refract / 1000):
                self.spike_times.append(t)
                init_refract = t+tres
            
            t += tres
        
        # Remove last spike time because it will be greater than tstop
        self.spike_times = self.spike_times[:-1]
    
    
