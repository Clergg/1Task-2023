#include "MyLib.h"

int minimum(int a, int b) {
	int temp = (a < b) ? a : b;
	return temp;
}

Person::Person() {
	Name = ""; surname = "";
	Exam = 0; Final = 0.0;
	HW.clear();
};
Person::Person(string N, string S, vector <int> H,
	int E, float F) {
	Name = N;
	surname = S;
	HW = H;
	Exam = E;
	Final = F;
}
Person::Person(const Person& P) {
	Name = P.Name;
	surname = P.surname;
	HW = P.HW;
	Exam = P.Exam;
	Final = P.Final;

}
Person& Person:: operator =(const Person& P) {
	if (this == &P) return *this;
	Name = P.Name;
	surname = P.surname;
	HW = P.HW;
	Exam = P.Exam;
	Final = P.Final;
	return *this;
};
Person::~Person() {
	Name.clear();
	surname.clear();
	HW.clear();
	Exam = 0;
	Final = 0.0;
}

