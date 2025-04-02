
#include <stdio.h>
#include "fpga417_lab4.h"

int main() {
    int data[LENGTH] = {1, 2, 3, 4, 5, 6, 7, 8};  // Input data
    int coeffs[3] = {3, 5, 3};           // Applied filter
    fpga417_fir(data, coeffs);    // Function for the filter
    return 0;
}

