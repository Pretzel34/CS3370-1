# CS3370
Advanced C++ course.

#Building
To auto build a make file you will need cmake.

When you have cmake run:
cmake .

then you can run make.

#Running
You can run the portsetter program by doing either:

./portsetter -p PORT
or
env PORT=50 MY_PORT=70 (./portsetter -p -e) or (./portsetter -p -e MY_PORT).

Updated changes:

Eviroment variables are set at the begining of the program.
Additional method "setEnv()" was created to create enviroment variables.

char myPort[40]="PORT";
	char bar[40]="BAR";
	setEnv(3114, myPort);
	setEnv(3116, bar);
	
void setEnv(int port, char* varName) {
	char buffer[80] = "export ";
	strcat(buffer, varName);
	strcat(buffer, "=");
	
	string strPort = to_string(port);
	strcat(buffer, strPort.c_str());
	
	system(buffer);

}