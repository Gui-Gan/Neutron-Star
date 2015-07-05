/*rapulsar2.c	   pwe: 02/04/2015
                G.G. 01/07/2015
Takes rtlsdr averaged with "average_raw" .bin files, applies averaging and folding algorithm in blocks. Outputs text file of folded average.

Command format:- rapulsar2 <infile> <outfile> <clock rate(MHz)) <No. output data points> <Pulsar period(ms)>*/
Compile Example: gcc RAPULSAR2_avg.C -o RAPULSAR2_avg -lm -D_FILE_OFFSET_BITS=64 -Wall
