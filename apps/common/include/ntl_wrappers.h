/*
  Copyright (c) 2010-12 Andreas Paffenholz
 
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2, or (at your option) any
  later version: http://www.gnu.org/licenses/gpl.txt.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
*/

#include "polymake/client.h"
#include "polymake/Matrix.h"
#include "polymake/Set.h"
#include "polymake/Integer.h"
#include "polymake/linalg.h"
#include "polymake/common/ntl_matrix.h"

namespace polymake { namespace common {

    //
    // integer kernel
    //

    /* computes the integer kernel of a list of row vectors v_1, ..., v_m, i.e.
       a basis of the space of all integer vectors w such that 
       w_1v_1+...*w_mv_m = 0

       if homogeneous is true then the space is restricted to all 
       integer vectors w such that additionally w_1+...+w_m = 0
     */
    template <typename E>
      inline
      typename pm::enable_if<Matrix<E>, std::numeric_limits<E>::is_integer>::type
      integer_kernel ( const Matrix<E> & L, bool homogeneous ) {
      NTL_matrix<E> mat;
      if ( homogeneous )
	mat = NTL_matrix<E>((ones_vector<E>(L.rows()))|L);
      else
	mat = NTL_matrix<E>(L);
      return mat.integer_kernel();
    }


    /* convenience function that computes the integer kernel of the affine 
       part of a list of rwo vectors (i.e. removes the leading 1 present in
       the properties LATTICE_POINTS and VERTICES of polymake)
    */
    template <typename E>
      inline
      typename pm::enable_if<Matrix<E>, std::numeric_limits<E>::is_integer>::type
      affine_integer_kernel ( const Matrix<E> & L ) {
      NTL_matrix<E> mat(L.minor(All,~scalar2set(0)));
      return mat.integer_kernel();
    }


    //
    // short lattice basis using LLL
    //

    template <typename E>
      inline
      typename pm::enable_if<Matrix<E>, std::numeric_limits<E>::is_integer>::type
      lll_affine ( const Matrix<E> & L ) {
      NTL_matrix<E> mat(L.minor(All,~scalar2set(0)));
      typename NTL_matrix<E>::lll_type lll_result = mat.lll();
      return (ones_vector<E>(lll_result.first)|lll_result.second.minor(range(L.rows()-lll_result.first,L.rows()-1),All));
    }

    template <typename E>
      inline
      typename pm::enable_if<Matrix<E>, std::numeric_limits<E>::is_integer>::type
      lll ( const Matrix<E> & L ) {
      NTL_matrix<E> mat(L);
      typename NTL_matrix<E>::lll_type lll_result = mat.lll();
      return (lll_result.second.minor(range(L.rows()-lll_result.first,L.rows()-1),All));
    }

    template <typename E>
      inline
      typename pm::enable_if<Matrix<E>, std::numeric_limits<E>::is_integer>::type
      HNF ( const Matrix<E> & A ) {

      if ( rank(A) != A.cols() )
	throw std::runtime_error("hermit_normal_form: matrix must have full column rank");

      NTL_matrix<E> mat(A);
      Set<int> basis = basis_rows(A);
      Integer determinant = abs(det(A.minor(basis,All)));
      return  mat.hermite_normal_form(determinant);
    }


    template <typename E>
      inline
      typename pm::enable_if<Matrix<E>, std::numeric_limits<E>::is_integer>::type
      HNF_affine ( const Matrix<E> & A ) {

      if ( rank(A.minor(All,~scalar2set(0))) != A.cols()-1 )
	throw std::runtime_error("hermit_normal_form_affine: matrix must have full column rank");


      NTL_matrix<E> mat(A.minor(All,~scalar2set(0)));
      Set<int> basis = basis_rows(A.minor(All,~scalar2set(0)));
      Integer determinant = abs(det(A.minor(basis,~scalar2set(0))));
      Matrix<E> result = ((ones_vector<E>(basis.size()))|mat.hermite_normal_form(determinant));
      return result;
    }



  }
}
