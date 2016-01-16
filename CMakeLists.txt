cmake_minimum_required(VERSION 3.4)

project(LB/tuples
	VERSION 0.0.0
	LANGUAGES CXX
)
set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/${PROJECT_VERSION})

add_library(tuples INTERFACE)
#set_property(TARGET tuples PROPERTY CXX_STANDARD 17)
target_compile_options(tuples
	INTERFACE
		"-std=c++1z"
)
target_include_directories(tuples
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
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
		"tuples.hpp"
	DESTINATION include/${PROJECT_NAME}
)

enable_testing()

add_executable(test-basic
	"test/basic.cpp"
)
target_link_libraries(test-basic
	PUBLIC
		tuples
)
add_test(
	NAME basic
	COMMAND test-basic
)
