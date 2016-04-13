#ifndef LB_tuples_tuple_prune_HeaderPlusPlus
#define LB_tuples_tuple_prune_HeaderPlusPlus

#include "tuple.hpp"
#include "tuple_contains.hpp"

#include <type_traits>

namespace LB
{
	namespace tuples
	{
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
	}
}

#endif
