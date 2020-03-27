/*
 * Copyright (c) 1997-1999 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Mar  8 17:44:57 EST 1999 */

#include <fftw-int.h>
#include <fftw.h>

/* Generated by: ./genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -notwiddleinv 7 */

/*
 * This function contains 60 FP additions, 36 FP multiplications,
 * (or, 60 additions, 36 multiplications, 0 fused multiply/add),
 * 22 stack variables, and 28 memory accesses
 */
static const fftw_real K222520933 = FFTW_KONST(+0.222520933956314404288902564496794759466355569);
static const fftw_real K900968867 = FFTW_KONST(+0.900968867902419126236102319507445051165919162);
static const fftw_real K623489801 = FFTW_KONST(+0.623489801858733530525004884004239810632274731);
static const fftw_real K433883739 = FFTW_KONST(+0.433883739117558120475768332848358754609990728);
static const fftw_real K974927912 = FFTW_KONST(+0.974927912181823607018131682993931217232785801);
static const fftw_real K781831482 = FFTW_KONST(+0.781831482468029808708444526674057750232334519);

/*
 * Generator Id's : 
 * $Id: exprdag.ml,v 1.36 1999/02/19 17:22:11 athena Exp $
 * $Id: fft.ml,v 1.41 1999/02/19 17:22:13 athena Exp $
 * $Id: to_c.ml,v 1.24 1999/02/19 17:22:17 athena Exp $
 */

void fftwi_no_twiddle_7(const fftw_complex *input, fftw_complex *output, int istride, int ostride)
{
     fftw_real tmp1;
     fftw_real tmp15;
     fftw_real tmp4;
     fftw_real tmp11;
     fftw_real tmp24;
     fftw_real tmp31;
     fftw_real tmp7;
     fftw_real tmp13;
     fftw_real tmp18;
     fftw_real tmp33;
     fftw_real tmp10;
     fftw_real tmp12;
     fftw_real tmp21;
     fftw_real tmp32;
     ASSERT_ALIGNED_DOUBLE();
     tmp1 = c_re(input[0]);
     tmp15 = c_im(input[0]);
     {
	  fftw_real tmp2;
	  fftw_real tmp3;
	  fftw_real tmp22;
	  fftw_real tmp23;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp2 = c_re(input[istride]);
	  tmp3 = c_re(input[6 * istride]);
	  tmp4 = tmp2 + tmp3;
	  tmp11 = tmp2 - tmp3;
	  tmp22 = c_im(input[istride]);
	  tmp23 = c_im(input[6 * istride]);
	  tmp24 = tmp22 + tmp23;
	  tmp31 = tmp23 - tmp22;
     }
     {
	  fftw_real tmp5;
	  fftw_real tmp6;
	  fftw_real tmp16;
	  fftw_real tmp17;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp5 = c_re(input[2 * istride]);
	  tmp6 = c_re(input[5 * istride]);
	  tmp7 = tmp5 + tmp6;
	  tmp13 = tmp5 - tmp6;
	  tmp16 = c_im(input[2 * istride]);
	  tmp17 = c_im(input[5 * istride]);
	  tmp18 = tmp16 + tmp17;
	  tmp33 = tmp17 - tmp16;
     }
     {
	  fftw_real tmp8;
	  fftw_real tmp9;
	  fftw_real tmp19;
	  fftw_real tmp20;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp8 = c_re(input[3 * istride]);
	  tmp9 = c_re(input[4 * istride]);
	  tmp10 = tmp8 + tmp9;
	  tmp12 = tmp8 - tmp9;
	  tmp19 = c_im(input[3 * istride]);
	  tmp20 = c_im(input[4 * istride]);
	  tmp21 = tmp19 + tmp20;
	  tmp32 = tmp20 - tmp19;
     }
     {
	  fftw_real tmp36;
	  fftw_real tmp35;
	  fftw_real tmp26;
	  fftw_real tmp27;
	  ASSERT_ALIGNED_DOUBLE();
	  c_re(output[0]) = tmp1 + tmp4 + tmp7 + tmp10;
	  tmp36 = (K781831482 * tmp31) + (K974927912 * tmp33) + (K433883739 * tmp32);
	  tmp35 = tmp1 + (K623489801 * tmp4) - (K900968867 * tmp10) - (K222520933 * tmp7);
	  c_re(output[6 * ostride]) = tmp35 - tmp36;
	  c_re(output[ostride]) = tmp35 + tmp36;
	  {
	       fftw_real tmp38;
	       fftw_real tmp37;
	       fftw_real tmp34;
	       fftw_real tmp30;
	       ASSERT_ALIGNED_DOUBLE();
	       tmp38 = (K433883739 * tmp31) + (K974927912 * tmp32) - (K781831482 * tmp33);
	       tmp37 = tmp1 + (K623489801 * tmp7) - (K222520933 * tmp10) - (K900968867 * tmp4);
	       c_re(output[4 * ostride]) = tmp37 - tmp38;
	       c_re(output[3 * ostride]) = tmp37 + tmp38;
	       tmp34 = (K974927912 * tmp31) - (K781831482 * tmp32) - (K433883739 * tmp33);
	       tmp30 = tmp1 + (K623489801 * tmp10) - (K900968867 * tmp7) - (K222520933 * tmp4);
	       c_re(output[5 * ostride]) = tmp30 - tmp34;
	       c_re(output[2 * ostride]) = tmp30 + tmp34;
	  }
	  c_im(output[0]) = tmp15 + tmp24 + tmp18 + tmp21;
	  tmp26 = (K781831482 * tmp11) + (K974927912 * tmp13) + (K433883739 * tmp12);
	  tmp27 = tmp15 + (K623489801 * tmp24) - (K900968867 * tmp21) - (K222520933 * tmp18);
	  c_im(output[ostride]) = tmp26 + tmp27;
	  c_im(output[6 * ostride]) = tmp27 - tmp26;
	  {
	       fftw_real tmp14;
	       fftw_real tmp25;
	       fftw_real tmp28;
	       fftw_real tmp29;
	       ASSERT_ALIGNED_DOUBLE();
	       tmp14 = (K433883739 * tmp11) + (K974927912 * tmp12) - (K781831482 * tmp13);
	       tmp25 = tmp15 + (K623489801 * tmp18) - (K222520933 * tmp21) - (K900968867 * tmp24);
	       c_im(output[3 * ostride]) = tmp14 + tmp25;
	       c_im(output[4 * ostride]) = tmp25 - tmp14;
	       tmp28 = (K974927912 * tmp11) - (K781831482 * tmp12) - (K433883739 * tmp13);
	       tmp29 = tmp15 + (K623489801 * tmp21) - (K900968867 * tmp18) - (K222520933 * tmp24);
	       c_im(output[2 * ostride]) = tmp28 + tmp29;
	       c_im(output[5 * ostride]) = tmp29 - tmp28;
	  }
     }
}

fftw_codelet_desc fftwi_no_twiddle_7_desc =
{
     "fftwi_no_twiddle_7",
     (void (*)()) fftwi_no_twiddle_7,
     7,
     FFTW_BACKWARD,
     FFTW_NOTW,
     121,
     0,
     (const int *) 0,
};
