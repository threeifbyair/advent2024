# Specify minimum CMake version required
cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

# Set the C and C++ compilers to Clang
set(CMAKE_C_COMPILER /home/abell/.local/bin/clang)
set(CMAKE_CXX_COMPILER /home/abell/.local/bin/clang++)
set(CMAKE_CXX_STANDARD_LIBRARY libc++)

# Enables the Standard module support. This needs to be done
# before selecting the languages.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -stdlib=libc++")

# Set C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the custom language compiler (hypothetical)
set(CPP2_COMPILER cppfront) # Replace with your actual compiler command
set(CPP2_FLAGS -import-std -import-cpp2-util)              # Any specific flags for the custom language

# Specify the build rules for cpp2 files
function(add_cpp2_file target cpp2_file is_module)
    # Define the output object file
    set(output_file "${CMAKE_CURRENT_BINARY_DIR}/${cpp2_file}.cpp")

    # Add a custom command to compile the .cpp2 file
    add_custom_command(
        OUTPUT ${output_file}
        COMMAND ${CPP2_COMPILER} ${CPP2_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/${cpp2_file} -o ${output_file}
        DEPENDS ${cpp2_file}
        COMMENT "Compiling ${cpp2_file} with ${CPP2_COMPILER}"
    )

    add_custom_target(cpp2_to_cpp_target_${cpp2_file}
        DEPENDS ${output_file}
    )
    add_dependencies(${target} cpp2_to_cpp_target_${cpp2_file})

    # Add the output object file to the target
    if(is_module)
        target_sources(${target} PRIVATE FILE_SET CXX_MODULES BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR} FILES ${output_file})
    else()
        target_sources(${target} PRIVATE ${output_file})
    endif()
endfunction()

# Specify the build types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Set the default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Set compiler flags for different build types
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

cmake_policy(SET CMP0167 NEW)
set(Boost_DIR /home/abell/.local/lib/cmake/Boost-1.89.0)

# Define the project name and version
project(advent2024 VERSION 1.0 LANGUAGES "CXX")

# Find Boost
find_package(Boost REQUIRED COMPONENTS program_options)

if(Boost_FOUND)
    add_executable(advent2024)

    target_include_directories(advent2024 PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(advent2024 PRIVATE Boost::program_options)

    #target_compile_options(advent2024 PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    #target_link_options(advent2024 PRIVATE -fsanitize=address)

    # Include directories
    include_directories(include)
    include_directories(/home/abell/src/cppfront/include)

    # Add subdirectory for the source files
    add_subdirectory(src)
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# And a second executable for encrypting files
add_executable(encrypt_file src/encrypt_file.cpp)
target_include_directories(encrypt_file PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(encrypt_file PRIVATE Boost::program_options)


