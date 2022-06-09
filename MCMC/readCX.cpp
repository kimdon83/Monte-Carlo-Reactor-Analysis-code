#include <iomanip>
#include <iostream>
#include <strstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sstream>

#include "readCX.h"
using namespace std;

readCX::readCX(){
	//int step_len, j_final, stopper, step_start, step_final, err_counter;
}
readCX::~readCX(){
	//int step_len, j_final, stopper, step_start, step_final, err_counter;
}
void readCX::read(int name){
	//	copy CX file to buff	
	string s, s1;

	stringstream ss;
	ss << name << ".txt";
	s = ss.str();
	cout << "reading " << s << endl;///
	ifstream infp;
	infp.open(s);

	int loc = infp.tellg();
	infp.seekg(0, ios::end);
	int filesize = infp.tellg();
	infp.seekg(loc);

	char *buff = new char[filesize];
	infp.read(buff, filesize);
	infp.close();

	istrstream inFp(buff);
	char *tmp;
	char line[265];
	// read energy boundary
	tmp = strstr(buff, "4d");
	
	inFp.seekg((int)(tmp - buff));
	inFp >> line;
	
	for (int i = 0; i < 8; i++){
		inFp >> line;
		en_boundary[i] = atof(line);
	}
	// read CX and Nu
	tmp = strstr(buff, "7d");
	inFp.seekg((int)(tmp - buff));
	inFp >> line;
	
	for (int i = 0; i < 7; i++){
		inFp >> line;
		trans[i] = atof(line); // transport CX
	}
	for (int i = 0; i < 7; i++){
		inFp >> line;
		total_scatter[i] = atof(line); // total scattering CX
	}
	for (int i = 0; i < 7; i++){
		inFp >> line;
		fission[i] = atof(line); // fisstion CX
	}
	for (int i = 0; i < 7; i++){
		inFp >> line;
		Nu[i] = atof(line); // Nu CX
	}
	// read scattering CX (a to b)
	tmp = strstr(buff, "9d");
	inFp.seekg((int)(tmp - buff));
	inFp >> line;


	for (int j = 0; j < 7; j++){
		for (int i = 0; i < 7; i++){
			inFp >> line;
			scatter[6 - i][j] = atof(line);// scatter i to j
		}
	}
	// read Chi
	tmp = strstr(buff, "10d");//
	inFp.seekg((int)(tmp - buff));
	inFp >> line;

	for (int i = 0; i < 7; i++){
		inFp >> line;
		chi[i] = atof(line);// chi
	}
	
	delete[] buff;
	buff = NULL;
}
