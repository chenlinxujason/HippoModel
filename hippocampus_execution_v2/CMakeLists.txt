cmake_minimum_required(VERSION 3.22)
project(hippocampus_execution_simple LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set these two installation paths in the cmake command shown in README.md.
set(CARLSIM_ROOT "" CACHE PATH "CARLsim installation prefix")
set(CARLSIM_SOURCE_DIR "" CACHE PATH "CARLsim source directory")

find_package(Boost REQUIRED)
find_package(HDF5 REQUIRED COMPONENTS C)
find_package(OpenMP REQUIRED COMPONENTS CXX)
find_package(HighFive REQUIRED)

find_path(CARLSIM_INCLUDE_DIR carlsim.h
    PATHS "${CARLSIM_ROOT}/include" NO_DEFAULT_PATH REQUIRED)
find_path(CARLSIM_SPIKE_INCLUDE_DIR spikegen_from_file.h
    PATHS "${CARLSIM_ROOT}/include" "${CARLSIM_SOURCE_DIR}/tools/spike_generators"
    NO_DEFAULT_PATH REQUIRED)
find_path(CARLSIM_STOPWATCH_INCLUDE_DIR stopwatch.h
    PATHS "${CARLSIM_ROOT}/include" "${CARLSIM_SOURCE_DIR}/tools/stopwatch"
    NO_DEFAULT_PATH REQUIRED)
find_library(CARLSIM_LIBRARY NAMES carlsim
    PATHS "${CARLSIM_ROOT}/lib" "${CARLSIM_ROOT}/lib64" NO_DEFAULT_PATH REQUIRED)
find_library(CARLSIM_SPIKE_LIBRARY NAMES carlsim-spike-generators
    PATHS "${CARLSIM_ROOT}/lib" "${CARLSIM_ROOT}/lib64" NO_DEFAULT_PATH REQUIRED)
find_library(CARLSIM_STOPWATCH_LIBRARY NAMES carlsim-stopwatch
    PATHS "${CARLSIM_ROOT}/lib" "${CARLSIM_ROOT}/lib64" NO_DEFAULT_PATH REQUIRED)

foreach(region DG CA3 CA1)
    add_executable(hippomodel_run_${region} src/run_${region}.cpp)
    target_compile_definitions(hippomodel_run_${region} PRIVATE CARLSIM_USERCONN=1)
    target_include_directories(hippomodel_run_${region} PRIVATE
        include "${CARLSIM_INCLUDE_DIR}" "${CARLSIM_SPIKE_INCLUDE_DIR}"
        "${CARLSIM_STOPWATCH_INCLUDE_DIR}" ${HDF5_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
    target_link_libraries(hippomodel_run_${region} PRIVATE
        "${CARLSIM_LIBRARY}" "${CARLSIM_SPIKE_LIBRARY}" "${CARLSIM_STOPWATCH_LIBRARY}"
        HighFive ${HDF5_LIBRARIES} OpenMP::OpenMP_CXX)
endforeach()
