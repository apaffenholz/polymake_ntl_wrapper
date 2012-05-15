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
  $Project: lll $$Id: lattice.cc 188 2012-02-26 14:57:32Z paffenholz $
*/

#include "polymake/client.h"
#include "polymake/Matrix.h"
#include "polymake/Integer.h"
#include "polymake/common/tools.h"


namespace polymake { namespace polytope {


    UserFunctionTemplate4perl("# @category Lattice Polytopes"
			      "# returns the determinant of the lattice spanned by the rows of L"
			      "# assumes that the matrix has full column rank."
			      "# @param L  Matrix<int>"
			      "# @return int",
			      "lattice_determinant<E>(Matrix<E>)");
   

  }}
