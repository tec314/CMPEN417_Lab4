#include <stdio.h>
#include <stdlib.h>

#include "fpga417_lab4_example.h"

#define LENGTH 50
int * hw_array;
int * sw_array;
int * common_array;

void init();
void deinit();
void initialize_array(int ** array, int length);
int compare_array(int * a, int * b, int length);
void copy_array(int * a, int * b, int length);
void do_add_reference(int * a, int * b, int length);
int main(void)
{
	init();
	do_add_reference(sw_array, common_array, LENGTH);
	do_array_add(hw_array, common_array, LENGTH);

	if(compare_array(hw_array, sw_array, 50) == 1)
		printf("HW does not match SW\n");
	else
		printf("HW and SW match\n");

	deinit();
	return 0;
}
void deinit()
{
	free(hw_array);
	free(sw_array);
	free(common_array);
}
void init()
{
	srand(0);
	initialize_array(&hw_array, LENGTH);
	initialize_array(&sw_array, LENGTH);
	initialize_array(&common_array, LENGTH);
	copy_array(hw_array, sw_array, LENGTH);
}
void do_add_reference(int * a, int * b, int length)
{
	int i;
	for(i = 0; i<length; ++i) a[i] = a[i] + b[i];
}
void initialize_array(int ** arr, int length)
{
	int idx;
	*arr = (int *)malloc(sizeof(int) * length);
	for(idx = 0; idx<length; ++idx)
		(*arr)[idx] = rand() % 255;
}
int compare_array(int * a, int * b, int length)
{
	int i;
	for(i = 0; i< length; ++i) if(a[i] != b[i]) return 1;
	return 0;
}
void copy_array(int * a, int * b, int length)
{
	int i;
	for(i = 0; i< length; ++i) a[i] = b[i];
}
