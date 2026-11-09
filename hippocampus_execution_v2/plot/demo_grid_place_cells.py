"""Plot existing EC grid-cell and hippocampal spike recordings.

Keep RatMovement.py beside this script. MEC spikes stay in ../results/;
hippocampal spikes go in ../results/DG/, ../results/CA3/, and ../results/CA1/.
The rat trajectory must match the trajectory used to generate those recordings.
GridCell.py and both parameter pickles are included beside this script.
Grid-spike generation still awaits the current main generation script and HDF5 data.
"""

# Interactive backend in Spyder/IPython; ordinary execution uses Matplotlib defaults.
FIGURE_BACKEND = 'qt'
try:
    from IPython import get_ipython
    ipython = get_ipython()
    if ipython is not None:
        if FIGURE_BACKEND.lower() == 'qt':
            ipython.run_line_magic('matplotlib', 'qt')
        elif FIGURE_BACKEND.lower() == 'inline':
            ipython.run_line_magic('matplotlib', 'inline')
except Exception as e:
    print('[WARNING] Could not set Matplotlib backend.')
    print(f'          Reason: {e}')

import os
from pathlib import Path

import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage import gaussian_filter
from scipy.stats import gaussian_kde

from RatMovement import RatMovement

# Trajectory: time in ms, space in cm. Keep these consistent with the input spikes.
seed = 1760
t_offset = 10000
tstop = 1200000
tres = 1
sres = 4.0
xlim = 60.0
ylim = 60.0
topspeed = 0.03
max_interval = 500.0

# Edit filenames here; the place-cell examples use 1,200-second recordings.
RESULTS_DIR = Path(__file__).resolve().parent.parent / 'results'
MEC_SPIKE_FILE = os.path.join(
    RESULTS_DIR,
    'MEC_66000cells_1200.0sec(mean=2.1Hz,ymax=2.4,60x60cm,non-uniform grid field,d*10,min=0.1Hz)_SimData_MCscale5.dat',
)
DGGC_SPIKE_FILE = os.path.join(RESULTS_DIR, 'DG', 'spk_DG_GC_1200sec.dat')
CA3PC_SPIKE_FILE = os.path.join(RESULTS_DIR, 'CA3', 'spk_CA3_PC_1200sec.dat')
CA1PC_SPIKE_FILE = os.path.join(RESULTS_DIR, 'CA1', 'spk_CA1_PC_type3_1200sec.dat')
SPIKE_FILES = {
    'EC_GRID': MEC_SPIKE_FILE,
    'DGGC': DGGC_SPIKE_FILE,
    'CA3PC': CA3PC_SPIKE_FILE,
    'CA1PC': CA1PC_SPIKE_FILE,
}
PLACE_CELL_POPULATIONS = ['DGGC', 'CA3PC', 'CA1PC']

# Analysis and overview settings.
ANALYSIS_START_MS = int(t_offset)
ANALYSIS_END_MS = int(tstop)
ANALYSIS_START_S = ANALYSIS_START_MS / 1000.0
ANALYSIS_END_S = ANALYSIS_END_MS / 1000.0
if ANALYSIS_END_MS <= ANALYSIS_START_MS:
    raise ValueError('tstop must be greater than t_offset.')
MAP_SMOOTH_SIGMA_BINS = 0.75
N_OVERVIEW_CELLS = 280
OVERVIEW_NCOLS = 20
EC_FR_LOW_HZ = 0.1
EC_FR_HIGH_HZ = 2.2
HIPPOCAMPAL_FR_LOW_HZ = 0.1
HIPPOCAMPAL_FR_HIGH_HZ = 2.65
OVERVIEW_FR_RANGES_HZ = {
    'EC_GRID': (EC_FR_LOW_HZ, EC_FR_HIGH_HZ),
    'DGGC': (HIPPOCAMPAL_FR_LOW_HZ, HIPPOCAMPAL_FR_HIGH_HZ),
    'CA3PC': (HIPPOCAMPAL_FR_LOW_HZ, HIPPOCAMPAL_FR_HIGH_HZ),
    'CA1PC': (HIPPOCAMPAL_FR_LOW_HZ, HIPPOCAMPAL_FR_HIGH_HZ),
}
PLACE_CMAP = 'jet'
SHOW_EACH_SUBPLOT_COLORBAR = False
RANDOM_RATE_HZ = 0.7
RANDOM_SEED = 345
SPATIAL_INFORMATION_XMIN = 0.0
SPATIAL_INFORMATION_XMAX = 0.55
SPATIAL_INFORMATION_KDE_POINTS = 500
SPATIAL_INFORMATION_KDE_BW_METHOD = 'scott'

