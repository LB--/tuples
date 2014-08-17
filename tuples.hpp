#ifndef resplunk_util_Tuples_HeaderPlusPlus
#define resplunk_util_Tuples_HeaderPlusPlus

#include <cstdint>
#include <tuple>
#include <functional>
#include <type_traits>

namespace resplunk
{
	namespace util
	{
		namespace tuple_unpack
		{
			template<std::uintmax_t...>
			struct seq final
			{
			};
			template<std::uintmax_t N, std::uintmax_t... S>
			struct gens final
			: gens<N-1, N-1, S...>
			{
			};
			template<std::uintmax_t... S>
			struct gens<0, S...> final
			{
				using type = seq<S...>;
			};
		};

		template<template<typename...> typename To, typename Tuple>
		struct tuple_template_forward;
		template<template<typename...> typename To, typename... Args>
		struct tuple_template_forward<To, std::tuple<Args...>> final
		{
			using type = To<Args...>;
		};

		template<typename... Tuples>
		struct tuple_type_cat
		{
			using type = typename std::function<decltype(std::tuple_cat<Tuples...>)>::result_type;
		};

		namespace impl
		{
			template<typename Type, typename... Args>
			struct tuple_contains;
			template<typename Type, typename First, typename... Rest>
			struct tuple_contains<Type, First, Rest...> final
			{
				static constexpr bool value = (std::is_same<Type, First>::value || tuple_contains<Type, Rest...>::value);
			};
			template<typename Type>
			struct tuple_contains<Type> final
			: std::false_type
			{
			};
		}

		template<typename Tuple, typename Type>
		struct tuple_contains final
		{
			static constexpr bool value = tuple_template_forward<impl::tuple_contains, typename tuple_type_cat<std::tuple<Type>, Tuple>::type>::type::value;
		};

		namespace impl
		{
			template<typename Current, typename... Args>
			struct tuple_prune;
			template<typename Current, typename First, typename... Rest>
			struct tuple_prune<Current, First, Rest...> final
			{
				using type = typename std::conditional
				<
					util::tuple_contains<Current, First>::value,
					tuple_prune<Current, Rest...>,
					tuple_prune<typename tuple_type_cat<Current, std::tuple<First>>::type, Rest...>
				>::type::type;
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
			using type = typename tuple_template_forward<impl::tuple_prune, typename tuple_type_cat<std::tuple<std::tuple<>>, Tuple>::type>::type::type;
		};

		template<template<typename...> typename Check, typename... Tuple>
		struct multi_assert;
		template<template<typename...> typename Check, typename First, typename... Rest>
		struct multi_assert<Check, First, Rest...> final
		{
			static constexpr bool value = (tuple_template_forward<Check, First>::type::value && multi_assert<Check, Rest...>::value);
		};
		template<template<typename...> typename Check>
		struct multi_assert<Check> final
		: std::true_type
		{
		};
	}
}

#endif
