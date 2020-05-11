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

#include "Exponential.hpp"
#include <memory>
#include <math.h>
#include <stdexcept>

Exponential::Exponential(const BasisElement::Shared& comp) : 
	m_comp(comp->simplify())
{}

BasisElement::Shared Exponential::create(const BasisElement::Shared& comp)
{
	return std::unique_ptr<Exponential>(new Exponential(comp));
}

BasisElement::Shared Exponential::simplify() const
{
	return create(m_comp->simplify());
}

double Exponential::eval(const std::vector<double>& param) const
{
	return (double)exp(m_comp->eval(param));
}

BasisElement::Shared Exponential::derivative(unsigned int param) const
{
	throw std::logic_error("Exponential::derivative : Not implemented yet");
}
