#include "hippomodel/workflow/WorkflowArgs.h"

#include <stdexcept>
#include <string>

namespace hippomodel {

std::string parseConfigPath(int argc, char** argv) {
    std::string config = "config/hippomodel.toml";
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--config") {
            if (i + 1 >= argc) throw std::runtime_error("--config requires a file path");
            config = argv[++i];
        } else {
            throw std::runtime_error("Unknown command-line argument: " + arg);
        }
    }
    return config;
}

}  // namespace hippomodel