# Selected examples and figure output. Neuron IDs are zero-based.
SAVE_SELECTED_FIGURE = True
SELECTED_FIGURE_DIR = Path(__file__).resolve().parent.parent / 'figures' / 'place_field_analysis'
os.makedirs(SELECTED_FIGURE_DIR, exist_ok=True)
SELECTED_FIGURE_BASENAME_PREFIX = 'selected_EC_DG_CA3_CA1_spatial_firing_maps'
SELECTED_PLACE_FIELD_IDS = {
    'EC_GRID': [180, 9000, 32000, 46000, 65489],
    'DGGC': [39975, 50239, 53571, 85395, 119502],
    'CA3PC': [3756, 15057, 15723, 17762, 21986],
    'CA1PC': [855, 18581, 21211, 29544, 32229],
}
SELECTED_REGION_ORDER = ('EC_GRID', 'DGGC', 'CA3PC', 'CA1PC')
N_SELECTED_CELLS = len(SELECTED_PLACE_FIELD_IDS[SELECTED_REGION_ORDER[0]])
SELECTED_FIG_FIGSIZE = (2.12 * (N_SELECTED_CELLS + 1), 10.8)
SELECTED_FIG_DPI = 300
SELECTED_INTERPOLATION = 'bicubic'
SHOW_SELECTED_TICKS = False
SELECTED_TRAJECTORY_STEP = 1500
SELECTED_TRAJECTORY_COLOR = 'white'
SELECTED_TRAJECTORY_LINE_WIDTH = 0.7
SELECTED_TRAJECTORY_ALPHA = 0.4

if N_SELECTED_CELLS <= 0:
    raise ValueError('SELECTED_PLACE_FIELD_IDS must contain at least one cell per population.')
for pop_name in SELECTED_REGION_ORDER:
    n_ids = len(SELECTED_PLACE_FIELD_IDS[pop_name])
    if n_ids != N_SELECTED_CELLS:
        raise ValueError(
            f'SELECTED_PLACE_FIELD_IDS[{pop_name!r}] contains {n_ids} IDs, '
            f'but all selected populations must contain {N_SELECTED_CELLS} IDs.'
        )
print(
    f'[INFO] Analysis window: {ANALYSIS_START_S:.1f}–{ANALYSIS_END_S:.1f} s '
    f'({ANALYSIS_START_MS}–{ANALYSIS_END_MS} ms)'
)
print(f'[INFO] sres = {sres} cm')
print(f'[INFO] MAP_SMOOTH_SIGMA_BINS = {MAP_SMOOTH_SIGMA_BINS}')
print(f'[INFO] PLACE_CMAP = {PLACE_CMAP}')
print('[INFO] Spatial-map display = per-neuron z-score normalization')
print(f'[INFO] RANDOM_RATE_HZ = {RANDOM_RATE_HZ}')
print(f'[INFO] EC overview FR filter = {EC_FR_LOW_HZ:.2f}–{EC_FR_HIGH_HZ:.2f} Hz')
print(
    f'[INFO] DG/CA3/CA1 overview FR filter = {HIPPOCAMPAL_FR_LOW_HZ:.2f}–{HIPPOCAMPAL_FR_HIGH_HZ:.2f} Hz'
)


# Re-create the original trajectory and occupancy maps.
def get_rat_time_seconds(rat_obj):
    """Return trajectory times in seconds using the original unit convention."""
    t_raw = np.asarray(rat_obj.position['time'], dtype=float)
    if np.nanmax(t_raw) > 10000:
        return t_raw / 1000.0
    return t_raw


print('Creating rat movements')
rat = RatMovement(seed, tstop, tres, xlim, ylim, topspeed, max_interval)
rat.simulate()
rat.to_dictionary()
rat.compute_total_distance()
rat.compute_position_density(sres=sres)
rat_time_s = get_rat_time_seconds(rat)
print(f'[INFO] Generated rat trajectory time range: {rat_time_s[0]:.3f}–{rat_time_s[-1]:.3f} s')
print(f'[INFO] Trajectory/occupancy/map interval used: {ANALYSIS_START_S:.3f}–{ANALYSIS_END_S:.3f} s')
print('Rat movements finished')


def build_time_map():
    """Smooth occupancy in seconds; replace unvisited-bin denominators with one."""
    t_s = get_rat_time_seconds(rat)
    x = np.asarray(rat.position['x'], dtype=float)
    y = np.asarray(rat.position['y'], dtype=float)
    keep = (t_s >= ANALYSIS_START_S) & (t_s < ANALYSIS_END_S)
    nbins_x = int(xlim / sres)
    nbins_y = int(ylim / sres)
    time_map_raw = np.zeros((nbins_y, nbins_x), dtype=float)
    x_ind = (x[keep] / sres).astype(int)
    y_ind = (y[keep] / sres).astype(int)
    valid = (x_ind >= 0) & (x_ind < nbins_x) & (y_ind >= 0) & (y_ind < nbins_y)
    x_ind = x_ind[valid]
    y_ind = y_ind[valid]
    np.add.at(time_map_raw, (y_ind, x_ind), tres / 1000.0)
    print(
        f'[INFO] time_map total occupancy = {np.sum(time_map_raw):.2f} s; '
        f'visited bins = {np.sum(time_map_raw > 0)}'
    )
    if MAP_SMOOTH_SIGMA_BINS > 0:
        time_map_use = gaussian_filter(
            time_map_raw.astype(float),
            sigma=MAP_SMOOTH_SIGMA_BINS,
            mode='constant',
            cval=0.0,
        )
    else:
        time_map_use = time_map_raw.copy()
    time_map_use[time_map_use == 0] = 1.0
    return time_map_use


