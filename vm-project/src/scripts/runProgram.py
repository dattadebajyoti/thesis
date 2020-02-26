import subprocess 
import os 
import time
import statistics 

def execute(text): 
  
    # create a pipe to a child process 
    data, temp = os.pipe()  
    os.write(temp, bytes("5 10\n", "utf-8")); 
    os.close(temp) 

    start=time.time()
    # store output of the program as a byte string in s 
    s = subprocess.run(text, stdin = data, shell = True) 
    end=time.time()
    return int(round((end-start)*1000))


# Driver function 
if __name__=="__main__": 
    
    exec_times = int(input("Please enter how many times you want to run: "))
    print(exec_times)
    command1 = 'cd ../jitbuilder/Nested-Loop-Join/;make main'
    command2 = 'cd ../jitbuilder/Nested-Loop-Join/;./build/main'
    command3 = 'cd ../jitbuilder/Nested-Loop-Join/;make main;./build/main'
    #get data for using jit
    #Jit
    print("getting data for using Jit")
    compile_data_jit = []
    execution_data_jit = []
    total_time_jit = []
    #make a dry run
    print("Start dry run for all the 3 commands")
    execute(command3)
    print("Dry run complete for all commands")
    for i in range(exec_times):
        compile_data_jit.append(execute(command1))
        execution_data_jit.append(execute(command2))
    
    mean_compile_jit = statistics.mean(compile_data_jit)
    median_compile_jit = statistics.median(compile_data_jit)
    stdev_compile_jit = int(round(statistics.stdev(compile_data_jit)*1000))

    mean_exec_jit = statistics.mean(execution_data_jit)
    median_exec_jit = statistics.median(execution_data_jit)
    stdev_exec_jit = int(round(statistics.stdev(execution_data_jit)*1000))

    #for i in range(exec_times):
        #total_time_jit.append(execute(command3))
    
    mean_total_jit = mean_compile_jit+mean_exec_jit
    median_total_jit = median_compile_jit+median_exec_jit
    stdev_total_jit = stdev_compile_jit+stdev_exec_jit



    #*********************************************************************************************************************

    #get data for using Native
    #Native
    print("getting data for using native")
    compile_data_native = []
    execution_data_native = []
    total_time_native = []
    #make a dry run
    command4 = 'cd ../native/nested-loop/;make main'
    command5 = 'cd ../native/nested-loop/;./build/main'
    command6 = 'cd ../native/nested-loop/;make main;./build/main'
    print("Start dry run for all the 3 commands")
    execute(command6)
    print("Dry run complete for all commands")
    for i in range(exec_times):
        compile_data_native.append(execute(command4))
        execution_data_native.append(execute(command5))
    
    mean_compile_native = statistics.mean(compile_data_native)
    median_compile_native = statistics.median(compile_data_native)
    stdev_compile_native = int(round(statistics.stdev(compile_data_native)*1000))

    mean_exec_native = statistics.mean(execution_data_native)
    median_exec_native = statistics.median(execution_data_native)
    stdev_exec_native = int(round(statistics.stdev(execution_data_native)*1000))

    #for i in range(exec_times):
        #total_time_native.append(execute(command6))
    
    mean_total_native = mean_compile_native+mean_exec_native
    median_total_native = median_compile_native+median_exec_native
    stdev_total_native = stdev_compile_native+stdev_exec_native



    print("*****************************************Print compilation data for jit*********************************************")
    print("mean for compilation using jit: ", mean_compile_jit)
    print("median for compilation using jit: ", median_compile_jit)
    print("Standard deviation for compilation using jit: ", stdev_compile_jit)

    print("*****************************************Print execution data for jit***********************************************")
    print("mean for execution using jit: ", mean_exec_jit)
    print("median for execution using jit: ", median_exec_jit)
    print("Standard deviation for execution using jit: ", stdev_exec_jit)

    print("*****************************************Print total execution time data for jit*************************************")
    print("mean for execution using jit: ", mean_total_jit)
    print("median for execution using jit: ", median_total_jit)
    print("Standard deviation for execution using jit: ", stdev_total_jit)

    print("*****************************************Print compilation data for native*********************************************")
    print("mean for compilation using native: ", mean_compile_native)
    print("median for compilation using native: ", median_compile_native)
    print("Standard deviation for compilation using native: ", stdev_compile_native)

    print("*****************************************Print execution data for native***********************************************")
    print("mean for execution using native: ", mean_exec_native)
    print("median for execution using native: ", median_exec_native)
    print("Standard deviation for execution using native: ", stdev_exec_native)

    print("*****************************************Print total execution time data for native*************************************")
    print("mean for execution using native: ", mean_total_native)
    print("median for execution using native: ", median_total_native)
    print("Standard deviation for execution using native: ", stdev_total_native)
    
    print("+-------------+--------------+-------------------------+----------------------------+--------------------------+")
    print("|   Time      |  Compiler    |   Mean                  |      Median                |        Stdev             |")
    print("+-------------+--------------+-------------------------+----------------------------+--------------------------+")
    print("|  compile    |  JIT         |",mean_compile_jit     ,"|",median_compile_jit,      "|",stdev_compile_jit,     "|")
    print("|             +--------------+-------------------------+----------------------------+--------------------------+")
    print("|   Time      |  Native      |",mean_compile_native,  "|",median_compile_native   ,"|",stdev_compile_native,  "|")
    print("+-------------+--------------+-------------------------+----------------------------+--------------------------+")
    print("| Execution   |  JIT         |",mean_exec_jit        ,"|",median_exec_jit         ,"|",stdev_exec_jit,        "|")
    print("|             +--------------+-------------------------+----------------------------+--------------------------+")
    print("|   Time      |  Native      |",mean_exec_native     ,"|",median_exec_native      ,"|",stdev_exec_native,     "|")
    print("+-------------+--------------+-------------------------+----------------------------+--------------------------+")
    print("|   Total     |  JIT         |",mean_total_jit       ,"|",median_total_jit        ,"|",stdev_total_jit,       "|")
    print("|             +--------------+-------------------------+----------------------------+--------------------------+")
    print("|   Time      |  Native      |",mean_total_native    ,"|",median_total_native     ,"|",stdev_total_native,    "|")
    print("+-------------+--------------+-------------------------+----------------------------+--------------------------+")



    
