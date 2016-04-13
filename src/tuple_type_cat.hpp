#ifndef LB_tuples_tuple_type_cat_HeaderPlusPlus
#define LB_tuples_tuple_type_cat_HeaderPlusPlus

#include "tuple.hpp"
#include "tuple_template_forward.hpp"

namespace LB
{
	namespace tuples
	{
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
	}
}

#endif
