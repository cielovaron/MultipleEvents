#ifndef __RECG_HPP
#define __RECG_HPP

class RECG{
public:
	void center(int start, int end);
private:
	void analyse(int start, int end, char *name);
	void mkfeature(int start, int end);
	void exe_hcopy(void);
	void hvite_htk(int start, int end);
};

#endif