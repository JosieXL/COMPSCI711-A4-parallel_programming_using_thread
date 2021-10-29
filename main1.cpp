#include <stdio.h>
#include "functions.h"
#include "factorial.h"

int main() {
	int arr[] = { 1, 8, 6, 3, 4 };
	int maxNum = find_max(arr, 5);
	printf("max = %d\n", maxNum);
	int fac = factorial(7);
	printf("7! = %d\n", fac);
	return 0;
}