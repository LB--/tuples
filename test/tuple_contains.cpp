#include "tuples.hpp"

int main() noexcept
{
	using namespace LB::tuples;

	using t1 = tuple<int, int>;
	using t2 = tuple<int, float>;
	static_assert(!tuple_contains<t1, float>::value, "t1 contains float");
	static_assert(tuple_contains<t2, float>::value, "t2 doesn't contain float");
}
