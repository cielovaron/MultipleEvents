#ifndef __FILTER_HPP
#define __FILTER_HPP
class FIL{
public:
	void filter_main(void);
	void LPF(void);
	void HPF(void);
	void BPF(void);
private:
	void mk_window(int N);
	void mk_FIR(void);
	double delta,*fe,*wf,*b;
	int J;
};
#endif