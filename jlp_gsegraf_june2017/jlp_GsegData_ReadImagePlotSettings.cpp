/*******************************************************************************
* jlp_GsegData_ReadImagePlotSettings.cpp
*
* Read the image parameters and the corresponding plot settings 
* from the parameter file.
*
* JLP
* Version 02/05/2017
*******************************************************************************/
#include "jlp_gseg_data.h"

/******************************************************************************
* INPUT:
*  param_filename: name of the plot parameter file
*  axis_type0 : "3d", etc
*
* OUTPUT:
*  image_filename : image filename
*  image_coords_flag[4] : "abs" or "rel"
*  text_image_anchor : "NORTH", "CENTER", etc
*  x_image, y_image, z_image
*******************************************************************************/
int JLP_GsegData::GetImagePlotSettings(char *image_filename0,
                                       char *image_coords_flag0,
                                       char *image_anchor_text0,
                                       double *x_image0, double *y_image0,
                                       double *z_image0)
{
int status = -1;
  if(image_filename1[0] != '\0') {
   strcpy(image_filename0, image_filename1);
   strcpy(image_anchor_text0, image_anchor_text1);
   strcpy(image_coords_flag0, image_coords_flag1);
   *x_image0 = x_image1;
   *y_image0 = y_image1;
   *z_image0 = z_image1;
   status = 0;
  }
return(status);
}
/******************************************************************************
* INPUT:
*  param_filename: name of the plot parameter file
*  axis_type0 : "3d", etc
*
* OUTPUT (to private variables) :
*  image_filename1 : image filename
*  image_coords_flag1[4] : "abs" or "rel"
*  image_anchor_text1 : "NORTH", "CENTER", etc
*  x_image, y_image, z_image
*******************************************************************************/
int JLP_GsegData::ReadImagePlotSettingsFromFile(char *param_filename, 
                                            char *axis_type0)
{
int i, status = -1; 
unsigned int i1_str, i2_str, size;
double xanchor, yanchor, window_coords[2];
char *string, input_anchor[10]; 
char line1[256], fname_test[128];
FILE *fptr, *fptr_image;

image_filename1[0] = '\0';
x_image1 = 0.;
y_image1 = 0.;
z_image1 = 0.;

/* Get image filename */
   fptr = fopen(param_filename, "r");
   while ( fgets(line1, 256, fptr) != NULL )
      {
      /* Get image filename */
      if ( strncmp(line1, "image_filename", 14) == 0 )
         {
         size = strlen(&line1[14]);
         if((string = gseg_get_string(string_get, &line1[14], &i1_str, &i2_str, 
                                 &size, 0)) 
             != NULL)
            {
            strcpy(fname_test, string);
// Check validity of filename by opening it and closing it aftwerwards
            if ( (fptr_image = fopen(fname_test, "r")) != NULL ) 
              {
               strcpy(image_filename1, fname_test);
               status = 0;
               fclose(fptr_image);
              }
            else
               {
               size = strlen("Cannot open image file:\n") 
                      + strlen(fname_test);
               string = new char[size + 1];
               sprintf(string, "%s%s", "Cannot open image file:\n", 
                       fname_test);
               JLP_ErrorDialog(string);
               delete[] string;
               return(-1);
               }
            }

/* Get image coordinates and input_anchor */
         memset(image_coords_flag1, 0, sizeof(image_coords_flag1));
         for ( i=1; i<=2; i++ )
            if ( fgets(line1, 256, fptr) != NULL )
               {
               if ( strncmp(line1, "image_coords_abs", 16) == 0 ||
                    strncmp(line1, "image_coords_rel", 16) == 0 )
                  {
                  if ( (strcmp(axis_type0, "3d") != 0 &&
                        strncmp(line1, "image_coords_abs", 16) == 0 &&
                        sscanf(&line1[16], "%lf %lf", &x_image1,
                               &y_image1) == 2) ||
                       (strcmp(axis_type0, "3d") == 0 &&
                        strncmp(line1, "image_coords_abs", 16) == 0 &&
                        sscanf(&line1[16], "%lf %lf %lf", 
                               &x_image1, &y_image1, &z_image1) == 3) ||
                       (strncmp(line1, "image_coords_rel", 16) == 0 &&
                        sscanf(&line1[16], "%lf %lf", &x_image1, 
                               &y_image1) == 2) )
                     {
                     strncpy(image_coords_flag1, &line1[13], 3);
                     } 
                 else
                     {
                     size = strlen("Invalid or incomplete image coordinates for image file:\n") +
                            strlen(image_filename1);
                     string = new char[size + 1];
                     sprintf(string, "%s%s",
                             "Invalid or incomplete image coordinates for image file:\n",
                             image_filename1);
                     JLP_ErrorDialog(string);
                     delete[] string;
                     exit(1);
                     }
                  }

               else if ( strncmp(line1, "image_anchor", 12) == 0 )
                  {
                  memset(input_anchor, 0, sizeof(input_anchor));
                  size = strlen(&line1[12]);
                  if((string = gseg_get_string(string_get, &line1[12], &i1_str, 
                                          &i2_str, &size, 0)) != NULL )
                     {
                     strncpy(&input_anchor[0], string, 9);
                     }
                  else
                     {
                     size = strlen("Image anchor not found for image file:\n") +
                                   strlen(image_filename1);
                     string = new char[size + 1];
                     sprintf(string, "%s %s",
                       "Fatal error: image anchor not found for image file:\n", 
                             image_filename1);
                     JLP_ErrorDialog(string);
                     delete[] string;
                     exit(1);
                     }
                  }
               else
                  {
                  size = strlen("Image coordinates or image anchor not found for image file:\n") +
                                strlen(image_filename1);
                  string = new char[size + 1];
                  sprintf(string, "%s%s",
                   "Fatal error: image coordinates or image anchor not found for image file:\n", 
                         image_filename1);
                  JLP_ErrorDialog(string);
                  delete[] string;
                  exit(1);
                  }
               }

         }

      else if ( strncmp(line1, "#####", 5) == 0 )
         break;
      }

fclose(fptr);

/* Define the image anchor */
  if(status == 0) {
   if ( strcmp(input_anchor, "center") == 0 )
      strcpy(image_anchor_text1, "CENTER");
   else if ( strcmp(input_anchor, "north") == 0 )
      strcpy(image_anchor_text1, "NORTH");
   else if ( strcmp(input_anchor, "northeast") == 0 )
      strcpy(image_anchor_text1, "NORTH_EAST");
   else if ( strcmp(input_anchor, "east") == 0 )
      strcpy(image_anchor_text1, "EAST");
   else if ( strcmp(input_anchor, "southeast") == 0 )
      strcpy(image_anchor_text1, "SOUTH_EAST");
   else if ( strcmp(input_anchor, "south") == 0 )
      strcpy(image_anchor_text1, "SOUTH");
   else if (strcmp(input_anchor, "southwest") == 0 )
      strcpy(image_anchor_text1, "SOUTH_WEST");
   else if ( strcmp(input_anchor, "west") == 0 )
      strcpy(image_anchor_text1, "WEST");
   else if ( strcmp(input_anchor, "northwest") == 0 )
      strcpy(image_anchor_text1, "NORTH_WEST");
   else
      {
      size = strlen("Invalid image anchor for image file:\n") +
             strlen(image_filename1);
      string = new char[size + 1];
      sprintf(string, "%s%s",
              "Fatal error: invalid image anchor for image file:\n", 
              image_filename1);
      JLP_ErrorDialog(string);
      delete[] string;
      exit(1);
      }
  }

return(status);
}
