/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* DIPs.h: header file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#ifndef DIPS_H
#define DIPS_H

#include "Image.h"
#include "FileIO.h"

typedef enum
{
	HueRotateFilter
}FilterType;

// HueRotate filter
IMAGE *HueRotate(IMAGE *image, float angle);

// Saturate filter
IMAGE *Saturate(IMAGE *image, float percent);

#endif
