#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"

//Written by Ross Kuiper and Gary Gritters
//Last edit 02/03/2020
//Use this file to read a .wav file into a pointer's memory location.
//Also use this file to store the data from a pointer into a file. 
size_t read_file(char* filename, char **buffer){

    //Need a file pointer to interact with the file
    FILE *fp;

    //Open it with, "r", read only
    //Open file with name "filename",
    //should be an argument from the commandline
    fp = fopen(filename, "r");
    struct stat buf;

    //Info about the file
    stat(filename, &buf);

    //Store size, to be used and passed
    size_t size = buf.st_size;

    //Malloc for new pointer
    *buffer = malloc(size*sizeof(char));
	
	//check if malloc worked
	if(buffer == NULL){
		perror("Initial buffer malloc failed");
		return 0;
	}

    //Read the file into buffer.
    //Remember, buffer is a pointer to myPointer. This will
    //remalloc myPointer to be a pointer to the data from the .wav file
    fread(*buffer, 1, size, fp);

	//
	if(feof(fp) != 0){
		perror("Read didn't finish");
		return 0;
	}

    //Close it, we don't need it anymore.
    fclose(fp);

    //Returns the size of the file
    return size;	
}

size_t write_file(char* filename, char* buffer, size_t size){

    //Again need a file pointer to properly access the file
    FILE *fp;

    //Access the file with "w". This let's us change it. 
    fp = fopen(filename, "w");

    //Change the file with the new data
    fwrite(buffer, 1, size, fp);

    //Saves the new data to the file.
    fclose(fp);

    //Returns size of file.
    return size;	
}
