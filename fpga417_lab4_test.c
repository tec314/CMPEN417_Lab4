
#include <stdio.h>
#include "fpga417_lab4.h"

int main() {
    int data[LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8};  // Your input data
    int coeffs[3] = {3, 5, 3};           // Filter coefficients
    fpga417_fir(data, coeffs);           // Apply the FIR filter
    return 0;
}

