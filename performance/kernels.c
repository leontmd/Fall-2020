/*******************************************
 * Solutions for the CS:APP Performance Lab
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

#define RIN(i,n) (i*n)
#define RINJ(rin,j) (rin+j)

/* 
 * Please fill in the following student struct 
 */
student_t student = {
  "Skylar Shyu",     /* Full name */
  "skylar.shyu@utah.edu",  /* Email address */
};

/***************
 * COMPLEX KERNEL
 ***************/

/******************************************************
 * Your different versions of the complex kernel go here
 ******************************************************/

/* 
 * naive_complex - The naive baseline version of complex 
 */
char naive_complex_descr[] = "naive_complex: Naive baseline implementation";
void naive_complex(int dim, pixel *src, pixel *dest)
{
  int i, j;

  for(i = 0; i < dim; i++)
    for(j = 0; j < dim; j++)
    {

      dest[RIDX(dim - j - 1, dim - i - 1, dim)].red = ((int)src[RIDX(i, j, dim)].red +
						      (int)src[RIDX(i, j, dim)].green +
						      (int)src[RIDX(i, j, dim)].blue) / 3;
      
      dest[RIDX(dim - j - 1, dim - i - 1, dim)].green = ((int)src[RIDX(i, j, dim)].red +
							(int)src[RIDX(i, j, dim)].green +
							(int)src[RIDX(i, j, dim)].blue) / 3;
      
      dest[RIDX(dim - j - 1, dim - i - 1, dim)].blue = ((int)src[RIDX(i, j, dim)].red +
						       (int)src[RIDX(i, j, dim)].green +
						       (int)src[RIDX(i, j, dim)].blue) / 3;

    }
}


char complex_descr[] = "Blocking attempt";
void complex(int dim, pixel *src, pixel *dest)
{
  int i, j, ii, jj, W;
  if (dim > 255)
    W = 32;
  else
    W = 16;
  for(i = 0; i < dim; i+=W)
    {
      int dim_1 = dim-1;
      //int dim_i_1 = dim_1 - i;
      for(j = 0; j < dim; j+=W)
	    {
        for(ii = i; ii < i+W; ii++)
        {
          //int iiXdim = ii * dim;
          int dim_1_ii = dim_1 - ii;

          for(jj = j; jj < j+W; jj++)
          {
            int source_int = RIDX(jj, ii, dim);
            int destination_int = RIDX(dim_1_ii, dim_1 - jj, dim); 
            unsigned short sumdivthree = (src[source_int].red + src[source_int].green + src[source_int].blue) / 3;
            dest[destination_int].red = sumdivthree;
            dest[destination_int].green = sumdivthree;
            dest[destination_int].blue = sumdivthree;
            /*
            source = *(src + RIDX(jj + 1, ii, dim));
            destination = (dest + RIDX(dim_1_ii, dim_1 - jj - 1, dim));
            sumdivthree = (source.red + source.green + source.blue) / 3;
            destination->red = sumdivthree;
            destination->green = sumdivthree;
            destination->blue = sumdivthree;*/
          }
        }
      
      }
    }
}
/*
char current_complex_descr[] = "current_complex: trying to unroll";
void current_complex(int dim, pixel *src, pixel *dest)
{
  int i, j;
  for(i = 0; i < dim; i++)
    {
      int dim_1 = dim - 1;
      int dim_i_1 = dim_1 - i;

      for(j = 0; j < dim - 1; j+=2)
	    {
        
        pixel source = *(src + RIDX(i, j, dim));
        pixel* destination = (dest + RIDX(dim_1 - j, dim_i_1, dim));
        unsigned short sumdivthree = (source.red + source.green + source.blue) / 3;
        destination->red = sumdivthree;
        destination->green = sumdivthree;
        destination->blue = sumdivthree;
        
        source = *(src + RIDX(i, j + 1, dim));
        destination = (dest + RIDX(dim_1 - j - 1, dim_i_1, dim));
        sumdivthree = (source.red + source.green + source.blue) / 3;
        destination->red = sumdivthree;
        destination->green = sumdivthree;
        destination->blue = sumdivthree;
      }
    }
}
*/

