project(dina_utility_test)

cmake_minimum_required(VERSION 3.22)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

# This flags are used if cmake is called with -DCMAKE_BUILD_TYPE=PROFILE set(CMAKE_C_FLAGS_PROFILE --coverage) set(CMAKE_CXX_FLAGS_PROFILE --coverage) add_executable(program example.cpp)
#set(CMAKE_CXX_FLAGS_PROFILE --coverage)

include_directories(
    ../include/
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
    dina_utility_test 

    main.cpp
    version.cpp
    bitmask.cpp
)

target_link_libraries(dina_utility_test gtest GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(dina_utility_test)