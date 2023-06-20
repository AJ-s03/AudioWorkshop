#include <iostream>
using namespace std;
#include "wav_struct.cpp"
#include <fstream>


int get_block_size(WAVHEADER header){
    BYTE bytesPerSample = header.bitsPerSample / 8;
    BYTE block_size = bytesPerSample * header.numChannels;
    return block_size;
}

int main(){
    WAVHEADER header;
    ifstream infile("input.wav", ios :: binary);
    ofstream outfile("reverse_audio.wav", ios :: binary);
    infile.read((char *) &header, sizeof(header));
    uint8_t block_size[get_block_size(header)];
    outfile.write((char *) &header, sizeof(header));
    infile.seekg(0, ios :: end);
    infile.seekg(-4, ios :: cur);
    outfile.seekp(44, ios :: beg);
    while (infile.tellg() >= 44){
        infile.read((char *) &block_size, sizeof(get_block_size(header)));
        infile.seekg(-8, ios :: cur);
        outfile.write((char *) &block_size, sizeof(get_block_size(header)));
    }
    return 0;
}