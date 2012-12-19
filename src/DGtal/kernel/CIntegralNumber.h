/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file CIntegralNumber.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/02
 *
 * Header file for concept CIntegralNumber.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CIntegralNumber_RECURSES)
#error Recursive header files inclusion detected in CIntegralNumber.h
#else // defined(CIntegralNumber_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CIntegralNumber_RECURSES

#if !defined CIntegralNumber_h
/** Prevents repeated inclusion of headers. */
#define CIntegralNumber_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class CIntegralNumber
  /**
Description of \b concept '\b CIntegralNumber' <p>
     @ingroup Concepts
     @brief Aim: Concept checking for Integral Numbers. Models of this
     concept should be listed in NumberTraits class and should have
     the isIntegral property.
     
 ### Refinement of 
    
 ### Associated types 
    
 ### Notation
     - \t X : A type that is a model of CIntegralNumber
     - \t x, \t y  : Object of type X
    
 ### Definitions
    
 ### Valid expressions and 
     <table>
     <tr> 
     <td class=CName> \b Name </td> 
     <td class=CExpression> \b Expression </td>
     <td class=CRequirements> \b Type requirements </td> 
     <td class=CReturnType> \b Return type </td>
     <td class=CPrecondition> \b Precondition </td> 
     <td class=CSemantics> \b Semantics </td> 
     <td class=CPostCondition> \b Postcondition </td> 
     <td class=CComplexity> \b Complexity </td>
     </tr>
     <tr> 
     <td class=CName>            \t X should be tagged \b true in \t NumberTraits for \t IsIntegral. </td>
     <td class=CExpression>      typename NumberTraits<X>::IsIntegral </td> 
     <td class=CRequirements>    TagTrue </td>
     <td class=CReturnType>      </td>
     <td class=CPrecondition>    </td> 
     <td class=CSemantics>       </td> 
     <td class=CPostCondition>   </td> 
     <td class=CComplexity>      </td>
     </tr>
     </table>
    
 ### Invariants###

    
 ### Models###
     double, BigInteger,  short, int, long long, int16_t, int32_t, int64_t.

 ### Notes###

@tparam T the type that is checked. T should be a model of
     CBoundedInteger.
    
   */
  template <typename T>
  struct CIntegralNumber
  {
    // ----------------------- Concept checks ------------------------------
  public:
    BOOST_CONCEPT_USAGE(CIntegralNumber)
    {
      // Will compile iff Integral.
      ConceptUtils::checkTrue( myIsIntegral );
    }
    
    // ------------------------- Internals ------------------------------------
  private:
    typename NumberTraits<T>::IsIntegral myIsIntegral;

  }; // end of concept CIntegralNumber
  
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CIntegralNumber_h

#undef CIntegralNumber_RECURSES
#endif // else defined(CIntegralNumber_RECURSES)
