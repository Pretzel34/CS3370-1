#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Rat {
 char name[50];
 int age;
};

 istream& operator>>(istream& in, Rat& rat) {
   in >> rat.name;
   in >> rat.age;
 }

 ostream& operator<<(ostream& out, Rat& rat) {
  out << rat.name;
  out << '\n';
  out << rat.age;
  out << '\n';
 };

//----- TEXT I/O -----//
void display(Rat& rat) {
 cout << rat.name << endl;
 cout << rat.age << endl;
}

void writeTextData(ofstream& textFile, Rat& rat) {
  textFile << rat;
}

void readTextData(ifstream& textFile, Rat& rat) {
  textFile >> rat;
}

//----- BINARY I/O -----//
void writeBinaryData(ofstream& binaryFile, Rat& rat) {
  binaryFile << rat;
}

void readBinaryData(ifstream& binaryFile, Rat& rat) {
  binaryFile >> rat;
}

int main() {
 Rat r1, r2, r3, r4, r5;
 r1.name[0] = 'B';
 r1.name[1] = 'e';
 r1.name[2] = 'n';
 r1.age = 2;

 r2.name[0] = 'W';
 r2.name[1] = 'i';
 r2.name[2] = 'l';
 r2.name[3] = 'l';
 r2.name[4] = 'a';
 r2.name[5] = 'r';
 r2.name[6] = 'd';
 r2.age = 3;

 cout << "Display r1 via display()" << '\n';
 display(r1);
 cout << "Display r2 via display()" << '\n';
 display(r2);


 ofstream rf1("ratfarm.txt", ios::out | ios::trunc);
 writeTextData(rf1, r1);
 writeTextData(rf1, r2);
 rf1.close();

 ofstream obrf3("ratfarm3.txt", ios::binary | ios::trunc);
 writeBinaryData(obrf3, r1);
 obrf3.close();

 ifstream if1("ratfarm.txt", ios::in);
 readTextData(if1, r3);
 readTextData(if1, r4);
 if1.close();

 ifstream ibrf3("ratfarm3.txt", ios::in | ios::binary);
 readBinaryData(ibrf3, r5);
 ibrf3.close();

 cout << "Display r3 via display()" << '\n';
 display(r3);
 cout << "Display r4 via display()" << '\n';
 display(r4);

 cout << "Display r5 via display()" << '\n';
 display(r5);

 ofstream rf2("ratfarm2.txt", ios::out | ios::trunc);
 rf2 << r1;
 rf2 << r2;
 rf2.close();

 if1.open("ratfarm.txt", ios::in);
 if1 >> r3;
 if1 >> r4;
 if1.close();

 cout << "Display r3 via << to cout" << '\n';
 cout << r3;
 cout << "Display r4 via << to cout" << '\n';
 cout << r4;
}
