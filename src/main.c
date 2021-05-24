#include"sort.h"
#include"compare.h"
#include"split.h"

#include<stdlib.h>


int main(int argc, char ** argv){
	if(argc != 3)
		return -1;

	sort(argv[1], argv[2], compare_hue, split_n);

	return 0;
}
