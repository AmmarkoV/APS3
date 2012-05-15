#ifndef APS3_H_INCLUDED
#define APS3_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif



struct APS3Context
{
  unsigned int width;
  unsigned int height;
  unsigned int depth;

  unsigned int data_size;
  unsigned char * data;

  unsigned int aps3_data_size;
  unsigned char * aps3_data;


};


struct APS3Context * APS3_Create(unsigned int width,unsigned int height,unsigned int depth);
int APS3_Destroy(struct APS3Context * aps3);

int APS3_AddFrame(struct APS3Context * aps3,unsigned int pos_x,unsigned int pos_y,unsigned int width,unsigned int height,unsigned int depth,unsigned char * frame);

int APS3_Write(struct APS3Context * aps3, char * filename);
int APS3_Read(struct APS3Context * aps3, char * filename);

#ifdef __cplusplus
}
#endif

#endif // APS3_H_INCLUDED