/*
char complex_descr[] = "code motion, strength reduction, etc. etc.";
void complex(int dim, pixel *src, pixel *dest)
{
  int i,j;
  
  int dimSubOne = dim - 1;
  for(i = 0; i < dim; i++)
    {
      int idRIDX = RIN(i,dim);
      int dimSubOneAndi = dimSubOne - i;

      for(j = 0; j < dim; j++)
	    {
        int dimSubOneAndj = dimSubOne - j;
        int idSubOneRIDX = RIN(dimSubOneAndj, dim);
        int ijdSubOneRIDX = RINJ(idSubOneRIDX, dimSubOneAndi);
        int ijdRIDX = RINJ(idRIDX,j);
        pixel source = *(src + ijdRIDX); //red pixel
        int sumdivthree = (int)(source.red + source.green + source.blue) / 3;
        pixel *destination = (dest + ijdSubOneRIDX);
        destination->red = sumdivthree;
        destination->green = sumdivthree;
        destination->blue = sumdivthree;
      }
    }
}
*/

/*********************************************************************
 * register_complex_functions - Register all of your different versions
 *     of the complex kernel with the driver by calling the
 *     add_complex_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_complex_functions() {
  //add_complex_function(&current_complex, current_complex_descr);
  //add_complex_function(&blocking_complex, blocking_complex_descr);
  // add_complex_function(&complex2, complex2_descr);
  add_complex_function(&complex, complex_descr);
  //add_complex_function(&naive_complex2, naive_complex_descr2);
  add_complex_function(&naive_complex, naive_complex_descr);
}


/***************
 * MOTION KERNEL
 **************/

/***************************************************************
 * Various helper functions for the motion kernel
 * You may modify these or add new ones any way you like.
 **************************************************************/

__attribute__((always_inline))static pixel weighted_combo(int dim, int i, int j, pixel *src)
{
  int ii, jj;
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;
  int num_neighbors = 0;

  
  for(ii=0; ii < 3; ii++)
    for(jj=0; jj < 3; jj++)
      if ((i + ii < dim) && (j + jj < dim))
	      {
	        num_neighbors++;
          red += (int) src[RIDX(i+ii,j+jj,dim)].red;
          green += (int) src[RIDX(i+ii,j+jj,dim)].green;
          blue += (int) src[RIDX(i+ii,j+jj,dim)].blue;
	      }
  
  current_pixel.red = (unsigned short) (red / num_neighbors);
  current_pixel.green = (unsigned short) (green / num_neighbors);
  current_pixel.blue = (unsigned short) (blue / num_neighbors);

  return current_pixel;
}

/*
[  |  |  ]
[  |  |  ]
[  |  |  ]
*/
__attribute__((always_inline))static pixel okayCombo(int dim, int i, int j, pixel *src)
{
  pixel current_pixel;

  int red, green, blue;
  red = green = blue = 0;
  int num_neighbors = 9;

  int iXn = i * dim;
  int iXnJ = iXn + j;
  int iXnJ1 = iXn + j + 1;
  int iXnJ2 = iXn + j + 2;

  int i2Xn = (i+1) * dim;
  int i2XnJ = i2Xn + j;
  int i2XnJ1 = i2Xn + j + 1;
  int i2XnJ2 = i2Xn + j + 2;

  int i3Xn = (i+2) * dim;
  int i3XnJ = i3Xn + j;
  int i3XnJ1 = i3Xn + j + 1;
  int i3XnJ2 = i3Xn + j + 2;

  red += (int)src[iXnJ].red;
  green += (int)src[iXnJ].green;
  blue += (int)src[iXnJ].blue;

  red += (int)src[iXnJ1].red;
  green += (int)src[iXnJ1].green;
  blue += (int)src[iXnJ1].blue;

  red += (int)src[iXnJ2].red;
  green += (int)src[iXnJ2].green;
  blue += (int)src[iXnJ2].blue;

  red += (int)src[i2XnJ].red;
  green += (int)src[i2XnJ].green;
  blue += (int)src[i2XnJ].blue;

  red += (int)src[i2XnJ1].red;
  green += (int)src[i2XnJ1].green;
  blue += (int)src[i2XnJ1].blue;

  red += (int)src[i2XnJ2].red;
  green += (int)src[i2XnJ2].green;
  blue += (int)src[i2XnJ2].blue;

  red += (int)src[i3XnJ].red;
  green += (int)src[i3XnJ].green;
  blue += (int)src[i3XnJ].blue;

  red += (int)src[i3XnJ1].red;
  green += (int)src[i3XnJ1].green;
  blue += (int)src[i3XnJ1].blue;

  red += (int)src[i3XnJ2].red;
  green += (int)src[i3XnJ2].green;
  blue += (int)src[i3XnJ2].blue;
  
  current_pixel.red = (unsigned short) (red / num_neighbors);
  current_pixel.green = (unsigned short) (green / num_neighbors);
  current_pixel.blue = (unsigned short) (blue / num_neighbors);
  return current_pixel;
}
/*
[  |  ]
[  |  ]
[  |  ]
*/
__attribute__((always_inline))static pixel kindaEdgeCombo(int dim, int i, int j, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;
  int num_neighbors = 6;

  int iXn = i * dim;
  int iXnJ = iXn + j;
  int iXnJ1 = iXn + j + 1;
  
  int i2Xn = iXn + dim;
  int i2XnJ = i2Xn + j;
  int i2XnJ1 = i2Xn + j + 1;

  int i3Xn = i2Xn + dim;
  int i3XnJ = i3Xn + j;
  int i3XnJ1 = i3Xn + j + 1;

  red += (int)src[iXnJ].red;
  green += (int)src[iXnJ].green;
  blue += (int)src[iXnJ].blue;

  red += (int)src[iXnJ1].red;
  green += (int)src[iXnJ1].green;
  blue += (int)src[iXnJ1].blue;
  //
  red += (int)src[i2XnJ].red;
  green += (int)src[i2XnJ].green;
  blue += (int)src[i2XnJ].blue;

  red += (int)src[i2XnJ1].red;
  green += (int)src[i2XnJ1].green;
  blue += (int)src[i2XnJ1].blue;
  //
  red += (int)src[i3XnJ].red;
  green += (int)src[i3XnJ].green;
  blue += (int)src[i3XnJ].blue;

  red += (int)src[i3XnJ1].red;
  green += (int)src[i3XnJ1].green;
  blue += (int)src[i3XnJ1].blue;
  
  current_pixel.red = (unsigned short) (red / num_neighbors);
  current_pixel.green = (unsigned short) (green / num_neighbors);
  current_pixel.blue = (unsigned short) (blue / num_neighbors);
  return current_pixel;
}

