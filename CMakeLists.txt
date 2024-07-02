cmake_minimum_required(VERSION 3.16)
project(ShinMegamiTensei LANGUAGES CXX)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)
# Set asset path
add_compile_definitions(ASSET_PATH="${CMAKE_SOURCE_DIR}/StaticAssets/")

# Use vcpkg toolchain
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()

# Collect all source and header files
set(SOURCE_FILES
    src/Source/main.cpp
    src/Source/Renderer.cpp
    src/Source/Common.cpp
)

set(HEADER_FILES
    src/Includes/Common.hpp
    src/Includes/Renderer.hpp
)

# Add the main executable
add_executable(ShinMegamiTensei ${SOURCE_FILES} ${HEADER_FILES})

# Set the C++ standard to 23 if CMake version is greater than 3.12
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ShinMegamiTensei PROPERTY CXX_STANDARD 23)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src/Includes)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(ShinMegamiTensei PRIVATE OpenGL::GL)

# Find and link cxxopts
find_package(cxxopts CONFIG REQUIRED)
target_link_libraries(ShinMegamiTensei PRIVATE cxxopts::cxxopts)

# Find and link xsimd
find_package(xsimd CONFIG REQUIRED)
target_link_libraries(ShinMegamiTensei PRIVATE xsimd)

# Find and link GLEW
find_package(GLEW REQUIRED)
target_link_libraries(ShinMegamiTensei PRIVATE GLEW::GLEW)

# Find and link GLFW
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ShinMegamiTensei PRIVATE glfw)

