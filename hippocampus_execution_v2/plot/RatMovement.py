import numpy as np
import pylab as plt
import pickle

class RatMovement:
    def __init__(self, seed, tstop, dt, xlim, ylim, topspeed, max_interval):
        # Random number generator
        self.ranGen = np.random.default_rng(seed=seed)
        self.seed = seed

        # Length of simulation
        self.tstop = tstop
        self.dt = dt
        self.num_bins = int(tstop / dt)

        # Boundaries of enclosure
        self.xlim = xlim # cm
        self.ylim = ylim # cm

        # Initialize simulation time
        self.t = np.arange(self.num_bins)
        
        # The vertices
        self.vert_x = [0, 0, xlim, xlim, 0] # extra 0 for visualization purposes; completes the square
        self.vert_y = [0, ylim, ylim, 0, 0]

        # Initial position
        self.x = np.zeros(self.num_bins)
        self.x[0] = xlim / 2
        self.y = np.zeros(self.num_bins)
        self.y[0] = ylim / 2

        # Initial angle
        self.ang = self.ranGen.uniform(0, 2 * np.pi)
        
        # Initial speed
        # Maximum distance that can be traveled (cm/ms)
        self.topspeed = topspeed
        self.speed = self.ranGen.uniform(0, topspeed)
        
        # Initial velocity
        self.vx = self.speed * np.cos(self.ang)
        self.vy = self.speed * np.sin(self.ang)

        # Initial interval
        self.max_interval = max_interval # ms
        self.interval = self.ranGen.uniform(0, max_interval) # ms

    def simulate(self):
        # Get this simulation a rollin'
        t_interval = 0
        for ii in range(1, self.num_bins):
            x_delta = self.vx * self.dt
            y_delta = self.vy * self.dt
            self.x[ii] = self.x[ii - 1] + x_delta
            self.y[ii] = self.y[ii - 1] + y_delta

            # Reflecting position if goes beyonds borders
            self.check_borders(x_delta, y_delta, ii)
            
            t_interval += self.dt
            
            # Update velocities after interval is reached
            if t_interval >= self.interval:
                self.update_velocity()
                t_interval = 0

    def check_borders(self, x_delta, y_delta, ind):
        flag = 0
        if self.x[ind] > self.xlim:
            traveled = self.xlim - self.x[ind - 1]
            reflection = x_delta - traveled
            self.x[ind] = self.xlim - reflection
            flag = 1
        if self.x[ind] < 0:
            traveled = self.x[ind - 1]
            reflection = x_delta - traveled
            self.x[ind] = reflection
            flag = 1
        if self.y[ind] > self.ylim:
            traveled = self.ylim - self.y[ind - 1]
            reflection = y_delta - traveled
            self.y[ind] = self.ylim - reflection
            flag = 1
        if self.y[ind] < 0:
            traveled = self.y[ind - 1]
            reflection = y_delta - traveled
            self.y[ind] = reflection
            flag = 1
        if flag:
            self.ang += np.pi/2
            self.vx = self.speed * np.cos(self.ang)
            self.vy = self.speed * np.sin(self.ang)
    
    def update_velocity(self):
        # Making the animal prefer to travel in the longer direction
        if self.xlim < self.ylim:
            roll = self.ranGen.uniform(0, 1)
            coin = self.ranGen.integers(0, 1, endpoint=True)
            coeff = float(self.xlim)/self.ylim
            if roll < coeff:
                if coin == 0:
                    self.ang = self.ranGen.uniform(-np.pi / 4, np.pi / 4)
                else:
                    self.ang = self.ranGen.uniform(3 * np.pi / 4, 5 * np.pi / 4)
            else:
                if coin == 0:
                    self.ang = self.ranGen.uniform(np.pi / 4, 3 * np.pi / 4)
                else:
                    self.ang = self.ranGen.uniform(5 * np.pi / 4, 7 * np.pi / 4)
        elif self.ylim < self.xlim:
            roll = self.ranGen.uniform(0, 1)
            coin = self.ranGen.integers(0, 1, endpoint=True)
            coeff = float(self.ylim)/self.xlim
            if roll < coeff:
                if coin == 0:
                    self.ang = self.ranGen.uniform(np.pi / 4, 3 * np.pi / 4)
                else:
                    self.ang = self.ranGen.uniform(5 * np.pi / 4, 7 * np.pi / 4)
            else:
                if coin == 0:
                    self.ang = self.ranGen.uniform(-np.pi / 4, np.pi / 4)
                else:
                    self.ang = self.ranGen.uniform(3 * np.pi / 4, 5 * np.pi / 4)
        else:
            self.ang = self.ranGen.uniform(0, 2 * np.pi)
        self.speed = self.ranGen.uniform(0, self.topspeed)
        self.vx = self.speed * np.cos(self.ang)
        self.vy = self.speed * np.sin(self.ang)
        self.interval = self.ranGen.uniform(0, self.max_interval)
    
    def to_dictionary(self):
        self.position = {}
        self.position['x'] = self.x
        self.position['y'] = self.y
        self.position['time'] = self.t
        self.position['tstop'] = self.tstop
        self.position['tres'] = self.dt
        
    def add_noise(self, stdev=0.5):
        self.stdev = stdev
        self.x_noise = self.ranGen.normal(0, stdev, len(x_track))
        self.y_noise = self.ranGen.normal(0, stdev, len(x_track))
        self.x += self.x_noise
        self.y += self.y_noise

    def compute_total_distance(self):
        self.total_distance = np.sum( np.sqrt( np.diff(self.x)**2 + np.diff(self.y)**2 ) )
        print("Total Distance: %f cm" % self.total_distance)
    
    def compute_position_density(self, sres):
        self.sres = sres
        x_bins = int(self.xlim / self.sres)
        y_bins = int(self.ylim / self.sres)
        self.position_density = np.zeros((y_bins, x_bins))
        x_ind = (self.x / self.sres).astype(int)
        y_ind = (self.y / self.sres).astype(int)
        for ii in range(self.num_bins):
            self.position_density[y_ind[ii]][x_ind[ii]] += 1
        
        self.cv = np.std(self.position_density) / np.mean(self.position_density)
        print("CV: %f" % self.cv)
        ## cv is coefficient of variation
    
    def plot_trajectory(self):
        fig_trajectory = plt.figure()
        plt.plot(self.x, self.y, "w", linewidth=0.2)
        x_plot = np.linspace(0, self.xlim, self.position_density.shape[1] + 1)
        y_plot = np.linspace(0, self.ylim, self.position_density.shape[0] + 1)
        ax = plt.pcolormesh(x_plot, y_plot, self.position_density)
        ax.axes.set_aspect("equal")
        plt.xlabel("x-position (cm)")
        plt.ylabel("y-position (cm)")
        plt.xlim(0, self.xlim)
        plt.ylim(0, self.ylim)
        return fig_trajectory
    
    def save_data(self, fname="data_rat_positions.pickle"):
        with open(fname, "wb") as f:
            pickle.dump(self.position, f)
