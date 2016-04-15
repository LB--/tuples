#ifndef LB_tuples_tuple_forward_HeaderPlusPlus
#define LB_tuples_tuple_forward_HeaderPlusPlus

#include "tuple.hpp"

#include <cstddef>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace LB
{
	namespace tuples
	{
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
				std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{}
			);
		}
	}
}

#endif
