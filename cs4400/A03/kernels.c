/*******************************************
 * Solutions for the CS:APP Performance Lab
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
  "Leon Tran",     /* Full name */
  "u1274029@utah.edu",  /* Email address */
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

void tunned_complex(int dim, pixel *src, pixel *dest)
{
  int i, j, k, l, W;
  if (dim > 255) {  W = 32; }
  else
    W = 16;
  for(i = 0; i < dim; i += W)
  {
    int dim_subtract_one = dim - 1;
    for(j = 0; j < dim; j += W)
    {
      for(k = i; k < i + W; k++)
      {
        int cur_dim = dim_subtract_one - k;
        for(l = j; l < j + W; l++)
        {
          int src_index = RIDX(l, k, dim);
          int dest_index = RIDX(cur_dim, dim_subtract_one - l, dim); 
          unsigned short average_sum = (src[src_index].red + src[src_index].green + src[src_index].blue) / 3;
          dest[dest_index].red = average_sum;
          dest[dest_index].green = average_sum;
          dest[dest_index].blue = average_sum;
        }
      }
    }
  }
}
/* 
 * complex - Your current working version of complex
 * IMPORTANT: This is the version you will be graded on
 */
char complex_descr[] = "complex: Current working version";
void complex(int dim, pixel *src, pixel *dest)
{
  tunned_complex(dim, src, dest);
}

/*********************************************************************
 * register_complex_functions - Register all of your different versions
 *     of the complex kernel with the driver by calling the
 *     add_complex_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_complex_functions() {
  add_complex_function(&complex, complex_descr);
  add_complex_function(&naive_complex, naive_complex_descr);
}


/***************
 * MOTION KERNEL
 **************/

/***************************************************************
 * Various helper functions for the motion kernel
 * You may modify these or add new ones any way you like.
 **************************************************************/


/* 
 * weighted_combo - Returns new pixel value at (i,j) 
 */
static pixel weighted_combo(int dim, int i, int j, pixel *src) 
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

__attribute__((always_inline)) static pixel unrolled_combo(int i, int j, int dim, pixel *src)
  {
    pixel current_pixel;
    int red, green, blue;
    red = green = blue = 0;

    int row1 = i * dim;
    int row1_plus_j = row1 + j;
    int row1_plus_j_plus_1 = row1 + j + 1;
    int row1_plus_j_plus_2 = row1+ j+ 2;

    int row2 = (i+1) * dim;
    int row2_plus_j = row2 + j;
    int row2_plus_j_plus_1 = row2 + j + 1;
    int row2_plus_j_plus_2 = row2 + j + 2;

    int row3 = (i+2) * dim;
    int row_3_plus_j = row3 + j;
    int row_3_plus_j_plus_1 = row3 + j + 1;
    int row_3_plus_j_plus_2 = row3 + j + 2;
    
    red += (int)src[row1_plus_j].red;
    blue += (int)src [row1_plus_j].blue;
    green += (int)src[row1_plus_j].green;

    red += (int)src[row1_plus_j_plus_1].red;
    blue += (int)src[row1_plus_j_plus_1].blue;
    green += (int)src[row1_plus_j_plus_1].green;
    red += (int)src[row1_plus_j_plus_2].red;
    blue += (int)src[row1_plus_j_plus_2].blue;
    green += (int)src[row1_plus_j_plus_2].green;

    red += (int)src[row2_plus_j].red;
    blue += (int)src[row2_plus_j].blue;
    green += (int)src[row2_plus_j].green;
    red += (int)src[row2_plus_j_plus_1].red;
    blue += (int)src[row2_plus_j_plus_1].blue;
    green += (int)src[row2_plus_j_plus_1].green;
    red += (int)src[row2_plus_j_plus_2].red;
    blue += (int)src[row2_plus_j_plus_2].blue;
    green += (int)src[row2_plus_j_plus_2].green;

    red += (int)src[row_3_plus_j].red;
    blue += (int)src[row_3_plus_j].blue;
    green += (int)src[row_3_plus_j].green;
    red += (int)src[row_3_plus_j_plus_1].red;
    blue += (int)src[row_3_plus_j_plus_1].blue;
    green += (int)src[row_3_plus_j_plus_1].green;
    red += (int)src[row_3_plus_j_plus_2].red;
    blue += (int)src[row_3_plus_j_plus_2].blue;
    green += (int)src[row_3_plus_j_plus_2].green;

    current_pixel.red = (unsigned short)(red / 9);
    current_pixel.blue = (unsigned short)(blue / 9);
    current_pixel.green = (unsigned short)(green / 9);
    return current_pixel;
  }

