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

#ifndef _MULTIPLICATION_HPP_
#define _MULTIPLICATION_HPP_

#include <memory>
#include <symbolic_computation/basis_objects/BasisFunction.hpp>
#include <list>

class Multiplication : public BasisElement
{
	public:
		using Shared = std::unique_ptr<Multiplication>;

	protected:
		/// List of elements in the operation 
		std::list<BasisElement::Shared> m_elements;
		
		/**
		 *  \brief Constructor
		 */
		Multiplication(){}

	public:
		/**
		 *  \brief Multiplication creation
		 */
		static Multiplication::Shared create();

		/**
		 *  \brief Appends an operation at the end of the list
		 */
		template<typename T>
		void append(const T& element)
		{
			auto elt = element->simplify();
			
			auto ptr = elt.release();

			auto commu = dynamic_cast<Multiplication*>(ptr);
			if(commu)
			{
				while(!(commu->m_elements.empty()))
				{
					auto cur_ptr = (*(commu->m_elements.begin())).release();
					commu->m_elements.pop_front();
					m_elements.push_back(BasisElement::Shared(cur_ptr));
				}
			}
			else
			{
				m_elements.push_back(BasisElement::Shared(ptr));
			}
		}

		/**
		 *  \brief Returns simplified version of element
		 */
		virtual BasisElement::Shared simplify() const;

		/**
		 *  \brief Element evaluation
		 */
		virtual double eval(const std::vector<double>&) const;
		
		/**
		 *  \brief Computes derivated function
		 */
		virtual BasisElement::Shared derivative(unsigned int param) const;
};

#endif // _MULTIPLICATION_HPP_



