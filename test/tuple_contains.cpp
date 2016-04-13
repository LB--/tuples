#include "tuple_contains.hpp"

int main() noexcept
{
	using namespace LB::tuples;

	using t1 = tuple<int, int>;
	using t2 = tuple<int, float>;
	static_assert(!tuple_contains<t1, float>{}, "t1 contains float");
	static_assert(tuple_contains_v<t2, float>, "t2 doesn't contain float");
}
