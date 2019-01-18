/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/* Modified by Mihnea Chirila for EECS 22 Fall 2018                                                            */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

/* header files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

/* function definitions */

/* Prints command line options available to user */
void PrintMenu(void){
    printf("Options: MovieLab [option]\n"
    "-------------------------------------\n"
    "Option:         Function:\n"
    "-h              Display options menu\n"
    "-f <frameNum>   Number of frames in the input move\n" 
    "-i <file.ppm>   Import an image in .ppm format\n"
    "-m <file.yuv>   Import a movie in .yuv format\n"        
    "-o <file.yuv>   Export a movie in .yuv format\n"
    "-s <WxH>        Size of a movie frame (Width x Height)\n"
    "-reverse        Reverse the movie\n"
    "-hue            Apply an iterative hue filter on the image to create a movie \n"
    );
}


int main(int argc, char *argv[])
{
    //variable declarations
    MOVIE *myMovie;
    IMAGE *myImage;
    char *movieInFName = NULL;
    char *movieOutFName = NULL;
    char *imageFName = NULL;

    int loadType;                //used to determine if loading image or movie
    int numFrames;
    int W, H;

    iterableFilter filter = NULL;
    int doFilter;
    float start, end, step;

    int doReverse;

/*
    myMovie = LoadMovie("hue.yuv", 73, 300, 200);

    YUV2RGBMovie(myMovie);
    myImage = myMovie -> Frames -> First -> RGBImage;
    SaveImage("bw", myImage);
    exit(10);
//*/

    if(argc == 1){
        printf("Please input an option.\n");
        PrintMenu();
        exit(12);
    }

    // set operation variables based on input
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0){                    // print options menu  
            PrintMenu();
            exit(10);
        }
        else if(strcmp(argv[i], "-m") == 0){               // load movie  
            i++;
            if(i < argc && (strstr(argv[i], ".yuv") != NULL)){
                loadType = 1;
                movieInFName = argv[i];
                printf("Current movieInFileName: %s\n", movieInFName);
            }
            else{
                perror("Missing or invalid argument for -m!\n");
                PrintMenu();
                exit(10);
            }
        }
        else if(strcmp(argv[i], "-i") == 0){               // load image
            i++;
            if(i < argc && (strstr(argv[i], ".ppm") != NULL)){
                loadType = 0;
                imageFName = argv[i];
                printf("Current imageFileName: %s\n", imageFName);
            }
            else{
                perror("Missing or invalid argument for -i!\n");
                PrintMenu();
                exit(10);
            }
        }
        else if(strcmp(argv[i], "-o") == 0){               // output movie
            i++;
            if(i < argc && (strstr(argv[i], ".yuv") != NULL)){
                movieOutFName = argv[i];
                printf("Current movieOutFileName: %s\n", movieOutFName);
            }
            else{
                perror("Missing or invalid argument for -o!\n");
                PrintMenu();
                exit(10);
            }
        }
        else if(strcmp(argv[i], "-f") == 0){
            i++;
            if(i < argc){
                numFrames = atoi(argv[i]); 
                printf("Number of frames: %d\n", numFrames);
            }
            else{
                perror("Missing or invalid argument for -f!\n");
                PrintMenu();
                exit(10);
            }
        }
        else if(strcmp(argv[i], "-s") == 0){
            i++;

            char w_sub[4];
            char h_sub[4];
            int x_loc = 0;

            if(i < argc){
                char *x = strchr(argv[i], 'x');
                x_loc = (int)(x - argv[i]);

                printf("x location: %d\n", x_loc);

                W = atoi(strncpy(w_sub, argv[i], x_loc));
                H = atoi(strncpy(h_sub, argv[i] + x_loc + 1, strlen(argv[i]) - x_loc));

                printf("Frame width: %d\n", W);
                printf("Frame height: %d\n", H);
            }
            else{
                perror("Missing or invalid argument for -f!\n");
                PrintMenu();
                exit(10);
            }
        }
        else if(strcmp(argv[i], "-start=") == 0){
            i++;
            if(i < argc){
                start = atof(argv[i]); 
                printf("Start percentage: %.2f\n", start);
            }
            else{
                perror("Missing or invalid argument for -start=!\n");
                PrintMenu();
                exit(10);
            }
        }
        else if(strcmp(argv[i], "-end=") == 0){
            i++;
            if(i < argc){
                end = atof(argv[i]); 
                printf("End percentage: %.2f\n", end);
            }
            else{
                perror("Missing or invalid argument for -end=!\n");
                PrintMenu();
                exit(10);
            }
        }
        else if(strcmp(argv[i], "-step=") == 0){
            i++;
            if(i < argc){
                step = atof(argv[i]); 
                printf("Step percentage: %.2f\n", step);
            }
            else{
                perror("Missing or invalid argument for -step=!\n");
                PrintMenu();
                exit(10);
            }
        }
        else if(strcmp(argv[i], "-reverse") == 0){
            doReverse = 1;       
        }
        else if(strcmp(argv[i], "-hue") == 0){
            doFilter = 1;
            filter = HueRotate;
        }
        else{
            fprintf(stderr, "Unknown option %s!\n", argv[i]);
            PrintMenu();
            exit(10);
        }
    }

    // load files based on input
    if(loadType == 1){ //loads movie in .yuv format        
        myMovie = LoadMovie(movieInFName, numFrames, W, H);
    }
    else if(loadType == 0){
        myImage = LoadImage(imageFName); 

        myMovie = doIterativeFilter(myImage, filter, start, end, step);
    }

    // perform operations based on input
    if(doReverse == 1)
        ReverseImageList(myMovie->Frames); 

    // save movie
    SaveMovie(movieOutFName, myMovie); 
   
    // clear variables
 
    return 0;
}

/* EOF */
