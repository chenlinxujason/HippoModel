# HippoModel

HippoModel is a CARLsim6-based C++ package for running and optimizing large-scale hippocampal spiking neural network models. It currently supports DG, CA3, and CA1 workflows with shared execution, connectivity loading, loss calculation, and Nelder-Mead optimization infrastructure.

This repository is organized so another developer can quickly find where to change neuron parameters, synapse parameters, inputs, connections, optimization targets, and loss settings.

## 1. Select the region

Edit one file:

```cpp
include/hippomodel/user/ProjectSelection.h
```

Example:

```cpp
inline constexpr hippomodel::Region kSelectedRegion = hippomodel::Region::DG;
```

Allowed values:

```cpp
hippomodel::Region::DG
hippomodel::Region::CA3
hippomodel::Region::CA1
```

After changing the selected region, rebuild the code.

## 2. Build

Go to the project folder:

```bash
cd ~/CARLsim/projects/largescalemodel_scale10
```

Configure and build:

```bash
sudo cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/home/song/CARLsim/userconn/carlsim -S . -B build && sudo cmake --build build -j
```

After normal code edits, only rebuild:

```bash
sudo cmake --build build -j
```

## 3. Run one simulation

```bash
LD_LIBRARY_PATH=/home/song/CARLsim/userconn/carlsim/lib ./build/hippomodel_run --config config/hippomodel.toml
```

## 4. Run optimization

```bash
LD_LIBRARY_PATH=/home/song/CARLsim/userconn/carlsim/lib ./build/hippomodel_optimize --config config/hippomodel.toml
```

The scaling factor order written to `nelder_mead.txt` follows:

```cpp
spec.optimized_connection_order[0]
spec.optimized_connection_order[1]
spec.optimized_connection_order[2]
...
```

Check these files for the exact order:

```text
src/region/DG/DGRegionSpec.cpp
src/region/CA3/CA3RegionSpec.cpp
src/region/CA1/CA1RegionSpec.cpp
```

DG, CA3, and CA1 now all use target/convergence-style connection-order blocks.

## 5. Code structure

```text
include/hippomodel/        Public headers
src/                       C++ implementation
tools/                     Main executable entry points
config/hippomodel.toml     Runtime configuration
```

Important source folders:

```text
src/region/DG/             DG-specific model setup
src/region/CA3/            CA3-specific model setup
src/region/CA1/            CA1-specific model setup
src/io/                    HDF5 connectivity loading
src/network/               CARLsim network building and connection generators
src/loss/                  Optimization objective functions
src/analysis/              Firing-rate, correlation, and PSD calculations
src/optimizer/             Nelder-Mead and logging utilities
src/workflow/              Run/optimization workflow orchestration
```

## 6. Where to modify common things

### Change Izhikevich neuron parameters

Edit:

```text
src/region/DG/DGModelSetup.cpp
src/region/CA3/CA3ModelSetup.cpp
src/region/CA1/CA1ModelSetup.cpp
```

Look for explicit CARLsim calls:

```cpp
sim.setNeuronParameters(...);
```

This is where to change Izhikevich parameters.

### Change synaptic conductance time constants

Edit the same files:

```text
src/region/DG/DGModelSetup.cpp
src/region/CA3/CA3ModelSetup.cpp
src/region/CA1/CA1ModelSetup.cpp
```

Look for:

```cpp
sim.setConductances(...);
```

This is where to modify AMPA/NMDA/GABA conductance rise/decay parameters.

### Add/delete connections or modify max weight/gain

Edit:

```text
src/region/DG/DGConnectionSetup.cpp
src/region/CA3/CA3ConnectionSetup.cpp
src/region/CA1/CA1ConnectionSetup.cpp
```

Connections are written in explicit CARLsim style:

```cpp
connectionIDs["LEC3_CA1PC"] = sim.connect(EC_LEC3, CA1_PC, myConn, 1.0, 0.268, SYN_FIXED);
```

The last numeric value before `SYN_FIXED` is the CARLsim max weight / gain argument used by `sim.connect(...)`.

### Change baseline synaptic weights

Edit:

```text
src/region/DG/DGBaselineWeights.cpp
src/region/CA3/CA3BaselineWeights.cpp
src/region/CA1/CA1BaselineWeights.cpp
```

