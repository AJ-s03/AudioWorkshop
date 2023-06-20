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
    ifstream infile("mixkit-trumpet-fanfare-2293.wav", ios :: binary);
    ofstream outfile("slow_audio.wav", ios :: binary);
    infile.read((char *) &header, sizeof(header));
    uint8_t block_size[get_block_size(header)];
    header.sampleRate -= int(header.sampleRate/2);
    header.byteRate = header.sampleRate * header.numChannels * header.bitsPerSample / 8;
    outfile.write((char *) &header, sizeof(header));
    infile.seekg(44, ios :: beg);
    outfile.seekp(44, ios :: beg);
    while (infile.read((char *) &block_size, sizeof(get_block_size(header)))){
        outfile.write((char *) &block_size, sizeof(get_block_size(header)));
    }
    return 0;
}