/*******************************************************************************
 * Copyright (c) 2016, 2018 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "NestedLoop.hpp"


//===========================================
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <chrono> 
using namespace std;

using vec = vector<string>;
using matrix = vector<vec>;
//=============================================
//store the matrix in a vector
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

//=================================================

void printMatrix(const matrix& M)
{
    for (vec row : M)
    {
        for (string s : row) cout << setw(12) << left << s << " ";  
        cout << '\n';
    }
}

//======================================================================

NestedLoop::NestedLoop(OMR::JitBuilder::TypeDictionary *types)
   : OMR::JitBuilder::MethodBuilder(types)
   {
   DefineLine(LINETOSTR(__LINE__));
   DefineFile(__FILE__);

   DefineName("NestedLoop");

   
   pInt = types->PointerTo(Int32);
   DefineParameter("A", pInt);
   DefineParameter("B", pInt);
   DefineParameter("R", pInt);
   DefineParameter("N", Int32);
   DefineParameter("res", pInt);
   DefineReturnType(Int32);
   }


//=================================================BUILDIL for String=============================================
bool
NestedLoop::buildIL()
   {

   //store no_res only if a value is not match for both arrays
   OMR::JitBuilder::IlValue *match_false = ConstInt32(0);

   OMR::JitBuilder::IlValue *A = Load("A");

   OMR::JitBuilder::IlValue *B = Load("B");

   OMR::JitBuilder::IlValue *R = Load("R");

   OMR::JitBuilder::IlValue *N = Load("N");


   
   DefineLocal("result", Int32);
   Store("result", ConstInt32(0));

   OMR::JitBuilder::IlBuilder *aLoop=NULL;
   ForLoopUp("a", &aLoop,
             ConstInt32(1),
             Load("N"),
             ConstInt32(1));

   OMR::JitBuilder::IlBuilder *bLoop=NULL;
   aLoop->ForLoopUp("b", &bLoop,
   aLoop->          ConstInt32(1),
   aLoop->          Load("N"),
   aLoop->          ConstInt32(1));
   OMR::JitBuilder::IlBuilder *match_found=NULL;

   bLoop->           IfThen(&match_found,
   bLoop->              EqualTo(
   bLoop->                 LoadAt(pInt,
   bLoop->                    IndexAt(pInt,
                                       A,
   bLoop->                             Load("a"))),
   bLoop->                 LoadAt(pInt,
   bLoop->                    IndexAt(pInt,
                                       B,
   bLoop->                             Load("b")))
                     ));
   //If value matched
   match_found->             StoreAt(
   match_found->                IndexAt(pInt,
                                       R,
   match_found->                   Load("a")),
   match_found->                      LoadAt(pInt,
   match_found->                       IndexAt(pInt,
                                       A,
   match_found->                          Load("a")))
                     );
   match_found->             Store("result",Add(
                        Load("result"),
                        ConstInt32(1)
                     ));

   Return(
      Load("result"));

   return true;
   }
//======================================================================================================






//print the array
void 
printStringMatrix(int32_t *S, int32_t total_rows){
   for(int32_t i = 1; i < total_rows; i++){
      if(S[i] != 0){
      cout<<S[i]<<endl;
      }
   }
   cout<<"\n";
}



void
NestedLoop::run(int n)
   {
   //read matrices before initialising
   printf("Step 0: read matrices before initialising\n");
   //read csv into temp1 and temp2
   matrix temp1 = readCSV("../../../../data-temp/testing-data/data1_1000000.csv");
   matrix temp2 = readCSV("../../../../data-temp/testing-data/data2_1000000.csv");
   
   //define the 1-D array size
   const int32_t total_rows=temp1.size();


  
   //================================================================================
   printf("Step 1: initialize JIT\n");
   bool initialized = initializeJit();
   if (!initialized)
      {
      fprintf(stderr, "FAIL: could not initialize JIT\n");
      exit(-1);
      }

   printf("Step 2: define matrices\n");
   
   //int32_t A[total_rows];
   //int32_t B[total_rows];
   //int32_t R[total_rows];

   int *A = (int*)malloc(total_rows*sizeof(int));
   int *B = (int*)malloc(total_rows*sizeof(int));
   int *R = (int*)malloc(total_rows*sizeof(int));

   for(int32_t i = 1; i < total_rows; i++){
         A[i] = atoi(temp1[i][3].c_str());
         B[i] = atoi(temp2[i][1].c_str());
   }


   printf("Step 3: define type dictionaries\n");
   OMR::JitBuilder::TypeDictionary types;

   printf("Step 4: compile MatMult method builder\n");
   NestedLoop method(&types);
   void *entry=0;
   
   int32_t rc = compileMethodBuilder(&method, &entry);
   if (rc != 0)
      {
      
      fprintf(stderr,"FAIL: compilation error %d\n", rc);
      exit(-2);
      }
  
   printf("Step 5: invoke MatMult compiled code\n");
   NestedLoopFunctionType *test = (NestedLoopFunctionType *)entry;
   int32_t res = 0;
   int32_t Count = test(A, B, R, total_rows, res);
  
   
   //cout<<"print result array: "<<Count<<endl;

   //printStringMatrix(R, total_rows);
   
   printf ("Step 6: shutdown JIT\n");
   shutdownJit();

   printf("PASS\n");
   }
