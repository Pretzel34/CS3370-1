#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Chinchilla {
private:
  string name;
  int age;

public:
  Chinchilla(): name(""), age(0) {}
  Chinchilla(string n, int a): name(n), age(a) {}

  string get_name() {
    return name;
  }

  void set_name(string new_name) {
    name = new_name;
  }

  int get_age() {
    return age;
  }

  void set_age(int new_age) {
    age = new_age;
  }

  friend istream& operator>>(istream& in, Chinchilla& chinchilla) {
    in >> chinchilla.name;
    in >> chinchilla.age;
  }

  friend ostream& operator<<(ostream& out, Chinchilla& chinchilla) {
   out << chinchilla.name;
   out << '\n';
   out << chinchilla.age;
   out << '\n';
  };

  void display() {
   cout << name << endl;
   cout << age << endl;
  }

  void writeTextData(ofstream& textFile) {
    textFile << *this;
  }

  void readTextData(ifstream& textFile) {
    textFile >> name;
    textFile >> age;
  }

  //----- BINARY I/O -----//
  void writeBinaryData(ofstream& binaryFile) {
    binaryFile << *this;
  }

  void readBinaryData(ifstream& binaryFile) {
    binaryFile >> name;
    binaryFile >> age;
  }
};

int main() {
  Chinchilla c1("Ben", 2), c2("Willard", 2), c3, c4, c5;

  c1.display();
  c2.display();

  ofstream cf1("chinchillafarm.txt", ios::out | ios::trunc);
  c1.writeTextData(cf1);
  c2.writeTextData(cf1);
  cf1.close();

  ofstream obcf3("chinchillafarm3.txt", ios::binary | ios::trunc);
  c1.writeBinaryData(obcf3);
  obcf3.close();

  ifstream if1("chinchillafarm.txt", ios::in);
  c3.readTextData(if1);
  c4.readTextData(if1);
  if1.close();

  ifstream ibcf3("chinchillafarm3.txt", ios::in | ios::binary);
  c5.readBinaryData(ibcf3);
  ibcf3.close();

  c3.display();
  c4.display();

  c5.display();

  ofstream rf2("chinchillafarm2.txt", ios::out | ios::trunc);
  rf2 << c1;
  rf2 << c2;
  rf2.close();

  if1.open("chinchillafarm.txt", ios::in);
  if1 >> c3;
  if1 >> c4;
  if1.close();

  cout << "Display c3 via << to cout" << '\n';
  cout << c3;
  cout << "Display c4 via << to cout" << '\n';
  cout << c4;

  return 0;
}
