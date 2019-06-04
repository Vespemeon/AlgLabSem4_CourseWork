#pragma once

#include <string>
#include <iostream>

using namespace std;

class arc
{
public:
	string start;
	string finish;
	int capacity;

	arc()
	{
		start = '\0';
		finish = '\0';
		capacity = 0;
	}

	~arc() {}
};