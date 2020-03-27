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
/* Generated on Mon Mar  8 17:44:41 EST 1999 */

#include <fftw-int.h>
#include <fftw.h>

/* Generated by: ./genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -notwiddle 12 */

/*
 * This function contains 96 FP additions, 16 FP multiplications,
 * (or, 88 additions, 8 multiplications, 8 fused multiply/add),
 * 40 stack variables, and 48 memory accesses
 */
static const fftw_real K866025403 = FFTW_KONST(+0.866025403784438646763723170752936183471402627);
static const fftw_real K500000000 = FFTW_KONST(+0.500000000000000000000000000000000000000000000);

/*
 * Generator Id's : 
 * $Id: exprdag.ml,v 1.36 1999/02/19 17:22:11 athena Exp $
 * $Id: fft.ml,v 1.41 1999/02/19 17:22:13 athena Exp $
 * $Id: to_c.ml,v 1.24 1999/02/19 17:22:17 athena Exp $
 */

void fftw_no_twiddle_12(const fftw_complex *input, fftw_complex *output, int istride, int ostride)
{
     fftw_real tmp5;
     fftw_real tmp53;
     fftw_real tmp36;
     fftw_real tmp28;
     fftw_real tmp35;
     fftw_real tmp54;
     fftw_real tmp10;
     fftw_real tmp56;
     fftw_real tmp39;
     fftw_real tmp33;
     fftw_real tmp38;
     fftw_real tmp57;
     fftw_real tmp16;
     fftw_real tmp42;
     fftw_real tmp72;
     fftw_real tmp45;
     fftw_real tmp92;
     fftw_real tmp75;
     fftw_real tmp21;
     fftw_real tmp47;
     fftw_real tmp77;
     fftw_real tmp50;
     fftw_real tmp93;
     fftw_real tmp80;
     ASSERT_ALIGNED_DOUBLE();
     {
	  fftw_real tmp1;
	  fftw_real tmp2;
	  fftw_real tmp3;
	  fftw_real tmp4;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp1 = c_re(input[0]);
	  tmp2 = c_re(input[4 * istride]);
	  tmp3 = c_re(input[8 * istride]);
	  tmp4 = tmp2 + tmp3;
	  tmp5 = tmp1 + tmp4;
	  tmp53 = tmp1 - (K500000000 * tmp4);
	  tmp36 = K866025403 * (tmp3 - tmp2);
     }
     {
	  fftw_real tmp24;
	  fftw_real tmp25;
	  fftw_real tmp26;
	  fftw_real tmp27;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp24 = c_im(input[0]);
	  tmp25 = c_im(input[4 * istride]);
	  tmp26 = c_im(input[8 * istride]);
	  tmp27 = tmp25 + tmp26;
	  tmp28 = tmp24 + tmp27;
	  tmp35 = tmp24 - (K500000000 * tmp27);
	  tmp54 = K866025403 * (tmp25 - tmp26);
     }
     {
	  fftw_real tmp6;
	  fftw_real tmp7;
	  fftw_real tmp8;
	  fftw_real tmp9;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp6 = c_re(input[6 * istride]);
	  tmp7 = c_re(input[10 * istride]);
	  tmp8 = c_re(input[2 * istride]);
	  tmp9 = tmp7 + tmp8;
	  tmp10 = tmp6 + tmp9;
	  tmp56 = tmp6 - (K500000000 * tmp9);
	  tmp39 = K866025403 * (tmp8 - tmp7);
     }
     {
	  fftw_real tmp29;
	  fftw_real tmp30;
	  fftw_real tmp31;
	  fftw_real tmp32;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp29 = c_im(input[6 * istride]);
	  tmp30 = c_im(input[10 * istride]);
	  tmp31 = c_im(input[2 * istride]);
	  tmp32 = tmp30 + tmp31;
	  tmp33 = tmp29 + tmp32;
	  tmp38 = tmp29 - (K500000000 * tmp32);
	  tmp57 = K866025403 * (tmp30 - tmp31);
     }
     {
	  fftw_real tmp12;
	  fftw_real tmp13;
	  fftw_real tmp14;
	  fftw_real tmp15;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp12 = c_re(input[3 * istride]);
	  tmp13 = c_re(input[7 * istride]);
	  tmp14 = c_re(input[11 * istride]);
	  tmp15 = tmp13 + tmp14;
	  tmp16 = tmp12 + tmp15;
	  tmp42 = tmp12 - (K500000000 * tmp15);
	  tmp72 = K866025403 * (tmp14 - tmp13);
     }
     {
	  fftw_real tmp73;
	  fftw_real tmp43;
	  fftw_real tmp44;
	  fftw_real tmp74;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp73 = c_im(input[3 * istride]);
	  tmp43 = c_im(input[7 * istride]);
	  tmp44 = c_im(input[11 * istride]);
	  tmp74 = tmp43 + tmp44;
	  tmp45 = K866025403 * (tmp43 - tmp44);
	  tmp92 = tmp73 + tmp74;
	  tmp75 = tmp73 - (K500000000 * tmp74);
     }
     {
	  fftw_real tmp17;
	  fftw_real tmp18;
	  fftw_real tmp19;
	  fftw_real tmp20;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp17 = c_re(input[9 * istride]);
	  tmp18 = c_re(input[istride]);
	  tmp19 = c_re(input[5 * istride]);
	  tmp20 = tmp18 + tmp19;
	  tmp21 = tmp17 + tmp20;
	  tmp47 = tmp17 - (K500000000 * tmp20);
	  tmp77 = K866025403 * (tmp19 - tmp18);
     }
     {
	  fftw_real tmp78;
	  fftw_real tmp48;
	  fftw_real tmp49;
	  fftw_real tmp79;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp78 = c_im(input[9 * istride]);
	  tmp48 = c_im(input[istride]);
	  tmp49 = c_im(input[5 * istride]);
	  tmp79 = tmp48 + tmp49;
	  tmp50 = K866025403 * (tmp48 - tmp49);
	  tmp93 = tmp78 + tmp79;
	  tmp80 = tmp78 - (K500000000 * tmp79);
     }
     {
	  fftw_real tmp11;
	  fftw_real tmp22;
	  fftw_real tmp23;
	  fftw_real tmp34;
	  ASSERT_ALIGNED_DOUBLE();
	  tmp11 = tmp5 + tmp10;
	  tmp22 = tmp16 + tmp21;
	  c_re(output[6 * ostride]) = tmp11 - tmp22;
	  c_re(output[0]) = tmp11 + tmp22;
	  {
	       fftw_real tmp91;
	       fftw_real tmp94;
	       fftw_real tmp95;
	       fftw_real tmp96;
	       ASSERT_ALIGNED_DOUBLE();
	       tmp91 = tmp5 - tmp10;
	       tmp94 = tmp92 - tmp93;
	       c_re(output[3 * ostride]) = tmp91 - tmp94;
	       c_re(output[9 * ostride]) = tmp91 + tmp94;
	       tmp95 = tmp28 + tmp33;
	       tmp96 = tmp92 + tmp93;
	       c_im(output[6 * ostride]) = tmp95 - tmp96;
	       c_im(output[0]) = tmp95 + tmp96;
	  }
	  tmp23 = tmp16 - tmp21;
	  tmp34 = tmp28 - tmp33;
	  c_im(output[3 * ostride]) = tmp23 + tmp34;
	  c_im(output[9 * ostride]) = tmp34 - tmp23;
	  {
	       fftw_real tmp63;
	       fftw_real tmp83;
	       fftw_real tmp82;
	       fftw_real tmp84;
	       fftw_real tmp66;
	       fftw_real tmp70;
	       fftw_real tmp69;
	       fftw_real tmp71;
	       ASSERT_ALIGNED_DOUBLE();
	       {
		    fftw_real tmp61;
		    fftw_real tmp62;
		    fftw_real tmp76;
		    fftw_real tmp81;
		    ASSERT_ALIGNED_DOUBLE();
		    tmp61 = tmp36 + tmp35;
		    tmp62 = tmp39 + tmp38;
		    tmp63 = tmp61 - tmp62;
		    tmp83 = tmp61 + tmp62;
		    tmp76 = tmp72 + tmp75;
		    tmp81 = tmp77 + tmp80;
		    tmp82 = tmp76 - tmp81;
		    tmp84 = tmp76 + tmp81;
	       }
	       {
		    fftw_real tmp64;
		    fftw_real tmp65;
		    fftw_real tmp67;
		    fftw_real tmp68;
		    ASSERT_ALIGNED_DOUBLE();
		    tmp64 = tmp42 + tmp45;
		    tmp65 = tmp47 + tmp50;
		    tmp66 = tmp64 - tmp65;
		    tmp70 = tmp64 + tmp65;
		    tmp67 = tmp53 + tmp54;
		    tmp68 = tmp56 + tmp57;
		    tmp69 = tmp67 + tmp68;
		    tmp71 = tmp67 - tmp68;
	       }
	       c_im(output[ostride]) = tmp63 - tmp66;
	       c_im(output[7 * ostride]) = tmp63 + tmp66;
	       c_re(output[10 * ostride]) = tmp69 - tmp70;
	       c_re(output[4 * ostride]) = tmp69 + tmp70;
	       c_re(output[7 * ostride]) = tmp71 - tmp82;
	       c_re(output[ostride]) = tmp71 + tmp82;
	       c_im(output[10 * ostride]) = tmp83 - tmp84;
	       c_im(output[4 * ostride]) = tmp83 + tmp84;
	  }
	  {
	       fftw_real tmp41;
	       fftw_real tmp89;
	       fftw_real tmp88;
	       fftw_real tmp90;
	       fftw_real tmp52;
	       fftw_real tmp60;
	       fftw_real tmp59;
	       fftw_real tmp85;
	       ASSERT_ALIGNED_DOUBLE();
	       {
		    fftw_real tmp37;
		    fftw_real tmp40;
		    fftw_real tmp86;
		    fftw_real tmp87;
		    ASSERT_ALIGNED_DOUBLE();
		    tmp37 = tmp35 - tmp36;
		    tmp40 = tmp38 - tmp39;
		    tmp41 = tmp37 - tmp40;
		    tmp89 = tmp37 + tmp40;
		    tmp86 = tmp75 - tmp72;
		    tmp87 = tmp80 - tmp77;
		    tmp88 = tmp86 - tmp87;
		    tmp90 = tmp86 + tmp87;
	       }
	       {
		    fftw_real tmp46;
		    fftw_real tmp51;
		    fftw_real tmp55;
		    fftw_real tmp58;
		    ASSERT_ALIGNED_DOUBLE();
		    tmp46 = tmp42 - tmp45;
		    tmp51 = tmp47 - tmp50;
		    tmp52 = tmp46 - tmp51;
		    tmp60 = tmp46 + tmp51;
		    tmp55 = tmp53 - tmp54;
		    tmp58 = tmp56 - tmp57;
		    tmp59 = tmp55 + tmp58;
		    tmp85 = tmp55 - tmp58;
	       }
	       c_im(output[5 * ostride]) = tmp41 - tmp52;
	       c_im(output[11 * ostride]) = tmp41 + tmp52;
	       c_re(output[2 * ostride]) = tmp59 - tmp60;
	       c_re(output[8 * ostride]) = tmp59 + tmp60;
	       c_re(output[11 * ostride]) = tmp85 - tmp88;
	       c_re(output[5 * ostride]) = tmp85 + tmp88;
	       c_im(output[2 * ostride]) = tmp89 - tmp90;
	       c_im(output[8 * ostride]) = tmp89 + tmp90;
	  }
     }
}

fftw_codelet_desc fftw_no_twiddle_12_desc =
{
     "fftw_no_twiddle_12",
     (void (*)()) fftw_no_twiddle_12,
     12,
     FFTW_FORWARD,
     FFTW_NOTW,
     193,
     0,
     (const int *) 0,
};
