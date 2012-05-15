#include <stdio.h>
#include <stdlib.h>
#include "../APS3.h"


#define PPMREADBUFLEN 256

struct Image
{
  char * pixels;
  unsigned int size_x;
  unsigned int size_y;
  unsigned int depth;
  unsigned int image_size;
};


int ReadPPM(char * filename,struct Image * pic)
{
    FILE *pf=0;
    pf = fopen(filename,"rb");

    if (pf!=0 )
    {
        char buf[PPMREADBUFLEN], *t;
        unsigned int w=0, h=0, d=0;
        int r=0;

        t = fgets(buf, PPMREADBUFLEN, pf);
        if ( (t == 0) || ( strncmp(buf, "P6\n", 3) != 0 ) ) { fclose(pf); return 0; }
        do
        { /* Px formats can have # comments after first line */
           t = fgets(buf, PPMREADBUFLEN, pf);
           if ( t == 0 ) { fclose(pf); return 0; }
        } while ( strncmp(buf, "#", 1) == 0 );
        r = sscanf(buf, "%u %u", &w, &h);
        if ( r < 2 ) { fclose(pf); return 0; }
        // The program fails if the first byte of the image is equal to 32. because
        // the fscanf eats the space and the image is read with some bit less
        r = fscanf(pf, "%u\n", &d);
        if ( (r < 1) || ( d != 255 ) ) { fclose(pf); return 0; }

        if ( (w!=pic->size_x) || (h!=pic->size_y) )
           {
             fprintf(stderr,"Incorrect file size ( %s ) :P\n",filename);
             if ( w * h > pic->size_x * pic->size_y )
               {
                 fprintf(stderr,"File %s will lead to overflow stopping read..\n",filename);
                 fclose(pf);
                 return 0;
               }
           }

        if ( pic->pixels != 0 )
        {
            size_t rd = fread(pic->pixels,3, w*h, pf);
            fclose(pf);
            if ( rd < w*h )
            {
               return 0;
            }
            return 1;
        }
        fclose(pf);
    }
  return 0;
}

int WritePPM(char * filename,struct Image * pic)
{

    FILE *fd=0;
    fd = fopen(filename,"wb");

    if (fd!=0)
	{
     unsigned int n=0;

     fprintf(fd, "P6\n%d %d\n255\n", pic->size_x, pic->size_y);
     n = (unsigned int ) ( pic->size_x * pic->size_y ) ;

     fwrite(pic->pixels, 3, n, fd);

     fflush(fd);
     fclose(fd);

     return 1;
	}

  return 0;
}


void ComplainAboutCalling()
{
 fprintf(stderr,"Usage ------------------------------\n");
 fprintf(stderr,"apsconverter -d image.aps3 image.ppm  | if you want to decode an aps3 image OR \n");
 fprintf(stderr,"apsconverter -e image.ppm image.aps3  | if you want to encode an aps3 image \n");
}




int EncodeFile(char * input_file,char * output_file)
{
 return 0;
}


int DecodeFile(char * input_file,char * output_file)
{
 return 0;
}


int main(int argc, char *argv[])
{
    printf("APS Converter!\n");

    int i=0;
        for (i=0; i<argc; i++)
         {
             if (strcmp(argv[i],"-e")==0)
                   { if (i+2<=argc)
                     {
                       fprintf(stderr,"Encode - %s to %s APS file \n",argv[i+1],argv[i+2]);
                       return EncodeFile(argv[i+1],argv[i+2]);
                     } else
                     {
                       ComplainAboutCalling();
                       return 1;
                     }
                   } else
              if (strcmp(argv[i],"-d")==0)
                   {
                     if (i+2<=argc)
                     {
                       fprintf(stderr,"Encode - %s to %s APS file \n",argv[i+1],argv[i+2]);
                       return DecodeFile(argv[i+1],argv[i+2]);
                     } else
                     {
                       ComplainAboutCalling();
                       return 1;
                     }
                   }

         }

    return 0;

}
