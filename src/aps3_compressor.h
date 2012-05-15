#ifndef APS3_COMPRESSOR_H_INCLUDED
#define APS3_COMPRESSOR_H_INCLUDED

#include "APS3.h"

struct APS3HEADER
{
   unsigned char A;
   unsigned char P;
   unsigned char Version;
   unsigned int width;
   unsigned int height;

   unsigned char background_R;
   unsigned char background_G;
   unsigned char background_B;


   unsigned char depth; // 0 = 8bit , 1 = 16bit , 2 = 24bit , 3 = 32bit

   unsigned char comment_length;
};

int decodeAPS3(struct APS3Context * aps3);
int encodeAPS3(struct APS3Context * aps3);

#endif // APS3_COMPRESSOR_H_INCLUDED
