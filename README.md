# Hippomodel CARLsim Refactor

This project is a refactored CARLsim6 package-style workflow for running and optimizing large-scale hippocampal spiking neural network models. CARLsim is the simulator. This project organizes CARLsim model setup, HDF5 connectivity loading, spike input configuration, execution, and Nelder-Mead optimization for DG, CA3, and CA1.

The code is designed so a new user can change common experiment settings from `config/hippomodel.toml`, while region-specific CARLsim model setup remains in explicit C++ files using the original CARLsim API style:

```cpp
sim.setConductances(...);
sim.setNeuronParameters(...);
connectionIDs["..."] = sim.connect(...);
```

## Current status

| Region | Run workflow | Optimization workflow | Connectivity loader | Model setup | Connection setup | Evaluator |
|---|---:|---:|---:|---:|---:|---:|
| DG | Yes | Yes | Yes | Yes | Yes | Yes |
| CA3 | Yes | Yes | Yes | Yes | Yes | Yes |
| CA1 | Yes | Yes | Yes | Yes | Yes | Yes |

## Project structure

```text
largescalemodel_scale10/
├── CMakeLists.txt
├── README.md
├── config/
│   └── hippomodel.toml                 # runtime settings: inputs, targets, optimizer settings
├── include/hippomodel/
│   ├── analysis/                       # firing-rate, correlation, PSD declarations
│   ├── config/                         # RuntimeConfig and config parser declarations
│   ├── core/                           # Region enum
│   ├── io/                             # HDF5 connectivity loader declarations
│   ├── loss/                           # DG/CA3/CA1 evaluator declarations
│   ├── network/                        # CARLsim network builders and user connection generators
│   ├── optimizer/                      # Nelder-Mead, ProgressiveEI, logger, simplex generator
│   ├── region/                         # DG/CA3/CA1 region-specific setup declarations
│   ├── user/                           # selected region variable
│   └── workflow/                       # run/optimize workflow declarations
├── src/
│   ├── analysis/                       # firing-rate, correlation, PSD implementations
│   ├── config/                         # TOML-like config parser and validation
│   ├── io/                             # DG/CA3/CA1 HDF5 connectivity loading
│   ├── loss/                           # DG/CA3/CA1 objective functions
│   ├── network/                        # group creation, inputs, setupNetwork, monitors
│   ├── optimizer/                      # logging support
│   ├── region/                         # explicit CARLsim model/connection setup and bounds
│   └── workflow/                       # top-level run and optimization control flow
├── tools/
│   ├── main_run.cpp                    # builds ./build/hippomodel_run
│   └── main_optimize.cpp               # builds ./build/hippomodel_optimize
└── legacy/original/                    # original uploaded code, reference only
```

Do not modify `legacy/original/` for normal work. It is not used by CMake and is not required to run the project.

## Build and run

### 1. Go to the project folder

```bash
>>> cd ~/CARLsim/projects/largescalemodel_scale10
```

### 2. Configure and build

Use this after creating the project, after replacing this refactor package, or after changing `CMakeLists.txt`:

```bash
>>> sudo cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/home/song/CARLsim/userconn/carlsim -S . -B build && sudo cmake --build build -j
```

The `-j` option builds in parallel and is faster. This also works if you prefer a serial build:

```bash
>>> sudo cmake --build build
```

### 3. Rebuild after normal code edits

After editing `.cpp` or `.h` files, usually only run:

```bash
>>> sudo cmake --build build -j
```

### 4. Run the selected region once

```bash
>>> LD_LIBRARY_PATH=/home/song/CARLsim/userconn/carlsim/lib ./build/hippomodel_run --config config/hippomodel.toml
```

### 5. Run Nelder-Mead optimization

```bash
>>> LD_LIBRARY_PATH=/home/song/CARLsim/userconn/carlsim/lib ./build/hippomodel_optimize --config config/hippomodel.toml
```

## Select DG, CA3, or CA1

Edit one file:

```text
include/hippomodel/user/ProjectSelection.h
```

For DG:

```cpp
inline constexpr hippomodel::Region kSelectedRegion = hippomodel::Region::DG;
```

For CA3:

```cpp
inline constexpr hippomodel::Region kSelectedRegion = hippomodel::Region::CA3;
```

For CA1:

