#ifndef LB_tuples_tuple_HeaderPlusPlus
#define LB_tuples_tuple_HeaderPlusPlus

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
	}
}

#endif
