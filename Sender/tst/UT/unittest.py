import sys
import os
import re
import pprint

# pls dont read this code..... its a shame that i wrote the script
# in a bad fashion even after joining TCQ. 
# Any way a execuse :
# pls pick one among the below , preferrably option 3.
# 1. had to pull this off faster 
# 2. i am new to python language
# 3. Its ok sana it work pls dont feel bad about it.... 
#
# TODO: refactor this dirty code




mainfile_name = "mainfile.c"
mainfile_header = """
#include "testcases.c"
int main()
{
"""

Env_init_TestCase = "Environment_Initialization(); \n"
mainfile_testcases = ""   # this gets build during run time

mainfile_footer= """
return 0;
}
"""


def create_mainfile(foldername):
    print("*****************************************")
    print("Creating Testcases started")   
    print("*****************************************")
    with open("./"+foldername+"/testcases.c","r") as reader:
        testcaseslist = re.findall("TC_.*[(]",reader.read())
    mainfile_testcases = Env_init_TestCase + ( "); \n" + Env_init_TestCase ).join(testcaseslist) + ");"
    mainfile_testcases.replace("void", "")
    with open("./"+foldername+"/"+mainfile_name,"w") as writer:
        writer.write(mainfile_header + mainfile_testcases +mainfile_footer)

    print("Testcases are as follow")    
    pprint.pprint(testcaseslist)
    print("Creating Testcases exited succesfully")    


def compile_ut_using_gcc(foldername):
    global mainfile_name
    print("*************************************************")
    print("Compiling the unittest in the folder:"+foldername)
    print("*************************************************")
    try:
        os.remove("./TestcaseExecuter.exe")
    except FileNotFoundError:
        pass

    gcc_command = "gcc ./"+foldername+"/*.c"+ " -o ./TestcaseExecuter"
    if os.system(gcc_command) != 0:
        print("Exiting because of compilation errors")
        exit()
    
def execute_testcases(foldername):
    print("*********************")
    print("Executing Test cases")
    print("*********************")
    run_exe_command = "TestcaseExecuter.exe"
    os.system(run_exe_command)
    

if __name__ == "__main__":
    foldername =sys.argv[1]
    create_mainfile(foldername)
    compile_ut_using_gcc(foldername)
    execute_testcases(foldername)

   
    