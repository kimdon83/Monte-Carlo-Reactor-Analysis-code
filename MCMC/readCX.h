#ifndef _readCX_h_
#define _readCX_h_


class readCX{
public:
	
	double trans[7];
	double total_scatter[7];
	double fission[7];
	double Nu[7];
	double chi[7];
	double scatter[7][7]; //a to b
	double en_boundary[8];
	//numbering is g-1 eg. CX[4]-> group 5

	readCX();
	~readCX();
	void read(int);
};
#endif
