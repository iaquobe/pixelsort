#include"sort.h"


void sort(void* start, size_t len, size_t size_el, __compar_fn_t compare){
	if(rand() % 100 < 100){
		qsort(start, len, size_el, compare);
	}
}
