/*
  Copyright (c) 2010-14 Andreas Paffenholz
 
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
#include "polymake/Integer.h"
#include "polymake/common/ntl_matrix.h"
#include "polymake/common/ntl_wrappers.h"

namespace polymake { namespace common {

    UserFunctionTemplate4perl("# @category Lattice Polytopes"
			      "# returns the non-zero part of the hermite normal form"
			      "# the (n x m) input matrix must have full rank m, so n>=m"
			      "# @param Matrix A"
			      "# @return Matrix",
			      "HNF<E>(Matrix<E>)");

    UserFunctionTemplate4perl("# @category Lattice Polytopes"
			      "# returns the non-zero part of the hermite normal form of the affine part of the input"
			      "# the (n x (m+1)) input matrix must have full rank m, so n>=m"
			      "# @param Matrix A"
			      "# @return Matrix",
			      "HNF_affine<E>(Matrix<E>)");


  }}


