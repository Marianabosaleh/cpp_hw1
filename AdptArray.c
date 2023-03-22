#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <assert.h>
#include "AdptArray.h"

typedef struct AdptArray_ 
{
    int arrSize;
    PElement* arrPElement;
    // function pointers
    DEL_FUNC DelElement ;
    COPY_FUNC copyElement;
    PRINT_FUNC printElement;
    
}AdptArray;
// interface implementation 

//create adt array function
PAdptArray CreateAdptArray(COPY_FUNC copyElement, DEL_FUNC DelElement,PRINT_FUNC printElement){
    PAdptArray parr;
    // check if the function implemented 
    if (copyElement == NULL || DelElement == NULL || printElement == NULL) 
        return NULL;

    if((parr=malloc(sizeof(AdptArray))))
    {
        parr->arrSize=0;
        parr->arrPElement= NULL;
        parr->DelElement=DelElement;
        parr->copyElement=copyElement;
        parr->printElement=printElement;
    }
    return parr;
}

//delete adt array function
void DeleteAdptArray(PAdptArray parr){
    if (parr != NULL){
		
        for(int i=0;i< parr->arrSize;i++){
            if((parr->arrPElement)[i]){
                parr->DelElement((parr->arrPElement)[i]);
            }
        }
        free(parr->arrPElement);
        free(parr);
    }
}
//set adt array function, repalce the old element with the new element in the givin i i 
Result SetAdptArrayAt(PAdptArray parr, int i, PElement element) {

    if (parr == NULL || i < 0) {
        return FAIL;
    }

    if (i >= parr->arrSize) {
        // Increase the size of the array by reallocating memory
        PElement* new_elements = realloc(parr->arrPElement, (i + 1) * sizeof(PElement));
        if (new_elements == NULL) {
            return FAIL;
        }
        // Set the new elements to NULL
        memset(new_elements + parr->arrSize, 0, (i + 1 - parr->arrSize) * sizeof(PElement));
        parr->arrPElement = new_elements;
        parr->arrSize = i + 1;
    }

    // Delete the old element, if it exists
    if (parr->arrPElement[i] != NULL) {
        parr->DelElement(parr->arrPElement[i]);
    }
}

PElement GetAdptArrayAt(PAdptArray parr, int i){

    if (i< 0 || i >= parr->arrSize) {
        return NULL;
    }
    PElement elem = parr -> arrPElement[i]; 
    if(elem == NULL){
        return NULL;
    }
    return parr->copyElement(elem);
}

int GetAdptArraySize(PAdptArray parr){
    if(parr==NULL)
        return 0;
    return parr->arrSize;
}

void PrintDB(PAdptArray parr){
    if(parr!=NULL){
        for(int i=0;i<parr->arrSize;i++){
            if((parr->arrPElement)[i])
                parr-> printElement((parr->arrPElement)[i]);
        }
    }

}