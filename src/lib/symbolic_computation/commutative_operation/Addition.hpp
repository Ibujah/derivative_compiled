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

#ifndef _ADDITION_HPP_
#define _ADDITION_HPP_

#include <memory>
#include <symbolic_computation/basis_objects/BasisFunction.hpp>
#include <symbolic_computation/basis_objects/Integer.hpp>
#include <list>

class Addition : public BasisElement
{
	public:
		using Shared = std::shared_ptr<Addition>;

	protected:
		/// List of elements in the operation 
		std::list<BasisElement::Shared> m_elements;
		
		/**
		 *  \brief Constructor
		 */
		Addition(){}

	public:
		/**
		 *  \brief Addition creation
		 */
		static Addition::Shared create();

		/**
		 *  \brief Appends an operation at the end of the list
		 */
		template<typename T>
		void append(const T& element)
		{
			auto elt = element->simplify();
			
			const auto commu = std::dynamic_pointer_cast<Addition>(elt);
			const auto inte  = std::dynamic_pointer_cast<Integer>(elt);
			if(commu)
			{
				for(const auto &cur_elt : commu->m_elements)
				{
					m_elements.push_back(cur_elt->simplify());
				}
			}
			else if(inte)
			{
				if(inte->value() != 0)
				{
					m_elements.push_back(elt->simplify());
				}
			}
			else
			{
				m_elements.push_back(elt->simplify());
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

#endif // _ADDITION_HPP_


