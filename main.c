#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "file.h"

//Written by Gary Gritters and Ross Kuiper
//Last edit 02/03/2020
//Code to reverse a .wav file so it can be played in reverse

//# of arguments, and the arguments
int main(int argc, char** argv){

    //Will use this pointer to store the data of the .wav
    char* myPointer;

    //Read .wav file, and will set myPointer to the data
    size_t size = read_file(argv[1], &myPointer);
	if(size == 0){
		perror("Read failed");
		return 1;
	}
    wav_file* myWav;

    //Castes myPointer into the wav_file struct named myWav
    myWav = parse(myPointer);

    //Print out info on the .wav currently stored in myWav.
    //This is the first 43 bytes
    //of the .wav file.
    printf("File: %s", argv[1]);
    printf("\n==========================");
    printf("\n-File size is %zu. Read %d bytes.",
		    size, myWav->chunkSize);
    printf("\n-Format is \"%c%c%c%c\" with format data length %d.",
		    myWav->varies[0], myWav->varies[1],
		    myWav->varies[2], myWav->varies[3],
		    myWav->lengthFmt);
    printf("\n-Format type is %c%c%c%cfmt.", myWav->needBe[0],
		    myWav->needBe[1], myWav->needBe[2],
		    myWav->needBe[3]);
    printf("\n-%hi channels with a sample rate of %d.",
		    (myWav->numChan), myWav->sampRate);
    printf("\n-%d byte rate, %hi alignment, %hi bits per sample.",
		    myWav->byteRate, myWav->bAlign, myWav->bitsPerSamp);
    printf("\n-Data is \"%c%c%c%c\" and data size is %d.\n",
		    myWav->beginData[0], myWav->beginData[1],
		    myWav->beginData[2], myWav->beginData[3],
		    myWav->sizeOfData);

    //Set up pointer to reverse the .wav
    char* reversed = malloc(size);
	if(reversed == NULL){
		perror("Reversed buffer malloc failed");
		return 3;
	}

    //Store the info from .wav  Will not be changed.
    for(int i = 0; i < 44; ++i){
		*(reversed + i) = *(myPointer + i);
    }
    int j = 44;	

    //Now, reverse the .wav
    for(int i = size-1; i > 43; i-=2){
        *(reversed + j) = *(myPointer + i - 1);
		j++;
		*(reversed + j) = *(myPointer + i);
		j++;
    }

    //Create the new file from 2nd argument
    size_t write_size = write_file(argv[2], reversed, size);
	if(write_size != size){
		perror("Write size and read size differ");
		return 4;
	}

    //Can't forget to free the pointers!
    free(reversed);
    free(myPointer);
    return 0;
}
