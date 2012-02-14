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
 * @file ImageContainerBySTLMap.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/06/15
 *
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/13
 *
 * Header file for module ImageContainerBySTLMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageContainerBySTLMap_RECURSES)
#error Recursive header files inclusion detected in ImageContainerBySTLMap.h
#else // defined(ImageContainerBySTLMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageContainerBySTLMap_RECURSES

#if !defined ImageContainerBySTLMap_h
/** Prevents repeated inclusion of headers. */
#define ImageContainerBySTLMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <map>

#include "DGtal/base/Common.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/ConstRangeAdapter.h"
#include "DGtal/base/OutputIteratorAdapter.h"
#include "DGtal/base/CLabel.h"
#include "DGtal/kernel/domains/CDomain.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  // namespace details
  // {
  // ///////////////////////////////////////////////////////////////////////////
  // // Helper class
  //   /**
  //    * Class template for the comparison of the points.
  //    */
  //   struct PointComparator
  //   {
  //   /** 
  //    * comparator
  //    * 
  //    * @param p a first point
  //    * @param q a second point
  //    * @return 'true' if p < q, 'false' otherwise
  //    *
  //    * @tparam T a type of point
  //    */
  //     template < typename T >
  //     bool operator()(const T& p, const T& q) const 
  //     {
  // 	typename T::Dimension k = T::dimension - 1;
  // 	while (k >= 0)
  // 	  {
  // 	    if (p[k] < q[k]) return true; 
  // 	    if (p[k] > q[k]) return false; 
  // 	    ++k; 
  // 	  }
  // 	//each pair of coordinates are equal
  // 	return false; 
  //     }

  //   }; 
  // }

  /////////////////////////////////////////////////////////////////////////////
  // class ImageContainerBySTLMap
  /**
   * Description of class 'ImageContainerBySTLMap' <p>
   * Aim: Model of CImage implementing the association Point<->Value
   * using an STL map.
   *
   *
   * @see testImage.cpp
   */

  template <typename TDomain, typename TValue>
  class ImageContainerBySTLMap: 
    public map<typename TDomain::Point,TValue,/*details::PointComparator*/>
  {

  public:

    /// domain
    BOOST_CONCEPT_ASSERT(( CDomain<TDomain> ));
    typedef TDomain Domain;    
    typedef typename Domain::Point Point;
    typedef typename Domain::Vector Vector;
    typedef typename Domain::Integer Integer;
    typedef typename Domain::Size Size;
    typedef typename Domain::Dimension Dimension;

    /// static constants
    static const typename Domain::Dimension dimension = Domain::dimension;

    /// range of values
    BOOST_CONCEPT_ASSERT(( CLabel<TValue> ));
    typedef TValue Value;
    typedef ConstRangeAdapter<typename map<Point,Value>::const_iterator, 
			      Pair2nd<Value>, Value > ConstRange; 

    /// output iterator
    typedef OutputIteratorAdapter<typename map<Point,Value>::iterator,
				  Pair2ndMutator<Value>, Value > OutputIterator; 

    /////////////////// Data members //////////////////
  private: 

    /// Aliasing pointer on the image domain
    const Domain* myDomain;

    /// Functor used for returning only the value of any pair
    Pair2nd<Value> myInputF;

    /// Functor used to update the value of any pair
    Pair2ndMutator<Value> myOutputF;

    /// Default value
    Value myDefaultValue;

    /////////////////// standard services //////////////////

  public: 

    /** 
     * Constructor from a Domain
     * 
     * @param aDomain the image domain.
     * @param aValue a default value associated to the domain points
     * that are not contained in the underlying map.
     */
    ImageContainerBySTLMap(const Domain &aDomain, const Value& aValue = 0);


    /** 
     * Destructor.
     *
    */
    ~ImageContainerBySTLMap();

  
    /////////////////// Interface //////////////////

   
    /**
     * Get the value of an image at a given position given
     * by a Point.
     *
     * @pre the point must be in the domain
     *
     * @param aPoint the point.
     * @return the value at aPoint.
     */
    Value operator()(const Point & aPoint) const;

    /**
     * Set a value on an Image at a position specified by a Point.
     *
     * @pre @c it must be a point in the image domain.
     *
     * @param aPoint the point.
     * @param aValue the value.
     */
    void setValue(const Point &aPoint, const Value &aValue);
    

    /**
     * @return the domain associated to the image.
     */
    const Domain &domain() const; 

    /**
     * @return the range providing begin and end
     * iterators to scan the values of image.
     */
    ConstRange range() const;

    /**
     * @return an output iterator to write values.
     */
    OutputIterator output();
    
    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;


    /**
     * @return the validity of the Image
     */
    bool isValid() const;

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;


    /// built-in iterators
    typedef typename map<Point,Value>::iterator Iterator;
    typedef typename map<Point,Value>::const_iterator ConstIterator;
    typedef typename map<Point,Value>::reverse_iterator ReverseIterator;
    typedef typename map<Point,Value>::const_reverse_iterator ConstReverseIterator;
    ///\todo create span iterators
    class SpanIterator: public Iterator
    {
      friend class ImageContainerBySTLMap<TDomain,TValue>;

    public:
      SpanIterator( const Point & p ,
		    const Dimension aDim ,
		    ImageContainerBySTLMap<TDomain,TValue> *aMap ) :   
	myStartingPoint( p ),  myDimension ( aDim ),   myMap ( aMap )
      {
	myPos = myMap->find( p );
      }


      const Value & operator*() const
      {
	return (*myPos).second;
      }
      
      /**
       * Implements the next() method
       *
       **/
      void next()
      {
	while ((myPos != myMap->end()) && 
	       ( (*myPos).first.at(myDimension) != myStartingPoint.at(myDimension)))
	  {
	    myPos++;
	  }
      }

      /**
       * Implements the prev() method
       *
       **/
      void prev()
      {
	while ((myPos != myMap->end()) && 
	       ( (*myPos).first.at(myDimension) != myStartingPoint.at(myDimension)))
	  {
	    myPos--;
	  }
      }      

      /**
       * Operator ++ (++it)
       *
       */
      SpanIterator &operator++()
      {
	this->next();
	return *this;
      }

      /**
       * Operator ++ (it++)
       *
       */
      SpanIterator &operator++ ( int )
      {
	SpanIterator tmp = *this;
	++*this;
	return tmp;
      }


      /**
       * Operator -- (--it)
       *
       */
      SpanIterator &operator--()
      {
	this->prev();
	return *this;
      }

      /**
       * Operator -- (it--)
       *
       */
      SpanIterator &operator-- ( int )
      {
	SpanIterator tmp = *this;
	--*this;
	return tmp;
      }

    private:
      
      ///Copie of starting point
      Point myStartingPoint;
      
      ///Current  position in the built-in iterator
      Iterator myPos;

      /// Copy of the underlying images
      ImageContainerBySTLMap<TDomain,TValue> *myMap;

      ///Dimension on which the iterator must iterate
      Dimension myDimension;

    };

    SpanIterator span_begin(const Point &aPoint, const Dimension aDimension)
    {
      return SpanIterator ( aPoint, aDimension, this);
    }

    SpanIterator span_end(const Point &aPoint,const Dimension aDimension)
    {
      Point tmp = aPoint;
      tmp.at( aDimension ) = myDomain->lowerBound.at( aDimension ) +
	myDomain->upperBound.at( aDimension ) - 
	myDomain->lowerBound.at( aDimension ) + 1;
      return SpanIterator( tmp, aDimension, this);
    }

  };


  /**
   * Overloads 'operator<<' for displaying objects of class 'Image'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Image' to write.
   * @return the output stream after the writing.
   */
  template <typename TDomain, typename TValue>
  inline
  std::ostream&
  operator<< ( std::ostream & out, const ImageContainerBySTLMap<TDomain,TValue> & object )
  {
    object.selfDisplay ( out );
    return out;
  }


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions
#include "DGtal/images/ImageContainerBySTLMap.ih"
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageContainerBySTLMap_h

#undef ImageContainerBySTLMap_RECURSES
#endif // else defined(ImageContainerBySTLMap_RECURSES)
