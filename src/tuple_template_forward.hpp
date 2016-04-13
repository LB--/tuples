#ifndef LB_tuples_tuple_template_forward_HeaderPlusPlus
#define LB_tuples_tuple_template_forward_HeaderPlusPlus

#include "tuple.hpp"

#include <tuple>

namespace LB
{
	namespace tuples
	{
		template<template<typename...> typename To, typename Tuple>
		struct tuple_template_forward;
		template<template<typename...> typename To, typename... Args>
		struct tuple_template_forward<To, tuple<Args...>> final
		{
			using type = To<Args...>;
		};
		template<template<typename...> typename To, typename... Args>
		struct tuple_template_forward<To, std::tuple<Args...>> final
		{
			using type = To<Args...>;
		};
		template<template<typename...> typename To, typename Tuple>
		using tuple_template_forward_t = typename tuple_template_forward<To, Tuple>::type;
	}
}

#endif
