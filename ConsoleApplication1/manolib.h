
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm> //sortui
#include <thread>
#include <execution>
#include <future> 
#include <functional> //del greater ir less funkciju
#include <deque>
#include <chrono>
#include <list>

using std::cout;
using std::cin;
using std::min;
using std::endl;
using std::vector;
using std::stringstream;
using std::launch;
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
using std::ifstream;
using std::ofstream;
using std::ws;
using std::istringstream;
using std::cerr;
using std::nth_element;
using std::future;
using std::runtime_error;
using std::ios;
using std::exception;
using std::to_string;
using std::ostringstream;
using std::deque;
using std::list;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

const string vardai[] = { "Jonas", "Petras", "Marius", "Lukas", "Tomas", "Simas", "Andrius", "Darius" };
const string pavardes[] = { "Kazlauskas", "Petraitis", "Jonaitis", "Mikalauskas", "Bagdonas", "Vaitkus", "Urbonas", "Grigas" };

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
	/*Stud() : P(nullptr), pazkiek(0) {}  ///default konstruktorius

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
	}*/
};

bool sortVardu(const Stud& a, const Stud& b);
bool sortPav(const Stud& a, const Stud& b);
bool sortMed(const Stud& a, const Stud& b);
bool sortGal(const Stud& a, const Stud& b);
double mediana(const vector<int>& paz, double egrez,string var);
double galvid(double egrez, double ndvd);
double ndvid(const vector<int>& paz);
void rng(vector<int>& paz);  ///nd pazymiu gen
void rng(int& egrez);  ///egz pazymiu gen
void rng(string& vardas, string& pavarde);  ///vardu generavimas
void skaitymas(deque<Stud>& grupe, duration<double>& veiklaik);
void isvedimas(int pas, int pasmv, const deque<Stud>& grupe);
bool gautteisinga(int& input, const string& prompt, int min, int max);   ///error handlingas neteisingos ivesties atveju
void failogen(const string& failopav, int irasuk);
void atrinkimas(deque<Stud>& grupe, deque<Stud>& nerdai, list<Stud>& galiorka, int pasmv, duration<double>& veiklaik);
vector<Stud> processBatch(const vector<string>& lines);