set(CORE_TEST_SOURCES
	test-matrix.cpp
	test-tetromino.cpp
)

set(EXECUTABLE_NAME "core-tests")
add_executable(${EXECUTABLE_NAME} ${CORE_TEST_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE 
	Catch2::Catch2WithMain
  Tetris::Core
) 

include(CTest)
include(Catch)
catch_discover_tests(${EXECUTABLE_NAME})
