#include "fpga417_lab4.h"
#include <stdio.h>


void fpga417_fir(int *data, int *filter) {
	int temp[LENGTH+2]={0};
	int result;
	for (int h = 2; h < LENGTH; h++){
		temp[h]=data[h];
	}
	for (int i = 2; i < LENGTH+2; i++) {
	        result = (temp[i] * filter[0]) + (temp[i-1] * filter[1]) +  (temp[i-2] * filter[2]);
	        data[i-2] = result;
	    }


}

