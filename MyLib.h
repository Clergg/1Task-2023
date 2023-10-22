#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <iomanip> 


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::setprecision;
using std::fixed;
using std::left;
using std::right;


int minimum(int a, int b);

class Person {
	string Name, surname;
	vector<int>HW;
	int Exam;
	float Final;
public:
	Person();
	Person(string N, string S, vector <int> H,
		int E, float F);
	Person& operator=(const Person& P);
	Person (const  Person& P);
	~Person();
	//setters
	inline void SetName(string N) { Name = N; }
	//overloaded cin
	//overloaded cout
	//final poin calculation from average of median 
	void printPerson() {
		cout << Name << " : " << surname << " | ";
		for (auto &ref : HW) cout <<ref << " : ";
		cout << Exam <<" ; final points: " << Final << endl;
	
	}
};