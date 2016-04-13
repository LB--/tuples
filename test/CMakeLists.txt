
macro(simple_test _name)
	add_executable(test-${_name}
		"${_name}.cpp"
	)
	target_link_libraries(test-${_name}
		PUBLIC
			tuples
	)
	add_test(
		NAME ${_name}
		COMMAND test-${_name}
	)
endmacro()

simple_test(tuple_template_forward)
simple_test(tuple_forward)
simple_test(tuple_type_cat)
simple_test(tuple_contains)
simple_test(tuple_prune)
simple_test(multi_assert)
