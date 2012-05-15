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
  $Project: lll $$Id: tools.h 190 2012-02-26 22:51:05Z paffenholz $
*/

#include "polymake/client.h"
#include "polymake/Matrix.h"
#include "polymake/Vector.h"
#include "polymake/Set.h"
#include "polymake/Integer.h"
#include "polymake/Rational.h"
#include "polymake/PowerSet.h"
#include "polymake/linalg.h"

namespace polymake { namespace common {

    template <typename E>
      typename pm::enable_if<E, std::numeric_limits<E>::is_integer>::type
      lattice_determinant ( const Matrix<E> & M ) {
      
      int r = M.cols();
      if (rank(M) != r ) throw std::runtime_error("lattice_determinant: matrix needs full column rank");

      Integer g(0);
      for (Entire< Subsets_of_k<const sequence&> >::const_iterator i=entire(all_subsets_of_k(sequence(0,M.rows()),r)); !i.at_end(); ++i) 
	g = gcd(g,abs(det(M.minor(*i,All))));
      
      return g;
    }

  }}
