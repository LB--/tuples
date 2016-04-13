#ifndef LB_tuples_tuple_contains_HeaderPlusPlus
#define LB_tuples_tuple_contains_HeaderPlusPlus

#include "tuple.hpp"
#include "tuple_template_forward.hpp"
#include "tuple_type_cat.hpp"

#include <type_traits>

namespace LB
{
	namespace tuples
	{
		namespace impl
		{
			template<typename Type, typename... Args>
			struct tuple_contains;
			template<typename Type, typename First, typename... Rest>
			struct tuple_contains<Type, First, Rest...> final
			: std::integral_constant //C++17: use std::bool_constant
			<
				bool,
				std::is_same<Type, First>::value || tuple_contains<Type, Rest...>::value
			>
			{
			};
			template<typename Type>
			struct tuple_contains<Type> final
			: std::false_type
			{
			};
		}

		template<typename Tuple, typename Type>
		struct tuple_contains final
		: std::integral_constant //C++17: use std::bool_constant
		<
			bool,
			tuple_template_forward_t
			<
				impl::tuple_contains,
				tuple_type_cat_t<tuple<Type>, Tuple>
			>::value
		>
		{
		};
		template<typename Tuple, typename Type>
		constexpr bool tuple_contains_v = tuple_contains<Tuple, Type>::value;
	}
}

#endif
