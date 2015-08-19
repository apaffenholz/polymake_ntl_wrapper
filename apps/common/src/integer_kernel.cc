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
  $Project: lll $$Id: integer_kernel.cc 188 2012-02-26 14:57:32Z paffenholz $
*/

#include "polymake/client.h"
#include "polymake/Matrix.h"
#include "polymake/Integer.h"
#include "polymake/common/ntl_matrix.h"
#include "polymake/common/ntl_wrappers.h"

namespace polymake { namespace common {

    UserFunctionTemplate4perl("# @category Linear Algebra"
			      "# returns an the integer kernel of the rows of L"
			      "# @param Matrix L"
			      "# @return Matrix",
			      "integer_kernel<E>(Matrix<E>; $ = 0 )");


    UserFunctionTemplate4perl("# @category Linear Algebra"
			      "# returns an the integer kernel of the rows of L, assuming that L is a set of homogeneous points"
			      "# @param Matrix L"
			      "# @return Matrix",
			      "affine_integer_kernel<E>(Matrix<E>)");

  }}


