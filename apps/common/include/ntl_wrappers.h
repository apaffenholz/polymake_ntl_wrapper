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
-------------------------------------------------------------------------------
  $Project: lll $$Id: ntl_wrappers.h 209 2012-04-11 13:34:21Z paffenholz $
*/

#include "polymake/client.h"
#include "polymake/Matrix.h"
#include "polymake/Set.h"
#include "polymake/Integer.h"
#include "polymake/linalg.h"
#include "polymake/common/ntl_matrix.h"

namespace polymake { namespace common {

    template <typename E>
      inline
      typename pm::enable_if<Matrix<E>, std::numeric_limits<E>::is_integer>::type
      integer_kernel ( const Matrix<E> & L, bool homogeneous ) {
      NTL_matrix<E> mat;
      if ( homogeneous )
	mat = NTL_matrix<E>(ones_vector<E>(L.cols())|T(L));
      else
	mat = NTL_matrix<E>(T(L));
      return mat.integer_kernel();
    }


    template <typename E>
      inline
      typename pm::enable_if<Matrix<E>, std::numeric_limits<E>::is_integer>::type
      affine_integer_kernel ( const Matrix<E> & L ) {
      NTL_matrix<E> mat(T(L.minor(All,~scalar2set(0))));
      Matrix<E> IK = mat.integer_kernel();
      return (ones_vector<E>(IK.rows())|IK);
    }



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
      hermite_normal_form ( const Matrix<E> & A ) {

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
      hermite_normal_form_affine ( const Matrix<E> & A ) {

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
