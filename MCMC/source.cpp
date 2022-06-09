#include <stdio.h>
#include <iostream>

#include "rng.h"
#include "readINPUT.h"
#include "source.h"
#include "particle.h"
#include "ptcRUN.h"
#include "readCX.h"

#include "define.h"

extern rng RN;

source::source(){
	using namespace std;
	cout << "making source" << endl;///
}
source::~source(){
	
}
void source::mk_source(readINPUT &input, CriData &Data){
	if (input.mode == 1){ // 1: C_SOURCE, 2: S_SOURCE mode
		//make source particles
		int num = input.particle_num;
		
		Data.x = input.x_s + (input.xh_s - input.x_s)*RN.gnRN();
		Data.y = input.y_s + (input.yh_s - input.y_s)*RN.gnRN();
		Data.z = input.z_s + (input.zh_s - input.z_s)*RN.gnRN();
			
		Data.time = 0;
		Data.En = input.s_en;
	}
}