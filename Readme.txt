===========
Readme.txt
===========

----------------------------------------------------------------
This Readme.txt contains a brief description of the functional of the NewMakeApp - a simpler parallel version for the make app
----------------------------------------------------------------
// Author: Josie Li
// ID Number: 455398598
// UPI: xli556
// Update date: 6th September 2021
----------------------------------------------------------------

In the same directory with this ReadMe.txt as well as the cpp file we used to compile as exe file and run, there is a myMakefile, main.cpp, functions.cpp, functions.h, factorial.cpp, factorial.h. 
Dependencies: in myMakefile
functions.h -> functions.cpp -> function.o
factorial.h -> factorial.cpp -> factorial.o
functions.h, factorial.h -> main.cpp -> main.o
function.o factorial.o main.o -> a.out

I also create a makefile that get same dependency with myMakefile but the final out file is b.out. (This is used to check for the automatically check if a Makefile or makefile exists in the directory).

On the other hand, in order to check whether I really completed the function of getting the file name from the input of CMD, I created another main1.cpp, which was based on main.cpp with minor changes, and created Makefile-1 to put the dependency between main1.cpp and other cpp files (basically the same as the myMakefile but main.cpp is replaced by main1.cpp, a.out is replaced by bb.out). 


The NewMakeApp can be used to check whether the syntax of the makefile is follows as below:
	Target: Dependencies\n
		Command\n
		Command\n
	...
  Note: there is a whitespace (\s) after the colon, the spaces before the Command are a tab (\t)and each line ends up with a new line character \n.
  For Command, since I did not use Lexical analyser flex and parser bison, the commands are only in form of “g++ -option filename.extension ...” and they need to be valid cmd commands so that run on cmd.
  For filename, the only allowed regex is "[a-zA-Z0-9_-]+", means filename can only contain uppercase character, lowercase character, number, underline and hyphen.
  If the syntax not match，there will pop out a sentence “Wrong syntax in makefile!” and stop the execution.


  Note: for all the files, path selection is not provided for the time being, which means that all test files and corresponding Makefile must be in the same directory and at the same level as NewMakeApp.cpp and NewMakeApp.exe.


  The skip function is temporarily not provided, which means that regardless of whether the .o, a.out or other related files exist or have been changed, every execution of NewMakeApp will run all the required commands once until the original files are completely overwritten


  Thread, mutex have been used to separate the required commands to run/print with thread according to the dependency relation


  The -f option has been provided to obtain the corresponding makefile name, but only one makefile can be opened at a time. The specific command is NewMakeApp -f makefilename; 
If the command is only NewMakeApp, it will automatically search for the Makefile or makefile in the same directory. If both Makefile and makefile does not be found, pop out error message "No required Makefile/makefile".


  Error when building NewMakeApp.exe using g++ NewMakeApp.cpp in CMD when cpp file contains thread and mutex. Error said: 'mtx' was not declared in this scope and 'thread' was not declared in this scope. I do include both <thread> and <mutex> at the top of the cpp file. I find this error's solution online but none of them fit, maybe is the C++ version issue.
-----------------------------
NewMakeApp.exe is created by g++ from NewMakeApp.cpp without thread and mutex version
-----------------------------


After reading a single file to read the file name after -f in CMD, there may be 4 errors in NewMakeApp.cpp, error E0266-"system" is ambiguous, but these four errors do not affect the operation.

