#ifndef __cut_HPP
#define __cut_HPP
class CUT{
public:
	void cut_main(void);
private:
	//fuctions
	int label(void);
	void cut_process(int c);

	//variables
	float *ltime[2];
	char name[100][100];
};
#endif