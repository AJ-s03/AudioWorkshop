#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;


// #pragma comment(lib, "winmm.lib")

int main(){
    PlaySound(TEXT("input.wav"), NULL, SND_SYNC);
    return 0;
}