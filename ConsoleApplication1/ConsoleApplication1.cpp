#include "manolib.h"

double ndvid(const vector<int>& paz)
{
	double sum = 0.0;
	if (paz.empty()) return 0.0;
	for (double pazym : paz)
	{
		sum += pazym;
	}
	double ndvd = sum / paz.size();
	return ndvd;
}

double mediana(double egrez, double ndvd)
{
	double mediana = (egrez + ndvd) / 2;
	return mediana;
}

int main()
{
	vector<Stud> grupe;
	for (int i = 0;i < 1;i++)
	{
		Stud laik;
		cout << "Prasome ivesti studento varda"<<endl;
		cin >> laik.var;
		cout << "Prasome ivesti studento pavarde" << endl;
		cin >> laik.pav;
		cout << "Prasome ivesti studento namu darbu rezultatu kieki" << endl;
		cin >> laik.ndkiek;
		cout << "Prasome ivesti studento namu darbu rezultatus (po viena)" << endl;
			int pazym = 0;
			int j = 0;
			while(true)
			{
				cin >> pazym;
				if (pazym > 10 or pazym < 1) cout << "Iveskite skaiciu nuo 1 iki 10!" << endl;
				else
				{
					laik.paz.push_back(pazym);
					j++;
				}
				if (j == laik.ndkiek) break;
		}
		
		cout << "Prasome ivesti studento egzamino rezultata" << endl;
		cin >> laik.egrez;
		laik.ndvid = ndvid(laik.paz);
		laik.gal = (0.6 * double(laik.egrez) + (0.4 * double(laik.ndvid)));
		laik.med = mediana(laik.egrez, laik.ndvid);
		grupe.push_back(laik);
	}
	cout << left << setw(12) << "Pavarde" << setw(10) << "Vardas" << setw(20) << "Galutinis (vid.) / Galutinis (med.)" << endl;
	for (auto n : grupe)
	{
		cout <<fixed<<std::setprecision(2)<< n.pav << " " << n.var <<" "<<n.gal <<" "<<n.med << endl;

	}
}