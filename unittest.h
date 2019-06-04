#pragma once

#include <assert.h>
#include "linked_list.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include "arc.h"
#include "Ford_Fulkerson_algorithm.h"
#include <fstream>

using namespace std;

void test_flow1() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string str;
	List<string> *rec_list = new List<string>;

	ifstream in("flow1.txt");
	while (getline(in, str)) {
		rec_list->push_back(str);
	}
	Ford_Fulkerson_Alg finding(rec_list);
	assert(2000 == finding.maxflow);
	cout << "test_flow1 - succeed max flow is 2000\n" << endl;
}

void test_flow2() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string str;
	List<string> *rec_list = new List<string>;

	ifstream in("flow2.txt");
	while (getline(in, str)) {
		rec_list->push_back(str);
	}
	Ford_Fulkerson_Alg finding(rec_list);
	assert(15 == finding.maxflow);
	cout << "test_flow2 - succeed max flow is 15\n" << endl;

}

void test_flow3() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string str;
	List<string> *rec_list = new List<string>;
	ifstream in("flow3.txt");
	while (getline(in, str)) {
		rec_list->push_back(str);
	}
	Ford_Fulkerson_Alg finding(rec_list);
	assert(5 == finding.maxflow);
	cout << "test_flow3 - succeed max flow is 5\n" << endl;
}

void test_all() {

	test_flow1();

	test_flow2();

	test_flow3();

	cout << "All tests passed" << endl;
}