#include <stdio.h>
#include <stdlib.h>
#include "wav.h"

//Written by Gary Gritters and Ross Kuiper
//Last editted on 02/03/2020
//Will simply caste a pointer into a .wav struct
wav_file* parse(char* contents){
    return (wav_file*) contents;
}
