#include "stdafx.h"
#include "CppUnitTest.h"
#include "../maxsum/maxsum.h"
#include <cstdio>

extern int maxsum(int mat[][MAXCOL], int row_size, int col_size, int rRow, int rCol);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FstUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		int cc[MAXROW][MAXCOL];
		int n, m;
		void loadfile(char* filename) {
			//static bool isload(false);
			//if(!isload) isload = true; else return;
 			FILE* inputfile = fopen(filename, "r");
			fscanf(inputfile, "%d,%d,", &n, &m);
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m; ++j) {
					if(j == 0) fscanf(inputfile, "%d", &cc[i][j]);
					else fscanf(inputfile, ",%d", &cc[i][j]);
				}
			fclose(inputfile);
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m; ++j) 
					cc[i][j + m] = cc[i][j];
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m * 2; ++j) 
					cc[i + n][j] = cc[i][j];
		}
		TEST_METHOD(TestBaseCondition)
		{
			// TODO: Your test code here
			// setup test environment ,  save the parameter to a config file
			// create a class
			// initialize necessary members
			// call the function you want to test 
			// use Assert or other method to verify the result is correct. 
			// take down the environment and exit. 

			// or you can run another test.
			loadfile("../FstUnitTest/testdata1.txt");
			Assert::AreEqual(
				// Expected value:
				(int)28, 
				// Actual value:
				maxsum(cc, n, m, n, m));
		}
		TEST_METHOD(TestACondition) {
			loadfile("../FstUnitTest/testdata1.txt");
			Assert::AreEqual(
				// Expected value:
				50, 
				// Actual value:
				 maxUnicomBlock(cc, n, m, n, m));
		}
		TEST_METHOD(TestHVCondition) {
			loadfile("../FstUnitTest/testdata2.txt");
			//test /h
			Assert::AreEqual(
				// Expected value:
				20, 
				// Actual value:
				 maxsum(cc, n * 2, m, n, m),
				 L"horizontal false");
			//tes /v
			loadfile("../FstUnitTest/testdata3.txt");
			Assert::AreEqual(
				// Expected value:
				56, 
				// Actual value:
				 maxsum(cc, n, m * 2, n, m),
				 L"vertical false");

		}
	};
}