__attribute__((always_inline))static pixel kindaEdgeBottomCombo(int dim, int i, pixel *src)
{
pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;
  int num_neighbors = 6;

  int iXn = dim * (dim - 1) + i;
  int iXnJ = iXn + 1;
  int iXnJ1 = iXn + 2;
  
  int i2Xn = dim * (dim - 2) + i;
  int i2XnJ = i2Xn + 1;
  int i2XnJ1 = i2Xn + 2;

  red += (int)src[iXn].red;
  green += (int)src[iXn].green;
  blue += (int)src[iXn].blue;

  red += (int)src[iXnJ].red;
  green += (int)src[iXnJ].green;
  blue += (int)src[iXnJ].blue;

  red += (int)src[iXnJ1].red;
  green += (int)src[iXnJ1].green;
  blue += (int)src[iXnJ1].blue;
  //
  red += (int)src[i2Xn].red;
  green += (int)src[i2Xn].green;
  blue += (int)src[i2Xn].blue;

  red += (int)src[i2XnJ].red;
  green += (int)src[i2XnJ].green;
  blue += (int)src[i2XnJ].blue;

  red += (int)src[i2XnJ1].red;
  green += (int)src[i2XnJ1].green;
  blue += (int)src[i2XnJ1].blue;

  current_pixel.red = (unsigned short) (red / num_neighbors);
  current_pixel.green = (unsigned short) (green / num_neighbors);
  current_pixel.blue = (unsigned short) (blue / num_neighbors);
  return current_pixel;
}
/*
[  ]
[  ]
[  ]
*/
__attribute__((always_inline))static pixel edgeCombo(int dim, int i, pixel *src)
{
pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;
  int num_neighbors = 3;

  int iXn = i * dim + dim - 1;
  int i2Xn = (i+1) * dim + dim - 1;
  int i3Xn = (i+2) * dim + dim - 1;

  red += (int)src[iXn].red;
  green += (int)src[iXn].green;
  blue += (int)src[iXn].blue;
  //
  red += (int)src[i2Xn].red;
  green += (int)src[i2Xn].green;
  blue += (int)src[i2Xn].blue;
  //
  red += (int)src[i3Xn].red;
  green += (int)src[i3Xn].green;
  blue += (int)src[i3Xn].blue;

  current_pixel.red = (unsigned short) (red / num_neighbors);
  current_pixel.green = (unsigned short) (green / num_neighbors);
  current_pixel.blue = (unsigned short) (blue / num_neighbors);
  return current_pixel;
}

