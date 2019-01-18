/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
     MOVIE *m = (MOVIE *)malloc(sizeof(MOVIE));
     m -> Frames = CreateImageList();
     return m;
} /* end of CreateMovie */

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
    assert(movie);
    DeleteImageList(movie -> Frames);
    free(movie);
} /* end of DeleteMovie */

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
    IENTRY *c, *n;
    YUVIMAGE *y;
    IMAGE *i;    

    int C, D, E;

    c = (movie -> Frames) -> First;
    while(c != NULL){
        n = c -> Next;

        y = c -> YUVImage; 
        i = c -> RGBImage; 
        i = CreateImage((c -> YUVImage) -> W, (c -> YUVImage) -> H);

        for(int h=0; h<((c -> YUVImage) -> H); h++){
            for(int w=0; w<((c -> YUVImage) -> W); w++){
               C = (int)GetPixelY(y,w,h) - 16;
               D = (int)GetPixelU(y,w,h) - 128;
               E = (int)GetPixelV(y,w,h) - 128;  
               
               SetPixelR(i, w, h, clip((298*C         + 409*E + 128) >> 8));
               SetPixelG(i, w, h, clip((298*C - 100*D - 208*E + 128) >> 8)); 
               SetPixelB(i, w, h, clip((298*C + 516*D         + 128) >> 8)); 
            }
        }

        DeleteYUVImage(y);
        y = NULL;

        if(i == NULL){
            perror("Creating RGBImage failed.\n");
            exit(10);
        }
        if(y != NULL){
            perror("Removing YUVImage failed.\n");
            exit(10);
        }

        c -> RGBImage = i;
        c = n;
    }
} /* end of YUV2RGB */

/* Convert an RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
    IENTRY *c, *n;
    YUVIMAGE *y;
    IMAGE *i;    

    c = (movie -> Frames) -> First;
    while(c != NULL){
        n = c -> Next;

        y = c -> YUVImage; 
        i = c -> RGBImage; 
        y = CreateYUVImage(ImageWidth(i), ImageHeight(i));

        for(int h=0; h<ImageHeight(i); h++){
            for(int w=0; w<ImageWidth(i); w++){
               SetPixelY(y, w, h, clip(((66*(int)GetPixelR(i,w,h) + 129*(int)GetPixelG(i,w,h) + 25*(int)GetPixelB(i,w,h) + 128) >> 8) + 16)); 
               SetPixelU(y, w, h, clip(((-38*(int)GetPixelR(i,w,h) - 74*(int)GetPixelG(i,w,h) + 112*(int)GetPixelB(i,w,h) + 128) >> 8) + 128)); 
               SetPixelV(y, w, h, clip(((112*(int)GetPixelR(i,w,h) - 94*(int)GetPixelG(i,w,h) - 18*(int)GetPixelB(i,w,h) + 128) >> 8) + 128)); 
            }
        }

        DeleteImage(i);
        i = NULL;

        if(y == NULL){
            perror("Creating YUVImage failed.\n");
            exit(10);
        }
        if(i != NULL){
            perror("Removing RGBImage failed.\n");
            exit(10);
        }

        c -> YUVImage = y;
        c = n;
    }
} /* end of RGB2YUV */

int MovieLength(const MOVIE *movie)
{
    return (movie->Frames)->Length;
}

int MovieHeight(const MOVIE *movie)
{
    int h;
    if(MovieLength(movie) == 0){
        printf("Current movie has no frames!\n");
        return 0;
    }
    else if(((movie->Frames) -> First) -> RGBImage != NULL)
        h = ImageHeight((((movie->Frames) -> First) -> RGBImage));
    else
        h = (((movie->Frames) -> First) -> YUVImage) -> H;
    
    return h;
}

int MovieWidth(const MOVIE *movie)
{
    int w;
    if(MovieLength(movie) == 0){
        printf("Current movie has no frames!\n");
        return 0;
    }
    else if(((movie->Frames) -> First) -> RGBImage != NULL)
        w = ImageWidth((((movie->Frames) -> First) -> RGBImage));
    else
        w = (((movie->Frames) -> First) -> YUVImage) -> W;
    
    return w;
}

/* EOF */
