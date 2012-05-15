#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "APS3.h"
#include "aps3_compressor.h"


int APS3ContextIsOk(struct APS3Context * aps3)
{
  if (aps3!=0) { return 1;}
  return 0;
}

struct APS3Context * APS3_Create(unsigned int width,unsigned int height,unsigned int depth)
{
 struct APS3Context * aps3=0;

 aps3 = (struct APS3Context *) malloc(sizeof(struct APS3Context));

 if (aps3!=0)
  {
      aps3->width=width;
      aps3->height=height;
      aps3->depth=depth;

      aps3->data_size=0;
      aps3->data=0;


      aps3->aps3_data_size=0;
      aps3->aps3_data=0;
  }

 return aps3;
};

int APS3_Destroy(struct APS3Context * aps3)
{
  if (APS3ContextIsOk(aps3))
  {
    if (aps3->data!=0) { free(aps3->data); }
    if (aps3->aps3_data!=0) { free(aps3->aps3_data); }
    free(aps3);
  }

 return 1;
};


int APS3_AddFrame(struct APS3Context * aps3,unsigned int pos_x,unsigned int pos_y,unsigned int width,unsigned int height,unsigned int depth,unsigned char * frame)
{
 if (APS3ContextIsOk(aps3))
   {
     if ((pos_x==0)&&(pos_y==0)&&(aps3->width==width)&&(aps3->height==height) )
      {
          memcpy(aps3->data,frame,width*height*3*sizeof(unsigned char));
          return 1;
      } else
      {
          fprintf(stderr,"Currently unhandled AddFrame operation\n");
      }
   }
 return 0;
};


int APS3_ConvertTo(struct APS3Context * aps3)
{
    return encodeAPS3(aps3);
}


int APS3_ConvertFrom(struct APS3Context * aps3)
{
    return decodeAPS3(aps3);
}


int APS3_Write(struct APS3Context * aps3, char * filename)
{
  if (APS3ContextIsOk(aps3))
   {
     if (!APS3_ConvertTo(aps3))
      {
         fprintf(stderr,"Failed to convert to APS3\n");
      } else
     if (aps3->aps3_data!=0)
      {
        FILE * pFile=0;
        pFile = fopen (filename,"wb");
        if (pFile!=0)
         {
          fwrite (aps3,1,sizeof(struct APS3Context),pFile);
          fwrite (aps3->aps3_data,1,aps3->aps3_data_size, pFile );
          fclose (pFile);
          return 1;
         }
      }
   }
 return 0;
};

int APS3_Read(struct APS3Context * aps3, char * filename)
{
  if (APS3ContextIsOk(aps3))
   {
        FILE * pFile=0;
        pFile = fopen (filename,"rb");
        if (pFile!=0)
         {
          struct APS3Context tmp={0};
          tmp.data=0; tmp.aps3_data=0;

          fread (&tmp,1,sizeof(tmp),pFile);
          *aps3=tmp;
          fread (aps3->aps3_data , 1 , sizeof(aps3->aps3_data) , pFile );
          fclose (pFile);

          if (!APS3_ConvertFrom(aps3))
          {
            fprintf(stderr,"Failed to convert from APS3\n");
            return 0;
          }

          return 1;
         }

   }
 return 0;
};
