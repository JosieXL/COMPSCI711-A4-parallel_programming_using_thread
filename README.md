# COMPSCI711-A4-parallel_programming_using_thread

Make is an application program for directing recompilation. A makefile specifies targets, dependencies, and rules to create the targets from the dependencies. A rule is of the form:

 	targets : dependencies ...
      command
  	  command
      ...

Design and develop your own make application which exploits the parallelism in the makefile. You may assume that the makefiles are simple and explicit: there is no implicit rule — all rules have to be explicitly stated in the makefile; there are no variables, 'special' targets, conditionals, or functions.

Use C++ and its standard thread library.


The assignment asks you to develop a parallel version of (a simplified) make app.


make app and the makefile： https://en.wikipedia.org/wiki/Make_(software)
