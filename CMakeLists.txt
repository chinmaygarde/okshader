cmake_minimum_required(VERSION 3.22)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")
include(ok_library)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/third_party/cmake_toolbox")
include(CMakeToolboxInitialize)

CMakeToolboxInitialize()

SetCAndCXXStandard(11 20)

EnableCCache()

project(ok)

enable_testing()
include(GoogleTest)
include(CTest)

add_subdirectory(third_party/glfw EXCLUDE_FROM_ALL)
set(GOOGLETEST_PATH "third_party/swiftshader/third_party/googletest")
set(BENCHMARK_ENABLE_TESTING FALSE)
add_subdirectory(third_party/googlebenchmark EXCLUDE_FROM_ALL)
add_subdirectory(third_party/glm EXCLUDE_FROM_ALL)
set(BUILD_TESTING FALSE)
add_subdirectory(third_party/swiftshader EXCLUDE_FROM_ALL)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(bench)
