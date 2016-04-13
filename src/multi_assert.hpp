#ifndef LB_tuples_multi_assert_HeaderPlusPlus
#define LB_tuples_multi_assert_HeaderPlusPlus

#include "tuple.hpp"
#include "tuple_template_forward.hpp"

#include <type_traits>

namespace LB
{
	namespace tuples
	{
		template<template<typename...> typename Check, typename... Tuple>
		struct multi_assert;
		template<template<typename...> typename Check, typename First, typename... Rest>
		struct multi_assert<Check, First, Rest...> final
		: std::integral_constant //C++17: use std::bool_constant
		<
			bool,
			tuple_template_forward_t<Check, First>::value &&
			multi_assert<Check, Rest...>::value
		>
		{
		};
		template<template<typename...> typename Check>
		struct multi_assert<Check> final
		: std::true_type
		{
		};
		template<template<typename...> typename Check, typename... Tuple>
		constexpr bool multi_assert_v = multi_assert<Check, Tuple...>::value;
	}
}

#endif
