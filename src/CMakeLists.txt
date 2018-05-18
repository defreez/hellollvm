project(hellollvm)
set(func2vec_VERSION_MAJOR 0)
set(func2vec_VERSION_MINOR 1)

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

include_directories(hello)
include_directories(llvm-passes)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS} ${COMPILE_FLAGS})
link_directories(${LLVM_INSTALL_PREFIX}/lib)

find_package(Boost COMPONENTS program_options REQUIRED)

set(HELLO_FILES
        hello/main.cpp
        )
set(PASS_FILES
        llvm-passes/FunctionNames.cpp
        )

# This cannot be a shared library because LLVM uses globals for options.
# The MODULE target can be loaded by opt on the command line.
# The SHARED target is linked into main.
add_library(mypasses MODULE ${PASS_FILES})
add_library(hellollvm SHARED ${PASS_FILES})
set_target_properties(mypasses PROPERTIES COMPILE_FLAGS -fno-exceptions)
set_target_properties(hellollvm PROPERTIES COMPILE_FLAGS -fno-exceptions)

llvm_map_components_to_libnames(llvm_libs support core irreader analysis)
target_link_libraries(hellollvm ${llvm_libs} ${Boost_LIBRARIES})

add_executable(hello ${HELLO_FILES})
add_dependencies(hello hellollvm)
target_link_libraries(hello hellollvm)
