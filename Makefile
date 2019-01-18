# Makefile for hw4, EECS22 Fall 2017 fall 
# Author: Huan Chen
# Modified by: Mihnea Chirila
# Modification: Ali Nickparsa 11/11/2018
# Date:   11/01/2017
CC     = gcc
DEBUG  = -g -DDEBUG 

CFLAGS = -Wall -ansi -std=c99 -c
LFLAGS = -Wall

OBJS = MovieLab.o Movie.o MovieIO.o FileIO.o Image.o ImageList.o DIPs.o IterativeFilter.o
DEPS = Image.h FileIO.h DIPs.h ImageList.h IterativeFilter.h Movie.h MovieIO.h

DESIGN = MovieLab
all: $(DESIGN)
MovieLab: $(OBJS) libFilter.a
	$(CC) $(DEBUG) $(LFLAGS) $(OBJS) -lm -L. -lFilter -o MovieLab
Test: Test.o Image.o
	$(CC) Test.c Test.o Image.o  -o Test


libFilter.a: DIPs.o
	ar rc libFilter.a DIPs.o
	ranlib libFilter.a

MovieLab.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o
FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(DEBUG) $(CFLAGS) FileIO.c -o FileIO.o
MovieIO.o: MovieIO.c MovieIO.h Movie.h FileIO.h Image.h
	$(CC) $(DEBUG) $(CFLAGS) MovieIO.c -o MovieIO.o
DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o
ImageList.o: ImageList.c ImageList.h Image.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o
Movie.o: Movie.c Movie.h ImageList.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o 
IterativeFilter.o: IterativeFilter.c IterativeFilter.h Image.h Movie.h
	$(CC) $(CFLAGS) IterativeFilter.c -o IterativeFilter.o
Test.o: Test.c Image.h
	$(CC) $(CFLAGS) Test.c -o Test.o

clean:
	rm -f *.o *.a $(DESIGN) `find . -name '*.ppm' ! -name 'HSSOE.ppm'`
	rm reverse.yuv test.yuv

