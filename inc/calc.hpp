#ifndef __CALC_HPP
#define __CALC_HPP

class CALC{
public:
	double energy(int start, int end);
	double movingaverage(int c,int band,int opt,double *input);
	double filter_energy(short *input);
	double SpSmooth(int c, int band, double *input);
	void sfft(int l, int flag);
	double sinc(double a);
};

#endif