time_map = build_time_map()
x_plot = np.linspace(0, rat.xlim, time_map.shape[1] + 1)
y_plot = np.linspace(0, rat.ylim, time_map.shape[0] + 1)


def build_spatial_score_movement_histogram():
    t_s = get_rat_time_seconds(rat)
    x = np.asarray(rat.position['x'], dtype=float)
    y = np.asarray(rat.position['y'], dtype=float)
    keep = (t_s >= ANALYSIS_START_S) & (t_s < ANALYSIS_END_S)
    nbins_x = int(xlim / sres)
    nbins_y = int(ylim / sres)
    hist_movement = np.zeros((nbins_y, nbins_x), dtype=float)
    x_ind = (x[keep] / sres).astype(int)
    y_ind = (y[keep] / sres).astype(int)
    valid = (x_ind >= 0) & (x_ind < nbins_x) & (y_ind >= 0) & (y_ind < nbins_y)
    np.add.at(hist_movement, (y_ind[valid], x_ind[valid]), 1.0)
    return hist_movement


SPATIAL_SCORE_MOVEMENT_HISTOGRAM = build_spatial_score_movement_histogram()


# Load CARLsim spikes and index each neuron.
def read_spike_dat(dat_path):
    """Skip the 20-byte header and read int32 (time_ms, neuron_id) pairs."""
    dat_path = os.path.expanduser(dat_path)
    if not os.path.exists(dat_path):
        raise FileNotFoundError(f'Spike file not found: {dat_path}')
    with open(dat_path, 'rb') as f:
        f.seek(20)
        raw = np.fromfile(f, dtype=np.int32)
    if raw.size % 2 != 0:
        raw = raw[:-1]
    data = raw.reshape(-1, 2)
    spike_times_ms = data[:, 0].astype(np.int64)
    neuron_ids = data[:, 1].astype(np.int64)
    keep = (spike_times_ms >= ANALYSIS_START_MS) & (spike_times_ms < ANALYSIS_END_MS) & (neuron_ids >= 0)
    spike_times_ms = spike_times_ms[keep]
    neuron_ids = neuron_ids[keep]
    print(
        f'[INFO] Loaded {len(spike_times_ms):,} spikes from {os.path.basename(dat_path)} '
        f'in analysis window; active cells = {len(np.unique(neuron_ids)):,}'
    )
    return (spike_times_ms, neuron_ids)


def make_spike_index(spike_times_ms, neuron_ids):
    """Group spike times by neuron so repeated lookup needs no full-file scan."""
    sort_idx = np.argsort(neuron_ids)
    sorted_ids = neuron_ids[sort_idx]
    sorted_times = spike_times_ms[sort_idx]
    unique_ids, start_idx, counts = np.unique(sorted_ids, return_index=True, return_counts=True)
    id_to_row = {int(cid): i for i, cid in enumerate(unique_ids)}
    return (sorted_times, unique_ids, start_idx, counts, id_to_row)


def get_cell_spikes(cell_id, sorted_times, start_idx, counts, id_to_row):
    row = id_to_row.get(int(cell_id), None)
    if row is None:
        return np.array([], dtype=np.int64)
    idx0 = start_idx[row]
    n_spikes = counts[row]
    return sorted_times[idx0:idx0 + n_spikes]


def select_overview_ids(pop_name, unique_ids, counts):
    if pop_name not in OVERVIEW_FR_RANGES_HZ:
        raise KeyError(f'No overview firing-rate range defined for {pop_name}.')
    duration_s = ANALYSIS_END_S - ANALYSIS_START_S
    if duration_s <= 0:
        raise ValueError('The analysis duration must be positive.')
    firing_rates_hz = counts.astype(float) / duration_s
    fr_low_hz, fr_high_hz = OVERVIEW_FR_RANGES_HZ[pop_name]
    eligible = (firing_rates_hz >= fr_low_hz) & (firing_rates_hz <= fr_high_hz)
    active_ids = np.asarray(unique_ids[eligible], dtype=np.int64)
    active_ids = np.sort(active_ids)
    print(
        f'[INFO] {pop_name}: {len(active_ids):,} cells passed '
        f'the {fr_low_hz:.2f}–{fr_high_hz:.2f} Hz overview filter.'
    )
    if len(active_ids) == 0:
        return np.array([], dtype=np.int64)
    if len(active_ids) <= N_OVERVIEW_CELLS:
        return active_ids
    idx = np.linspace(0, len(active_ids) - 1, N_OVERVIEW_CELLS).astype(int)
    return active_ids[idx]


