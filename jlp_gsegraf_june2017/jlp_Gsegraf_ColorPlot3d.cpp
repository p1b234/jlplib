/*******************************************************************************
*
* jlp_Gsegraf_ColorPlot3d.c
*
* Plots three-dimensional contour information as a function of color.
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
#include "jlp_gseg_axes.h"           // JLP_GsegAxes class
#include "jlp_gseg_data.h"           // JLP_GsegData class

/******************************************************************************
*
******************************************************************************/
void JLP_Gsegraf::ColorPlot3d(int iplot, int xindex, int yindex, 
                  int zindex, int nx, int ny)
{
/* Declare variables */
int width, height, quadrant;
int i, j, k, i11, i22, j11, j22, nxdata, nydata, nx_interp, ny_interp;
int ipixel, jpixel, index_colors, index_zi, ncoords;
UINT32 *colors;
double dev_x1_box, dev_x2_box, dev_y1_box, dev_y2_box, 
       xmin, xmax, ymin, ymax, zmin, zmax, rmin, rmax, radius;
double x, y, xscale, yscale, zscale, rscale, origin[3];
double xorigin, yorigin, *xcolor0, *ycolor0, *zcolor0;
double *xi, *yi, *zi, dx, dy, Ry[9], Rz[9], Ryz[9]; 
double *ppp, r[3], zscale2, fraction;
JLP_DPixbuf pixbuf_color;

// Get current plot settings
 jlp_gseg_axes1->GetBoxSettings(&dev_x1_box, &dev_x2_box, &dev_y1_box,
                                &dev_y2_box, &xmin, &xmax, &ymin, &ymax,
                                &zmin, &zmax, &rmin, &rmax, &xscale, &yscale,
                                &zscale, &rscale, &xorigin, &yorigin,
                                &radius, origin, Ry, Rz, Ryz, &ncoords);

 width  = roundint(dev_x2_box - dev_x1_box);
 height = roundint(dev_y2_box - dev_y1_box);

/* Find data indices in range */
 for ( i=1; i<=nx; i++ )
    if ( xmin <= jlp_gseg_data1->XColor(xindex+i-1) )
       {
       i11 = i;
       break;
       }

 for ( i=nx; i>=1; i-- )
    if ( jlp_gseg_data1->XColor(xindex+i-1) <= xmax )
       {
       i22 = i;
       break;
       }

 for ( j=1; j<=ny; j++ )
    if ( ymin <= jlp_gseg_data1->YColor(yindex+j-1) )
       {
       j11 = j;
       break;
       }

 for ( j=ny; j>=1; j-- )
    if ( jlp_gseg_data1->YColor(yindex+j-1) <= ymax )
       {
       j22 = j;
       break;
       }


/* Get interpolated values of x and y */
 nxdata = i22 - i11 + 1;
 nx_interp = ninterp[iplot-1]*(nxdata - 1) + 1;
 nydata = j22 - j11 + 1;
 ny_interp = ninterp[iplot-1]*(nydata - 1) + 1;
 xi = new double[nx_interp];
 yi = new double[ny_interp];
 zi = new double[nx_interp*ny_interp];

 xi[0] = jlp_gseg_data1->XColor(xindex+i11-1);
 for ( i=i11; i<i22; i++ )
    {
    dx = (jlp_gseg_data1->XColor(xindex+i) 
            - jlp_gseg_data1->XColor(xindex+i-1)) / ninterp[iplot-1];
    for ( k=1; k<=ninterp[iplot-1]; k++ )
       xi[ninterp[iplot-1]*(i-i11)+k] = jlp_gseg_data1->XColor(xindex+i-1) 
                                          + k*dx;
    }

 yi[0] = jlp_gseg_data1->YColor(yindex+j11-1);
 for ( j=j11; j<j22; j++ )
    {
    dy = (jlp_gseg_data1->YColor(yindex+j) 
            - jlp_gseg_data1->YColor(yindex+j-1))/ninterp[iplot-1];
    for ( k=0; k<ninterp[iplot-1]; k++ )
       yi[ninterp[iplot-1]*(j-j11)+k] = jlp_gseg_data1->YColor(yindex+j-1) 
                                          + k*dy;
    }


/* Get interpolated values of z (bilinear interpolation) */
 xcolor0 = jlp_gseg_data1->XColorPtr(xindex);
 ycolor0 = jlp_gseg_data1->YColorPtr(yindex);
 zcolor0 = jlp_gseg_data1->ZColorPtr(zindex);
 for ( i=1; i<=nx_interp; i++ )
    for ( j=1; j<=ny_interp; j++ )
       interp2(nx, ny, 1, xcolor0, ycolor0, zcolor0,
               &xi[i-1], &yi[j-1], &zi[ny_interp*(i-1)+(j-1)]);

/* Create color array */
 colors = new UINT32[width*height];
 for ( i=1; i<=width; i++ )
    for ( j=1; j<=height; j++ )
       colors[height*(i-1)+(j-1)] = 0xFFFFFF00;   /* transparent */

/* Calculate plot colors */
 zscale2 = 1.0/(zmax - zmin);
 if ( quadrant == 1 || quadrant == 4 )
    for ( i=1; i<=nx_interp; i++ )
       for ( j=1; j<=ny_interp; j++ )
          {
          r[0] = (xi[i-1] - xmin)*xscale;
          r[1] = (yi[j-1] - ymin)*yscale;
          r[2] = (zi[ny_interp*(i-1)+(j-1)] - zmin)*zscale;
          ppp = multiply_mv(Ryz, &r[0]);
          for ( k=1; k<=3; k++, ppp++ )
             r[k-1] = *ppp;
          ipixel = roundint(origin[1] + r[1] - dev_x1_box);
          jpixel = roundint(origin[2] - r[2] - dev_y1_box);

          index_colors = height*(ipixel - 1) + (jpixel - 1);
          if ( index_colors < 0 || index_colors > width*height )
             continue;

          index_zi = ny_interp*(i-1)+(j-1);
          fraction = (zi[index_zi] - zmin)*zscale2;
          if ( 0.0 <= fraction && fraction <= 1.0  )
             colors[index_colors] = interp_color_spectrum(fraction, 
                                    n_color_spectrum_1, color_spectrum_1) 
                                    - 0xFF + alphacolor[iplot-1];
          }

 else if ( quadrant == 2 || quadrant == 3 )
    for ( i=nx_interp; i>1; i-- )
       for ( j=1; j<=ny_interp; j++ )
          {
          r[0] = (xi[i-1] - xmin)*xscale;
          r[1] = (yi[j-1] - ymin)*yscale;
          r[2] = (zi[ny_interp*(i-1)+(j-1)] - zmin)*zscale;
          ppp = multiply_mv(Ryz, &r[0]);
          for ( k=1; k<=3; k++, ppp++ )
             r[k-1] = *ppp;
          ipixel = roundint(origin[1] + r[1] - dev_x1_box);
          jpixel = roundint(origin[2] - r[2] - dev_y1_box);

          index_colors = height*(ipixel - 1) + (jpixel - 1);
          if ( index_colors < 0 || index_colors > width*height )
             continue;

          index_zi = ny_interp*(i-1)+(j-1);
          fraction = (zi[index_zi] - zmin)*zscale2;
          if ( 0.0 <= fraction && fraction <= 1.0  )
             colors[index_colors] = interp_color_spectrum(fraction, 
                                    n_color_spectrum_1, color_spectrum_1) 
                                    - 0xFF + alphacolor[iplot-1];
          }

/* Allocate memory for the  pixbuf */
   GSEG_NewDPixbuf(&pixbuf_color, width, height);

/* Specify pixbuf colors */
   if ( quadrant == 1 )
      for ( i=1; i<=width; i++ )
         for ( j=1; j<=height; j++ )
            GSEG_PutPixelDPixbuf(&pixbuf_color, i-1, j-1, 
                                 colors[height*(i-1)+(j-1)]);
   else if ( quadrant == 2 )
      for ( i=width; i>=1; i-- )
         for ( j=1; j<=height; j++ )
            GSEG_PutPixelDPixbuf(&pixbuf_color, i-1, j-1, 
                                 colors[height*(i-1)+(j-1)]);
   else if ( quadrant == 3 )
      for ( i=width; i>=1; i-- )
         for ( j=height; j>=1; j-- )
            GSEG_PutPixelDPixbuf(&pixbuf_color, i-1, j-1, 
                                 colors[height*(i-1)+(j-1)]);
   else if ( quadrant == 4 )
      for ( i=1; i<=width; i++ )
         for ( j=height; j>=1; j-- )
            GSEG_PutPixelDPixbuf(&pixbuf_color, i-1, j-1, 
                                 colors[height*(i-1)+(j-1)]);


/* Draw pixbuf on canvas */
   x = (dev_x1_box + dev_x2_box)/2.0;
   y = (dev_y1_box + dev_y2_box)/2.0;
   jlp_gseg1->GSEG_DrawDPixbuf(&pixbuf_color, x, y, "CENTER");

/* Free memory */
 GSEG_FreeDPixbuf(&pixbuf_color);
 free(xi);
 free(yi);
 free(zi);
 free(colors);

 return;
}

