// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <chrono> 
using namespace std;
using namespace std::chrono;
#include "NestedLoop.hpp"

using vec = vector<string>;
using matrix = vector<vec>;

//======================================================================

matrix readCSV(string filename)
{
    char separator = ',';
    matrix result;
    string row, item;

    ifstream in(filename);
    while (getline(in, row))
    {
        vec R;
        stringstream ss(row);
        while (getline(ss, item, separator)) R.push_back(item);
        result.push_back(R);
    }
    in.close();
    return result;
}

//======================================================================

void printMatrix(const matrix& M)
{
    for (vec row : M)
    {
        for (string s : row) cout << setw(12) << left << s << " ";    
        cout << '\n';
    }
}

int NestedForLoop(int32_t *A,int32_t *B,int32_t *R, int total_rows, int32_t return_val){
    for (int i = 1; i < total_rows; i++) {
        for (int j = 1; j < total_rows; j++) {
            if (A[i] == B[j]) {
                R[i] = A[i];
            }
        }
    }
    return 1;
}


void 
printStringMatrix(int32_t *S, int total_rows){
   for(int i = 1; i < total_rows; i++){
      if(S[i] != 0){
      cout<<S[i]<<endl;
      }
   }
   cout<<"\n";
}

int32_t NestedLoop()
{
    //cout << "Debajyoti" << endl;

    matrix temp1 = readCSV("../../../../data-temp/testing-data/data1_1000000.csv");
    matrix temp2 = readCSV("../../../../data-temp/testing-data/data2_1000000.csv");
    int total_rows=temp1.size();

    int *A = (int*)malloc(total_rows*sizeof(int));
    int *B = (int*)malloc(total_rows*sizeof(int));
    int *R = (int*)malloc(total_rows*sizeof(int));

    for(long int i = 1; i < total_rows; i++){
          A[i] = atoi(temp1[i][3].c_str());
          B[i] = atoi(temp2[i][1].c_str());
    }
    int res = 0;
    int count = NestedForLoop(A, B, R, total_rows, res);
   
    //printStringMatrix(R, total_rows);
    

    cout << "\n\n";

    return 1;

}


