// Test-2023.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MyLib.h"

int main()
{
    vector<Person>Group;
    for (int j = 0; j < 3; j++) {
        string N, S;
        int W, n, E;
        vector <int> temp;
        float Fin;
        cout << "please input person name and surname: ";
        cin >> N >> S;
        cout << "please input how many works has person: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {

            cout << "please input work" << i + 1 << " evaluation point: ";
            cin >> W;
            temp.push_back(W);
        }
        cout << "please input Final exam result: ";
        cin >> E;
        Fin = 0.4 * (std::accumulate(temp.begin(), temp.end(), 0.0) / temp.size()) + 0.6 * E;
        Person A(N, S, temp, E, Fin);
        Group.push_back(A);
        A.~Person();
        temp.clear();
    } 
    for (auto& B : Group) B.printPerson();
    system("pause");

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
