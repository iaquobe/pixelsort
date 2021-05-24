#include"sort.h"
#include"lodepng.h"

#include<stdio.h>
#include<stdlib.h>

void sort(char *filein, char *fileout, int (*compare)(char*, char*), int* (*split)(int *, int, int)){
	unsigned error;
	unsigned char* image = 0;
	unsigned width, height;
	
	error = lodepng_decode24_file(&image, &width, &height, filein);
	if(error){
		printf("error %u: %s\n", error, lodepng_error_text(error));
		return;
	}


	int* splits = 0;
	int nsplits = 10;
	for(int i = 0; i < height; i++){
		splits = split(&nsplits, width, height);
		int last = 0;

		for(int j = 0; j < nsplits; j++){
			unsigned char* start = image + (i * width  + last) * sizeof(char) * 3;
			unsigned int cur_width = splits[j] - last;
			qsort(start ,cur_width, sizeof(char) * 3, (int (*)(const void *, const void*))compare);

			last = splits[j]; 
		}
		free(splits);
	}


	error = lodepng_encode24_file(fileout, image, width, height);
	if(error){
		printf("error %u: %s\n", error, lodepng_error_text(error));
		return;
	}

}
