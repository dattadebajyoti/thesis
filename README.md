A Comparison of JIT Compiler Overhead
Building project
The project has the following dependencies:

gcc or clang
cmake 3.2+
Linux (2.6.31+) with perf installed (perf_events available)
Eclipse OMR
python 3 
After cloning this repository cd into src/lib and perform the following operations.

Install and Build JITBuilder
Clone the Eclipse OMR repository in src/lib:

 git clone https://github.com/eclipse/omr
 cd omr
 mkdir build
 cd build
 cmake .. -DOMR_COMPILER=1 -DOMR_JITBUILDER=1 -DOMR_TEST_COMPILER=1
 make
 cd ../jitbuilder/release/cpp
 ln -s ../../../build/jitbuilder/libjitbuilder.a .


# build and run the code samples
 make test

Running the code:

Goto src/scripts dir
run the python script runProgram.py using the command : python3 runProgram.py

Tips:
Remember to specify the path where you need to run make commands in the python script
Remember to specify the path where the .csv file are present in the NestedLopp.cpp file