# Display maps use direct millisecond indexing into the trajectory.
def build_spike_map_from_spikes(spikes):
    nbins_x = int(xlim / sres)
    nbins_y = int(ylim / sres)
    spike_map = np.zeros((nbins_y, nbins_x), dtype=float)
    spikes = np.asarray(spikes, dtype=np.int64)
    spikes = spikes[(spikes >= ANALYSIS_START_MS) & (spikes < ANALYSIS_END_MS)]
    if len(spikes) == 0:
        return spike_map
    time_idx = (spikes / tres).astype(int)
    valid_time = (time_idx >= 0) & (time_idx < len(rat.position['x']))
    time_idx = time_idx[valid_time]
    x_ind = (np.asarray(rat.position['x'])[time_idx] / sres).astype(int)
    y_ind = (np.asarray(rat.position['y'])[time_idx] / sres).astype(int)
    valid_xy = (x_ind >= 0) & (x_ind < nbins_x) & (y_ind >= 0) & (y_ind < nbins_y)
    x_ind = x_ind[valid_xy]
    y_ind = y_ind[valid_xy]
    np.add.at(spike_map, (y_ind, x_ind), 1.0)
    return spike_map


def build_rate_map_from_spikes(spikes):
    spike_map = build_spike_map_from_spikes(spikes)
    if MAP_SMOOTH_SIGMA_BINS > 0:
        spike_map_use = gaussian_filter(
            spike_map.astype(float),
            sigma=MAP_SMOOTH_SIGMA_BINS,
            mode='constant',
            cval=0.0,
        )
    else:
        spike_map_use = spike_map
    rate_map = spike_map_use / time_map
    return rate_map


def zscore_rate_map(rate_map):
    """Standardize each neuron map by its own spatial mean and standard deviation."""
    rate_map = np.asarray(rate_map, dtype=float)
    finite_mask = np.isfinite(rate_map)
    if not np.any(finite_mask):
        return np.zeros_like(rate_map, dtype=float)
    finite_vals = rate_map[finite_mask]
    mean = np.mean(finite_vals)
    std = np.std(finite_vals)
    if not np.isfinite(std) or std <= 0:
        return np.zeros_like(rate_map, dtype=float)
    z_map = np.zeros_like(rate_map, dtype=float)
    z_map[finite_mask] = (rate_map[finite_mask] - mean) / std
    return z_map


# Score maps retain the original searchsorted time alignment.
def build_spatial_score_spike_histogram(spikes):
    nbins_x = int(xlim / sres)
    nbins_y = int(ylim / sres)
    hist_spikes = np.zeros((nbins_y, nbins_x), dtype=float)
    spikes = np.asarray(spikes, dtype=np.int64)
    spikes = spikes[(spikes >= ANALYSIS_START_MS) & (spikes < ANALYSIS_END_MS)]
    if spikes.size == 0:
        return hist_spikes
    spike_times_s = spikes.astype(float) / 1000.0
    time_idx = np.searchsorted(rat_time_s, spike_times_s, side='left')
    valid_time = (time_idx >= 0) & (time_idx < len(rat.position['x']))
    time_idx = time_idx[valid_time]
    x = np.asarray(rat.position['x'], dtype=float)
    y = np.asarray(rat.position['y'], dtype=float)
    x_ind = (x[time_idx] / sres).astype(int)
    y_ind = (y[time_idx] / sres).astype(int)
    valid_xy = (x_ind >= 0) & (x_ind < nbins_x) & (y_ind >= 0) & (y_ind < nbins_y)
    np.add.at(hist_spikes, (y_ind[valid_xy], x_ind[valid_xy]), 1.0)
    return hist_spikes


def build_fixed_gaussian_rate_map_for_spatial_score(spikes):
    hist_spikes = build_spatial_score_spike_histogram(spikes)
    occupancy_time_s = SPATIAL_SCORE_MOVEMENT_HISTOGRAM * (tres / 1000.0)
    if MAP_SMOOTH_SIGMA_BINS > 0:
        spike_map_use = gaussian_filter(
            hist_spikes.astype(float),
            sigma=MAP_SMOOTH_SIGMA_BINS,
            mode='constant',
            cval=0.0,
        )
        occupancy_map_use = gaussian_filter(
            occupancy_time_s.astype(float),
            sigma=MAP_SMOOTH_SIGMA_BINS,
            mode='constant',
            cval=0.0,
        )
    else:
        spike_map_use = hist_spikes.astype(float)
        occupancy_map_use = occupancy_time_s.astype(float)
    occupancy_map_use[occupancy_map_use == 0] = 1.0
    return spike_map_use / occupancy_map_use


def spatial_information_score_unweighted_mean(hist_rate, hist_movement):
    """Keep the original arithmetic mean of bin rates in the information score."""
    p = hist_movement / hist_movement.sum()
    r_ave = np.mean(hist_rate)
    with np.errstate(divide='ignore', invalid='ignore'):
        score = np.sum(p * hist_rate / r_ave * np.log2(hist_rate / r_ave))
    return float(score)