```cpp
inline constexpr hippomodel::Region kSelectedRegion = hippomodel::Region::CA1;
```

Then rebuild:

```bash
>>> sudo cmake --build build -j
```

The run and optimization commands stay the same.

## What to edit for common changes

### Change input spike files

Edit:

```text
config/hippomodel.toml
```

The HDF5 connectivity file is shared by DG, CA3, and CA1:

```toml
[paths]
connectivity_h5 = "connectivity/CA1EC_scale2_DGMC_scale5_data_divergence_scale10.h5"
```

Spike inputs are region-specific.

DG uses:

```toml
[inputs.DG.EC_LEC]
mode = "file"
file = "results/spk_EC_LEC.dat"

[inputs.DG.EC_MEC]
mode = "file"
file = "results/MEC_66000cells_1200.0sec(mean=2.1Hz,ymax=2.4,60x60cm,non-uniform grid field,d_10,min=0.1Hz)_SimData_MCscale5.dat"
```

CA3 uses:

```toml
[inputs.CA3.EC_LEC]
mode = "file"
file = "results/spk_EC_LEC.dat"

[inputs.CA3.EC_MEC]
mode = "file"
file = "results/spk_EC_MEC.dat"

[inputs.CA3.DG_GC]
mode = "file"
file = "results/spk_DG_GC.dat"
```

CA1 uses:

```toml
[inputs.CA1.EC_LEC3]
mode = "file"
file = "results/spk_EC_LEC3.dat"

[inputs.CA1.EC_MEC3]
mode = "file"
file = "results/spk_EC_MEC3.dat"

[inputs.CA1.CA3_PC]
mode = "file"
file = "results/spk_CA3_PC.dat"
# file = "results/spk_CA3_PC_correct_0.9Hz.dat"
```

### Use Poisson input instead of spike file input

For any input group, change:

```toml
mode = "file"
file = "results/some_input.dat"
```

to:

```toml
mode = "poisson"
rate_hz = 2.1
```

Example: CA3 with Poisson DG input, while LEC and MEC remain file-based:

```toml
[inputs.CA3.DG_GC]
mode = "poisson"
rate_hz = 0.66

[inputs.CA3.EC_LEC]
mode = "file"
file = "results/spk_EC_LEC.dat"

[inputs.CA3.EC_MEC]
mode = "file"
file = "results/spk_EC_MEC.dat"
```

The input handling code is here:

```text
src/network/DGNetworkBuilder.cpp
src/network/CA3NetworkBuilder.cpp
src/network/CA1NetworkBuilder.cpp
```

File input uses `SpikeGeneratorFromFile` and `sim.setSpikeGenerator(...)`. Poisson input uses `PoissonRate` and `sim.setSpikeRate(...)` after `sim.setupNetwork()`.

### Change Izhikevich neuron parameters

Edit the region-specific model setup file:

```text
src/region/DG/DGModelSetup.cpp
src/region/CA3/CA3ModelSetup.cpp
src/region/CA1/CA1ModelSetup.cpp
```

Look for:

```cpp
sim.setNeuronParameters(...);
```

That is where Izhikevich parameters are set. After changing these files, rebuild:

```bash
>>> sudo cmake --build build -j
```

### Change synapse conductance parameters

Edit the same model setup file:

```text
src/region/DG/DGModelSetup.cpp
src/region/CA3/CA3ModelSetup.cpp
src/region/CA1/CA1ModelSetup.cpp
```

Look for:

```cpp
sim.setConductances(...);
```

This is where conductance decay/rise parameters are set. After changing conductances, rebuild.

### Add, delete, or modify connections

Edit the region-specific connection setup file:

```text
src/region/DG/DGConnectionSetup.cpp
src/region/CA3/CA3ConnectionSetup.cpp
src/region/CA1/CA1ConnectionSetup.cpp
```

Look for connection lines such as:

```cpp
connectionIDs["LEC3_CA1PC"] = sim.connect(EC_LEC3, CA1_PC, myConn, 1.0, 0.268, SYN_FIXED);
```

The fifth argument is the fast/slow gain or maximum weight argument used by CARLsim for that connection. Keep the `connectionIDs["..."]` key identical to the connection name used in the region spec.

If you add or delete a connection, also update the matching region spec:

