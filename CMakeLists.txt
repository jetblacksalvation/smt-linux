cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Set the build type to Debugs
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/Includes")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Source/*.cpp" )
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/Includes/*.hpp")

add_executable(ShinMegamiTensei src/main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(ShinMegamiTensei PRIVATE sfml-graphics)
target_link_libraries(ShinMegamiTensei PRIVATE sfml-graphics)
target_compile_features(ShinMegamiTensei PRIVATE cxx_std_20)

target_include_directories(ShinMegamiTensei PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Common)

if(WIN32)
    add_custom_command(
        TARGET ShinMegamiTensei
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:ShinMegamiTensei>
        VERBATIM)
endif()

install(TARGETS ShinMegamiTensei)
