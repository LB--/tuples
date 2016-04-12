#include "tuples.hpp"

static constexpr bool are_equal(int x, int y)
{
	return x == y;
}

int main() noexcept
{
	using namespace LB::tuples;

	static constexpr auto t1 = std::make_tuple(1, 1);
	static constexpr auto t2 = std::make_tuple(1, 2);
	static_assert(tuple_forward(are_equal, t1), "t1 doesn't contain the same value twice");
	static_assert(!tuple_forward(are_equal, t2), "t2 contains the same value twice");
}
