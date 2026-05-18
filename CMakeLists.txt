cmake_minimum_required(VERSION 3.22)
project(hippomodel_largescalemodel LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(HIPPOMODEL_ENABLE_CARLSIM "Build CARLsim-based executables" ON)

message(STATUS "Build type = ${CMAKE_BUILD_TYPE}")
message(STATUS "HIPPOMODEL_ENABLE_CARLSIM = ${HIPPOMODEL_ENABLE_CARLSIM}")

if(HIPPOMODEL_ENABLE_CARLSIM)
    find_package(Boost REQUIRED)
    include_directories(${Boost_INCLUDE_DIRS})

    if(NOT DEFINED carlsim_DIR)
        set(carlsim_DIR "/home/song/CARLsim/userconn/carlsim/lib/cmake/carlsim")
    endif()
    if(NOT CARLSIM_LIBRARY)
        set(CARLSIM_LIBRARY "/home/song/CARLsim/userconn/carlsim/lib/libcarlsim.so"
            CACHE FILEPATH "Path to libcarlsim.so")
    endif()
    if(NOT CARLSIM_INCLUDE_DIR)
        set(CARLSIM_INCLUDE_DIR "/home/song/CARLsim/userconn/carlsim/include"
            CACHE PATH "CARLsim include directory")
    endif()

    find_package(carlsim REQUIRED)

    message(STATUS "carlsim_DIR = ${carlsim_DIR}")
    message(STATUS "CARLSIM_LIBRARY = ${CARLSIM_LIBRARY}")
    message(STATUS "CARLSIM_INCLUDE_DIR = ${CARLSIM_INCLUDE_DIR}")
    message(STATUS "CARLSIM_NO_CUDA = ${CARLSIM_NO_CUDA}")

    if(CARLSIM_NO_CUDA)
        message(FATAL_ERROR
            "CARLSIM_NO_CUDA is ON. This would compile hippomodel with -D__NO_CUDA__. "
            "Stop here because this can make large network setup extremely slow.")
    endif()

    find_package(HDF5 REQUIRED)
    find_package(OpenMP REQUIRED)
    find_package(HighFive REQUIRED)

    set(HIPPOMODEL_COMMON_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/hippomodel/optimizer
        ${CMAKE_CURRENT_SOURCE_DIR}/include/hippomodel/region/DG
        ${CMAKE_CURRENT_SOURCE_DIR}/include/hippomodel/region/CA3
        ${CMAKE_CURRENT_SOURCE_DIR}/include/hippomodel/region/CA1
        ${CARLSIM_INCLUDE_DIR}
        /home/song/CARLsim/userconn/CARLsim6/tools/spike_generators
        /home/song/CARLsim/userconn/carlsim/lib
    )

    set(HIPPOMODEL_COMMON_LIBS
        /home/song/CARLsim/userconn/carlsim/lib/libcarlsim.so
        /home/song/CARLsim/userconn/carlsim/lib/libcarlsim-stopwatch.so
        /home/song/CARLsim/userconn/carlsim/lib/libcarlsim-spike-generators.so
        hdf5
        z
        HighFive
        OpenMP::OpenMP_CXX
    )

    add_library(hippomodel_core
        src/config/RuntimeConfig.cpp
        src/workflow/WorkflowArgs.cpp
        src/region/DG/DGRegionSpec.cpp
        src/region/DG/DGModelSetup.cpp
        src/region/DG/DGConnectionSetup.cpp
        src/region/DG/DGOptimizationBounds.cpp
        src/region/CA3/CA3RegionSpec.cpp
        src/region/CA3/CA3ModelSetup.cpp
        src/region/CA3/CA3ConnectionSetup.cpp
        src/region/CA3/CA3OptimizationBounds.cpp
        src/region/CA1/CA1RegionSpec.cpp
        src/region/CA1/CA1ModelSetup.cpp
        src/region/CA1/CA1ConnectionSetup.cpp
        src/region/CA1/CA1OptimizationBounds.cpp
        src/io/DGConnectivityLoader.cpp
        src/io/CA3ConnectivityLoader.cpp
        src/io/CA1ConnectivityLoader.cpp
        src/network/DGConnectionGenerator.cpp
        src/network/DGNetworkBuilder.cpp
        src/network/CA3ConnectionGenerator.cpp
        src/network/CA3NetworkBuilder.cpp
        src/network/CA1ConnectionGenerator.cpp
        src/network/CA1NetworkBuilder.cpp
        src/analysis/FiringRate.cpp
        src/analysis/Correlation.cpp
        src/analysis/PSD.cpp
        src/loss/DGEvaluator.cpp
        src/loss/CA3Evaluator.cpp
        src/loss/CA1Evaluator.cpp
        src/optimizer/OptimizationLogger.cpp
        src/workflow/RunWorkflow.cpp
        src/workflow/OptimizeWorkflow.cpp
    )

    target_compile_features(hippomodel_core PUBLIC cxx_std_17)
    target_compile_definitions(hippomodel_core PUBLIC CARLSIM_USERCONN=1)
    target_include_directories(hippomodel_core PUBLIC ${HIPPOMODEL_COMMON_INCLUDE_DIRS})
    target_link_directories(hippomodel_core PUBLIC /home/song/CARLsim/userconn/carlsim/lib)
    target_link_libraries(hippomodel_core PUBLIC ${HIPPOMODEL_COMMON_LIBS})

    add_executable(hippomodel_run tools/main_run.cpp)
    target_link_libraries(hippomodel_run PRIVATE hippomodel_core)

    add_executable(hippomodel_optimize tools/main_optimize.cpp)
    target_link_libraries(hippomodel_optimize PRIVATE hippomodel_core)

    foreach(target hippomodel_core hippomodel_run hippomodel_optimize)
        set_target_properties(${target} PROPERTIES
            BUILD_RPATH   "/home/song/CARLsim/userconn/carlsim/lib"
            INSTALL_RPATH "/home/song/CARLsim/userconn/carlsim/lib"
        )
    endforeach()

    set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
endif()
