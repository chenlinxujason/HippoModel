#pragma once

#include "hippomodel/core/Region.h"

namespace hippomodel::user {

// -----------------------------------------------------------------------------
// USER-EDITED REGION SELECTION
// -----------------------------------------------------------------------------
// Change only this line when switching the compiled CARLsim package target.
// The build and run commands remain identical:
//   sudo cmake --build build
//   ./build/hippomodel_run --config config/hippomodel.toml
//   ./build/hippomodel_optimize --config config/hippomodel.toml
//
// Available values:
//   hippomodel::Region::DG
//   hippomodel::Region::CA3   // placeholder until CA3 code is integrated
//   hippomodel::Region::CA1   // placeholder until CA1 code is integrated
// -----------------------------------------------------------------------------
inline constexpr hippomodel::Region kSelectedRegion = hippomodel::Region::DG;

}  // namespace hippomodel::user