def calculate_all_population_unweighted_spatial_information(
    pop_name,
    sorted_times,
    unique_ids,
    start_idx,
    counts,
    id_to_row,
):
    duration_s = ANALYSIS_END_S - ANALYSIS_START_S
    if duration_s <= 0:
        raise ValueError('The analysis duration must be positive.')
    firing_rates_hz = counts.astype(float) / duration_s
    fr_low_hz, fr_high_hz = OVERVIEW_FR_RANGES_HZ[pop_name]
    eligible = (firing_rates_hz >= fr_low_hz) & (firing_rates_hz <= fr_high_hz)
    cell_ids = np.asarray(unique_ids[eligible], dtype=np.int64)
    scores = np.full(cell_ids.size, np.nan, dtype=float)
    for index, cell_id in enumerate(cell_ids):
        spikes = get_cell_spikes(cell_id, sorted_times, start_idx, counts, id_to_row)
        rate_map = build_fixed_gaussian_rate_map_for_spatial_score(spikes)
        scores[index] = spatial_information_score_unweighted_mean(
            rate_map,
            SPATIAL_SCORE_MOVEMENT_HISTOGRAM,
        )
    return {'cell_ids': cell_ids, 'unweighted_mean': scores}


# Random Poisson control; this does not generate grid-cell spikes.
def generate_random_spikes(rate_hz, rng):
    duration_s = ANALYSIS_END_S - ANALYSIS_START_S
    expected_spikes = rate_hz * duration_s
    n_spikes = rng.poisson(expected_spikes)
    if n_spikes <= 0:
        return np.array([], dtype=np.int64)
    spike_times_s = rng.uniform(ANALYSIS_START_S, ANALYSIS_END_S, size=n_spikes)
    spike_times_ms = np.sort((1000.0 * spike_times_s).astype(np.int64))
    return spike_times_ms


def build_random_examples():
    rng = np.random.default_rng(RANDOM_SEED)
    examples = []
    for ii in range(N_OVERVIEW_CELLS):
        spikes = generate_random_spikes(RANDOM_RATE_HZ, rng)
        rate_map = build_rate_map_from_spikes(spikes)
        examples.append({
            'label': f'Rand {ii + 1}, n={len(spikes)}',
            'cell_id': ii + 1,
            'n_spikes': len(spikes),
            'spikes': spikes,
            'rate_map': rate_map,
        })
    n_spikes_all = [ex['n_spikes'] for ex in examples]
    print(
        f'[INFO] Random control: rate={RANDOM_RATE_HZ} Hz, '
        f'mean spikes/cell={np.mean(n_spikes_all):.1f}, '
        f'expected={RANDOM_RATE_HZ * (ANALYSIS_END_S - ANALYSIS_START_S):.1f}'
    )
    return examples


# Choose overview and manually selected cells.
def build_real_overview_examples(pop_name, sorted_times, unique_ids, start_idx, counts, id_to_row):
    selected_ids = select_overview_ids(pop_name, unique_ids, counts)
    examples = []
    for cell_id in selected_ids:
        spikes = get_cell_spikes(cell_id, sorted_times, start_idx, counts, id_to_row)
        rate_map = build_rate_map_from_spikes(spikes)
        examples.append({
            'label': f'ID {int(cell_id)}',
            'cell_id': int(cell_id),
            'n_spikes': len(spikes),
            'spikes': spikes,
            'rate_map': rate_map,
        })
    if len(examples) < N_OVERVIEW_CELLS:
        fr_low_hz, fr_high_hz = OVERVIEW_FR_RANGES_HZ[pop_name]
        print(
            f'[WARNING] {pop_name}: requested {N_OVERVIEW_CELLS} overview cells, '
            f'but only {len(examples)} cells passed '
            f'the {fr_low_hz:.2f}–{fr_high_hz:.2f} Hz firing-rate filter.'
        )
    return examples


def build_blank_selected_example(pop_name, column_index):
    return {
        'label': f'{pop_name} unassigned column {column_index + 1}',
        'cell_id': None,
        'n_spikes': 0,
        'spikes': np.array([], dtype=np.int64),
        'rate_map': np.zeros_like(time_map, dtype=float),
        'is_blank': True,
    }


def get_cell_firing_rate_hz(n_spikes):
    duration_s = ANALYSIS_END_S - ANALYSIS_START_S
    if duration_s <= 0:
        raise ValueError('The analysis duration must be positive.')
    return float(n_spikes) / float(duration_s)


def is_cell_within_fr_range(pop_name, n_spikes):
    if pop_name not in OVERVIEW_FR_RANGES_HZ:
        raise KeyError(f'No firing-rate range defined for {pop_name}.')
    fr_low_hz, fr_high_hz = OVERVIEW_FR_RANGES_HZ[pop_name]
    firing_rate_hz = get_cell_firing_rate_hz(n_spikes)
    return firing_rate_hz >= fr_low_hz and firing_rate_hz <= fr_high_hz


