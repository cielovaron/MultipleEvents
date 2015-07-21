#ifndef __MIX_HPP
#define __MIX_HPP
class MIX{
public:
  void control(char *annotation);
private:
  void read_annotation(char *annotation,int type);
  void cut_reagion(int pos);
  void marge();
  void snr_calc(int x);
  void rand_init();
  void LABEL(char *filename, int n);

  int start,end;
  float c_ltime[500][2];
  char c_label[500][100];
  float e_ltime[500][2];
  char e_label[500][100];

  int events;
  int eventnums;
  double b_event_e;
  double a_event_e;
  double eSNR[2];
  int event_start;
};

#endif