__attribute__((always_inline)) static pixel first_right(int i, int j, int dim, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;

  int row1 = i * dim;
  int row1_plus_j = row1 + j;
  int row1_plus_j_plus_1 = row1 + j + 1;

  int row2 = (i+1)*dim;
  int row2_plus_j = row2 + j;
  int row2_plus_j_plus_1 = row2 + j + 1;

  int row3 = (i+2) * dim;
  int row3_plus_j = row3 + j;
  int row3_plus_j_plus_1 = row3 + j + 1;
  
  red += (int)src[row1_plus_j].red;
  blue += (int)src[row1_plus_j].blue;
  green += (int)src[row1_plus_j].green;

  red += (int)src[row1_plus_j_plus_1].red;
  blue += (int)src[row1_plus_j_plus_1].blue;
  green += (int)src[row1_plus_j_plus_1].green;
  
  red += (int)src[row2_plus_j].red;
  blue += (int)src[row2_plus_j].blue;
  green += (int)src[row2_plus_j].green;
  
  red += (int)src[row2_plus_j_plus_1].red;
  blue += (int)src[row2_plus_j_plus_1].blue;
  green += (int)src[row2_plus_j_plus_1].green;
  
  red += (int)src[row3_plus_j].red;
  blue += (int)src[row3_plus_j].blue;
  green += (int)src[row3_plus_j].green;
  
  red += (int)src[row3_plus_j_plus_1].red;
  blue += (int)src[row3_plus_j_plus_1].blue;
  green += (int)src[row3_plus_j_plus_1].green;

  current_pixel.red = (unsigned short)(red / 6);
  current_pixel.blue = (unsigned short)(blue / 6);
  current_pixel.green = (unsigned short)(green / 6);
  return current_pixel;
}

__attribute__((always_inline)) static pixel second_right(int i, int j, int dim, pixel *src)
{
  pixel current_pixel;
  int red, blue, green;
  red = blue = green = 0;

  int row1 = i * dim;
  int row1_plus_j = row1 + j;

  int row2 = (i + 1) * dim;
  int row_2_plus_j = row2 + j;

  int row3 = (i + 2) * dim;
  int row_3_plus_j = row3 + j;
    
  red += (int)src[row1_plus_j].red;
  blue += (int)src[row1_plus_j].blue;
  green += (int)src[row1_plus_j].green;

  red += (int)src[row_2_plus_j].red;
  blue += (int)src[row_2_plus_j].blue;
  green += (int)src[row_2_plus_j].green;

  red += (int)src[row_3_plus_j].red;
  blue += (int)src[row_3_plus_j].blue;
  green += (int)src[row_3_plus_j].green;

  current_pixel.red = (unsigned short)(red / 3);
  current_pixel.blue = (unsigned short)(blue / 3);
  current_pixel.green = (unsigned short)(green / 3);
  return current_pixel;
}

__attribute__((always_inline)) static pixel first_bottom(int i, int j, int dim, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;

  int row1 = i * dim;
  int row1_plus_j = row1 + j;
  int row1_plus_j_plus_1 = row1 + j + 1;
  int row_1_plus_j_plus_2 = row1 + j + 2;

  int row2 = (i + 1) * dim;
  int row2_plus_j = row2 + j;
  int row2_plus_j_plus_1 = row2 + j + 1;
  int row2_plus_j_plus_2 = row2 + j + 2;

  red += (int)src[row1_plus_j].red;
  blue += (int)src[row1_plus_j].blue;
  green += (int)src[row1_plus_j].green;

  red += (int)src[row1_plus_j_plus_1].red;
  blue += (int)src[row1_plus_j_plus_1].blue;
  green += (int)src[row1_plus_j_plus_1].green;
  red += (int)src[row_1_plus_j_plus_2].red;
  blue += (int)src[row_1_plus_j_plus_2].blue;
  green += (int)src[row_1_plus_j_plus_2].green;

  red += (int)src[row2_plus_j].red;
  blue += (int)src[row2_plus_j].blue;
  green += (int)src[row2_plus_j].green;
  red += (int)src[row2_plus_j_plus_1].red;
  blue += (int)src[row2_plus_j_plus_1].blue;
  green += (int)src[row2_plus_j_plus_1].green;
  red += (int)src[row2_plus_j_plus_2].red;
  blue += (int)src[row2_plus_j_plus_2].blue;
  green += (int)src[row2_plus_j_plus_2].green;

  current_pixel.red = (unsigned short)(red / 6);
  current_pixel.blue = (unsigned short)(blue / 6);
  current_pixel.green = (unsigned short)(green / 6);
  return current_pixel;
}

__attribute__((always_inline)) static pixel second_bottom(int i, int j, int dim, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;

  int row1 = i*dim;
  int row1_plus_j = row1 + j;
  int row1_plus_j_plus_1 = row1 + j + 1;
  int row1_plus_j_plus_2 = row1 + j + 2;

  red += (int)src[row1_plus_j].red;
  blue += (int)src[row1_plus_j].blue;
  green += (int)src[row1_plus_j].green;

  red += (int)src[row1_plus_j_plus_1].red;
  blue += (int)src[row1_plus_j_plus_1].blue;
  green += (int)src[row1_plus_j_plus_1].green;
  red += (int)src[row1_plus_j_plus_2].red;
  blue += (int)src[row1_plus_j_plus_2].blue;
  green += (int)src[row1_plus_j_plus_2].green;

  current_pixel.red = (unsigned short)(red / 3);
  current_pixel.blue = (unsigned short)(blue / 3);
  current_pixel.green = (unsigned short)(green / 3);
  return current_pixel;
}