```text
src/region/DG/DGRegionSpec.cpp
src/region/CA3/CA3RegionSpec.cpp
src/region/CA1/CA1RegionSpec.cpp
```

The region spec controls:

```text
connection name
pre group
post group
baseline synaptic weight
connection order for optimization
EI registration index order
velocity rules
firing-rate defaults
```

### Change baseline synaptic weights

Edit:

```text
src/region/DG/DGRegionSpec.cpp
src/region/CA3/CA3RegionSpec.cpp
src/region/CA1/CA1RegionSpec.cpp
```

Look for `spec.connections`. Each entry has this format:

```cpp
{"connection_name", "pre_group", "post_group", connection_probability, max_weight, baseline_weight}
```

The optimizer searches scaling factors. The absolute weight used in CARLsim is:

```text
absolute weight = baseline_weight × scaling_factor
```

### Change delay velocity rules

Edit the region spec:

```text
src/region/DG/DGRegionSpec.cpp
src/region/CA3/CA3RegionSpec.cpp
src/region/CA1/CA1RegionSpec.cpp
```

Look for:

```cpp
spec.default_velocity = 0.13;
spec.velocity_by_pre_group = { ... };
```

The delay calculation is implemented in:

```text
src/network/DGConnectionGenerator.cpp
src/network/CA3ConnectionGenerator.cpp
src/network/CA1ConnectionGenerator.cpp
```

### Change firing-rate targets or bounds

Edit:

```text
config/hippomodel.toml
```

Firing-rate targets are here:

```toml
[loss.firing_rate.targets]
DG_GC = 0.66
CA3_PC = 0.9
CA1_PC = 2.6
```

Firing-rate bounds are here:

```toml
[loss.firing_rate.bounds.CA1_PC]
lower = 2.5
upper = 3.59
```

These values are used by the DG, CA3, and CA1 evaluators:

```text
src/loss/DGEvaluator.cpp
src/loss/CA3Evaluator.cpp
src/loss/CA1Evaluator.cpp
```

### Change correlation target and setup

Edit:

```text
config/hippomodel.toml
```

Look for:

```toml
[loss.correlation]
target_mean_abs_corr = 0.2
n_slices = 500
bin_ms = 5
n_shuffle = 3
dv_ymin_mm = 0.0
dv_ymax_mm = 10.0
```

The correlation is computed on the principal-cell population of the selected region:

```text
DG  -> DG_GC
CA3 -> CA3_PC
CA1 -> CA1_PC
```

The implementation is in:

```text
src/analysis/Correlation.cpp
```

The evaluators call it from:

```text
src/loss/DGEvaluator.cpp
src/loss/CA3Evaluator.cpp
src/loss/CA1Evaluator.cpp
```

### Change PSD / oscillation setup

Edit:

```text
config/hippomodel.toml
```

Look for:

```toml
[loss.oscillation]
bin_ms = 5
ref_f1_hz = 1.0
ref_f2_hz = 60.0
theta_f1_hz = 4.0
theta_f2_hz = 9.0
beta_f1_hz = 10.0
beta_f2_hz = 20.0
gamma_f1_hz = 21.0
gamma_f2_hz = 55.0
low_f1_hz = 0.0
low_f2_hz = 2.0
target_theta = 0.3
target_beta = 0.3
target_gamma = 0.3
target_two_hz = 0.3
```

PSD is computed from the global population spike-count time series of the principal-cell group:

```text
DG  -> DG_GC
CA3 -> CA3_PC
CA1 -> CA1_PC
```

The PSD implementation is in:

```text
src/analysis/PSD.cpp
```

The current total oscillation loss uses:

```text
beta error + gamma error
```

inside:

```text
src/loss/DGEvaluator.cpp
src/loss/CA3Evaluator.cpp
src/loss/CA1Evaluator.cpp
```

### Change optimization lower/upper bounds

Edit:

```text
src/region/DG/DGOptimizationBounds.cpp
src/region/CA3/CA3OptimizationBounds.cpp
src/region/CA1/CA1OptimizationBounds.cpp
```

These files preserve the region-specific per-connection bound logic from the original NMOpt code. Not every connection uses the same lower/upper scale rule.

Global default scale parameters are in:

```toml
[optimizer]
lower_scale = 0.009
upper_scale = 15.0
```

