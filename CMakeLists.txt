project(example)

# set(CMAKE_C_COMPILER clang)
# set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.22)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://mirror.ghproxy.com/https://github.com/libcpr/cpr.git
                         GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
set(CPR_USE_SYSTEM_CURL ON)
FetchContent_MakeAvailable(cpr)

add_executable(example "example.cpp")
target_link_libraries(example spdlog::spdlog_header_only)
target_link_libraries(example fmt::fmt-header-only)
target_link_libraries(example cpr::cpr)