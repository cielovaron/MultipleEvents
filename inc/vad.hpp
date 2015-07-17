#ifndef __VAD_HPP
#define __VAD_HPP
class VAD{
public:
	void vad_main(void);
private:
	void pre(void);
	void seek(void);
	void classifier(int frameid);
	double eave;
	double save;
	double lave;
};
#endif
