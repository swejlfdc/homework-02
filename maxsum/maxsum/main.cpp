#include "maxsum.h"
#include<cstdio>
#include<cstring>
#include<cstdlib>

int c[MAXROW][MAXCOL];
extern int N, M;
extern bool HEXT, VEXT, FROMFILE, FINDRECT;

void inputFromFile(char* filename) {
 	FILE* inputfile = fopen(filename, "r");
	fscanf(inputfile, "%d,%d,", &N, &M);
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < M; ++j) {
			if(j == 0) fscanf(inputfile, "%d", &c[i][j]);
			else fscanf(inputfile, ",%d", &c[i][j]);
		}
	fclose(inputfile);
}

int main(int argc, char** args) {
	char filename[256];
	for(int i = 1; i < argc; ++i) {
		if(strcmp(args[i], "/h") == 0) HEXT = true;
		if(strcmp(args[i], "/v") == 0) VEXT = true;
		if(strcmp(args[i], "/a") == 0) FINDRECT = false;
		if(args[i][0] != '/')
			FROMFILE = true,
			memcpy(filename, args[i], strlen(args[i])+1);
	}
	if(FROMFILE) inputFromFile(filename);
	int scanRow(N), scanCol(M);
	if(VEXT) 
		VDoubleExtend(c, N, M), M *= 2;
	if(HEXT) 
		HDoubleExtend(c, N, M), N *= 2;
	int ans;
	if(FINDRECT) 
		ans = maxsum(c, N, M, scanRow, scanCol);
	else  
		ans = maxUnicomBlock(c, N, M, scanRow, scanCol);

	printf("%d\n", ans);
	system("pause");	
	return 0;
}
