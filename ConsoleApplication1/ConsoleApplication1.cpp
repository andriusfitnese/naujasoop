#include "manolib.h"

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
		cout << "Prasome ivesti studento namu darbu rezultatus" << endl;
		cin >> laik.ndrez;
		cout << "Prasome ivesti studento namu darbu rezultatus" << endl;
		cin >> laik.egrez;
		laik.gal = (0.6 * double(laik.egrez) + (0.4 * double(laik.ndrez)));
		laik.med = double((laik.egrez + laik.ndrez)) / 2;
		grupe.push_back(laik);
	}
	for (auto n : grupe)
	{
		cout << left << setw(12) << "Pavarde" << setw(10) << "Vardas" << setw(20) << "Galutinis (vid.) / Galutinis (med.)"<<endl;
		cout <<fixed<<left<<setw(12)<<std::setprecision(2)<< n.pav <<setw(10)<< n.var <<setw(19)<<n.gal <<setw(19)<<n.med << endl;
	}
}