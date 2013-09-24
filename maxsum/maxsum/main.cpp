#include<cstdio>
#include<iostream>
#define MAXCOL 1000
#define MAXROW 1000
#define getmax(a,b) if(a<b) a=b

const int inf = 0x7fffffff;
int c[MAXROW][MAXCOL];

int input(int* output) {
	int a, cnt = 0; 
	for(; ~scanf("%d", &a); ++cnt) 
		output[cnt] = a;
	return cnt;	
}

int maxsum(int* c, int size) {
	int ret = -inf, minpre = 0, prefix = 0;
	for(int i = 0; i < size; i++) {
		prefix += c[i];
		if(prefix - minpre > ret) 
			ret = prefix - minpre;
		if(prefix < minpre) minpre = prefix;
	}
	return ret;
}

int maxsum(int *mat[MAXCOL], int row_size, int col_size) {
	int arr[MAXCOL];
	int ret = -inf;
	for(int i = 0; i < row_size; ++i) {
		memset(arr, 0, sizeof(arr));
		for(int j = i; j < row_size; ++j) {
			for(int k = 0; k < col_size; ++k)
				arr[k] += mat[j][k];
			int tmp = maxsum(arr, col_size);
			getmax(ret, tmp);
		}
	}
	return ret;
}

int main(int argc, char** args) {
	num = input(c);
	ans = maxsum(c, num);
	printf("%d\n", ans);
	system("pause");
	return 0;
}