#ifndef MAXSUM_H
#define MAXSUM_H
#ifdef MAXSUM_EXPORTS
#define MAXSUM_API   __declspec( dllexport )
#else
#define MAXSUM_API   __declspec( dllimport )
#endif
#define MAXCOL 2000
#define MAXROW 2000
#define getmax(a,b) if(a<b) a=b

MAXSUM_API int maxsum(int mat[][MAXCOL], int row_size, int col_size, int rRow, int rCol);
MAXSUM_API int maxUnicomBlock(int mat[][MAXCOL], int row_size, int col_size, int rRow, int rCol);
void VDoubleExtend(int mat[][MAXCOL], int row_size, int col_size) ;
void HDoubleExtend(int mat[][MAXCOL], int row_size, int col_size) ;

#endif