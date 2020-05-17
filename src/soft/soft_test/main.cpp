#include <iostream>

#include <stdexcept>
#include <symbolic_computation/basis_objects/Integer.hpp>
#include <symbolic_computation/basis_objects/Parameter.hpp>
#include <symbolic_computation/functions/Exponential.hpp>
#include <symbolic_computation/commutative_operation/Addition.hpp>

int main(int argc, char** argv)
{
	auto Int1 = Integer::create(1);
	auto Param2 = Parameter::create(2);
	auto Param5 = Parameter::create(5);
	auto ExpX = Exponential::create(Parameter::create(0));
	
	auto Add = Addition::create();
	Add->append(Int1);
	Add->append(Param2);

	std::vector<double> args{0.0, 1.0, 2.0, 3.0};
	std::cout << Int1->eval(args) << std::endl;
	std::cout << Param2->eval(args) << std::endl;
	std::cout << ExpX->eval(args) << std::endl;
	std::cout << Add->eval(args) << std::endl;
	std::cout << Add->derivative(2)->eval(args) << std::endl;
	try
	{
		std::cout << Param5->eval(args) << std::endl;
	}
	catch(std::logic_error &e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
