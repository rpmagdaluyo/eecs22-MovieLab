/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>

#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
    IENTRY *e = malloc(sizeof(IENTRY));
  
    if(!e){
        perror("Allocation failed!\n");
        exit(10);
    }
  
    e -> List = NULL;
    e -> Next = NULL;
    e -> Prev = NULL;
    e -> RGBImage = NULL;
    e -> YUVImage = NULL; 

    return e;
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
   assert(entry);
   
   if(entry -> RGBImage != NULL)
       DeleteImage(entry -> RGBImage);
   if(entry -> YUVImage != NULL)
       DeleteYUVImage(entry -> YUVImage);

   free(entry);
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
    ILIST *l = malloc(sizeof(ILIST));

    if(!l){
        perror("Allocation failed!\n");
        exit(10);
    }
    
    l -> Length = 0;
    l -> First = NULL;
    l -> Last = NULL;

    return l;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
    assert(list);

    IENTRY *e, *n;
    
    e = list -> First;
    while(e != NULL){
       n = e -> Next;
       DeleteImageEntry(e);
       e = n;
    }

    free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
    assert(list);
    assert(RGBimage);

    IENTRY *newEntry = CreateImageEntry();
 
    if(list -> Length > 0){ 
    
        newEntry -> List = list;
        newEntry -> Next = NULL;
        newEntry -> Prev = list -> Last;
        newEntry -> RGBImage = RGBimage;
        newEntry -> YUVImage = NULL;
    
        ((list -> Last)->Next) = newEntry;
        list -> Last = newEntry;
    }
    else{
        newEntry -> List = list;
        newEntry -> Next = NULL; 
        newEntry -> Prev = NULL;
        newEntry -> RGBImage = RGBimage;
        newEntry -> YUVImage = NULL;
        list -> First = newEntry;
        list -> Last = newEntry;
    }
    
    (list -> Length)++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
    assert(list);
    assert(YUVimage);

    IENTRY *newEntry = CreateImageEntry();
    
    if(list -> Length > 0){ 
    
        newEntry -> List = list;
        newEntry -> Next = NULL;
        newEntry -> Prev = list -> Last;

        newEntry -> YUVImage = YUVimage;
    
        ((list -> Last)->Next) = newEntry;
        list -> Last = newEntry;
    }
    else{
        newEntry -> List = list;
        newEntry -> Next = NULL; 
        newEntry -> Prev = NULL;

        newEntry -> YUVImage = YUVimage;

        list -> First = newEntry;
        list -> Last = newEntry;
    }

    (list -> Length)++;
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	unsigned int newFrameNum = 0;
	unsigned int counter = 0;
	IENTRY *curr = NULL; /* current entry in the list */
	IENTRY *prev = NULL; /* previous kept entry in the list */
	IENTRY *next = NULL; /* next entry in the list */

	assert(list);
	assert(factor > 0);

	curr = list->First;

	while (curr != NULL) {
		next = curr->Next;

		if (counter % factor == 0) {
			newFrameNum ++;

			curr->Prev = prev;
			if (prev != NULL) {
				prev->Next = curr;
			}
			prev = curr;
		} else {
			if (curr->RGBImage != NULL) {
				DeleteImage(curr->RGBImage);
			}

			if (curr->YUVImage != NULL) {
				DeleteYUVImage(curr->YUVImage);
			}

			curr->List = NULL;
			curr->Next = NULL;
			curr->Prev = NULL;
			curr->RGBImage = NULL;
			curr->YUVImage = NULL;
			free(curr);
		}

		curr = next;
		counter ++;
	}

	list->Last = prev;
	if (prev != NULL) {
		prev->Next = NULL;
	}
	list->Length = newFrameNum;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
    assert(list);

    ILIST *newList = (ILIST *)malloc(sizeof(ILIST));
    IENTRY *O_C, *O_P;

    O_C = list -> Last;
    while(O_C != NULL){
        O_P = O_C -> Prev;
       
        AppendYUVImage(newList, O_C -> YUVImage);

        O_C = O_P;
    }

    list -> First = newList -> First;
    list -> Last = newList -> Last;

    free(newList);
}























/* EOF */
