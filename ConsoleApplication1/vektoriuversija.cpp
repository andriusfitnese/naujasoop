#include "manolib.h"

double galvid(double egrez, double ndvd)
{
double galutinis = (0.6 * egrez) + (0.4 * ndvd);
return galutinis;
}
double mediana(double egrez, double ndvd)
{
	double mediana = (egrez + ndvd) / 2;
		return mediana;
}
double ndvid(const vector<int>& paz)
{
	double sum = 0.0;
	if (paz.empty()) return 0.0;
	for(double pazym : paz)
	{ 
		sum += pazym;
	}
	double ndvd = sum / paz.size();
	return ndvd;
}
void rng(vector<int>& paz)
{
	Stud laik;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> pazkiek(1, 10);
	uniform_int_distribution<int> pazym(1, 10);
	int pazymk = pazkiek(gen);
	cout << "Generuojami pazymiai..." << endl;
	for (int i = 0;i < pazymk;i++)
	{
		int paz = pazym(gen);
		laik.paz.push_back(paz);
		cout << paz << " ";
	}
	cout << endl;
}

int main()
{
	vector<Stud> grupe;
	Stud laik;

	while (true)
	{
		cout << "Iveskite studento varda (parasykite stop, jei esate jau ivede visus)" << endl;
		cin >> laik.var;
		if (laik.var == "stop") break;
		cout << "Iveskite jo pavarde" << endl;
		cin >> laik.pav;

		cout << "Iveskite jo namu darbu rezultatus ( jei norit, kad butu sugeneruoti, parasykite -2, ivede visus, parasykite -1)" << endl;
		int pazym;
		int i = 0;
		while (true)
		{
			cin >> pazym;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Iveskite SKAICIU nuo 1 iki 10" << endl;
				continue;
			}
			if (pazym == -2 and i < 1)rng(laik.paz);
			else if (pazym == -2 and i > 0) cout << "Generuoti galima tik is pradziu." << endl;
			else i++;
			if (pazym == -1)break;
			if (pazym > 10 or pazym < 1 and not - 2) cout << "Iveskite skaiciu nuo 1 iki 10!" << endl;
			else if (pazym == -2 and i > 0) cout << "Veskite ranka arba uzbaikite su -1." << endl;
			else laik.paz.push_back(pazym);
		}
		cout << "Iveskite jo egzamino rezultata" << endl;
		while (true)
		{
			cin >> laik.egrez;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Iveskite SKAICIU nuo 1 iki 10" << endl;
				continue;
			}
			else if (laik.egrez < 1 or laik.egrez>10)cout << "Iveskite skaiciu tarp 1 ir 10!" << endl;
			else break;
		}
	
			laik.ndvid = ndvid(laik.paz);
			laik.gal = galvid(laik.egrez, laik.ndvid);
			laik.med = mediana(laik.egrez, laik.ndvid);
			grupe.push_back(laik);
	}
	cout << left << setw(12) << "Pavarde" << setw(10) << "Vardas" << setw(20) << "Galutinis (vid.) / Galutinis (med.)" << endl;
	for (auto n : grupe)
	{
		cout <<fixed<<left<<setw(12)<<std::setprecision(2)<< n.pav <<setw(10)<< n.var <<setw(19)<<n.gal <<setw(19)<<n.med << endl;
	}
}