#include "maxsum.h"
#include<cstdio>
#include<utility>
#include<queue>
#include<iostream>

using namespace std;

const int inf = 0x7fffffff;
int N, M;
bool HEXT(0), VEXT(0), FROMFILE(0), FINDRECT(1);


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

int maxsum(int mat[][MAXCOL], int row_size, int col_size, int rRow, int rCol) {
	int arr[MAXCOL];
	int ret = -inf;
	for(int ni = 0; ni < row_size - rRow + 1; ++ni)
		for(int nj = 0; nj < col_size - rCol + 1; ++nj) {			
			memset(arr, 0, sizeof(arr));
			for(int i = ni; i < ni + rRow && i < row_size; ++i) {
				for(int j = nj; j < nj + rCol && j < col_size; ++j)
					arr[j - nj] += mat[i][j];
				int tmp = maxsum(arr, rCol);
				getmax(ret, tmp);
			}
	}
	return ret;
}
	
int maxsum(int mat[][MAXCOL], int row_size, int col_size) {
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

int** apply2DIntArr(int row, int col) {	
	int **ret = new int*[row];
	for(int i = 0; i < row; ++i) ret[i] = new int[col];
	return ret;
}

void release2DIntArr(int** arr, int row, int col) {
	for(int i = 0; i < row; ++i) delete[col] arr[i];
	delete[row] arr;
}

void colorBlock(int** mat, int row_size, int col_size, int row, int col, int color) {
	queue<pair<int, int> > Q;
	Q.push(make_pair(row, col));
	while(!Q.empty()) {
		pair<int, int> cur = Q.front();
		Q.pop();
		int r = cur.first, c = cur.second;
		if(r < 0 || r >= row_size || c < 0 || c >= col_size) continue;
		if(mat[r][c] == -1) {
			mat[r][c] = color;
			Q.push(make_pair(r - 1, c));
			Q.push(make_pair(r, c - 1));
			Q.push(make_pair(r + 1, c));
			Q.push(make_pair(r, c + 1));
		}
	}
}

int _maxUnicomBlock(int** mat, int row_size, int col_size) {
	int** map = apply2DIntArr(row_size, col_size);
	//for(int i = 0; i < row_size; ++i) memset(map[i], 0, sizeof(int) * col_size);

	for(int i = 0; i < row_size; ++i)
		for(int j = 0; j < col_size; ++j) 
			map[i][j] = (mat[i][j] >= 0) ? -1 : 0;

	//color positive block
	int block_num = 0;
	for(int i = 0; i < row_size; ++i)
		for(int j = 0; j < col_size; ++j) 
			if(map[i][j] == -1) colorBlock(map, row_size, col_size, i, j, ++block_num);
	//count block value 
	int* block = new int[block_num + 1];
	memset(block, 0, sizeof(block) * (block_num + 1));
	for(int i = 0; i < row_size; ++i)
		for(int j = 0; j < col_size; ++j) 
			block[map[i][j]] += mat[i][j];
	int ret = -inf;
	for(int i = 1; i <= block_num; ++i) 
		getmax(ret, block[i]);
	release2DIntArr(map, row_size, col_size);
	return ret;
}

int maxUnicomBlock(int mat[][MAXCOL], int row_size, int col_size, int rRow, int rCol) {
	int** rect;
	int ret = -inf;
	//apply for memory
	rect = apply2DIntArr(rRow, rCol);
	//main program
	for(int ni = 0; ni < row_size - rRow + 1; ++ni)
		for(int nj = 0; nj < col_size - rCol + 1; ++nj) {
			for(int i = ni; i < ni + rRow; ++i)
				for(int j = nj; j < nj + rCol; ++j) 
					rect[i - ni][j - nj] = mat[i][j];
			int tmp = _maxUnicomBlock(rect, rRow, rCol);
			getmax(ret, tmp);
		}
	//release memory
	release2DIntArr(rect, rRow, rCol);
	return ret;
}

void VDoubleExtend(int mat[][MAXCOL], int row_size, int col_size) {
	for(int i = 0; i < row_size; ++i)
		for(int j = 0; j < col_size; ++j) 
			mat[i][j + col_size] = mat[i][j];
}

void HDoubleExtend(int mat[][MAXCOL], int row_size, int col_size) {
	for(int i = 0; i < row_size; ++i)
		for(int j = 0; j < col_size; ++j) 
			mat[i + row_size][j] = mat[i][j];
}