cmake_minimum_required(VERSION 3.4)

project(LB/tuples
	VERSION 1.0.0
	LANGUAGES CXX
)
set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/${PROJECT_VERSION}")

add_library(tuples INTERFACE)
#set_property(TARGET tuples PROPERTY CXX_STANDARD 17)
target_compile_options(tuples
	INTERFACE
		"-std=c++1z"
)
target_include_directories(tuples
	INTERFACE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
		$<INSTALL_INTERFACE:include>
)

install(
	TARGETS
		tuples
	EXPORT tuples
)
install(
	EXPORT tuples
	DESTINATION cmake/LB
	NAMESPACE LB::
)
install(
	FILES
		"src/tuple.hpp"
		"src/tuple_template_forward.hpp"
		"src/tuple_forward.hpp"
		"src/tuple_type_cat.hpp"
		"src/tuple_contains.hpp"
		"src/tuple_prune.hpp"
		"src/multi_assert.hpp"
	DESTINATION include/${PROJECT_NAME}
)

option(BUILD_TESTS "Whether to build the tests" ON)
if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()
