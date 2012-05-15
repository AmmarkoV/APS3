#ifndef APS3_H_INCLUDED
#define APS3_H_INCLUDED

struct APS3Context
{
  unsigned int width;
  unsigned int height;
  unsigned int depth;

  unsigned char * data;

};

struct APS3Context * InitAPS3Context(unsigned int width,unsigned int height,unsigned int depth);
int AddFrame(unsigned int pos_x,unsigned int pos_y,unsigned int width,unsigned int height,unsigned int depth,unsigned char * frame);


#endif // APS3_H_INCLUDED
