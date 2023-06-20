#include <iostream>
#include "wav_struct.cpp"
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

int lock = 0;

class Reverse{
    public:
        WAVHEADER header;
        Reverse(){};
        Reverse(char path[50]){
            ifstream infile(path, ios :: binary);
            infile.read((char *) &header, sizeof(header));
        }
        void reverse_audio(int Block_size, char path[50]);
        friend int get_block_size();
        
};

void Reverse :: reverse_audio(int Block_size, char path[50]){
    ifstream infile(path, ios :: binary);
    ofstream outfile("reverse_audio.wav", ios :: binary);
    uint8_t *block_size = new uint8_t[Block_size];
    outfile.write((char *) &header, sizeof(header));
    infile.seekg(0, ios :: end);
    infile.seekg(-4, ios :: cur);
    outfile.seekp(44, ios :: beg);
    while (infile.tellg() >= 44){
        infile.read((char *) &block_size, sizeof(Block_size));
        infile.seekg(-8, ios :: cur);
        outfile.write((char *) &block_size, sizeof(Block_size));
    }
    return;
}

class fast{
    public:
        WAVHEADER header;
        int factor = 1;
        fast(){};
        fast(char path[50]){
            ifstream infile(path, ios :: binary);
            infile.read((char *) &header, sizeof(header));
        }
        void fast_audio(int Block_size, char path[50]);
        friend int get_block_size();
};

void fast :: fast_audio(int Block_size, char path[50]){
    ifstream infile(path, ios :: binary);
    ofstream outfile("fast_audio.wav", ios :: binary);
    uint8_t *block_size = new uint8_t[Block_size];
    header.sampleRate += int(header.sampleRate/factor);
    header.byteRate = header.sampleRate * header.numChannels * header.bitsPerSample / 8;
    outfile.write((char *) &header, sizeof(header));
    infile.seekg(44, ios :: beg);
    outfile.seekp(44, ios :: beg);
    while (infile.read((char *) &block_size, sizeof(Block_size))){
        outfile.write((char *) &block_size, sizeof(Block_size));
    }
    return;
}

class slow{
    public:
        WAVHEADER header;
        int factor = 2;
        slow(){};
        slow(char path[50]){
            ifstream infile(path, ios :: binary);
            infile.read((char *) &header, sizeof(header));
        }
        void slow_audio(int Block_size, char path[50]);
        friend int get_block_size();
};

void slow :: slow_audio(int Block_size, char path[50]){
    ifstream infile(path, ios :: binary);
    ofstream outfile("slow_audio.wav", ios :: binary);
    uint8_t *block_size = new uint8_t[Block_size];
    header.sampleRate -= int(header.sampleRate/factor);
    header.byteRate = header.sampleRate * header.numChannels * header.bitsPerSample / 8;
    outfile.write((char *) &header, sizeof(header));
    infile.seekg(44, ios :: beg);
    outfile.seekp(44, ios :: beg);
    while (infile.read((char *) &block_size, sizeof(Block_size))){
        outfile.write((char *) &block_size, sizeof(Block_size));
    }
    return;
}

class cmp{
    public:
    WAVHEADER header1, header2;
    int per = 0;
    cmp(){}
    cmp(char path[50], char path2[50]){
        ifstream infile1(path, ios :: binary);   
        ifstream infile2(path2, ios :: binary);
        infile1.read((char *) &header1, sizeof(header1));
        infile2.read((char *) &header2, sizeof(header2));
    }
    void compare();
};

void cmp :: compare(){
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
    return;
}

int get_block_size(WAVHEADER header){
    BYTE bytesPerSample = header.bitsPerSample / 8;
    BYTE block_size = bytesPerSample * header.numChannels;
    return block_size;
}


int main(){
    Reverse ob1;
    fast ob2;
    slow ob3;
    cmp ob4;
    char file[50];
    int ch;
    char c;
    while (1){
        if (lock == 0){
            A:
            cout <<"File path : ";
            cin >> file;
            cout << "Lock file(y/n) : ";
            cin >> c;
            if (c == 'y' || c == 'Y'){
                lock = 1;
            }
            else if (c == 'n' || c == 'N'){
                lock = 0;
            }
        }
        cout << "Enter the choices.\n";
        cout << "1 to Reverse the audio.\n";
        cout << "2 to increase the playback speed.\n";
        cout << "3 to decrease the playback speed.\n";
        cout << "4 to compare two audio fils.\n";
        cout << "5 to play the music.\n";
        cout << "6 to start over.\n";
        cout << "7 to exit\n";
        cin >> ch;
        switch (ch){
        case 1:
            ob1 = Reverse(file);
            ob1.reverse_audio(get_block_size(ob1.header), file);
            cout << "The audio has been reversed successfully. Search for ""reverse_audio"" file.\n";
            break;
        case 2:
            ob2 = fast(file);
            ob2.fast_audio(get_block_size(ob2.header), file);
            cout << "Playback speed has been increased by the factor of " << ob2.factor;
            cout << ". Search for ""fast_audio"" file.\n";
            break;
        case 3:
            ob3 = slow(file);
            ob3.slow_audio(get_block_size(ob3.header), file);
            cout << "Playback speed has been decreased by the factor of " << ob3.factor;
            cout << ". Search for ""slow_audio"" file.\n";
            break;
        case 4:
            char file2[50];
            cout << "Path of the file to be compared : ";
            cin >> file2;
            ob4 = cmp(file, file2);
            ob4.compare();
            break;
        case 5:
            PlaySound(TEXT(file), NULL, SND_SYNC);
            break;
        case 6:
            goto A;
        case 7:
            exit(0);
        default:
            break;
        }
    }
    return 0;
}