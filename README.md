[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)
# Description

- this is the final submission of osn mini project 1.
  
### How to run?:
To run and use this shell download zip and unzip and write the following commands in terminal: 
 ``` sh
  make main
 ./a.out 
 ```
### Functionality:
- Upon entering the terminal, a prompt is displayed
- The shell is invoked from the home folder (represented by ~).
- Input commands are executed based on the current directory and the command itself.
- To indicate the end of input, press Enter after entering a command.
  
- The shell supports all the specifications mentioned in Part-A and PART-B and Part - C


### File Information:
- `main.c`: This file contains the main function which calls all other functions
- all other files contain functions that are used for the execution of the respective command
- the respective header files contain function headers.
- `defines.h`:contains all the macros that are used throught the project
- `utilities.c`: just has some function for string modification.

  
# Assumptions
- The output formats for some commands are not exactly matching to the ones mentioned on the course website , but still the crucial and necessary information is present.
- the user defined commands are not considered as different processes. the commands run using execvp are different processes
- piping , input -ouput redirection are handled by different parsers but in unison all work.
- very few extra '\n' characters may sometimes appear but they have been minimised.
- some functions have been defined in headers.h (mainly the execution ones) because the struct pointer was needed in the function argument
- a global struct pointer is used in the program and a global char* array is also used
  
# Also very important the files of part A during mid submission work completely on their own also but some of them have been modified for including some features in Part B and Part C


  
  
