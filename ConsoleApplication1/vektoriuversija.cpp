#include "manolib.h"

double galvid(double egrez, double ndrez)
{
double galutinis = (0.6 * egrez) + (0.4 * ndrez);
return galutinis;
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


int main()
{
	vector<Stud> grupe;

	while (true)
	{
		Stud laik;
		cout << "Iveskite studento varda (parasykite stop, jei esate jau ivede visus)" << endl;
		cin >> laik.var;
		if (laik.var == "stop") break;
		cout << "Iveskite jo pavarde"<<endl;
		cin >> laik.pav;
		cout << "Iveskite jo namu darbu rezultatus (parasykite -1, kai ivesite visus)" << endl;
		int pazym;
			while (true)
			{
				cin >> pazym;
				if (pazym == -1)break;
				laik.paz.push_back(pazym);
			}
			cout << "Iveskite jo egzamino rezultata" << endl;
		cin >> laik.egrez;
			grupe.push_back(laik);
			/*laik.gal = galvid(laik.egrez, laik.ndrez);
			laik.ndvid = ndvid(laik.paz);
			laik.med = double((laik.egrez + laik.ndrez)) / 2;
			grupe.push_back(laik);*/
	}
	cout << left << setw(12) << "Pavarde" << setw(10) << "Vardas" << setw(20) << "Galutinis (vid.) / Galutinis (med.)" << endl;
	for (auto n : grupe)
	{
		cout <<fixed<<left<<setw(12)<<std::setprecision(2)<< n.pav <<setw(10)<< n.var <<setw(19)<<n.gal <<setw(19)<<n.med << endl;
	}
}