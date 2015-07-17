#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<sys/stat.h>
#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<mix.hpp>
#include<io.hpp>
#include<time.h>
#include"private.hpp"

double event_e;
short *out;
//double noise_e;

void MIX::control(char *annotation){
  read_annotation(annotation,0);
  read_annotation(elabel,1);
  //snr_calc(0);
  //rand_init();
  //cut_reagion();
  //marge();
}

void MIX::read_annotation(char *annotation,int type){
  FILE *fp;
  int i=0;
  int ret;
  if(type == 0){
    if((fp = fopen(annotation,"r")) != NULL){
      while((ret=(fscanf(fp,"%f %f %s",&c_ltime[i][0], &c_ltime[i][1],c_label[i]))) != EOF){
        if((c_ltime[i][1]-c_ltime[i][0]) <= 0){
          std::cout << c_ltime[i][0] << " " << c_ltime[i][1] << " " << c_label[i] << std::endl;
        }
        i++;
      }
      fclose(fp);
    }
    events = i;
  }
  else{
    if((fp = fopen(annotation,"r")) != NULL){
      while((ret = (fscanf(fp,"%f %f %s", &e_ltime[i][0], &e_ltime[i][1], e_label[i]))) != EOF){
	if((e_ltime[i][1]-e_ltime[i][0]) <= 0){
	  std::cout << e_ltime[i][0] << " " << e_ltime[i][1] << " " << e_label[i] << std::endl;
	}
	if(strcmp(e_label[i] ,"bg") != 0 ){
	  i++;  
        }
      }
      fclose(fp);
    }
  }
}
void MIX::cut_reagion(){
  int i;	
  int high,low;

  high = e_length - c_length;
  //start = (int)(high * (double)rand()/(double)RAND_MAX);
  for(i=0;i<5;i++){
    end = (double)rand()/(double)RAND_MAX;
  }
  start = (int)( high * (double)rand() / (double)RAND_MAX);
  event_e = 0;
    
  for(i=0;i<c_length;i++){
    event_e += event[i+start] * event[i+start];
  }
   
  a_event_e = event_e/c_length;
}

void MIX::marge(){
  int i,j;
  int n,c;
    
  std::cout << "Clean\t:" << clean_e << std::endl;
  std::cout << "Noise\t:" << event_e << std::endl;
  std::cout << "事後SNR\t:" << eSNR[1] << std::endl;
}

void MIX::snr_calc(int x){
  int i,j;
  int n,c;
  n=0;
  c=0;
  clean_e = 0.0;
  event_e = 0.0;
  for(i=0;i<events;i++){
    if(strcmp(c_label[i],"bg") == 0){
      n++;
    }
    else{
      c++;
    }
    for(j=c_ltime[i][0]*samplingrate; j< c_ltime[i][1]*samplingrate && j < length; j++){
      if(strcmp(c_label[i],"bg") == 0){
  	//Sil 
  	event_e += (double)clean[j]*(double)clean[j]/(c_ltime[i][1]*samplingrate-c_ltime[i][0]*samplingrate);
      }
      if(strcmp(c_label[i],"bg") != 0){
  	//event
  	clean_e += (double)clean[j]*(double)clean[j]/(c_ltime[i][1]*samplingrate-c_ltime[i][0]*samplingrate);
      }
    }
  }
  event_e = event_e / n;
  clean_e = clean_e / c;
  b_event_e = event_e;
  eSNR[x] = 10 * log10(clean_e/event_e);
  std::cout << "Clean\t:" << clean_e << std::endl;
  std::cout << "Noise\t:" << event_e << std::endl;
  std::cout << "事前SNR\t:" << eSNR[x] << std::endl;
}


void MIX::rand_init(){
  srand((unsigned)time( NULL ));
}

