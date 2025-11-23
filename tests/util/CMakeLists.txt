set(UTIL_TEST_SOURCES
	test-ring-buffer.cpp
)

set(EXECUTABLE_NAME "util-tests")
add_executable(${EXECUTABLE_NAME} ${CORE_TEST_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE 
	Catch2::Catch2WithMain
	Tetris::Util
) 

include(CTest)
include(Catch)
catch_discover_tests(${EXECUTABLE_NAME})
