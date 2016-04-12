#include "tuples.hpp"

int main() noexcept
{
	using namespace LB::tuples;

	using t1 = tuple<int, int, float>;
	using t2 = tuple_template_forward_t<std::tuple, t1>;
	static_assert(std::is_same<t2, std::tuple<int, int, float>>{}, "t1 != t2");

	using t3 = std::tuple<float, int, double>;
	using t4 = tuple_template_forward_t<tuple, t3>;
	static_assert(std::is_same<t4, tuple<float, int, double>>{}, "t3 != t4");
}