Look for:

```cpp
std::map<std::string, float> makeCA1BaselineWeights() {
    return {
        {"LEC3_CA1PC", 0.9f},
        {"CA3PC_CA1PC", 0.255f},
    };
}
```

These baseline weights are multiplied by optimization scaling factors.

### Change group creation

Edit:

```text
src/region/DG/DGGroupSetup.cpp
src/region/CA3/CA3GroupSetup.cpp
src/region/CA1/CA1GroupSetup.cpp
```

These files use explicit CARLsim group creation:

```cpp
int CA3_PC = sim.createGroup("CA3_PC", num_CA3_PC, EXCITATORY_NEURON);
int CA1_BC = sim.createGroup("CA1_BC", num_CA1_BC, INHIBITORY_NEURON);
```

Spike-generator groups use:

```cpp
sim.createSpikeGeneratorGroup(...);
```

### Change HDF5 group/dataset names

Edit:

```text
src/region/DG/DGRegionSpec.cpp
src/region/CA3/CA3RegionSpec.cpp
src/region/CA1/CA1RegionSpec.cpp
```

Only HDF5 mapping and optimization order live here. Example:

```cpp
spec.h5_groups = {
    {"CA1_PC", "IDranges/CA1/PC", "CA1-PC"},
};
```

The loader uses this information to read:

```text
IDranges/...
Locs/HC
Div/<pre>/<post>/<global_pre_id>
```

### Change input files or switch to Poisson input

Edit:

```text
config/hippomodel.toml
```

File input example:

```toml
[inputs.CA1.EC_MEC3]
mode = "file"
file = "results/spk_EC_MEC3.dat"
```

Poisson input example:

```toml
[inputs.CA1.EC_MEC3]
mode = "poisson"
rate_hz = 2.1
```

You can mix input types. For example, CA3 can use Poisson `DG_GC` while `EC_LEC` and `EC_MEC` remain file-based.

### Change firing-rate targets and bounds

Edit:

```text
config/hippomodel.toml
```

Examples:

```toml
[loss.DG.firing_rate]
targetDGGCFR = 0.66
lowerDGGCFR = 0.55
upperDGGCFR = 0.92

[loss.CA3.firing_rate]
targetCA3PCFR = 0.9
lowerCA3PCFR = 0.67
upperCA3PCFR = 1.24

[loss.CA1.firing_rate]
targetCA1PCFR = 2.6
lowerCA1PCFR = 2.5
upperCA1PCFR = 3.59
```

### Change correlation target and number of dorsal-ventral slices

Edit:

```text
config/hippomodel.toml
```

Examples:

```toml
[loss.DG.correlation]
targetDGGCMeanAbsCorr = 0.2
numDGGCSlices = 500
DGGCcorrBinMs = 5

[loss.CA3.correlation]
targetCA3PCMeanAbsCorr = 0.2
numCA3PCSlices = 100
CA3PCcorrBinMs = 5

[loss.CA1.correlation]
targetCA1PCMeanAbsCorr = 0.2
numCA1PCSlices = 190
CA1PCcorrBinMs = 5
```

Typical slice choices:

```text
1/500 DG:     numDGGCSlices = 20
1/10 DG:      numDGGCSlices = 500
1/10 CA3_PC:  numCA3PCSlices = 100
1/10 CA1_PC:  numCA1PCSlices = 190
```

### Change PSD / oscillation settings

Edit:

```text
config/hippomodel.toml
```

Examples:

```toml
[loss.DG.oscillation]
DGGCpsdBinMs = 5
DGGCpsdReferenceBandHz = [1.0, 60.0]
DGGCthetaBandHz = [4.0, 9.0]
targetDGGCThetaPowerRatio = 0.3

[loss.CA3.oscillation]
CA3PCpsdBinMs = 5
CA3PCpsdReferenceBandHz = [1.0, 60.0]
targetCA3PCBetaPowerRatio = 0.3

[loss.CA1.oscillation]
CA1PCpsdBinMs = 5
CA1PCpsdReferenceBandHz = [1.0, 60.0]
targetCA1PCThetaPowerRatio = 0.3
```

### Change Nelder-Mead settings

Edit:

```text
config/hippomodel.toml
```

