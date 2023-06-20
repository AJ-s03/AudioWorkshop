#include <iostream>
using namespace std;
#include "wav_struct.cpp"
#include <fstream>
#include <cstring>

int main(int argc, char * argv[]){
    WAVHEADER header;
    if (argc <= 1){
        printf("Usage : ./a <input_file>.WAV\n");
        return 1;
    }
    ifstream infile(argv[2], ios :: binary);
    infile.read((char *) &header, sizeof(header));
    cout << strcmp("WAVE",char *(header.format));    



    /*cout << "chunkID : " << header.chunkID[0];
    cout << "\nchunkSize : " << header.chunkSize;
    cout << "\nformat : " << header.format[0];
    cout << "\nsubchunk1ID : " << header.subchunk1ID;
    cout << "\nsubchunk1Size : " << header.subchunk1Size;
    cout << "\naudioFormat : " << header.audioFormat;
    cout << "\nnumChannels : " << header.numChannels;
    cout << "\nsampleRate : " << header.sampleRate;
    cout << "\nbyteRate : " << header.byteRate;
    cout << "\nblockAlign : " << header.blockAlign;
    cout << "\nbitsPerSample : " << header.bitsPerSample;
    cout << "\nsubchunk2ID : " << header.subchunk2ID;
    cout << "\nsubchunk2Size : " << header.subchunk2Size;*/ 
    return 0;
}