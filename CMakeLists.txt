cmake_minimum_required(VERSION 3.0)
project(YourProjectName)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Set source directory
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/Common)

# Get all source and header files in the source directory
file(GLOB_RECURSE SOURCES "${SRCDIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
file(GLOB_RECURSE HEADERS "${SRCDIR}/*.hpp")

# Add executable target
add_executable(main ${SOURCES} ${HEADERS})

# Include headers directory
target_include_directories(main PRIVATE ${SRCDIR})

# Link SFML libraries to the executable
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)
