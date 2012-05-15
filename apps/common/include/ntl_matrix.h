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
  $Project: lll $$Id: ntl_matrix.h 193 2012-02-29 08:54:37Z paffenholz $
*/

#ifndef POLYMAKE_EXTENSION_LLL_NTL_GRAPH_H
#define POLYMAKE_EXTENSION_LLL_NTL_GRAPH_H

#include <polymake/Matrix.h>
#include <polymake/Integer.h>

#include <NTL/LLL.h>
#include <NTL/HNF.h>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/vec_vec_ZZ.h>


NTL_CLIENT

namespace polymake { namespace common {

    template <typename E>
    class NTL_matrix {
    public: 
      NTL_matrix ( const Matrix<E> & M );
      NTL_matrix ( const mat_ZZ & NTL_M ) : mat(NTL_M) {};
      NTL_matrix () : mat() {};
      ~NTL_matrix() { }
      NTL_matrix& operator= ( const NTL_matrix& other ) { 
	if ( *this != other ) {
	  mat = other.value();
	}
	return *this;
      }

      const NTL::mat_ZZ value() const { return mat; }
      NTL::mat_ZZ value() { return mat; }

      typedef std::pair<int,Matrix<E> > lll_type;

      lll_type lll();
      Matrix<E> integer_kernel();
      Matrix<E> hermite_normal_form( Integer det);
      Matrix<E> to_pm_Matrix ();

    private:
      NTL::mat_ZZ mat;


    public:
      // conversions between polymake numbers and NTL numbers

      // FIXME this is not really a clever conversion...
      // FIXME there should be a better way to do this.
      static inline Integer& to_Integer ( Integer& a, const ZZ& NTLInteger ){ 

	long nbytes = NumBytes(NTLInteger);
	unsigned char* bytes;
	Integer base(256);
	
	bool negative = false;
	if ( sign( NTLInteger ) < 0 )
	  negative  = true;
	
	bytes = new unsigned char[ (size_t)nbytes ];
	BytesFromZZ(bytes, NTLInteger, nbytes);
	
	a = Integer(0);      
	for( long i = nbytes - 1; i >= 0; --i ) {
	  a *= base;
	  a += Integer(bytes[i]);
	}
	if ( negative ) a *= -1;
	
	delete [] bytes;		
	return a;
      }
      
      static inline int to_int ( const ZZ& NTLInteger ) { 
	int n = NTL::to_int( NTLInteger );
	return n;
      }
      
    }; // class NTL_matrix
    


    // conversions from polymake to NTL

    template<>
    inline
    NTL_matrix<int>::NTL_matrix ( const Matrix<int> & M ) {
      int r = M.rows();
      int c = M.cols();
      mat.SetDims(r,c);

      for ( int i = 0; i < r; ++i ) 
	for ( int j = 0; j < c; ++j ) {
	  NTL::ZZ a = NTL::to_ZZ(M(i,j)); 
	  mat[i][j] = a;
	}
    }

    // construct NTL matrix from a polymake Integer matrix
    // FIXME this is done via conversion to string
    // FIXME I didn't find anything more efficient
    template <>
    inline
    NTL_matrix<Integer>::NTL_matrix ( const Matrix<Integer> & M ) {
      int r = M.rows();
      int c = M.cols();
      mat.SetDims(r,c);

      for ( int i = 0; i < r; ++i ) 
	for ( int j = 0; j < c; ++j ) {
	  NTL::ZZ a = to_ZZ(M(i,j).to_string().c_str());
	  mat[i][j] = a;
	}
    }


    // conversions from NTL to polymake
    template<>
    inline
    Matrix<int> NTL_matrix<int>::to_pm_Matrix () {      
      Matrix<int> M(mat.NumRows(),mat.NumCols());
      for ( int i = 0; i < mat.NumRows(); ++i ) 
	for ( int j = 0; j < mat.NumCols(); ++j ) 
	  M(i,j) = NTL::to_int(mat[i][j]);
      return M;
    }

    template<>
    inline
    Matrix<Integer> NTL_matrix<Integer>::to_pm_Matrix () {      
      Matrix<Integer> M(mat.NumRows(),mat.NumCols());
      for ( int i = 0; i < mat.NumRows(); ++i ) 
	for ( int j = 0; j < mat.NumCols(); ++j ) 
	  M(i,j) = to_Integer(M(i,j),mat[i][j]);
      return M;
    }


    // apply the lll algorithm to mat, return the rank
    // FIXME note: transforms the matrix
    template<typename E>
      inline typename NTL_matrix<E>::lll_type NTL_matrix<E>::lll () {
      ZZ det2;
      NTL::mat_ZZ LLL(mat);
      long r = NTL::LLL(det2,LLL);
      lll_type lll_result;
      lll_result.first = r;
      lll_result.second = NTL_matrix<E>(LLL).to_pm_Matrix();
      return lll_result;
    }

    // computes the Hermit normal form of the matrix mat
    template<typename E>
    inline Matrix<E> NTL_matrix<E>::hermite_normal_form ( Integer determinant ) {
      NTL::mat_ZZ HNF;
      NTL::HNF(HNF,mat,to_ZZ(determinant.to_string().c_str()));
      return NTL_matrix<E>(HNF).to_pm_Matrix();
    }


    // integral row dependencies
    template<typename E>
    inline Matrix<E> NTL_matrix<E>::integer_kernel () {
      NTL::mat_ZZ U,B;
      NTL::mat_ZZ Cmat(mat);
      NTL::ZZ det2;

      int m = Cmat.NumRows();
      long r = NTL::image(det2,Cmat,U);

      B.SetDims(m-r,m);

      for (long i = 1; i <= m-r; i++) 
	for (long j = 1; j <= m; j++) 
	  B(i,j) = U(i,j);

      return NTL_matrix<E>(B).to_pm_Matrix();
    }


    template <typename E>
    bool operator== ( const NTL_matrix<E>& m1, const NTL_matrix<E>& m2 ) {
      return m1.value() == m2.value();
    }

    template <typename E>
    bool operator!= ( const NTL_matrix<E>& m1, const NTL_matrix<E>& m2 ) {
      return !(m1 == m2);
    }

    
  }
}

#endif // POLYMAKE_EXTENSION_LLL_NTL_GRAPH_H
