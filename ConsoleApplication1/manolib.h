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
using std::sort;
using std::setprecision;



struct Stud {
	string pav;
	string var;
	int egrez;
	int pazkiek = 0;
	int* P;
	vector<int> paz;
	double ndvid;
	double gal;
	double med;

	Stud() : P(nullptr), pazkiek(0) {}  ///default konstruktorius

	~Stud() {
		delete[]P;
		P = nullptr; ///kad nebutu kabanti rodykle
	}

	Stud(const Stud& other)  ///kopijavimo konstruktorius
	{
		var = other.var;
		pav = other.pav;
		pazkiek = other.pazkiek;
		egrez = other.egrez;
		ndvid = other.ndvid;
		gal = other.gal;
		med = other.med;

		if (other.P != nullptr) {
			P = new int[pazkiek];
			for (int i = 0; i < pazkiek; i++) {
				P[i] = other.P[i];
			}
		}
		else {
			P = nullptr;
		}
	}
};
#endif