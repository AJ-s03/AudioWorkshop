#include <iostream>
using namespace std;
#include <fstream>
#include <cstdint>

typedef uint8_t   BYTE;
typedef uint16_t  WORD;
typedef uint32_t  DWORD;

typedef class{
    public:
    BYTE   chunkID[4];
    DWORD  chunkSize;
    BYTE   format[4];
    BYTE   subchunk1ID[4];
    DWORD  subchunk1Size;
    WORD   audioFormat;
    WORD   numChannels;
    DWORD  sampleRate;
    DWORD  byteRate;
    WORD   blockAlign;
    WORD   bitsPerSample;
    BYTE   subchunk2ID[4];
    DWORD  subchunk2Size;
}WAVHEADER;

int get_block_size(WAVHEADER header){
    BYTE bytesPerSample = header.bitsPerSample / 8;
    BYTE block_size = bytesPerSample * header.numChannels;
    return block_size;
}

int main(){
    WAVHEADER header;
    ifstream infile("input.wav", ios :: binary);
    ofstream outfile("generated_audio.wav", ios :: binary);
    infile.read((char *) &header, sizeof(header));
    uint8_t block_size[get_block_size(header)];
    outfile.write((char *) &header, sizeof(header));
    infile.seekg(44, ios :: beg);
    outfile.seekp(44, ios :: beg);
    while (infile.read((char *) &block_size, sizeof(get_block_size(header)))){
        outfile.write((char *) &block_size, sizeof(get_block_size(header)));
    }
    return 0;
}