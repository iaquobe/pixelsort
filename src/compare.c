#include"compare.h"

float to_hue(char r, char g, char b){
	float R = (float) r / 255;
	float G = (float) g / 255;
	float B = (float) b / 255;

	float min = R;
	float max = R;
	if(min > G)
		min = G;
	if(min > B)
		min = B;

	if(max < G)
		max = G;
	if(max < B)
		max = B;

	if(R > G && R > B){
		return (G - B)/(max-min);
	}
	if(G > B){
		return 2.0 + (B - R)/(max-min);
	}
	return 4.0 + (R - G)/(max-min);

}


int compare_sum(char* left, char* right){
	char suml = left[0] + left[1] + left[2];
	char sumr = right[0] + right[1] + right[2];

	if(suml < sumr)
		return -1;
	if(suml == sumr)
		return 0;
	return 1;
}


int compare_hue(char* left, char *right){
	float left_hue = to_hue(left[0], left[1], left[2]);
	float right_hue = to_hue(right[0], right[1], right[2]);

	if(left > right)
		return -1;
	if(left < right)
		return 1;
	return 0;
}
