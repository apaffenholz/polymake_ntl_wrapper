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
  $Project: lll $$Id: lll.cc 207 2012-03-27 14:14:17Z paffenholz $
*/

#include "polymake/client.h"
#include "polymake/Matrix.h"
#include "polymake/Integer.h"
#include "polymake/common/ntl_wrappers.h"


namespace polymake { namespace common {


    UserFunctionTemplate4perl("# @category Linear Algebra"
			      "# returns an LLL-reduced basis of the lattice spanned by the rows of L"
			      "# @param Matrix<int> L"
			      "# @return Matrix<int>",
			      "lll<E>(Matrix<E>)");

    UserFunctionTemplate4perl("# @category Linear Algebra" 
			      "# returns an LLL-reduced basis of the lattice spanned by the affine part of the rows of L"
			      "# assumes that the first column of L contains only ones."
			      "# @param  Matrix<int> L"
			      "# @return  Matrix<int>",
			      "lll_affine<E>(Matrix<E>)");


  }}
