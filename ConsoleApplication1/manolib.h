#ifndef MANOLIB_H
#define MANOLIB_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::fixed;
using std::setw;
using std::left;
using std::streamsize;
using std::numeric_limits;
struct Stud {
	std::string pav;
	std::string var;
	int egrez;
	vector<int> paz;
	double ndvid;
	double gal;
	double med;
};


#endif