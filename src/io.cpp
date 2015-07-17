/*
  音声入力用関数
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<sys/stat.h>
#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<io.hpp>
#include"private.hpp"

short *idata;
short *clean;
long length;
long c_length;
double clean_e;
short *event;
long e_length;

//int fftpoint;
int fftpower;  // Num of FFT  points on power: log
long totalframe;
char ftype[100];
double *energy;
double *power;
double *loge;
char modeldir[100];

//wave format
char reafword[4];
//64bit OS
int fsize;
//32bit OS
//long fsize;
char waveword[4];
char fatword[4];
int byte;
//long byte;
short formatid;
short channel;
int samplingrate;
int datav;
short blocksize;
short samplebit;
char dataword[4];
int wavebyte;

void WAVE::READ(char *filename, int fm, char opt){
  //変数定義
  struct stat buf;
  FILE *in;

  in = fopen(filename,"rb");

  switch (fm){
  case 1:{
    fread(reafword,4,1,in);
    fread(&fsize,4,1,in);
    fread(waveword,4,1,in);
    fread(fatword,4,1,in);
    fread(&byte,4,1,in);
    fread(&formatid,2,1,in);
    fread(&channel,2,1,in);
    fread(&samplingrate,4,1,in);
    fread(&datav,4,1,in);
    fread(&blocksize,2,1,in);
    fread(&samplebit,2,1,in);
    fread(dataword,4,1,in);
    fread(&wavebyte,4,1,in);
    samples = wavebyte / (samplebit * channel) * 8;
    idata = new short [samples];
    fread(idata,sizeof(short),samples,in);
    break;
  }
  case 2:{
    samples = buf.st_size / sizeof(short);
    idata = new short [samples];
    fread(idata, sizeof(short),samples,in);
    break;
  }
  case 3:{
    //read configure file
  }
  default :{
    std::cout << "This application is not supported for the audio format. Please convert other format" << std::endl;
    break;
  }
  }
  fclose(in);

  switch (opt){
  case 'b':{
    clean_e = 0.0;
    clean = new short[samples];
    for(int i=0; i < samples; i++){
      clean[i] = idata[i];
      clean_e += clean[i] * clean[i];
    }

    length = samples;
      
    //clean_e= clean_e / length;
    //std::cout << clean_e << std::endl;
    break;
  }
  case 'e':{
    event = new short[samples];
    for(int i=0; i < samples; i++){
      event[i] = idata[i];
    }
    //std::cout << samples << std::endl;
    e_length = samples;
    break;
  }
  default:{
    break;
  }
  }
}


void WAVE::EXPORT(char *filename,short *odata, long num){
  //変数定義
  char word[4];
  long temp;
  short a;
  int b;
  long time;
  FILE *out;

  //処理開始
  time = num * 2;
  out = fopen(filename, "wb");
  sprintf(word,"RIFF");
  fwrite(word,4,1,out);
  temp = time + 36;
  fwrite(&temp,4,1,out);
  sprintf(word,"WAVE");
  fwrite(word,4,1,out);
  sprintf(word,"fmt ");
  fwrite(word,4,1,out);
  b = 16;
  fwrite(&b,4,1,out);
  a=1;
  fwrite(&a,2,1,out);
  fwrite(&channel,2,1,out);
  fwrite(&samplingrate,4,1,out);
  fwrite(&datav,4,1,out);
  fwrite(&blocksize,2,1,out);
  a = 16;
  fwrite(&a,2,1,out);
  sprintf(word,"data");
  fwrite(word,4,1,out);
  fwrite(&time,4,1,out);
  for(b=0;b<num;b++){
    fwrite(&odata[b],sizeof(short),1,out);
  }
  fclose(out);
}
