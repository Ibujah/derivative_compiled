#include <iostream>

#include <symbolic_computation/basis_objects/Integer.hpp>
#include <symbolic_computation/basis_objects/Parameter.hpp>

int main(int argc, char** argv)
{
	auto Int1 = Integer::create(1);
	auto Param1 = Parameter::create(0);

	return 0;
}
