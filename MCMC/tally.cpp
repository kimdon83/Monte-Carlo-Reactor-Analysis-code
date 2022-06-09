#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "readINPUT.h"
#include "tally.h"
#include "cell.h"

using namespace std;

tally::tally(){
	count_scat=0;
	count_cap=0;
	count_loss=0;

	pre_k = 1;
	keff_C = 0;
	keff_T = 0;
	keff_Csum = 0;
	keff_Tsum = 0;
	keff_Csq = 0;
	keff_Tsq = 0;
	esti_C = 0;
	esti_C_temp = 0;
	esti_T = 0;
	esti_T_temp = 0;
}
tally::~tally(){

}
void tally::Tal_keff(readINPUT inn, ofstream &outp, int count, bool tflag, cell *pin,int Ncycle){
	int i, j;
	keff_C = esti_C / (double)inn.particle_num;
	keff_T = esti_T / (double)inn.particle_num;
	pre_k = keff_C;
	//if (tflag){
		nsrc = Ncycle;
		double Csum=keff_Csum / nsrc;
		double Csq = sqrt((keff_Csq / nsrc - Csum*Csum) / (nsrc - 1));
		double Tsum=keff_Tsum / nsrc;
		double Tsq= sqrt((keff_Tsq / nsrc - Tsum*Tsum) / (nsrc - 1));

		cout << "  keff_C" << " " << keff_C << " (" << Csq << ") " << "  keff_T" << " " << keff_T << " (" << Tsq << ") " << " " << count << endl;
		outp << "  keff_C" << " " << keff_C << " (" << Csq << ") " << "  keff_T" << " " << keff_T << " (" << Tsq << ") " << " " << count << endl;
	/*}
	else{
		nsrc = inn.inactCycle;
		cout << "  keff_C" << "  " << keff_C << "  keff_T" << " " << keff_T << "   " << count << endl;
		outp << "  keff_C" << "  " << keff_C << "  keff_T" << " " << keff_T << "   " << count << endl;
	}*/

	
	
	keff_Csum += keff_C;
	keff_Csq += keff_C*keff_C;

	keff_Tsum += keff_T;
	keff_Tsq += keff_T*keff_T;

	if (tflag){
		for (j = 0; j < inn.y_num_fi; j++){
			for (i = 0; i < inn.x_num_fi; i++){
				pin[i + inn.x_num_fi*j].cell_flux_sum += pin[i + inn.x_num_fi*j].cell_flux;
				pin[i + inn.x_num_fi*j].cell_flux_sq += pin[i + inn.x_num_fi*j].cell_flux*pin[i + inn.x_num_fi*j].cell_flux;

				pin[i + inn.x_num_fi*j].cell_power_sum += pin[i + inn.x_num_fi*j].cell_power;
				pin[i + inn.x_num_fi*j].cell_power_sq += pin[i + inn.x_num_fi*j].cell_power*pin[i + inn.x_num_fi*j].cell_power;
			}
		}
	}
	
	esti_C = 0;
	esti_T = 0;

	for (j = 0; j < inn.y_num_fi; j++){
		for (i = 0; i < inn.x_num_fi; i++){
			pin[i + inn.x_num_fi*j].cell_flux = 0;
			pin[i + inn.x_num_fi*j].cell_power = 0;
		}
	}
}
void tally::printTal(readINPUT inn, ofstream &outp, bool tflag, cell *pin){
	int i, j;
	if (tflag){
		nsrc = inn.actCycle;
	}
	else{
		nsrc = inn.inactCycle;
	}
	
	keff_Csum /= nsrc;
	keff_Csq = sqrt((keff_Csq / nsrc - keff_Csum*keff_Csum) / (nsrc - 1));
	keff_Tsum /= nsrc;
	keff_Tsq = sqrt((keff_Tsq / nsrc - keff_Tsum*keff_Tsum) / (nsrc - 1));

	cout << " keff_C " << keff_Csum << " " << keff_Csq << " keff_T " << keff_Tsum <<" " << keff_Csq<<endl;
	outp << " keff_C " << keff_Csum << " " << keff_Csq << " keff_T " << keff_Tsum << " " << keff_Csq << endl;


	keff_Csum = 0;
	keff_Csq = 0;
	keff_Tsum = 0;
	keff_Tsq = 0;
	
	/*int nsrc = inn.x_num_fi* inn.y_num_fi*inn.actCycle;
	int cellsize = inn.x_num_fi* inn.y_num_fi;
	for (int i = 0; i < cellsize; i++){
		pin[i].keff_C = pin[i].keff_Csum/ nsrc;
		pin[i].keff_T = pin[i].keff_Tsum/ nsrc;
	}*/
	outp << endl;
	if (tflag){
		cout.setf(ios::scientific, ios::floatfield);
		outp.setf(ios::scientific, ios::floatfield);

		for (j = 0; j < inn.y_num_fi; j++){
			for (i = 0; i < inn.x_num_fi; i++){
				pin[i + inn.x_num_fi*j].cell_flux_sum /= nsrc;
				pin[i + inn.x_num_fi*j].cell_flux_sq = sqrt((pin[i + inn.x_num_fi*j].cell_flux_sq / nsrc - pin[i + inn.x_num_fi*j].cell_flux_sum*pin[i + inn.x_num_fi*j].cell_flux_sum) / (nsrc - 1));
				pin[i + inn.x_num_fi*j].cell_power_sum /= nsrc;
				pin[i + inn.x_num_fi*j].cell_power_sq = sqrt((pin[i + inn.x_num_fi*j].cell_power_sq / nsrc - pin[i + inn.x_num_fi*j].cell_power_sum*pin[i + inn.x_num_fi*j].cell_power_sum) / (nsrc - 1));
			}
		}
		outp << "*********************PinFluxTally**************************" << endl;
		for (j = 0; j < inn.y_num_fi; j++){
			for (i = 0; i < inn.x_num_fi; i++){
				outp << pin[i + inn.x_num_fi*j].cell_flux_sum << " ";
			}
			outp << endl;
		}
		outp << endl;
		outp << "*********************PinFlux_Rel.SD_Tally**************************" << endl;
		for (j = 0; j < inn.y_num_fi; j++){
			for (i = 0; i < inn.x_num_fi; i++){
				outp << pin[i + inn.x_num_fi*j].cell_flux_sq / pin[i + inn.x_num_fi*j].cell_flux << " ";
			}
			outp << endl;
		}
		outp << endl;
		outp << "*********************PinPowerTally**************************" << endl;
		for (j = 0; j < inn.y_num_fi; j++){
			for (i = 0; i < inn.x_num_fi; i++){
				outp << pin[i + inn.x_num_fi*j].cell_power_sum << " ";
			}
			outp << endl;
		}
		outp << endl;
		outp << "*********************PinPower_Rel.SD_Tally**************************" << endl;
		for (j = 0; j < inn.y_num_fi; j++){
			for (i = 0; i < inn.x_num_fi; i++){
				outp << pin[i + inn.x_num_fi*j].cell_power_sq / pin[i + inn.x_num_fi*j].cell_power_sq << " ";
			}
			outp << endl;
		}
	}
	
}
