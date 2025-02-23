#include "manolib.h"
int main()
{
	vector<Stud> grupe;
	Stud laik;
	int pasir = 0;
	cout << "Pasirinkite, ar noresite vesti bent kelis duomenis ranka arba generuot (1); ar skaitysite is failo (2)" << endl;
	cin >> pasir;
	if (pasir == 2)
	{
		skaitymas(grupe);
	}
	else {
		while (true)
		{
			cout << "Iveskite studento varda (parasykite stop, jei esate jau ivede visus, parasykite gen, jei norite varda sugeneruoti)" << endl;
			cin >> laik.var;
			if (laik.var == "stop") break;
			if (laik.var == "gen") rng(laik.var, laik.pav);
			else
			{
				cout << "Iveskite jo pavarde" << endl;
				cin >> laik.pav;
			}

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
				if (pazym == -2 and i < 1)
				{
					rng(laik.paz);
					break;
				}
				else if (pazym == -2 and i > 0) cout << "Generuoti galima tik is pradziu." << endl;
				if (pazym == -1 and i > 0)break;
				else if (pazym == -1 and i < 1) cout << "Neivedete nei vieno namu darbu pazymio!";
				if ((pazym > 10 or pazym < 1) and pazym != -2) cout << "Iveskite skaiciu nuo 1 iki 10!" << endl;
				else if (pazym == -2 and i > 0) cout << "Veskite ranka arba uzbaikite su -1." << endl;
				else
				{
					laik.paz.push_back(pazym);
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
			laik.ndvid = ndvid(laik.paz);
			laik.gal = galvid(laik.egrez, laik.ndvid);
			laik.med = mediana(laik.paz, laik.egrez);
			grupe.emplace_back(std::move(laik));
			laik.paz.clear();
		}
	}
	int sortpas = 0;
	cout << "Pasirinkite, kaip norite surikiuoti (1 - Vardas, 2 - Pavarde, 3 - Mediana, 4 - Galutinis pazymys): ";
	cin >> sortpas;
	switch (sortpas) {
	case 1:
		sort(grupe.begin(), grupe.end(), sortVardu);
		cout << "Surikiuota pagal vardus (abeceles tvarka)." << endl;
		break;
	case 2:
		sort(grupe.begin(), grupe.end(), sortPav);
		cout << "Surikiuota pagal pavardes (abeceles tvarka)." << endl;
		break;
	case 3:
		sort(grupe.begin(), grupe.end(), sortMed);
		cout << "Surikiuota pagal mediana." << endl;
		break;
	case 4:
		sort(grupe.begin(), grupe.end(), sortGal);
		cout << "Surikiuota pagal galutini pazymi." << endl;
		break;
	default:
		cout << "Neteisingas pasirinkimas!" << endl;
		break;
	}
	int pas = 0;
	int pasmv = 0;
	cout << "I ekrana(1) ar i faila(2)?" << endl;
	while (true) {
		cin >> pas;
		if (cin.fail() || (pas != 1 && pas != 2)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Neteisingas pasirinkimas. Iveskite 1 arba 2." << endl;
		}
		else {
			break;
		}
		
	}
	cout << "Isvesti mediana(1), vidurki(2)?" << endl;
	cin >> pasmv;
	isvedimas(pas, pasmv, grupe);
}