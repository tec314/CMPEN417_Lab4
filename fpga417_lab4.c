#include "fpga417_lab4.h"
#include <stdio.h>


void fpga417_fir(int *data, int *filter) {
    int filter_coeff[3];
    int temp;

    for (int h = 0; h < 3; h++) {
            filter_coeff[h] = filter[h];
        }

    for (int i = 0; i < LENGTH+2; i++) {
    	fir(data[i], filter_coeff, &temp);
    	if (i>1 ){
    		data[i-2]=temp;

    	}
    }

}

void fir(int input, int filter[3],int*output){
	static int delay_line[3] = {0};  //Keep delay results throughout iterations
	    int result = 0;

	    delay_line[2]=delay_line[1]; //Shift the delay registers
	    delay_line[1]=delay_line[0];
	    delay_line[0]=input;

	    result = (delay_line[0]*filter[0])+(delay_line[1] * filter[1])+(delay_line[2]*filter[2]);

	    *output = result;//Write the output to the data
}
