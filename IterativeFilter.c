/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include "IterativeFilter.h"
#include "DIPs.h"

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, float start, float end, float change)
{
//functionality:
//calls a specific filter based in entered name (filter) for a period of time
//called determined by start and end

    MOVIE *myMovie = CreateMovie();
    ILIST *myFrames = myMovie -> Frames;
    IMAGE *nImage = malloc(sizeof(IMAGE));

    
    if(end > start){
        for(float i=start; i<=end; i+=change){
            nImage = CopyImage(image);
            nImage = filter(nImage, start);

            AppendRGBImage(myFrames, image);
        }
    }
    else{
        change = -change;
        for(float i=start; i>=end; i+=change){
            nImage = CopyImage(image);
            nImage = filter(nImage, start);

            AppendRGBImage(myFrames, image);
        }
    }
 
    RGB2YUVMovie(myMovie); 
   
    return myMovie;
}