but some connections override these values inside the region-specific bounds file.

### Change Nelder-Mead settings

Edit:

```text
config/hippomodel.toml
```

Look for:

```toml
[optimizer]
nm_mode = "GD_full"
max_iterations = 400
tolerance_percent = 1.0
lower_scale = 0.009
upper_scale = 15.0
```

The Nelder-Mead algorithm header is:

```text
include/hippomodel/optimizer/NelderMeadLegacyGD.h
```

The ProgressiveEI logic is:

```text
include/hippomodel/optimizer/ProgressiveEI.h
```

The initial simplex generation wrapper is:

```text
include/hippomodel/optimizer/SimplexGenerator.h
```

### Change output directory

Edit:

```text
config/hippomodel.toml
```

Use region-specific output directories:

```toml
[paths.DG]
output_dir = "results/refactor_DG_scale10"

[paths.CA3]
output_dir = "results/refactor_CA3_scale10"

[paths.CA1]
output_dir = "results/refactor_CA1_scale10"
```

The optimizer saves:

```text
effective_config.toml
loss_trajectory.csv
initialSimplex<REGION>_Gradient_Shift.csv
nelder_mead_output(<REGION>,scale10).txt
<REGION>_FR_and_Error(scale10).txt
<REGION>_Corr_and_Error(scale10).txt
<REGION>_betaR_and_Error(scale10).txt
<REGION>_gammaR_and_Error(scale10).txt
```

## Important files by region

### DG

```text
src/region/DG/DGModelSetup.cpp
src/region/DG/DGConnectionSetup.cpp
src/region/DG/DGRegionSpec.cpp
src/region/DG/DGOptimizationBounds.cpp
src/io/DGConnectivityLoader.cpp
src/network/DGNetworkBuilder.cpp
src/network/DGConnectionGenerator.cpp
src/loss/DGEvaluator.cpp
```

### CA3

```text
src/region/CA3/CA3ModelSetup.cpp
src/region/CA3/CA3ConnectionSetup.cpp
src/region/CA3/CA3RegionSpec.cpp
src/region/CA3/CA3OptimizationBounds.cpp
src/io/CA3ConnectivityLoader.cpp
src/network/CA3NetworkBuilder.cpp
src/network/CA3ConnectionGenerator.cpp
src/loss/CA3Evaluator.cpp
```

### CA1

```text
src/region/CA1/CA1ModelSetup.cpp
src/region/CA1/CA1ConnectionSetup.cpp
src/region/CA1/CA1RegionSpec.cpp
src/region/CA1/CA1OptimizationBounds.cpp
src/io/CA1ConnectivityLoader.cpp
src/network/CA1NetworkBuilder.cpp
src/network/CA1ConnectionGenerator.cpp
src/loss/CA1Evaluator.cpp
```

## Typical workflow

### Run DG

```bash
>>> cd ~/CARLsim/projects/largescalemodel_scale10
```

Edit:

```text
include/hippomodel/user/ProjectSelection.h
```

Set:

```cpp
inline constexpr hippomodel::Region kSelectedRegion = hippomodel::Region::DG;
```

Build:

```bash
>>> sudo cmake --build build -j
```

Run:

```bash
>>> LD_LIBRARY_PATH=/home/song/CARLsim/userconn/carlsim/lib ./build/hippomodel_run --config config/hippomodel.toml
```

### Optimize CA3

Edit:

```text
include/hippomodel/user/ProjectSelection.h
```

Set:

```cpp
inline constexpr hippomodel::Region kSelectedRegion = hippomodel::Region::CA3;
```

Build:

```bash
>>> sudo cmake --build build -j
```

Optimize:

```bash
>>> LD_LIBRARY_PATH=/home/song/CARLsim/userconn/carlsim/lib ./build/hippomodel_optimize --config config/hippomodel.toml
```

### Optimize CA1

Edit:

```text
include/hippomodel/user/ProjectSelection.h
```

Set:

```cpp
inline constexpr hippomodel::Region kSelectedRegion = hippomodel::Region::CA1;
```

Build:

```bash
>>> sudo cmake --build build -j
```

Optimize:

```bash
>>> LD_LIBRARY_PATH=/home/song/CARLsim/userconn/carlsim/lib ./build/hippomodel_optimize --config config/hippomodel.toml
```