__attribute__((always_inline)) static pixel first_right_corner(int i, int j, int dim, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;

  int row1 = i * dim;
  int row1_plus_j = row1 + j;
  int row1_plus_j_plus_1 = row1 + j + 1;

  int row2 = (i+1)*dim;
  int row2_plus_j = row2 + j;
  int row2_plus_j_plus_1 = row2 + j + 1;

  red += (int)src[row1_plus_j].red;
  blue += (int)src[row1_plus_j].blue;
  green += (int)src[row1_plus_j].green;

  red += (int)src[row1_plus_j_plus_1].red;
  blue += (int)src[row1_plus_j_plus_1].blue;
  green += (int)src[row1_plus_j_plus_1].green;

  red += (int)src[row2_plus_j].red;
  blue += (int)src[row2_plus_j].blue;
  green += (int)src[row2_plus_j].green;
  red += (int)src[row2_plus_j_plus_1].red;
  blue += (int)src[row2_plus_j_plus_1].blue;
  green += (int)src[row2_plus_j_plus_1].green;

  current_pixel.red = (unsigned short)(red / 4);
  current_pixel.blue = (unsigned short)(blue / 4);
  current_pixel.green = (unsigned short)(green / 4);
  return current_pixel;
}

__attribute__((always_inline)) static pixel second_right_corner(int i, int j, int dim, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;

  int row1 = i * dim;
  int row1_plus_j = row1 + j;

  red += (int)src[row1_plus_j].red;
  blue += (int)src[row1_plus_j].blue;
  green += (int)src[row1_plus_j].green;

  current_pixel.red = (unsigned short)(red);
  current_pixel.blue = (unsigned short)(blue);
  current_pixel.green = (unsigned short)(green);
  return current_pixel;
}

__attribute__((always_inline)) static pixel right_edge(int i, int j, int dim, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;

  int row1 = i * dim;
  int row1_plus_j = row1 + j;

  int row2 = (i + 1) * dim;
  int row2_plus_j = row2 + j;

  red += (int)src[row1_plus_j].red;
  blue += (int)src[row1_plus_j].blue;
  green += (int)src[row1_plus_j].green;

  red += (int)src[row2_plus_j].red;
  blue += (int)src[row2_plus_j].blue;
  green += (int)src[row2_plus_j].green;

  current_pixel.red = (unsigned short)(red / 2);
  current_pixel.blue = (unsigned short)(blue / 2);
  current_pixel.green = (unsigned short)(green / 2);
  return current_pixel;
}

__attribute__((always_inline)) static pixel bottom_edge(int i, int j, int dim, pixel *src)
{
  pixel current_pixel;
  int red, green, blue;
  red = green = blue = 0;

  int row1 = i * dim;
  int row1_plus_j = row1 + j;
  int row1_plus_j_plus_1 = row1 + j + 1;

  red += (int)src[row1_plus_j].red;
  blue += (int)src[row1_plus_j].blue;
  green += (int)src[row1_plus_j].green;

  red += (int)src[row1_plus_j_plus_1].red;
  blue += (int)src[row1_plus_j_plus_1].blue;
  green += (int)src[row1_plus_j_plus_1].green;

  current_pixel.red = (unsigned short)(red / 2);
  current_pixel.blue = (unsigned short)(blue / 2);
  current_pixel.green = (unsigned short)(green / 2);
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

void tunned_motion(int dim, pixel *src, pixel *dst)
{
  int i, j, k;
    
  for (i = 0; i < dim - 2; i++)
  {
    for (j = 0; j < dim - 2; j++)
    {
      dst[RIDX(i,j,dim)] = unrolled_combo(i,j,dim,src);
    }
    dst[RIDX(i,j,dim)] = first_right(i,j,dim,src);
    dst[RIDX(i,j + 1,dim)] = second_right(i,j + 1,dim,src);
  }
  
  for(k = 0;k < dim - 2; k++)
  {
    dst[RIDX(i, k, dim)] = first_bottom(i, k, dim, src);
    dst[RIDX(i + 1, k, dim)] = second_bottom(i + 1, k, dim, src);
  }
  dst[RIDX(i, j, dim)] = first_right_corner(i,j,dim,src);
  dst[RIDX(i + 1, j + 1, dim)] = second_right_corner(i + 1, j + 1, dim, src);
  dst[RIDX(i, j + 1, dim)] = right_edge(i, j + 1, dim, src);
  dst[RIDX(i + 1, j, dim)] = bottom_edge(i + 1, j, dim, src);
}

/*
 * motion - Your current working version of motion. 
 * IMPORTANT: This is the version you will be graded on
 */
char motion_descr[] = "motion: Current working version";
void motion(int dim, pixel *src, pixel *dst) 
{
  tunned_motion(dim, src, dst);
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
