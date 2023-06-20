#include <iostream>
using namespace std;
#include "wav_struct.cpp"
#include <fstream>

int main(){
    WAVHEADER header;
    ifstream infile("mixkit-trumpet-fanfare-2293.wav", ios :: binary);
    infile.read((char *) &header, sizeof(header));
    cout << header.subchunk2Size;
    if (header.subchunk2Size % 2 != 0){
        header.subchunk2Size++; 
    }
    return 0;
}