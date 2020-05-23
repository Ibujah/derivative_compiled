/*
Copyright (c) 2020 Bastien Durix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Multiplication.hpp"
#include "Addition.hpp"
#include <memory>

Multiplication::Shared Multiplication::create()
{
	return Multiplication::Shared(new Multiplication());
}

BasisElement::Shared Multiplication::simplify() const
{
	auto mult_simp = std::shared_ptr<Multiplication>(new Multiplication());
	
	auto inte_tot = Integer::create(1);

	for(const auto &elt : m_elements)
	{
		auto inte = std::dynamic_pointer_cast<Integer>(elt);
		if(inte)
		{
			if(inte->value() == 0)
				return Integer::create(0);
			else
				inte_tot = Integer::create(inte_tot->value() * inte->value());
		}
		else
		{
			mult_simp->append(elt->simplify());
		}
	}
	mult_simp->m_elements.push_front(inte_tot->simplify());
	
	return mult_simp;
}

double Multiplication::eval(const std::vector<double>& args) const
{
	double res = 1.0;

	for(const auto &elt : m_elements)
	{
		res *= elt->eval(args);
	}
	
	return res;
}

BasisElement::Shared Multiplication::derivative(unsigned int param) const
{
	auto add_der = Addition::create();
	
	for(unsigned int ind = 0; ind < m_elements.size(); ind++)
	{
		auto mult_der = Multiplication::create();
		unsigned int i = 0;
		for(auto it = m_elements.begin(); it != m_elements.end(); it++)
		{
			if(i == ind)
				mult_der->append((*it)->derivative(param));
			else
				mult_der->append((*it));
			i++;
		}
		add_der->append(mult_der);
	}
	
	return add_der;
}

