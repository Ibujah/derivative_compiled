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

#include "Addition.hpp"

Addition::Shared Addition::create()
{
	return Addition::Shared(new Addition());
}

BasisElement::Shared Addition::simplify() const
{
	auto add_simp = std::shared_ptr<Addition>(new Addition());
	
	auto inte_tot = Integer::create(0);
	
	for(const auto &elt : m_elements)
	{
		const auto inte = std::dynamic_pointer_cast<Integer>(elt);
		if(inte)
		{
			inte_tot = Integer::create(inte_tot->value() + inte->value());
		}
		else
		{
			add_simp->append(elt);
		}
	}
	
	const auto inte_final = Integer::create(inte_tot->value());

	add_simp->m_elements.push_front(inte_final->simplify());
	
	return add_simp;
}

double Addition::eval(const std::vector<double>& args) const
{
	double res = 0.0;

	for(auto it = m_elements.begin(); it != m_elements.end(); it++)
	{
		res += (*it)->eval(args);
	}
	
	return res;
}

BasisElement::Shared Addition::derivative(unsigned int param) const
{
	auto add_der = Addition::create();
	
	for(auto elt : m_elements)
	{
		add_der->append(elt->derivative(param));
	}
	
	return add_der;
}
