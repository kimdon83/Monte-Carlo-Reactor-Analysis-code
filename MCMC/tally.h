#ifndef _tally_h_
#define _tally_h_

using namespace std;

class tally{
public:

	

	double count_scat;
	double count_cap;
	double count_loss;
	
	double pre_k;
	double keff_Csum, keff_Tsum, keff_Csq, keff_Tsq;
	double keff_C, esti_C, esti_C_temp;
	double keff_T, esti_T, esti_T_temp;

	double nsrc;
	tally();
	~tally();

	void Tal_keff(readINPUT inn, ofstream &outp, int count, bool tflag, cell *pin,int Ncycle);
	void printTal(readINPUT inn, ofstream &outp, bool tflag,cell *pin);
	
};

#endif
