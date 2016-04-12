#include "tuples.hpp"

int main() noexcept
{
	using namespace LB::tuples;

	using t1 = tuple<int>;
	using t2 = tuple<float>;
	using t3 = typename tuple_type_cat<t1, t2>::type;
	static_assert(std::is_same<t3, tuple<int, float>>::value, "t1 + t2 != t3");
}
