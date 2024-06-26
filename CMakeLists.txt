cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)


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

./src/main.cpp
./src/Source/Common.cpp
./src/Source/CommonMath.cpp
./src/Source/EncounterState.cpp
./src/Source/GameMenu.cpp
./src/Source/GameState.cpp
./src/Source/Grid.cpp
./src/Source/Renderer.cpp
)

set(HEADER_FILES
    src/Includes/Common.hpp
    src/Includes/CommonMath.hpp
    src/Includes/EncounterState.hpp
    src/Includes/GameMenu.hpp
    src/Includes/IRenderer/Renderer.hpp
    src/Includes/IState/GameState.hpp
)

# Add the main executable
add_executable(CMakeSFMLProject "src/main.cpp" ${SOURCE_FILES} ${HEADER_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeSFMLProject PROPERTY CXX_STANDARD 23)
endif()

# Include subdirectory for Common library
include_directories(${CMAKE_SOURCE_DIR}/src/Includes)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