def build_selected_examples(pop_name, sorted_times, start_idx, counts, id_to_row):
    """Preserve selected IDs; absent or out-of-range cells are shown as blank maps."""
    selected_ids = list(SELECTED_PLACE_FIELD_IDS[pop_name])
    if len(selected_ids) != N_SELECTED_CELLS:
        raise ValueError(
            f'SELECTED_PLACE_FIELD_IDS[{pop_name!r}] contains {len(selected_ids)} IDs, '
            f'but Figure 6 requires {N_SELECTED_CELLS} selected cells per population.'
        )
    examples = []
    for column_index, cell_id in enumerate(selected_ids):
        if cell_id is None:
            examples.append(build_blank_selected_example(pop_name, column_index))
            continue
        spikes = get_cell_spikes(cell_id, sorted_times, start_idx, counts, id_to_row)
        if len(spikes) == 0:
            print(f'[WARNING] {pop_name} ID {cell_id} not found. Using blank map.')
            examples.append(build_blank_selected_example(pop_name, column_index))
            continue
        firing_rate_hz = get_cell_firing_rate_hz(len(spikes))
        if not is_cell_within_fr_range(pop_name, len(spikes)):
            fr_low_hz, fr_high_hz = OVERVIEW_FR_RANGES_HZ[pop_name]
            print(
                f'[WARNING] {pop_name} ID {cell_id} has FR={firing_rate_hz:.3f} Hz, '
                f'outside {fr_low_hz:.2f}–{fr_high_hz:.2f} Hz. Using blank map in Figure 6.'
            )
            examples.append(build_blank_selected_example(pop_name, column_index))
            continue
        rate_map = build_rate_map_from_spikes(spikes)
        examples.append({
            'label': f'{pop_name} ID {int(cell_id)}',
            'cell_id': int(cell_id),
            'n_spikes': len(spikes),
            'spikes': spikes,
            'rate_map': rate_map,
            'is_blank': False,
        })
    return examples


# Figures 1–5: population overviews and random control.
def plot_examples_grid(title, examples, show_peak_rate=False):
    if len(examples) == 0:
        raise ValueError(f'No examples available for {title}')
    ncols = OVERVIEW_NCOLS
    nrows = int(np.ceil(len(examples) / ncols))
    fig, axes = plt.subplots(nrows, ncols, figsize=(2.25 * ncols, 2.25 * nrows), squeeze=False)
    try:
        fig.canvas.manager.set_window_title(title)
    except Exception:
        pass
    for ax in axes.ravel():
        ax.axis('off')
    for ii, example in enumerate(examples):
        ax = axes.ravel()[ii]
        ax.axis('on')
        rate_map = np.asarray(example['rate_map'], dtype=float)
        z_map = zscore_rate_map(rate_map)
        finite_vals = rate_map[np.isfinite(rate_map)]
        peak_rate_hz = float(np.max(finite_vals)) if finite_vals.size > 0 else 0.0
        image = ax.pcolormesh(x_plot, y_plot, z_map, cmap=PLACE_CMAP, shading='flat')
        if SHOW_EACH_SUBPLOT_COLORBAR:
            plt.colorbar(image, ax=ax, fraction=0.046, pad=0.02)
        ax.axes.set_aspect('equal')
        ax.set_xlim(0, xlim)
        ax.set_ylim(0, ylim)
        if show_peak_rate:
            ax.set_title(f"{example['label']}\n{peak_rate_hz:.2f} Hz", fontsize=8)
        else:
            ax.set_title(example['label'], fontsize=8)
        ax.set_xticks([0, 30, 60])
        ax.set_yticks([0, 30, 60])
        ax.tick_params(axis='both', labelsize=8)
        row = ii // ncols
        col = ii % ncols
        if row == nrows - 1:
            ax.set_xlabel('x (cm)', fontsize=9)
        else:
            ax.set_xticklabels([])
        if col == 0:
            ax.set_ylabel('y (cm)', fontsize=9)
        else:
            ax.set_yticklabels([])
    fig.suptitle(title, fontsize=16, y=0.995)
    fig.subplots_adjust(left=0.04, right=0.98, top=0.94, bottom=0.05, wspace=0.18, hspace=0.28)
    return fig


# Figure 6: selected maps, trajectories, and spatial-information distributions.
def overlay_trajectory_on_rate_map(ax):
    t_s = get_rat_time_seconds(rat)
    x = np.asarray(rat.position['x'], dtype=float)
    y = np.asarray(rat.position['y'], dtype=float)
    keep = (t_s >= ANALYSIS_START_S) & (t_s < ANALYSIS_END_S)
    ax.plot(
        x[keep][::SELECTED_TRAJECTORY_STEP],
        y[keep][::SELECTED_TRAJECTORY_STEP],
        color=SELECTED_TRAJECTORY_COLOR,
        lw=SELECTED_TRAJECTORY_LINE_WIDTH,
        alpha=SELECTED_TRAJECTORY_ALPHA,
        zorder=10,
    )


def build_spatial_score_kde(scores):
    """Estimate score density and normalize its area within the displayed x range."""
    scores = np.asarray(scores, dtype=float)
    scores = scores[np.isfinite(scores)]
    x_curve = np.linspace(
        SPATIAL_INFORMATION_XMIN,
        SPATIAL_INFORMATION_XMAX,
        SPATIAL_INFORMATION_KDE_POINTS,
    )
    if scores.size < 2:
        return (x_curve, np.zeros_like(x_curve))
    score_std = float(np.std(scores))
    if not np.isfinite(score_std) or score_std <= 0:
        return (x_curve, np.zeros_like(x_curve))
    kde = gaussian_kde(scores, bw_method=SPATIAL_INFORMATION_KDE_BW_METHOD)
    density = kde(x_curve)
    density = np.asarray(density, dtype=float)
    density[~np.isfinite(density)] = 0.0
    density = np.clip(density, 0.0, None)
    area = np.trapz(density, x_curve)
    if np.isfinite(area) and area > 0:
        density = density / area
    return (x_curve, density)


