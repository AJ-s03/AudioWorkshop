#include <iostream>
using namespace std;
#include "wav_struct.cpp"
#include <fstream>

int main(){
    WAVHEADER header1, header2;
    int per = 0;
    ifstream infile1("input.wav", ios :: binary);   
    ifstream infile2("slow_audio.wav", ios :: binary);
    infile1.read((char *) &header1, sizeof(header1));
    infile2.read((char *) &header2, sizeof(header2)); 
    header1.sampleRate == header2.sampleRate ? per += 10 : 0;
    header1.byteRate == header2.byteRate ? per += 10 : 0;
    header1.blockAlign == header2.blockAlign ? per += 10 : 0;
    header1.subchunk2Size != header2.subchunk2Size ? per -= 50 : 0;
    if (per == 30){
        cout << "Audio files are similar." << endl;
    }
    else{
        cout << "Audio files are not similar." << endl;
    }
    return 0;
}