/*average_raw.c	   pwe: 02/04/2015 G.G. 01/07/215
Takes rtlsdr .bin files, applies averaging in order to reduce file size, outputs reduced .bin

Command format:- average_raw <infile> <outfile> <average>*/
Compile example: gcc average_raw.c -o average_raw -lm -D_FILE_OFFSET_BITS=64

