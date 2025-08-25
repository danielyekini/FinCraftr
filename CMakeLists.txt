cmake_minimum_required(VERSION 3.20)

project(fincraftr
    VERSION 1.0.0
    DESCRIPTION "FinCraftr - A bilingual quantitative finance toolkit"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include GNUInstallDirs for standard installation directories
include(GNUInstallDirs)

# Option to build as header-only
option(FINCRAFTR_HEADER_ONLY "Build as header-only library" ON)
option(FINCRAFTR_BUILD_SHARED "Build shared library" ON)
option(FINCRAFTR_BUILD_STATIC "Build static library" ON)
option(FINCRAFTR_BUILD_PYTHON_BINDINGS "Build Python bindings" OFF)

# Define the header files
set(FINCRAFTR_HEADERS
    cpp/include/fincraftr/equity/basic.hpp
    cpp/include/fincraftr/equity/index.hpp
    cpp/include/fincraftr/equity/profit.hpp
    cpp/include/fincraftr/equity/returns.hpp
    cpp/include/fincraftr/equity/valuation.hpp
    cpp/include/fincraftr/forwards/pricing.hpp
    cpp/include/fincraftr/options/binomial.hpp
    cpp/include/fincraftr/options/parity.hpp
    cpp/include/fincraftr/options/payoff.hpp
    cpp/include/fincraftr/options/profit.hpp
    cpp/include/fincraftr/rates/compounding.hpp
    cpp/include/fincraftr/rates/conversions.hpp
    cpp/include/fincraftr/rates/discount.hpp
)

# Create interface library for header-only usage
add_library(fincraftr_headers INTERFACE)
target_include_directories(fincraftr_headers INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cpp/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_features(fincraftr_headers INTERFACE cxx_std_20)

# Set up alias
add_library(fincraftr::headers ALIAS fincraftr_headers)

# If not header-only, create compiled libraries
if(NOT FINCRAFTR_HEADER_ONLY)
    # Create a source file that includes all headers to force compilation
    set(FINCRAFTR_COMPILE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/fincraftr_compile.cpp")
    file(WRITE ${FINCRAFTR_COMPILE_SOURCE} 
        "// Auto-generated file to compile all headers\n"
    )
    foreach(header ${FINCRAFTR_HEADERS})
        get_filename_component(header_name ${header} NAME_WE)
        get_filename_component(header_dir ${header} DIRECTORY)
        string(REPLACE "cpp/include/" "" relative_path ${header})
        file(APPEND ${FINCRAFTR_COMPILE_SOURCE} "#include <${relative_path}>\n")
    endforeach()
    file(APPEND ${FINCRAFTR_COMPILE_SOURCE} 
        "\n// Dummy function to ensure compilation\nvoid fincraftr_compile_check() {}\n"
    )

    # Build shared library
    if(FINCRAFTR_BUILD_SHARED)
        add_library(fincraftr_shared SHARED ${FINCRAFTR_COMPILE_SOURCE})
        target_include_directories(fincraftr_shared PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cpp/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )
        target_compile_features(fincraftr_shared PUBLIC cxx_std_20)
        set_target_properties(fincraftr_shared PROPERTIES
            OUTPUT_NAME fincraftr
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
        )
        add_library(fincraftr::shared ALIAS fincraftr_shared)
    endif()

    # Build static library
    if(FINCRAFTR_BUILD_STATIC)
        add_library(fincraftr_static STATIC ${FINCRAFTR_COMPILE_SOURCE})
        target_include_directories(fincraftr_static PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cpp/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )
        target_compile_features(fincraftr_static PUBLIC cxx_std_20)
        set_target_properties(fincraftr_static PROPERTIES
            OUTPUT_NAME fincraftr_static
            VERSION ${PROJECT_VERSION}
        )
        add_library(fincraftr::static ALIAS fincraftr_static)
    endif()
endif()

# Default target (header-only by default, shared if compiled)
if(FINCRAFTR_HEADER_ONLY)
    add_library(fincraftr ALIAS fincraftr_headers)
elseif(FINCRAFTR_BUILD_SHARED)
    add_library(fincraftr ALIAS fincraftr_shared)
elseif(FINCRAFTR_BUILD_STATIC)
    add_library(fincraftr ALIAS fincraftr_static)
endif()

# Python bindings
if(FINCRAFTR_BUILD_PYTHON_BINDINGS)
    find_package(pybind11 REQUIRED)
    pybind11_add_module(pyfincraftr python/bindings/main.cpp)
    target_link_libraries(pyfincraftr PRIVATE fincraftr_headers)
    target_compile_definitions(pyfincraftr PRIVATE VERSION_INFO=${PROJECT_VERSION})
    
    # Set output directory for Python module - pybind11 setup will handle installation
    set_target_properties(pyfincraftr PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()

# Installation
install(DIRECTORY cpp/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

# Install libraries
if(NOT FINCRAFTR_HEADER_ONLY)
    if(FINCRAFTR_BUILD_SHARED)
        install(TARGETS fincraftr_shared
            EXPORT fincraftrTargets
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )
    endif()
    
    if(FINCRAFTR_BUILD_STATIC)
        install(TARGETS fincraftr_static
            EXPORT fincraftrTargets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )
    endif()
endif()

# Always install the header interface
install(TARGETS fincraftr_headers
    EXPORT fincraftrTargets
)

# Generate and install CMake config files
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/fincraftrConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/fincraftrConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/fincraftrConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fincraftr
)

install(EXPORT fincraftrTargets
    FILE fincraftrTargets.cmake
    NAMESPACE fincraftr::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fincraftr
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/fincraftrConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/fincraftrConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fincraftr
)

# Export targets for build tree usage
export(EXPORT fincraftrTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/fincraftrTargets.cmake"
    NAMESPACE fincraftr::
)
