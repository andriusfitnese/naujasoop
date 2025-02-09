#ifndef MANOLIB_H
#define MANOLIB_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::fixed;
using std::setw;
using std::left;
using std::streamsize;
using std::numeric_limits;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::string;



struct Stud {
	string pav;
	string var;
	int egrez;
	int pazkiek;
	vector<int> paz;
	double ndvid;
	double gal;
	double med;
};
#endif