def plot_unweighted_spatial_score_histogram(ax, kde_plot_data, shared_ymax, show_xlabel=False):
    x_curve = kde_plot_data['x_curve']
    density = kde_plot_data['density']
    mean_score = kde_plot_data['mean_score']
    ax.fill_between(x_curve, 0.0, density, facecolor='0.80', edgecolor='none', zorder=1)
    ax.plot(x_curve, density, color='black', linewidth=1.5, zorder=2)
    ax.axvline(mean_score, color='black', linestyle='--', linewidth=1.2, zorder=4)
    ax.text(
        0.95,
        0.92,
        f'mean = {mean_score:.3f}',
        transform=ax.transAxes,
        ha='right',
        va='top',
        fontsize=9,
        fontweight='bold',
        color='black',
        zorder=10,
        bbox={'facecolor': 'white', 'edgecolor': 'none', 'alpha': 0.85, 'pad': 1.5},
    )
    ax.set_xlim(SPATIAL_INFORMATION_XMIN, SPATIAL_INFORMATION_XMAX)
    ax.set_ylim(0.0, shared_ymax)
    ax.set_box_aspect(1)
    ax.set_yticks([])
    ax.tick_params(axis='y', left=False, labelleft=False)
    if show_xlabel:
        ax.set_xticks([0.0, 0.2, 0.4])
        ax.tick_params(axis='x', bottom=True, labelbottom=True, labelsize=8)
        ax.set_xlabel('Spatial Information\n(bits/spike)', fontsize=9)
    else:
        ax.set_xticks([])
        ax.tick_params(axis='x', bottom=False, labelbottom=False)
    ax.set_title('')


def plot_selected_grid(selected_examples_all, spatial_scores_all):
    required = list(SELECTED_REGION_ORDER)
    nrows = len(required)
    n_place_cols = N_SELECTED_CELLS
    ncols_total = N_SELECTED_CELLS + 1
    fig, axes = plt.subplots(nrows, ncols_total, figsize=SELECTED_FIG_FIGSIZE, squeeze=False)
    try:
        fig.canvas.manager.set_window_title('Selected EC and hippocampal spatial firing maps')
    except Exception:
        pass
    kde_plot_data_all = {}
    shared_ymax = 0.0
    for pop_name in required:
        scores = np.asarray(spatial_scores_all[pop_name]['unweighted_mean'], dtype=float)
        scores = scores[np.isfinite(scores)]
        x_curve, density = build_spatial_score_kde(scores)
        mean_score = float(np.mean(scores)) if scores.size > 0 else np.nan
        kde_plot_data_all[pop_name] = {'x_curve': x_curve, 'density': density, 'mean_score': mean_score}
        if density.size > 0:
            density_max = float(np.max(density))
            if np.isfinite(density_max):
                shared_ymax = max(shared_ymax, density_max)
    if not np.isfinite(shared_ymax) or shared_ymax <= 0:
        shared_ymax = 1.0
    else:
        shared_ymax *= 1.05
    for row, pop_name in enumerate(required):
        examples = selected_examples_all[pop_name]
        if len(examples) != n_place_cols:
            raise ValueError(
                f'{pop_name} has {len(examples)} selected examples; '
                f'Figure 6 requires exactly {n_place_cols}.'
            )
        for col, example in enumerate(examples):
            ax = axes[row, col]
            if example.get('is_blank', False):
                ax.set_facecolor('white')
                ax.set_xlim(0, xlim)
                ax.set_ylim(0, ylim)
                ax.set_xticks([])
                ax.set_yticks([])
                for spine in ax.spines.values():
                    spine.set_visible(False)
                continue
            rate_map = np.asarray(example['rate_map'], dtype=float)
            z_map = zscore_rate_map(rate_map)
            finite_vals = rate_map[np.isfinite(rate_map)]
            peak_rate_hz = float(np.max(finite_vals)) if finite_vals.size > 0 else 0.0
            ax.imshow(
                z_map,
                cmap=PLACE_CMAP,
                origin='lower',
                interpolation=SELECTED_INTERPOLATION,
                extent=[0, xlim, 0, ylim],
                aspect='equal',
                zorder=1,
            )
            overlay_trajectory_on_rate_map(ax)
            ax.set_xlim(0, xlim)
            ax.set_ylim(0, ylim)
            if SHOW_SELECTED_TICKS:
                ax.set_xticks([0, 30, 60])
                ax.set_yticks([0, 30, 60])
                ax.tick_params(axis='both', labelsize=9)
            else:
                ax.set_xticks([])
                ax.set_yticks([])
            for spine in ax.spines.values():
                spine.set_visible(False)
            ax.set_title(f'{peak_rate_hz:.2f} Hz', fontsize=10, pad=4)
        histogram_ax = axes[row, -1]
        plot_unweighted_spatial_score_histogram(
            histogram_ax,
            kde_plot_data_all[pop_name],
            shared_ymax,
            show_xlabel=row == nrows - 1,
        )
    axes[0, 0].set_ylabel('EC Grid', fontsize=14, rotation=90, labelpad=18)
    axes[1, 0].set_ylabel('DG-GC', fontsize=14, rotation=90, labelpad=18)
    axes[2, 0].set_ylabel('CA3-PC', fontsize=14, rotation=90, labelpad=18)
    axes[3, 0].set_ylabel('CA1-PC', fontsize=14, rotation=90, labelpad=18)
    fig.suptitle('EC and Hippocampal Spatial Firing Maps', fontsize=20, fontweight='bold', y=0.98)
    fig.text(0.43, 0.04, 'Position', ha='center', va='center', fontsize=14)
    fig.text(0.04, 0.5, 'Position', ha='center', va='center', rotation='vertical', fontsize=14)
    fig.subplots_adjust(left=0.11, right=0.98, bottom=0.08, top=0.9, wspace=0.12, hspace=0.12)
    if SAVE_SELECTED_FIGURE:
        out_png = os.path.join(
            SELECTED_FIGURE_DIR,
            f'{SELECTED_FIGURE_BASENAME_PREFIX}_4x{N_SELECTED_CELLS}_plus_spatial_score_hist.png',
        )
        out_svg = os.path.join(
            SELECTED_FIGURE_DIR,
            f'{SELECTED_FIGURE_BASENAME_PREFIX}_4x{N_SELECTED_CELLS}_plus_spatial_score_hist.svg',
        )
        fig.savefig(out_png, dpi=SELECTED_FIG_DPI, bbox_inches='tight')
        fig.savefig(out_svg, dpi=SELECTED_FIG_DPI, bbox_inches='tight')
        print(f'[SAVED] {out_png}')
        print(f'[SAVED] {out_svg}')
    return fig


