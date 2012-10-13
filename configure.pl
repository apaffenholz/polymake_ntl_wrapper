#  Copyright (c) 1997-2012
#  Ewgenij Gawrilow, Michael Joswig (Technische Universitaet Darmstadt, Germany)
#  http://www.polymake.org
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by the
#  Free Software Foundation; either version 2, or (at your option) any
#  later version: http://www.gnu.org/licenses/gpl.txt.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#-------------------------------------------------------------------------------
# $Project: polymake $$Id: configure.pl.template 10887 2012-07-22 22:37:30Z gawrilow $


@make_vars=qw(  CXXflags LDflags Libs );

sub allowed_options {
   my ($allowed_options, $allowed_with)=@_;
   @$allowed_with{ qw( ntl ) }=();
}


sub usage {
   print STDERR "  --with-ntl=PATH to installation path of ntl library, if non-standard\n";
}


sub proceed {
   my ($options)=@_;
   my $ntl_path;
   if (defined ($ntl_path=$$options{ntl})) {
      my $ntl_inc="$ntl_path/include";
      my $ntl_lib=Polymake::Configure::get_libdir($ntl_path, "ntl");
      if (-f "$ntl_inc/NTL/ZZ.h" && -f "$ntl_lib/libntl.$Config::Config{dlext}" ) {
         $CXXflags="-I$ntl_inc";
         $LDflags="-L$ntl_lib -Wl,-rpath,$ntl_lib";
      } elsif (-f "$ntl_inc/NTL/ZZ.h" && -f "$ntl_lib/libntl.a" ) {
         $CXXflags="-I$ntl_inc";
         $LDflags="-L$ntl_lib";
      } else {
         die "Invalid installation location of ntl library: header file NTL/ZZ.h and/or library libntl.$Config::Config{dlext} / libntl.a not found\n";
      }

   } else {
      local $Polymake::Configure::Libs="-lntl -lgmp $Polymake::Configure::Libs";
      my $error=Polymake::Configure::build_test_program(<<'---');
#include "NTL/ZZ.h"
int main() {
    NTL::ZZ n;
    return 1;
}
---
      if ($?==0) {
         $error=Polymake::Configure::run_test_program();
         if ($?) {
            die "Could not run a test program checking for ntl library.\n",
                "The complete error log follows:\n$error\n\n",
                "Please investigate the reasons and fix the installation.\n";
         }
      } else {
         die "Could not compile a test program checking for ntl library.\n",
             "The most probable reasons are that the library is installed at a non-standard location,\n",
             "is not configured to build a shared module, or missing at all.\n",
             "The complete error log follows:\n$error\n\n",
             "Please install the library and specify its location using --with-ntl option, if needed.\n",
      }
   }

   $Libs="-lntl";
   return $ntl_path;
}
