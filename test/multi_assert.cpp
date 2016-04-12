#include "tuples.hpp"

int main() noexcept
{
	using namespace LB::tuples;

	using t1 = tuple<int, int>;
	using t2 = tuple<float, float>;
	using t3 = tuple<int, float>;

	static_assert(multi_assert<std::is_same, t1, t2>::value, "t1 or t2 isn't homogeneous");
	static_assert(!multi_assert<std::is_same, t1, t2, t3>::value, "t1, t2 and t3 are homogeneous");
}
