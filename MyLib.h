#pragma once
#include <iostream>
#include <string>
#include <vector>


using std::cout; 
using std::string;
using std::vector;

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

};