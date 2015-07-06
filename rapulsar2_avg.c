
/*rapulsar2_avg.c	   pwe: 02/04/2015 G.G. 01/07/215
Takes rtlsdr .bin files, applies averaging and folding algorithm in blocks. Outputs text file of folded average.

Command format:- rapulsar2 <infile> <outfile> <clock rate(MHz)) <No. output data points> <Pulsar period(ms)>*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


long long int count[16384];
long long int coun;
int PTS;
long long int file_end,p_num;
long double dats[16384],clck;
double periodf,dt,res,tim;
long double sumt[16384];
unsigned char ucha;
float smt=0.0;

FILE *fptr;
FILE *fpto;

void out_dat(void);


int main(int argc,char *argv[])

{

long long int ss;
int s;


/*check command line arguments*/
if(argc !=6)
    { printf("Format: rapulsar2 <infile> <outfile> <clock rate (MHz)> <output data points> < pulsar period(ms)>\n");
    exit(0);
    }

if((fptr=fopen(argv[1],"rb"))==NULL)
    {printf("Can't open file %s. \n",argv[1]);
    exit(0);
    }

clck=1/atof(argv[3]);
PTS=atoi(argv[4]);
periodf = atof(argv[5]);
dt=periodf/(double)PTS;
 
/*find length of input file*/
fseeko(fptr,0L,SEEK_END);
file_end=(long long int)(ftello(fptr));


p_num=(long long int)((file_end)/(PTS));

printf("No. Bytes = %lld   No. Blocks=%lld   PPeriod=%fms\n",(file_end),p_num,periodf);
fclose(fptr);

fptr=fopen(argv[1],"rb");


/*read input file,decode I and Q, determine power. Sum powers in folded period and on completion calculate bin average.
 At end of input file, output text file with averaged data*/

 {coun=0;

 for(ss=0;ss<p_num;ss++)
    {

    for(s=0;s<PTS;s++)
        {
        fread(&smt, sizeof(float), 1, fptr);
        tim=(double)(s+(ss*PTS));
        res=(double)clck/(dt*(double)1000.0);
        res=(double)tim*(double)res;
        tim=(long long int)res%(long long int)PTS;

        sumt[(int)tim]=sumt[(int)tim]+(long double)smt;
        count[(int)tim]=count[(int)tim]+1;
		coun=coun+1;
        }
    }

 }

printf("No. bins=%d  Count/bin=%lld\n",PTS,count[(int)tim]);
fpto = fopen(argv[2],"w");
out_dat();
fclose(fptr);
fclose(fpto);
printf("\nInfile=%s    Outfile=%s   End bin=%d   coun=%lld\n",argv[1],argv[2],(int)tim,coun);
exit(0);
}



void out_dat(void)
{
long int tt;

for(tt=0;tt<PTS;tt++)
    {
fprintf(fpto,"%ld    %Lf   %Ld\n",(tt),(sumt[tt]/count[tt]),count[tt]);
    }
}
