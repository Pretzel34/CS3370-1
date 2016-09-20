#Port Setter Requirements




##Functional Requirements
###Primary Cases

portsetter must print usage if passed no params
portsetter must print usage if it is passed an -h
portsetter must print usage if it is passed an --help
portsetter should a -p flag that accepts an integer
portsetter should a --port flag that accepts an integer
Parameter flags should be case sensitive and lower case for this project.

###Flags

-h --help
-p --port

##F#ailure Cases

CLI requirements
Errors state should print an appropriate error
Unexpected parameters should print an invalid flag error
Error’s state should print usage
Error’s state should return a  non-zero value
Port range limitations:
Port > 65k (port number cannot be over 65000)  //Neither can the power level :^)
Port < 1 // Port number cannot be 0
-p and --port should be mutually exclusive.(i.e. portsetter -p 2250 --port 2250 should generate an error)
-p and --port flag should only be allowed once.
Help should be mutually exclusive
-h flags should be mutually exclusive with any other flags.
--help flags should be mutually exclusive with any other flags.
I.e. portsetter -p 2250 --help, portsetter -p 2250 -h, or portsetter --port 2250 -h should generate an error. 
Flag should not accept values that immediately follow the flag (i.e.-pNumber)
First parameter has to start with a ‘-

###Nonfunctional

Executable generated should be portsetter.o
Can be portsetter.cpp.o

###Not Required
  Unit testing or a driver

