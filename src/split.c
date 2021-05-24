#include"split.h"

#include<stdlib.h>
int compare_int(const void* left, const void* right){
	int left_int = *((int *) left);
	int right_int = *((int *) right);

	if(left_int < right_int)
		return -1;
	if(left_int > right_int)
		return 1;
	return 0;
}

int* split_n(int *n, int width, int height){
	int *res = malloc(sizeof(int) * (*n));

	for(int i = 0; i < (*n); i++){
		res[i] = rand() % width; 
	}

	qsort(res, (*n), sizeof(int), compare_int);

	return res;
}


int* split_30(int *n, int width, int height){
	*n = 30;
	return split_n(n, width, height);
}

int* split_whole_line(int *n, int width, int height){
	int *res = malloc(sizeof(int));
	*n = 1; 

	*res = width;

	return res;

}
