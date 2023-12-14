﻿#include "Mylib1.h"
int minimum(int a, int b) {
	int temp = (a < b) ? a : b;
	return temp;
}
Person::Person() {
	mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
	int_distribution dist(0, 9);
	string Names[10] = { "Irma","Alma","Irena","Egle","Jolanta","Petras","Jonas","Ignas","Darius","Simas" };
	string Surnames_G[10] = { "Pavardaite1","Pavardaite2","Pavardaite3","Pavardaite4","Pavardaite5","Pavardaite6","Pavardaite7","Pavardaite8","Pavardaite9","Pavardaite10" };
	string Surnames_B[] = { "Pavardenis1","Pavardenis2","Pavardenis3","Pavardenis4","Pavardenis5","Pavardenis6","Pavardenis7","Pavardenis8","Pavardenis9","Pavardenis10" };
	Name = Names[dist(mt)];
	switch (*Name.rbegin()) {
	case 's':
		Surname = Surnames_B[dist(mt)];
		break;
	default:
		Surname = Surnames_G[dist(mt)];
		break;
	}
	Exam = dist(mt) + 1;
	for (int a = 0; a < 10; a++) HW.push_back(dist(mt) + 1);
	Final = 0.4 * (std::accumulate(HW.begin(), HW.end(), 0.0) /
		HW.size()) + 0.6 * Exam;

};
Person::Person(string N, string S, vector <int> H,
	int E, float F) {
	Name = N;
	Surname = S;
	HW = H;
	Exam = E;
	Final = F;
};
Person::Person(const Person& P) {
	Name = P.Name;
	Surname = P.Surname;
	HW = P.HW;
	Exam = P.Exam;
	Final = P.Final;
};
Person& Person::operator=(const Person& P) {
	if (this == &P) return *this;
	Name = P.Name;
	Surname = P.Surname;
	HW = P.HW;
	Exam = P.Exam;
	Final = P.Final;
	return *this;
};
Person::~Person() {
	Name.clear();
	Surname.clear();
	HW.clear();
	Exam = 0;
	Final = 0.0;

};
void Person::printPerson() {
	///cout « Name « " : " « Surname « " | " « Final « endl; 
	cout << left << setw(15) << Name << setw(15) << Surname << " | ";
	for (auto& ref : HW) cout << setw(3) << ref;
	cout << " | " << setw(3) << Exam << " ; final points: "
		<< setw(5) << setprecision(2) << fixed << Final << endl;

}
std::ostream& operator<<(std::ostream& out, const Person& A) {
	out << left << setw(15) << A.Name << right << setw(15) << A.Surname << " | ";
	for (auto& ref : A.HW) out << setw(3) << ref;
	out << " | " << setw(3) << A.Exam << " ; final points: "
		<< setw(5) << setprecision(2) << fixed << A.Final << endl;
	return out;

}
std::istream& operator>>(std::istream& in, Person& A) {
	in >> A.Name >> A.Surname >> A.Exam;
	for (int i = 0; i < 5; i++) {
		int n;
		in >> n; A.HW.push_back(n);
	}
	in >> A.Exam;
	A.Final = 0.4 * (std::accumulate(A.HW.begin(), A.HW.end(), 0.0) /
		A.HW.size()) + 0.6 * A.Exam;

	return in;
}
bool operator < (const Person& A, Person& B) {
	return A.getFinal() < B.getFinal();
}
bool operator > (const Person& A, Person& B) {
	return A.getFinal() > B.getFinal();
}
bool operator == (const Person& A, Person& B) {
	return A.getFinal() == B.getFinal();
}


bool myLess(Person& A, Person& B) {
	return A.getFinal() < B.getFinal();
}
bool lessName(Person& A, Person& B) {
	return A.getName() < B.getName();
}
bool lessSurname(Person& A, Person& B) {
	return A.getSurName() < B.getSurName();
}
