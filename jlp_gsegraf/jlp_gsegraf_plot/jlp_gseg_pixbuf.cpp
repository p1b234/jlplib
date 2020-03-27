/*******************************************************************************
* jlp_pixbuf.cpp
*
* JLP_DPixbuf: data pixel buffer
* JLP_TPixbuf: text pixel buffer
*
* JLp
* version 26/11/2016
*******************************************************************************/
#include <math.h>
#include <string.h>
#include "jlp_gsegraf_defs.h"

/*****************************************************************************
* Allocate memory for a bitmap mask (called pixbuf by gnome)
*
* INPUT:
*  nx0 : width of mask array
*  ny0 : height of mask array
*****************************************************************************/
int GSEG_NewDPixbuf(JLP_DPixbuf *pixbuf0, int nx0, int ny0)
{
int i, isize;
 isize = nx0 * ny0;

pixbuf0->array = NULL;
if(isize < 0) return(-1);

 pixbuf0->array = new UINT32[isize];
 for(i = 0; i < isize; i++) pixbuf0->array[i] = 0.; 
 pixbuf0->nx = nx0;
 pixbuf0->ny = ny0;

return(0);
}
/*****************************************************************************
* Set the pixel value (color value) of a pixbuf array 
*
* INPUT:
*  nx0 : width of mask array
*  ny0 : height of mask array
*****************************************************************************/
int GSEG_PutPixelDPixbuf(JLP_DPixbuf *pixbuf0, int ix0, int iy0, UINT32 color0)
{
int ii, status = -1, nx0, ny0;

nx0 = pixbuf0->nx;
ny0 = pixbuf0->ny;

ii = ix0 + iy0 * nx0;
if(ii > 0 && ii < nx0 * ny0) {
  pixbuf0->array[ii] = color0;
  status = 0;
  }

return(status);
}
/*****************************************************************************
* Free memory for a bitmap mask (called pixbuf by gnome)
*
*****************************************************************************/
int GSEG_FreeDPixbuf(JLP_DPixbuf *pixbuf0)
{
int nx0, ny0;

nx0 = pixbuf0->nx;
ny0 = pixbuf0->ny;

if((nx0 != 0) || (ny0 != 0)) {
 delete[] pixbuf0->array;
 pixbuf0->nx = 0;
 pixbuf0->ny = 0;
 }
pixbuf0->array = NULL;

return(0);
}

/*****************************************************************************
* Copy data pixbuf structure 
*
*****************************************************************************/
int GSEG_CopyDPixbuf(JLP_DPixbuf *pixbuf0, JLP_DPixbuf *pixbuf1)
{

pixbuf1->nx = pixbuf0->nx;
pixbuf1->ny = pixbuf0->ny;
pixbuf1->array = pixbuf0->array;

return(0);
}
/*****************************************************************************
* Create a new text pixpuf 
*
*****************************************************************************/
int GSEG_NewTPixbuf(JLP_TPixbuf *pixbuf0, char *text0, const char *font_name0,
                    const double font_size0, const UINT32 color0)
{

strcpy(pixbuf0->text, text0);
strcpy(pixbuf0->font_name, font_name0);
pixbuf0->font_size = font_size0;
pixbuf0->color = color0;

return(0);
}
/*****************************************************************************
* Copy text pixbuf structure 
*****************************************************************************/
int GSEG_CopyTPixbuf(JLP_TPixbuf *pixbuf1, JLP_TPixbuf *pixbuf0)
{

 strcpy(pixbuf1->text, pixbuf0->text);
 strcpy(pixbuf1->font_name, pixbuf0->font_name);
 pixbuf1->font_size = pixbuf0->font_size;
 pixbuf1->color = pixbuf0->color;

return(0);
}
