enable_testing()

find_package(Catch2 CONFIG REQUIRED) 

include_directories(${PROJECT_SOURCE_DIR}/src/core/include)

set(CORE_TEST_SOURCES
  testFlat2DArray.cpp
)

add_executable(core_tests ${CORE_TEST_SOURCES})
target_link_libraries(core_tests Catch2::Catch2WithMain) 

include(CTest)
include(Catch)
catch_discover_tests(core_tests)