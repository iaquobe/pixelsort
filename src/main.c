#include"pixelsort.h"
#include"compare.h"
#include"split.h"
#include"sort.h"

#include<stdlib.h>


int main(int argc, char ** argv){
	if(argc < 3 || argc > 4)
		return -1;

	char * maskfile = NULL;
	if(argc == 4)
		maskfile = argv[3]; 

	pixelsort(argv[1], argv[2], maskfile, compare_sum, split_similar, sort);

	return 0;
}
