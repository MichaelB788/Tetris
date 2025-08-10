set(CORE_TEST_SOURCES
  testFlat2DArray.cpp
	testPlayfield.cpp
	# TODO Add more tests for other core components
)

add_executable(core_tests ${CORE_TEST_SOURCES})

target_link_libraries(core_tests PRIVATE 
	tetris_core
	Catch2::Catch2WithMain
) 

include(CTest)
include(Catch)
catch_discover_tests(core_tests)