#ifndef FPGA417_LAB4_H  // Include guard to prevent multiple inclusions
#define FPGA417_LAB4_H

#define LENGTH 20  // Define the length constant

// Function prototype for the FIR filter function
void fpga417_fir(int *data, int *filter);

// Function prototype for the internal FIR computation
void fir(int input, int filter[3], int* output);

#endif // FPGA417_FIR_H
