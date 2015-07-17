#ifndef __SS_HPP
#define __SS_HPP
class SS{
public:
	void ss_main(void);
private:
	//fuctions
	int label(void);
	void ns_profile(int c);
	void mk_window(int f);
	void ss_process(void);
	//variables
	int tshiftpoint;
	float *ltime[2];
	double *wf;
	char name[100][100];
};
#endif