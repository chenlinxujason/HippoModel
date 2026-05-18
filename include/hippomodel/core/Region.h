#pragma once

#include <string>

namespace hippomodel {

enum class Region {
    DG,
    CA3,
    CA1
};

inline std::string toString(Region region) {
    switch (region) {
        case Region::DG:  return "DG";
        case Region::CA3: return "CA3";
        case Region::CA1: return "CA1";
    }
    return "UNKNOWN";
}

}  // namespace hippomodel
