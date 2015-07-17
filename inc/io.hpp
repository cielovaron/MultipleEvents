#ifndef __IO_HPP
#define __IO_HPP
class WAVE{
public:
	void READ(char *filename, int type, char opt);
	void EXPORT(char *filename, short *odata,long num);
private:
	long samples;
};

#endif