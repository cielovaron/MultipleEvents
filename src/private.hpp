#ifndef __PRIVATE_HPP
#define __PRIVATE_HPP

#define STRLEN 100

//Sound Data
extern short *idata;
extern short *out;

extern int snr;
extern short *clean;
extern long length;
extern long c_length;
extern double clean_e;
extern short *event;
extern long e_length;
extern double event_e;
//extern double noise_e;;
extern char saveid[STRLEN];
extern char elabel[STRLEN];
extern char annot[STRLEN];
extern double amp;
extern int amp_flag;


//以下wave format
extern char reafword[4];
//64bit OS
extern int fsize;
//32bit OS
//long fsize;
extern char waveword[4];
extern char fatword[4];
extern int byte;
//long byte;
extern short formatid;
extern short channel;
extern int samplingrate;
extern int datav;
extern short blocksize;
extern short samplebit;
extern char dataword[4];
extern int wavebyte;
//VAD

#endif
