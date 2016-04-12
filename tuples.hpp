#ifndef LB_tuples_tuples_HeaderPlusPlus
#define LB_tuples_tuples_HeaderPlusPlus

#include <cstdint>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace LB
{
	namespace tuples
	{
		template<typename... Types>
		struct tuple final
		{
			template<typename... Args>
			struct concat final
			{
				using type = tuple<Types..., Args...>;
			};
			template<typename... Args>
			using concat_t = typename concat<Args...>::type;
		};

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

		namespace impl
		{
			template<typename F, typename Tuple, std::size_t... I>
			constexpr decltype(auto) tuple_forward(F &&f, Tuple &&t, std::index_sequence<I...>)
			{
				return f(std::get<I>(std::forward<Tuple>(t))...); //not as robust as std::invoke
			}
		}

		//substitute for std::apply
		template<typename F, typename Tuple>
		constexpr decltype(auto) tuple_forward(F &&f, Tuple &&t)
		{
			return impl::tuple_forward
			(
				std::forward<F>(f),
				std::forward<Tuple>(t),
				std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>{}>{}
			);
		}

		template<typename... Tuples>
		struct tuple_type_cat;
		template<typename First, typename... Rest>
		struct tuple_type_cat<First, Rest...> final
		{
			template<typename... Args>
			using concat = typename First::template concat_t<Args...>;
			using type = tuple_template_forward_t<concat, typename tuple_type_cat<Rest...>::type>;
		};
		template<>
		struct tuple_type_cat<> final
		{
			using type = tuple<>;
		};
		template<typename... Tuples>
		using tuple_type_cat_t = typename tuple_type_cat<Tuples...>::type;

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

		namespace impl
		{
			template<typename Current, typename... Args>
			struct tuple_prune;
			template<typename Current, typename First, typename... Rest>
			struct tuple_prune<Current, First, Rest...> final
			{
				using type = typename std::conditional_t
				<
					tuples::tuple_contains<Current, First>::value,
					tuple_prune<Current, Rest...>,
					tuple_prune<typename tuple_type_cat<Current, tuple<First>>::type, Rest...>
				>::type;
			};
			template<typename Current>
			struct tuple_prune<Current> final
			{
				using type = Current;
			};
		}

		template<typename Tuple>
		struct tuple_prune final
		{
			using type = typename tuple_template_forward_t
			<
				impl::tuple_prune,
				tuple_type_cat_t<tuple<tuple<>>, Tuple>
			>::type;
		};
		template<typename Tuple>
		using tuple_prune_t = typename tuple_prune<Tuple>::type;

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
