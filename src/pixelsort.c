#include"pixelsort.h"
#include"lodepng.h"

#include<stdio.h>

#define ELEM_SIZE sizeof(char) * 3

unsigned char* read_from_mask(int line, int width, unsigned char* image, unsigned char* mask, int *len){
	*len = 0;
	for(int i = 0; i < width; i++){
		if(mask + (line * width + i) * ELEM_SIZE)
			(*len)++;
	}

	unsigned char* res = malloc((*len) * ELEM_SIZE);
	int res_position = 0; 
	for(int i = 0; i < width; i++){
		if(*(mask + (line * width + i) * ELEM_SIZE)){
			*(res + res_position * ELEM_SIZE + 0) = *(image + (line * width + i) * ELEM_SIZE + 0);
			*(res + res_position * ELEM_SIZE + 1) = *(image + (line * width + i) * ELEM_SIZE + 1);
			*(res + res_position * ELEM_SIZE + 2) = *(image + (line * width + i) * ELEM_SIZE + 2);
			res_position++;
		}
	}

	return res;
}



void write_from_mask(int line, int width, unsigned char *image, unsigned char* masked_values, unsigned char* mask){

	int masked_value_position = 0;
	for(int i = 0; i < width; i++){

		// mask is set
		if(*(mask + (line * width + i) * ELEM_SIZE)){
			*(image + (line * width + i) * ELEM_SIZE + 0) = *(masked_values + masked_value_position * ELEM_SIZE + 0);
			*(image + (line * width + i) * ELEM_SIZE + 1) = *(masked_values + masked_value_position * ELEM_SIZE + 1); 
			*(image + (line * width + i) * ELEM_SIZE + 2) = *(masked_values + masked_value_position * ELEM_SIZE + 2);
			masked_value_position++;
		}
	}

}

void pixelsort(char *filein, char *fileout, char *filemask, int (*compare)(char*, char*), int* (*split)(int *, int), void (*sort)(void*, size_t, size_t, __compar_fn_t)){

	// read image
	unsigned error;
	unsigned char* image = 0;
	unsigned width, height;
	error = lodepng_decode24_file(&image, &width, &height, filein);
	if(error){
		printf("error %u: %s\n", error, lodepng_error_text(error));
		return;
	}


	// read mask
	unsigned char* mask = 0;
	unsigned width_mask, height_mask; 
	if(filemask != NULL){
		error = lodepng_decode24_file(&mask, &width_mask, &height_mask, filemask);
		if(error){
			printf("error %u: %s\n", error, lodepng_error_text(error));
			return;
		}
		if(width_mask != width || height_mask != height){
			printf("mask and image have different dimensions");
			return;
		}
	}


	int* splits = 0;
	int nsplits = 20;
	for(int i = 0; i < height; i++){
		unsigned char* line = image + (i * width) * ELEM_SIZE;
		int line_len = width; 

		// change if mask is active
		if(filemask != NULL){
			line = read_from_mask(i, width, image, mask, &line_len);
		}



		splits = split(&nsplits, line_len);
		int last = 0;

		for(int j = 0; j < nsplits; j++){
			unsigned int cur_width = splits[j] - last;
			sort(line + last * ELEM_SIZE, cur_width, ELEM_SIZE, (int (*)(const void *, const void*))compare);

			last = splits[j]; 
		}
		free(splits);


		// write back to image if mask active
		if(filemask != NULL){
			write_from_mask(i, width, image, line, mask);
			free(line);
		}
	}


	// save image
	error = lodepng_encode24_file(fileout, image, width, height);
	if(error){
		printf("error %u: %s\n", error, lodepng_error_text(error));
		return;
	}

}