def process_population(pop_name, spike_times_ms, neuron_ids):
    print(f'[INFO] Building fast spike index for {pop_name} ...')
    sorted_times, unique_ids, start_idx, counts, id_to_row = make_spike_index(spike_times_ms, neuron_ids)
    print(f'[INFO] Fast spike index finished for {pop_name}; active cells = {len(unique_ids):,}')
    overview_examples = build_real_overview_examples(
        pop_name,
        sorted_times,
        unique_ids,
        start_idx,
        counts,
        id_to_row,
    )
    selected_examples = build_selected_examples(pop_name, sorted_times, start_idx, counts, id_to_row)
    spatial_scores = calculate_all_population_unweighted_spatial_information(
        pop_name,
        sorted_times,
        unique_ids,
        start_idx,
        counts,
        id_to_row,
    )
    return (overview_examples, selected_examples, spatial_scores)

# Load the existing EC and place-cell recordings, then make all six figures.
selected_examples_all = {}
spatial_scores_all = {}
print('\n' + '=' * 80)
print('Running EC_GRID')
print('=' * 80)
print(f'[INFO] Using EC grid-cell spike file: {MEC_SPIKE_FILE}')
ec_spike_times_ms, ec_neuron_ids = read_spike_dat(MEC_SPIKE_FILE)
ec_overview_examples, selected_examples_all['EC_GRID'], spatial_scores_all['EC_GRID'] = process_population(
    'EC_GRID',
    ec_spike_times_ms,
    ec_neuron_ids,
)
plot_examples_grid(
    title=f'Figure 1: EC grid-cell spatial firing maps (n = {len(ec_overview_examples)})',
    examples=ec_overview_examples,
)
del ec_spike_times_ms
del ec_neuron_ids
for figure_number, pop_name in enumerate(PLACE_CELL_POPULATIONS, start=2):
    print('\n' + '=' * 80)
    print(f'Running {pop_name}')
    print('=' * 80)
    spike_file = SPIKE_FILES[pop_name]
    print(f'[INFO] Using {pop_name} spike file: {spike_file}')
    spike_times_ms, neuron_ids = read_spike_dat(spike_file)
    overview_examples, selected_examples_all[pop_name], spatial_scores_all[pop_name] = process_population(
        pop_name,
        spike_times_ms,
        neuron_ids,
    )
    plot_examples_grid(
        title=f'Figure {figure_number}: {pop_name} spatial firing maps (n = {len(overview_examples)})',
        examples=overview_examples,
        show_peak_rate=True,
    )
    del spike_times_ms
    del neuron_ids
random_examples = build_random_examples()
plot_examples_grid(title=f'Figure 5: Random Poisson spike trains, {RANDOM_RATE_HZ} Hz '
        f'({
            ANALYSIS_START_S:.0f
        }–{ANALYSIS_END_S:.0f} s, n = {len(random_examples)})', examples=random_examples)
plot_selected_grid(selected_examples_all, spatial_scores_all)
print('\nDone.')
print('Generated six figures:')
print('  1. EC grid-cell overview')
print('  2. DGGC overview')
print('  3. CA3PC overview')
print('  4. CA1PC overview')
print('  5. Random Poisson control overview')
print(f'  6. Selected 4 x {N_SELECTED_CELLS} maps + right-column spatial-score histograms')
plt.show()
