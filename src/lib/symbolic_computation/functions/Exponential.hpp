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

#ifndef _EXPONENTIAL_HPP_
#define _EXPONENTIAL_HPP_

#include <symbolic_computation/basis_objects/BasisFunction.hpp>
#include <memory>

class Exponential : public BasisElement
{
	protected:
		/// \brief Element to compose with
		BasisElement::Shared m_comp;

		/**
		 *  \brief Constructor
		 */
		Exponential(const BasisElement::Shared& comp);
	
	public:
		/**
		 *  \brief Exponential creation
		 */
		static BasisElement::Shared create(const BasisElement::Shared& comp);

		/**
		 *  \brief Returns simplified version of element
		 */
		virtual BasisElement::Shared simplify() const;
		
		/**
		 *  \brief Element evaluation
		 */
		virtual double eval(const std::vector<double>& param) const;
		
		/**
		 *  \brief Computes derivated function
		 */
		virtual Shared derivative(unsigned int param) const;
};

#endif // _EXPONENTIAL_HPP_
