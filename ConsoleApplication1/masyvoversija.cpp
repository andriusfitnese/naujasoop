#include "manolib.h"



double mediana(int *P, double egrez, int dydis)
{
	if (dydis==0 || P==nullptr) return egrez;
	int* isrikiuotas = new int[dydis];
	for (int i = 0;i < dydis;i++)
	{
		isrikiuotas[i] = P[i];
	}
	sort(isrikiuotas, isrikiuotas + dydis);  ///rikiuojam nuo (iskaityto) pirmo elemento iki paskutinio+1(neiskaityto).

	double med;

	if (dydis % 2 == 0)
		med = (isrikiuotas[dydis / 2 - 1] + isrikiuotas[dydis / 2]) / 2.0;
	else
		med = isrikiuotas[dydis / 2];
	delete[] isrikiuotas;
	return (0.4 * med) + (0.6 * double(egrez));
}
double galvid(double egrez, double ndvd)
{
	double galutinis = (0.6 * egrez) + (0.4 * ndvd);
	return galutinis;
}
double ndvid(int *P, int dydis)
{
	if (dydis == 0 or P == nullptr) return 0.0;
	double sum = 0.0;
	for (int i=0;i<dydis;i++)
	{
		sum += P[i];
	}
	double ndvd = sum / dydis;
	return ndvd;
}
void rng(int*&P, int &dydis)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> pazkiek(1, 10);
	uniform_int_distribution<int> pazym(1, 10);
	dydis = pazkiek(gen);
	P = new int[dydis];
	cout << "Generuojami pazymiai..." << endl;
	for (int i = 0;i < dydis;i++)
	{
		P[i] = pazym(gen);
		cout << P[i] << " ";
	}
	cout << endl;
}

void rng(int& egrez)  ///gauname adresa egrez, sugeneruojame ir grazinam
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> pazym(1, 10);
	cout << "Generuojamas pazymys..." << endl;
	egrez = pazym(gen);
	cout << egrez << " ";
	cout << endl;
}

void rng(string& vardas, string& pavarde)
{
	cout << "Generuojamas vardas..." << endl;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> nameDist(0, 7);

	vardas = vardai[nameDist(gen)];
	pavarde = pavardes[nameDist(gen)];
	cout << vardas << " " << pavarde << endl;
}

int main()
{
	vector<Stud> grupe;
	Stud laik;

	while (true)
	{
		if (laik.P != nullptr)
		{
			delete[]laik.P;
			laik.P = nullptr;
		}
		cout << "Iveskite studento varda (parasykite stop, jei esate jau ivede visus, parasykite gen, jei norite varda sugeneruoti)" << endl;
		cin >> laik.var;
		if (laik.var == "stop") break;
		if (laik.var == "gen") rng(laik.var, laik.pav);
		else
		{
			cout << "Iveskite jo pavarde" << endl;
			cin >> laik.pav;
		}
		cout << "Iveskite jo namu darbu rezultatus ( jei norit, kad butu sugeneruoti, parasykite -2, o jei ranka ivede visus, parasykite -1)" << endl;
		int pazym;
		int i = 0;
		int daug = 5;
		laik.P = new int[daug];
		laik.pazkiek = 0;
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
			if (pazym == -2 and i < 1)
			{
				rng(laik.P, laik.pazkiek);
				break;
			}
			else if (pazym == -2 and i > 0) cout << "Generuoti galima tik is pradziu." << endl;
			if (pazym == -1)break;
			if (laik.pazkiek == daug) {
				daug *= 2;
				int* temp = new int[daug];

				for (int i = 0; i < laik.pazkiek; i++) {
					temp[i] = laik.P[i];
				}

				delete[] laik.P;
				laik.P = temp;
			}
			if ((pazym > 10 or pazym < 1) and pazym!= - 2) cout << "Iveskite skaiciu nuo 1 iki 10!" << endl;
			else if (pazym == -2 and i > 0) cout << "Veskite ranka arba uzbaikite su -1." << endl;
			else {
				laik.P[laik.pazkiek++] = pazym;
				i++;
			}
		}
		cout << "Iveskite jo egzamino rezultata. (jei norite, kad butu sugeneruotas, rasykite -1)" << endl;
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
			else if (laik.egrez == -1)
			{
				rng(laik.egrez);
				break;
			}	
			else if (laik.egrez < 1 or laik.egrez>10)cout << "Iveskite skaiciu tarp 1 ir 10!" << endl;
			else break;
		}

		laik.ndvid = ndvid(laik.P,laik.pazkiek);
		laik.gal = galvid(laik.egrez, laik.ndvid);
		laik.med = mediana(laik.P, laik.egrez, laik.pazkiek);
		grupe.push_back(laik);
	}
	int pas = 0;
	cout << "Isvesti mediana(1) ar vidurki(2)?" << endl;
	cin >> pas;
	if (pas == 1)
	{
		cout << left << setw(12) << "Pavarde" << setw(10) << "Vardas" << setw(10) << "Galutinis (med.)" << endl;
		for (auto &n : grupe)
		{
			cout << fixed << left << setw(12) << setprecision(2) << n.pav << setw(10) << n.var << setw(10) << n.med << endl;
		}
	}
	if (pas == 2)
	{
		cout << left << setw(12) << "Pavarde" << setw(10) << "Vardas" << setw(10) << "Galutinis (vid.)" << endl;
		for (auto &n : grupe)
		{
			cout << fixed << left << setw(12) << setprecision(2) << n.pav << setw(10) << n.var << setw(10) << n.gal << endl;
		}
	}

	return 0;
}
