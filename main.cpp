#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include "linked_list.h"
#include "Ford_Fulkerson_algorithm.h"
#include "unittest.h"

using namespace std;

template <class T>
void alg_ini(List<T> *ini_list);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string str;
	List<string> *rec_list = new List<string>;
	test_all();

	ifstream in("flow.txt");
	while (getline(in, str)) {
		rec_list->push_back(str);
	}
	alg_ini(rec_list);
}
template <class T>
void alg_ini(List<T> *ini_list) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Ford_Fulkerson_Alg finding(ini_list);
	cout << "max flow is " << finding.maxflow << endl <<endl;
	system("PAUSE");
}