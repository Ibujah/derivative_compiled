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

#include <memory>
#include <stdarg.h>
#include <stdexcept>

#include "Parameter.hpp"
#include "Integer.hpp"

Parameter::Parameter(int indice) : 
	m_indice(indice)
{}

Parameter::Shared Parameter::create(int indice)
{
	return std::shared_ptr<Parameter>(new Parameter(indice));
}

BasisElement::Shared Parameter::simplify() const
{
	return create(m_indice);
}

double Parameter::eval(const std::vector<double>& args) const
{
	if(args.size() <= m_indice)
		throw std::logic_error("Parameter::eval : Not enough arguments for this evaluation");

	return args[m_indice];
}

BasisElement::Shared Parameter::derivative(unsigned int param) const
{
	if(param == m_indice)
		return Integer::create(1);
	
	return Integer::create(0);
}
