/*******************************************************************************
*
* jlp_Gsegraf_ContourPlot2d.cpp
*
* Plots two-dimensional contour lines using contour lines of the same color or
* contour lines which vary in color.
*
* Copyright � 2008, 2009, 2010, 2011 Spencer A. Buckner
* http://savannah.gnu.org/projects/gsegrafix
*
* This file is part of GSEGrafix, a scientific and engineering plotting program.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* JLP
* Version 17/04/2017
*******************************************************************************/
#include <math.h>
#include "jlp_gsegraf.h"
#include "jlp_gseg_axes.h"         // JLP_GsegAxes class
#include "jlp_gseg_data.h"         // JLP_GsegData class

// #define DEBUG

/****************************************************************************
*
****************************************************************************/
void JLP_Gsegraf::ContourPlot2d(int iplot)
{
/* Declare variables */
int i, j, k, nx, ny, nzvalues, ncontours0; 
int width, height, nc, linewidth, style_flag0;
unsigned style_size0;
UINT32 style_color10, color, *color0 = NULL;
double dev_x1_box, dev_x2_box, dev_y1_box, dev_y2_box; 
double xmin, xmax, ymin, ymax, zmin, zmax,
       xscale, yscale, dz, x1, x2, y1, y2, fraction,
       dx1, dx2, dy1, dy2, *contours;
double *xi, *yi, *zi, x, y, dzdx, dzdy, dr, grad, dr0;
double xcontour_1, xcontour_2, ycontour_1, ycontour_2;
double *xcontour0, *ycontour0, *zcontour0;
JLP_DPixbuf pixbuf_contour;

/* Get plot box settings */
 jlp_gseg_axes1->GetBoxSettingsForLinear(&dev_x1_box, &dev_x2_box, &dev_y1_box,
                                         &dev_y2_box, &xmin, &xmax, &ymin,
                                         &ymax, &zmin, &zmax, &xscale, &yscale);


/* Get number of contour lines */
 jlp_gseg_axes1->GetNzValues(&nzvalues);
 ncontours0 = jlp_gseg_data1->NContours(iplot);
 if ( ncontours0 < 2 ) {
  nc = 2*nzvalues - 1;
  } else {
    nc = ncontours0;
  }
 contours = new double[nc];

#ifdef DEBUG
printf("ContourPlot2d/Debug nc=%d\n", nc);
#endif

/* Calculate contour-line values */
 for ( i=1; i<=nc; i++ )
    contours[i-1] = zmin + (i - 1)*(zmax - zmin)/(nc - 1);

// Style parameters:
 jlp_gseg_data1->GetStyleFlag(iplot, &style_flag0);
 jlp_gseg_data1->GetStyleSize(iplot, &style_size0);
 jlp_gseg_data1->GetStyleColor1(iplot, &style_color10);

#ifdef DEBUG
printf("ContourPlot2d/Debug : style_flag=%d, style_size=%d style_color10=%d\n", 
        style_flag0, style_size0, style_color10);
#endif

/* Contour plot with variable-color contour lines */
 if ( style_flag0 == 7 )
    {
/* Calculate contour-line colors */
    color0 = new UINT32[nc];
    for ( i=1; i<=nc; i++ ) {
      fraction = (double)(i - 1)/(double)(nc - 1);
/* alpha = 0xFF */
      color0[i-1] = interp_color_spectrum(fraction, n_color_spectrum_1,
                                           color_spectrum_1);
      }
/* Draw a scale bar, with labelled tick marks */
    jlp_gseg_axes1->DrawColorScale(2, color0, nc);
   }

/* Calculate pixbuf width and height */
   dx1 = 0.0;
   dx2 = 0.0;
   dy1 = 0.0;
   dy2 = 0.0;

   nx = jlp_gseg_data1->NXContour(iplot);
   ny = jlp_gseg_data1->NYContour(iplot);
   xcontour_1 = jlp_gseg_data1->XContour(iplot, 0);
   xcontour_2 = jlp_gseg_data1->XContour(iplot, nx - 1);
   ycontour_1 = jlp_gseg_data1->YContour(iplot, 0);
   ycontour_2 = jlp_gseg_data1->YContour(iplot, ny - 1);
#ifdef DEBUG
printf("ContourPlot2d/nx=%d ny=%d x1,x2,y1,y2 = %f %f %f %f\n", 
         nx, ny, xcontour_1, xcontour_2, ycontour_1, ycontour_2); 
#endif

   if ( xmin >= xcontour_1 )
      x1 = xmin;
   else
      {
      x1 = xcontour_1;
      dx1 = xcontour_1 - xmin;
      }

   if ( xmax <= xcontour_2 )
      x2 = xmax;
   else
      {
      x2 = xcontour_2;
      dx2 = xmax - xcontour_2;
      }

   if ( ymin >= ycontour_1 )
      y1 = ymin;
   else
      {
      y1 = ycontour_1;
      dy1 = ycontour_1 - ymin;
      }

   if ( ymax <= ycontour_2 )
      y2 = ymax;
   else
      {
      y2 = ycontour_2;
      dy2 = ymax - ycontour_2;
      }

   width  = roundint(dev_x2_box - dev_x1_box + 1.0 - (dx1 + dx2)*xscale);
   height = roundint(dev_y2_box - dev_y1_box + 1.0 - (dy1 + dy2)*yscale);


/* Check pixbuf width and height */
   if ( width <= 0 || height <= 0 ) {
     fprintf(stderr, "ContourPlot2d/Error: width=%d height=%d\n", width, height);
     return;
     }

/* Get interpolated values of x and y */
   xi = new double[width];
   yi = new double[height];
   zi = new double[width*height];
   for ( i=1; i<=width; i++ )
      xi[i-1] = x1 + (i - 1)*(x2 - x1)/(width - 1);
   for ( j=1; j<=height; j++ )
      yi[j-1] = y1 + (j - 1)*(y2 - y1)/(height - 1);


/* Get interpolated values of z (bilinear interpolation) */
   xcontour0 = jlp_gseg_data1->XContourPtr(iplot);
   ycontour0 = jlp_gseg_data1->YContourPtr(iplot);
   zcontour0 = jlp_gseg_data1->ZContourPtr(iplot);
   for ( i=1; i<=width; i++ )
      for ( j=1; j<=height; j++ )
         interp2(nx, ny, 1, xcontour0, ycontour0, 
                 zcontour0, &xi[i-1], &yi[j-1], 
                 &zi[height*(i-1)+(j-1)]);


/* Allocate memory for the  pixbuf */
   GSEG_NewDPixbuf(&pixbuf_contour, width, height);

/* style_flag=3 : contour plot with variable-color contour lines */
   if ( style_flag0 == 7 )
      {
      /* Draw contour lines */
      linewidth = style_size0;
      dr0 = (linewidth + 1.0)/2.0;
      for ( i=2; i<width; i++ )
         for ( j=height-1; j>1; j-- )
            {
            dzdx = (zi[height*(i)+(j-1)] - zi[height*(i-2)+(j-1)])/2.0;
            dzdy = (zi[height*(i-1)+(j)] - zi[height*(i-1)+(j-2)])/2.0;
            grad = sqrt(dzdx*dzdx + dzdy*dzdy);
            for ( k=1; k<=nc; k++ )
               {
               dz = fabs(zi[height*(i-1)+(j-1)] - contours[k-1]);
               dr = dz/grad;
               if ( dr <= dr0 - 1.0 )
                  {
/* alpha = 0xFF */
                  color = color0[k-1];
                  GSEG_PutPixelDPixbuf(&pixbuf_contour, i-1, height-j, color);
                  }
               else if ( dr <= dr0 )
                  {
/* alpha = (dr0 - dr)*0xFF */
                  color = color0[k-1] - (1 - dr0 + dr)*0xFF;
                  GSEG_PutPixelDPixbuf(&pixbuf_contour, i-1, height-j, color);
                  }
               }
            }
      }

/* style_flag=1 or 3: contour plot with constant-color contour lines */
   else if ( style_flag0 == 1 || style_flag0 == 3 )
      {
      /* Draw contour lines */
      linewidth = style_size0;
      dr0 = (linewidth + 1.0)/2.0;
      for ( i=2; i<width; i++ )
         for ( j=height-1; j>1; j-- )
            {
            dzdx = (zi[height*(i)+(j-1)] - zi[height*(i-2)+(j-1)])/2.0;
            dzdy = (zi[height*(i-1)+(j)] - zi[height*(i-1)+(j-2)])/2.0;
            grad = sqrt(dzdx*dzdx + dzdy*dzdy);
            for ( k=1; k<=nc; k++ )
               {
               dz = fabs(zi[height*(i-1)+(j-1)] - contours[k-1]);
               dr = dz/grad;
               if ( dr <= dr0 - 1.0 )
                  {
/* alpha = 0xFF */
                  color = style_color10;
                  GSEG_PutPixelDPixbuf(&pixbuf_contour, i-1, height-j, color);
                  }
               else if ( dr <= dr0 )
                  {
/* alpha = (dr0 - dr)*0xFF */
                  color = style_color10 - (1.0 - dr0 + dr)*0xFF;
                  GSEG_PutPixelDPixbuf(&pixbuf_contour, i-1, height-j, color);
                  }
               }
            }
      }


/* Draw pixbuf on canvas */
   x = dev_x1_box + dx1*xscale;
   y = dev_y2_box - dy1*yscale;
   jlp_gseg1->GSEG_DrawDPixbuf(&pixbuf_contour, x, y, "SOUTH_WEST");

/* Free memory */
GSEG_FreeDPixbuf(&pixbuf_contour);
free(contours);
if(color0 != NULL) free(color0);
free(xi);
free(yi);
free(zi);

return;
}
