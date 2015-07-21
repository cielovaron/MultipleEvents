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
#include<memory.hpp>
#include<mix.hpp>
#include"private.hpp"

char saveid[STRLEN];
char elabel[STRLEN];
char annot[STRLEN];

int snr;
int amp_flag;
double amp;
void useage(void){
  std::ifstream ifs("./README");
  std::string str;
  while(getline(ifs,str))
    {
      std::cout << str  << std::endl;
    }
  exit(0);
}

int main(int  argc, char *argv[]){
  /*
    変数の定義
    コマンドライン引数関連: http://www.fireproject.jp/feature/c-language/basic-library/getargs.html
    ff: File Format: 入力された音のデータについて定義, raw か wavかで読み取る方法を変えている

  */
  int opt;
  int ff;
  int cutopt=0;
  FILE *fp;
  char input[STRLEN];
  char config[STRLEN];
  char annotation[STRLEN];
  char wav[] = ".wav";
  char raw[] = ".raw";
  char *check;
  char outputsound[STRLEN];
  strcpy(saveid,"unknown.wav");
  strcpy(annot,"unknown.txt");
  amp_flag = 0;
  WAVE wave;
  MIX mix;

  MEM mem;
  //abcdefghijklmnopqrstuvwxyz
  //while((opt = getopt(argc, argv, "i:l:n:N:h:t:?:w:s:")) != -1){
  snr = 999;
  while((opt = getopt(argc, argv, "A:a:b:e:l:r:o:O:?h")) != -1){
    switch(opt){
    case 'A':{
      strcpy(input,optarg);
      amp = atof(input);
      amp_flag++;
      break;
    }
    case 'a':{
      strcpy(annotation,optarg);
      std::cout << "Annotation file\t:" << annotation << std::endl;
      break;
    }
    case 'b':{
      strcpy(input,optarg);
      std::cout << "Input file\t: " << input << std::endl;
      if((check = strstr(input,raw)) != NULL){
	ff = 2;
      }
      else if((check = strstr(input,wav)) != NULL){
	ff = 1;
      }
      wave.READ(input,ff,opt);
      c_length=length;
      break;
    }
    case 'e':{
      strcpy(input,optarg);
      std::cout << "Overlapped File\t: " << input << std::endl;
      if((check = strstr(input,raw)) != NULL){
	ff = 2;
      }
      else if((check = strstr(input,wav)) != NULL){
	ff = 1;
      }
      wave.READ(input,ff, opt);
      break;
    }
    case 'l':{
      strcpy(elabel,optarg);
      std::cout <<  "label file\t:" << elabel << std::endl;
      break;
    }
    case 'r':{
      strcpy(input,optarg);
      snr = atoi(input);
      std::cout << "SNR\t: " << snr << "[dB]"<<std::endl;
      break;
    }
    case 'o':{
      strcpy(saveid,optarg);
      std::cout << "Export file\t: " << saveid << std::endl;
      break;
    }
    case 'O':{
      strcpy(annot,optarg);
      std::cout << "Export file\t: " << annot << std::endl;
      break;
    }
    case '?':{
      useage();
      break;
    }
    default:{
      useage();
    }
    }
  }
  //mix.control(annotation);
  //std::cout << "File Length\t: " << c_length << std::endl;
  //wave.EXPORT(saveid,out,c_length);
  mem.clear();
  return 0;
}

