# Hippocampus execution and figures: regional data folders

All three MATLAB demos now read a separate spike folder and anatomical
location folder for their region. The CA3 and CA1 demos have also been
shortened using the same population-loop structure as the DG demo.

This ZIP includes the C++ execution code, MATLAB/Python plotting code, the
Python model modules, and both grid-parameter pickles. Recordings and the
connectivity HDF5 file are not included. Supply the complete files for each
region before clicking Run.

## Folder layout and MATLAB demos

| Region | Spike folder | Location folder | Script to open and Run |
|---|---|---|---|
| DG | `results/DG/` | `locations/DG/` | `plot/demoOAT_DG.m` |
| CA3 | `results/CA3/` | `locations/CA3/` | `plot/demoOAT_CA3.m` |
| CA1 | `results/CA1/` | `locations/CA1/` | `plot/demoOAT_CA1.m` |

Use **results** and **locations**, both plural. Region folder names are
uppercase. All three scripts select every population by default: nine in DG,
eight in CA3, and eight in CA1. Their input paths are relative to the script's
location, so MATLAB's current folder does not matter. For example, DG uses:

```matlab
spike_dir = fullfile(project_dir, 'results', 'DG');
location_dir = fullfile(project_dir, 'locations', 'DG');
```

Keep all scripts and seven supplied MATLAB helpers in the same `plot/`
folder. No new helper layers or sanity checks were added. The helpers retain
their original calculations and existing checks. MATLAB must provide
`pwelch` and `prctile`; the spectrum helper uses Signal Processing Toolbox.

Each demo produces Figure 7 (raster) and Figure 8 (firing-rate histograms,
pairwise correlations, and power spectra). Running another demo closes the
previous figures, as in the original scripts. Save figures before switching
regions if needed; each script has optional save lines at its end.

## Move existing files into the regional folders

First copy this package's `plot/` into your existing execution project. If you
also want future C++ runs to write directly into the new folders, copy the six
updated `include/dg`, `include/ca3`, and `include/ca1` files named
`LoadConnectivity.h` and `SetupNetwork.h` into that project and rebuild.
The corresponding complete source is included in this ZIP.

Run the following from the **project root** containing `plot/`, `results/`,
and `locations/`. It moves your existing flat hippocampal `.dat` files into
regional folders, including filenames with `_1200sec` suffixes. Existing
files at the destination are kept; any conflicting source files remain in
the old folder. EC/MEC/LEC files stay in the root data folders.

```bash
bash <<'BASH'
set -e
shopt -s nullglob
mkdir -p results/{DG,CA3,CA1} locations/{DG,CA3,CA1}
for region in DG CA3 CA1; do
    for file in results/spk_${region}_*.dat; do
        mv -n -- "$file" "results/$region/"
    done
    for file in locations/locs_${region}*.dat; do
        mv -n -- "$file" "locations/$region/"
    done
done
BASH
```

This command organizes existing files; it does not generate missing data.
If you only have the earlier GC sample, only the GC pair will be available.
The full DG demo still requires its other eight spike/location pairs. The
commented GC-only selection remains available in `demoOAT_DG.m` for that sample.

## Exact files required by each MATLAB demo

Each row needs both files. Keep capitalization, including `BisC` and `TML`.
These are standard C++ output names, without the Python `_1200sec` suffixes.

### DG

| Type | In `results/DG/` | In `locations/DG/` |
|---|---|---|
| GC | `spk_DG_GC.dat` | `locs_DGGC.dat` |
| MC | `spk_DG_MC.dat` | `locs_DGMC.dat` |
| AAC | `spk_DG_AAC.dat` | `locs_DGAAC.dat` |
| BC | `spk_DG_BC.dat` | `locs_DGBC.dat` |
| BCCCK | `spk_DG_BCCCK.dat` | `locs_DGBCCCK.dat` |
| HICAP | `spk_DG_HICAP.dat` | `locs_DGHICAP.dat` |
| HIPP | `spk_DG_HIPP.dat` | `locs_DGHIPP.dat` |
| MOPP | `spk_DG_MOPP.dat` | `locs_DGMOPP.dat` |
| TML | `spk_DG_TML.dat` | `locs_DGTML.dat` |

