#include "tuple_forward.hpp"

#include <functional>
#include <tuple>

int main() noexcept
{
	using namespace LB::tuples;

	static constexpr auto t1 = std::make_tuple(1, 1);
	static constexpr auto t2 = std::make_tuple(1, 2);
	static_assert(tuple_forward(std::equal_to<int>{}, t1), "t1 doesn't contain the same value twice");
	static_assert(!tuple_forward(std::equal_to<int>{}, t2), "t2 contains the same value twice");
}