```toml
[optimizer]
nm_mode = "GD_full"
max_iterations = 400
tolerance_percent = 1.0
lower_scale = 0.009
upper_scale = 15.0
```

`lower_scale` and `upper_scale` are read by `src/config/RuntimeConfig.cpp`, stored in `OptimizerConfig` in `include/hippomodel/config/RuntimeConfig.h`, and passed into the region-specific bounds builder in `src/workflow/OptimizeWorkflow.cpp`.

In the old monolithic code these appeared as local variables such as:

```cpp
double lowerScale = 0.01f;
double upperScale = 10.0f;
```

In the refactor, change them in `config/hippomodel.toml` unless you want to change the C++ default fallback.


### Developer note: change EI-shifted initial-simplex generation

This is mainly for developers who want to modify the Nelder-Mead initialization behavior, not for normal model-parameter tuning.

Edit:

```text
include/hippomodel/optimizer/SimplexGenerator.h
```

The active EI-shifted initial simplex generator is:

```cpp
hippomodel::opt::generateVerticesGDShift(...)
```

Important developer parameters inside this file include:

```cpp
double p_move = 0.9;      // probability of moving even when firing rate is inside the target band
const double dMed = 0.4;  // medium normalized FR-distance threshold
const double dLarge = 0.95; // large normalized FR-distance threshold
scale = 1.25;             // large outside-band EI shift
scale = 1.15;             // medium outside-band EI shift
scale = 1.1;              // small outside-band EI shift
scale = 1.12;             // inside-band EI shift
const double delta = 0.15; // Gaussian sampling band around shifted mean
```

The EC LEC/MEC pair ratio limit is passed from:

```text
src/workflow/OptimizeWorkflow.cpp
```

Look for:

```cpp
const double EC_PAIR_MAX_RATIO = 1.5;
```

This limits each matched LEC/MEC or LEC3/MEC3 pair to at most 1.5x difference during initial-simplex generation. The matching is name-based using `optimized_connection_order`, so DG, CA3, and CA1 can have different LEC/MEC indices without hard-coding the indices in `SimplexGenerator.h`.

The ratio correction uses a geometric projection, so if both LEC and MEC have accumulated upward or downward changes, their common-mode effect is mostly preserved while their relative ratio is constrained.

### Change special per-connection optimization bounds

Edit:

```text
src/region/DG/DGOptimizationBounds.cpp
src/region/CA3/CA3OptimizationBounds.cpp
src/region/CA1/CA1OptimizationBounds.cpp
```

These files intentionally keep explicit lower/upper-bound variables and explicit bound-packing blocks. This is easier to modify than a compressed loop because each special case is visible.

The lower-bound pattern is usually:

```cpp
double lowerLEC3PC = lowerScale * initGuess[0];
```

The generic upper-bound pattern is usually:

```cpp
double upperCA1BC_PC = upperScale * initGuess[25];
```

Some excitatory-input upper bounds use an experimentally chosen AP threshold divided by the current baseline weight. Those bounds use the baseline-weight map instead of hard-coded denominators:

```cpp
double upperLEC3PC = 22 / wt("LEC3_CA1PC"); // 22/0.832, 24 reach AP, use 22/ as upper bound
```

Baseline weights are defined separately in:

```text
src/region/DG/DGBaselineWeights.cpp
src/region/CA3/CA3BaselineWeights.cpp
src/region/CA1/CA1BaselineWeights.cpp
```

So if the baseline weight changes, the AP-threshold-style upper bound automatically uses the updated baseline weight.

Important: `OptimizationBounds.cpp` packs bounds in the same order as `optimized_connection_order`, even though `BaselineWeights.cpp` is written in divergence/source order for easier visualization.

## 7. Main design rule

The project uses one canonical connection order per region:

```text
src/region/DG/DGRegionSpec.cpp
src/region/CA3/CA3RegionSpec.cpp
src/region/CA1/CA1RegionSpec.cpp
```

That order controls:

```text
initGuess[i]
lowerBounds[i]
upperBounds[i]
scalingFactors[i]
nelder_mead.txt column i
```

The CARLsim connection itself is edited separately in:

```text
src/region/<REGION>/<REGION>ConnectionSetup.cpp
```

The baseline synaptic weight is edited separately in:

```text
src/region/<REGION>/<REGION>BaselineWeights.cpp
```
