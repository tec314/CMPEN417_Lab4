#include "fpga417_lab4.h"
#include <stdio.h>

void fir(int *temp, int *data,int index, int *filter){
	int output;
	output = (temp[index]*filter[0])+(temp[index-1]*filter[1])+(temp[index-2]*filter[2]);
	data[index-2] = output;
}

void fpga417_fir(int *data, int *filter) {
	int temp[LENGTH+2]={0};
	int result;
	for (int h = 0; h < LENGTH; h++){
		temp[h]=data[h];
	}

	for (int i = 2; i < LENGTH+2; i++) {
	        fir(temp, data, i, filter);
	    }


}