__attribute__((always_inline))static pixel edgeBottomCombo(int dim, int i, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;
  int num_neighbors = 3;

  int iXn = dim * (dim - 1) + i;
  int iXnJ = iXn + 1;
  int iXnJ1 = iXn + 2;

  red += (int)src[iXn].red;
  green += (int)src[iXn].green;
  blue += (int)src[iXn].blue;

  red += (int)src[iXnJ].red;
  green += (int)src[iXnJ].green;
  blue += (int)src[iXnJ].blue;

  red += (int)src[iXnJ1].red;
  green += (int)src[iXnJ1].green;
  blue += (int)src[iXnJ1].blue;

  current_pixel.red = (unsigned short) (red / num_neighbors);
  current_pixel.green = (unsigned short) (green / num_neighbors);
  current_pixel.blue = (unsigned short) (blue / num_neighbors);
  return current_pixel;
}

__attribute__((always_inline))static pixel innerCornerCombo(int pixnum, int dim, pixel *src)
{
  int red, green, blue;
  red = green = blue = 0;
  int num_neighbors = 4;
  red += src[pixnum].red;
  green += src[pixnum].green;
  blue += src[pixnum].blue;

  red += src[pixnum + 1].red;
  green += src[pixnum + 1].green;
  blue += src[pixnum + 1].blue;

  red += src[pixnum + dim].red;
  green += src[pixnum + dim].green;
  blue += src[pixnum + dim].blue;

  red += src[pixnum + dim + 1].red;
  green += src[pixnum + dim + 1].green;
  blue += src[pixnum + dim + 1].blue;

  pixel current_pixel;
  current_pixel.red = (unsigned short) (red / num_neighbors);
  current_pixel.green = (unsigned short) (green / num_neighbors);
  current_pixel.blue = (unsigned short) (blue / num_neighbors);
  return current_pixel;
}

__attribute__((always_inline))static pixel only2pix(int start, int offset, pixel *src)
{
  int red, green, blue;
  red = green = blue = 0;
  int num_neighbors = 2;
  pixel current_pixel;

  red += src[start].red;
  green += src[start].green;
  blue += src[start].blue;

  red += src[start + offset].red;
  green += src[start + offset].green;
  blue += src[start + offset].blue;

  current_pixel.red = (unsigned short) (red / num_neighbors);
  current_pixel.green = (unsigned short) (green / num_neighbors);
  current_pixel.blue = (unsigned short) (blue / num_neighbors);
  return current_pixel;
}


/******************************************************
 * Your different versions of the motion kernel go here
 ******************************************************/
/*
 * naive_motion - The naive baseline version of motion 
 */
char naive_motion_descr[] = "naive_motion: Naive baseline implementation";
void naive_motion(int dim, pixel *src, pixel *dst) 
{
  int i, j;
    
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(i, j, dim)] = weighted_combo(dim, i, j, src);
}

/*
 * motion - Your current working version of motion. 
 * IMPORTANT: This is the version you will be graded on
 */
char motion_descr[] = "motion: Current working version";
void motion(int dim, pixel *src, pixel *dst) 
{
  int dimSquared = dim * dim;
  int i,j;
  /*
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(i, j, dim)] = weighted_combo(dim, i, j, src);
  */
  for (i = 0; i < dim-2; i++)
    {
      int iXn = i * dim;
      for (j = 0; j < dim-2; j++)
      {
        dst[iXn + j] = okayCombo(dim, i, j, src);
      }
      dst[iXn + (dim - 2)] = kindaEdgeCombo(dim, i, j, src);
      dst[dimSquared - 2 * dim + i] = kindaEdgeBottomCombo(dim, i, src);
      dst[iXn + (dim - 1)] = edgeCombo(dim, i, src);
      dst[dimSquared - dim + i] = edgeBottomCombo(dim, i, src);
    }
  dst[dimSquared - dim - 2] = innerCornerCombo(dimSquared - dim - 2, dim, src);
  dst[dimSquared - 1] = src[dimSquared - 1];
  dst[dimSquared - dim - 1] = only2pix(dimSquared - dim - 1, dim, src); // 95, 94
  dst[dimSquared - 2] = only2pix(dimSquared - 2, 1, src);
  //dst[dim]

}

/********************************************************************* 
 * register_motion_functions - Register all of your different versions
 *     of the motion kernel with the driver by calling the
 *     add_motion_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_motion_functions() {
  add_motion_function(&motion, motion_descr);
  add_motion_function(&naive_motion, naive_motion_descr);
}
