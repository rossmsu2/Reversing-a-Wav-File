#ifndef WAV_H
#define WAV_H

//wav_file struct to hold the specficif bytes we need
typedef struct wav_file{
    char sameVal[4];
    int chunkSize;
    char needBe[4];
    char varies[4];
    int lengthFmt;
    short fmtType;
    short numChan;
    int sampRate;
    int byteRate;
    short bAlign;
    short bitsPerSamp;
    char beginData[4];
    int sizeOfData;	
} wav_file;

wav_file* parse(char* contents);

#endif
