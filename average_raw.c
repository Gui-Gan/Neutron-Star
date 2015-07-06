
/*average_raw.c	   pwe: 02/04/2015 G.G. 01/07/215


Command format:- average_raw <infile> <outfile> <average>*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long long int file_end,p_num;
unsigned char ucha;
unsigned char uchao;
FILE *fptr;
FILE *fpto;

int main(int argc,char *argv[])
{

unsigned long long int aux=0,aux2=0;
long double dat1=0.0;
long double dat2=0.0;
long double smt=0.0;
long long int division=0;
float aux3=0.0;

/*check command line arguments*/
if(argc !=4)
    { printf("Format: average_raw <infile> <outfile> <division> \n");
    exit(0);
    }

if((fptr=fopen(argv[1],"rb"))==NULL)
    {printf("Can't open file %s. \n",argv[1]);
    exit(0);
    }
division=(int)atof(argv[3]);
/*find length of input file*/
fseeko(fptr,0L,SEEK_END);
file_end=(long long)(ftello(fptr));
fclose(fptr);
fptr=fopen(argv[1],"rb");
fpto = fopen(argv[2],"wb");
/*read input file,decode I and Q, determine power.*/
for(aux=0;aux<file_end-1;aux+=2)
	{
		ucha=getc(fptr);	
		dat1=(float)ucha+0.0;
		dat1=(dat1-127.5)/128.0;
		ucha=getc(fptr);
		dat2=(float)ucha+0.0;
		dat2=(dat2-127.5)/128.0;
		smt=(dat1*dat1+dat2*dat2)+smt;
		aux2++;
		if(aux2==division)
			{
				aux2=0;
				smt=(smt/division);
				aux3=(float)smt;
				fwrite( &aux3, 1, sizeof(aux3), fpto ) ;
				//printf("%Lf		%f\n",smt,aux3);
				smt=0.0;
			}
	}
fclose(fptr);
fclose(fpto);
exit(0);
}
