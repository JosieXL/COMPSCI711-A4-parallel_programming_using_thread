#include <stdio.h>
#include "functions.h"
#include "factorial.h"

int main() {
	printf("hello world\n");
	int arr[] = { 1, 8, 6, 3, 4 };
	int maxNum = find_max(arr, 5);
	printf("max = %d\n", maxNum);
	int fac = factorial(5);
	printf("5! = %d\n", fac);
	return 0;
}