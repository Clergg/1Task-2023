#pragma once 
#include <iostream> 
#include <iomanip> 
#include <string> 
#include <vector> 
#include <numeric> 
#include <chrono> 
#include <random> 
#include <functional> 



using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::mt19937;

using hrClock = std::chrono::high_resolution_clock;
typedef std::uniform_int_distribution<int> int_distribution;

int minimum(int a, int b);

class Person {
	string Name, Surname;
	vector <int> HW;
	int Exam;
	float Final;
public:
	Person();
	Person(string N, string S,
		vector <int> H, int E, float F);
	Person& operator=(const Person& P);
	Person(const Person& P);
	~Person();
	///setters 
	inline void setName(string N) { Name = N; }
	inline void setSurname(string N) { Surname = N; }
	inline void setHW(vector <int> N) { HW.assign(N.begin(), N.end()); }

	inline void setExam(int N) { Exam = N; }
	inline void setFinal(float N) { Final = N; }


	///overloaded cin 
	///overloaded cout 
	friend std::istream& operator>>(std::istream& in, Person& A);
	/// final point calculation from average or median 
	friend std::ostream& operator<<(std::ostream& out, const Person& A);

	void printPerson();
	//getters 
	inline float getFinal() const { return Final; }
	inline string getName() const { return Name; }
	inline string getSurName() const { return Surname; }
	inline int getExam() const { return Exam; }
	inline vector <int> getHW() const { return HW; }



};
bool operator> (const Person& A, Person& B);
bool operator< (const Person& A, Person& B);
bool operator== (const Person& A, Person& B);
bool myLess(Person& A, Person& B);
bool lessName(Person& A, Person& B);
bool lessSurname(Person& A, Person& B);