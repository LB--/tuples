#include "tuples.hpp"

int main() noexcept
{
	using namespace LB::tuples;

	{
		using t1 = tuple<int, int, float>;
		using t2 = tuple_template_forward<std::tuple, t1>::type;
		static_assert(std::is_same<t2, std::tuple<int, int, float>>::value, "t1 != t2");
		using t3 = std::tuple<float, int, double>;
		using t4 = tuple_template_forward<tuple, t3>::type;
		static_assert(std::is_same<t4, tuple<float, int, double>>::value, "t3 != t4");
	}

	{
		using t1 = tuple<int>;
		using t2 = tuple<float>;
		using t3 = typename tuple_type_cat<t1, t2>::type;
		static_assert(std::is_same<t3, tuple<int, float>>::value, "t1 + t2 != t3");
	}

	{
		using t1 = tuple<int, int>;
		using t2 = tuple<int, float>;
		static_assert(!tuple_contains<t1, float>::value, "t1 contains float");
		static_assert(tuple_contains<t2, float>::value, "t2 doesn't contain float");
	}

	static_assert(std::is_same
	<
		tuple<void, int, short>,
		typename tuple_prune<tuple<void, void, int, void, int, short, void, short, int, short>
	>::type>::value, "tuple_prune is broken");
}