### CA3

| Type | In `results/CA3/` | In `locations/CA3/` |
|---|---|---|
| PC | `spk_CA3_PC.dat` | `locs_CA3PC.dat` |
| AAC | `spk_CA3_AAC.dat` | `locs_CA3AAC.dat` |
| BC | `spk_CA3_BC.dat` | `locs_CA3BC.dat` |
| BCCCK | `spk_CA3_BCCCK.dat` | `locs_CA3BCCCK.dat` |
| BisC | `spk_CA3_BisC.dat` | `locs_CA3BisC.dat` |
| OLM | `spk_CA3_OLM.dat` | `locs_CA3OLM.dat` |
| TL | `spk_CA3_TL.dat` | `locs_CA3TL.dat` |
| MFA | `spk_CA3_MFA.dat` | `locs_CA3MFA.dat` |

### CA1

| Type | In `results/CA1/` | In `locations/CA1/` |
|---|---|---|
| PC | `spk_CA1_PC.dat` | `locs_CA1PC.dat` |
| AAC | `spk_CA1_AAC.dat` | `locs_CA1AAC.dat` |
| BC | `spk_CA1_BC.dat` | `locs_CA1BC.dat` |
| BCCCK | `spk_CA1_BCCCK.dat` | `locs_CA1BCCCK.dat` |
| BisC | `spk_CA1_BisC.dat` | `locs_CA1BisC.dat` |
| OLM | `spk_CA1_OLM.dat` | `locs_CA1OLM.dat` |
| TL | `spk_CA1_TL.dat` | `locs_CA1TL.dat` |
| NG | `spk_CA1_NG.dat` | `locs_CA1NG.dat` |

All data for a region should come from the same simulation configuration.
The location IDs must correspond to that region's spike IDs. MATLAB plotting
of existing recordings does not require either pickle or an HDF5 file.

## Analysis preserved

All three scripts retain the original 10–13 second raster/correlation window
and 10–20 second firing-rate/spectrum window, 5 ms bins, and 200 PSD slices.
Only DG GC correlation is downsampled by 20. CA3 and CA1 correlation use all
neurons. The original population order, raster transparency, marker sizes,
and four-row raster space for GC or PC are retained. Unused ISI calculations,
settings, and historical comments were removed. A 40-second simulation covers
these MATLAB analysis windows.

## C++: regional output and replay paths

The six updated headers change file paths only:

- `include/dg/LoadConnectivity.h` and `include/dg/SetupNetwork.h`
- `include/ca3/LoadConnectivity.h` and `include/ca3/SetupNetwork.h`
- `include/ca1/LoadConnectivity.h` and `include/ca1/SetupNetwork.h`

New hippocampal spike files go directly to `results/DG`, `results/CA3`, or
`results/CA1`, and anatomical location files go to the corresponding
`locations` subfolder. CA3 reads `results/DG/spk_DG_GC.dat`; CA1 reads
`results/CA3/spk_CA3_PC.dat`. Replay-input monitors remain disabled, preserving
those input recordings. The regional folders must exist before execution;
they are included as empty folders and are created by the commands below.

Shared EC/MEC/LEC input and monitor files remain directly in `results/`, and
EC anatomical locations remain directly in `locations/`. The existing CA1
neuron monitor also retains its default output location in `results/`.

Build with the same CARLsim installation with existing `setUserConnectivity`
support, HighFive, HDF5, Boost, and OpenMP used by your original model. From
this project root, the earlier local installation example is:

```bash
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release \
  -DCARLSIM_ROOT="$HOME/CARLsim/userconn/carlsim" \
  -DCARLSIM_SOURCE_DIR="$HOME/CARLsim/userconn/CARLsim6"
cmake --build build -j 2
mkdir -p results/{DG,CA3,CA1} locations/{DG,CA3,CA1}
./build/hippomodel_run_DG && \
./build/hippomodel_run_CA3 && \
./build/hippomodel_run_CA1
```

