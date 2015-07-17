#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<sys/stat.h>
#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<memory.hpp>
#include<io.hpp>
#include"private.hpp"

void MEM::clear(void){
  int i;

  delete[] idata;
  delete[] clean;
  delete[] event;
  delete[] out;
  //delete[] energy;
  //for(i=0;i<event_num;i++){
  //	delete[] event[i];
  //}
  //delete[] event;
  //delete[] fx;
  //delete[] fy;

}
