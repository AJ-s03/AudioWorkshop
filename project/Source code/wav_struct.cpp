#include<cstdint>

typedef uint8_t   BYTE;
typedef uint16_t  WORD;
typedef uint32_t  Dword;

typedef class{
    public:
    BYTE   chunkID[4];
    Dword  chunkSize;
    BYTE   format[4];
    BYTE   subchunk1ID[4];
    Dword  subchunk1Size;
    WORD   audioFormat;
    WORD   numChannels;
    Dword  sampleRate;
    Dword  byteRate;
    WORD   blockAlign;
    WORD   bitsPerSample;
    BYTE   subchunk2ID[4];
    Dword  subchunk2Size;
}WAVHEADER;