Adjust the two CARLsim installation paths to your machine. If your existing
project is already configured, use its build command after replacing the six
headers. Run the executables from the project root. They replace existing
recordings with the same names.

The original required inputs remain:

| Folder | Filename |
|---|---|
| `connectivity/` | `CA1EC_scale2_DGMC_scale5_data_divergence_scale10.h5` |
| `results/` | `MEC_66000cells_1200.0sec(mean=2.1Hz,ymax=2.4,60x60cm,non-uniform grid field,d*10,min=0.1Hz)_SimData_MCscale5.dat` |
| `results/` | `MEC_128000cells_1200.0sec(mean=2.1Hz,ymax=2.4,60x60cm,non-uniform grid field,d*10,min=0.1Hz)_SimData_MCscale5.dat` |

The execution loops still run four 10-second blocks, totaling 40 seconds.
For 1200 seconds of place-cell data, change `4` to `120` in all three
`src/run_*.cpp` files and rebuild. Keep `sim.runNetwork(10, 0)`. MEC recordings
and all upstream simulation stages must cover that duration. Model parameters,
connectivity rules, fixed weights, and optimization code were not changed.

## Python and pickle file locations

Keep these together in `plot/`:

- `demo_grid_place_cells.py`
- `RatMovement.py` and `GridCell.py`
- `gridMapCoefficients.pickle` and `gridCellTopography.pickle`

The two pickles contain grid-model parameters, not neuron locations. They
require `pickle.load(f, encoding='latin1')` under Python 3. EC neuron locations
come from HDF5; the old location-pickle lines will remain commented when the
main grid generator is integrated. The current main generation script is
still needed for that integration; the supplied Python demo loads existing
grid/place spikes. No generation model or parameters were invented here.

The Python plotting paths now follow the regional folders too:

| Population | Folder | Filename |
|---|---|---|
| MEC | `results/` | The 66000-cell MEC file in the input table above |
| DG GC | `results/DG/` | `spk_DG_GC_1200sec.dat` |
| CA3 PC | `results/CA3/` | `spk_CA3_PC_1200sec.dat` |
| CA1 PC | `results/CA1/` | `spk_CA1_PC_type3_1200sec.dat` |

After a matching **1200-second** C++ run, you can copy its standard output names
to the Python filenames and run the Python script from the project root:

```bash
cp results/DG/spk_DG_GC.dat results/DG/spk_DG_GC_1200sec.dat
cp results/CA3/spk_CA3_PC.dat results/CA3/spk_CA3_PC_1200sec.dat
cp results/CA1/spk_CA1_PC.dat results/CA1/spk_CA1_PC_type3_1200sec.dat
python3 plot/demo_grid_place_cells.py
```

These copy commands replace existing destination files. Alternatively, edit
the three filename settings near the top of the Python script. The earlier
40-second sample cannot reproduce the 1200-second place-cell analysis merely
by renaming it. Use matching MEC spikes, hippocampal spikes, and trajectory.
Python plotting uses NumPy, SciPy, and Matplotlib. The selected-cell figure is
saved in `figures/place_field_analysis/` as PNG and SVG.

## Verification

All 25 regional spike/location pairs were checked against the C++ outputs.
The MATLAB settings, helper arguments, layouts, and original checks were
reviewed against the supplied scripts. C++ differences are confined to the
six path-bearing headers; the mains, model parameters, and fixed weights are
byte-identical to the earlier execution package. All three C++ mains passed
syntax checks with temporary dependency stubs; this is not an actual CARLsim
build. The migration command passed tests for all regions, 1200-second
filename suffixes, EC preservation, and existing-destination preservation.
Python syntax checks passed, and its numerical code is unchanged.

MATLAB, CARLsim linking, and GPU execution are unavailable in this environment,
so full-model runs and MATLAB rendering are not claimed. The supplied pickle
files and Python model modules passed the earlier small execution check.
