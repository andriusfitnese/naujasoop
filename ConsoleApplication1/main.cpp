#include "manolib.h"
int main()
{
	vector<Stud> grupe;
	deque<Stud> nerdai;
	list<Stud> galiorka;
	Stud laik;
	bool geras = false;
	int pasir = 0;
	auto veiklaik=duration<double>::zero();

	/*failogen("1000", 1000);
	failogen("10000", 10000);
	failogen("100000", 100000);
	failogen("1000000", 1000000);
	failogen("10000000", 10000000);*/
	while (!geras)
	{
		try {
			cout << "Pasirinkite, ar noresite vesti bent kelis duomenis ranka arba generuot (1); ar skaitysite is failo (2)" << endl;
			cin >> pasir;
			if (cin.fail() || (pasir != 1 && pasir != 2)) {
				throw runtime_error("Netinkamas pasirinkimas. Iveskite 1 arba 2.");
			}
			geras = true;
		}
		catch (const runtime_error& e)
		{
			cerr << "Klaida: " << e.what() << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	if (pasir == 2)
	{
		skaitymas(grupe, veiklaik);
		cout << "Skaitymas baigtas." << endl;
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
			bool tinka = false;
			while (!tinka)
			{
				try
				{
					cin >> pazym;
					if (cin.fail() or (pazym > 10 or pazym < 1) and pazym != -2 and pazym != -1)
					{
						throw runtime_error("Ivestas netinkamas simbolis/skaicius! Iveskite sveika skaiciu nuo 1 iki 10!");
					}
					if (pazym == -2 and i < 1)
					{
						rng(laik.paz);
						break;
					}
					else if (pazym == -2 and i > 0)
					{
						throw runtime_error("Generuoti galima tik is pradziu.Veskite ranka arba uzbaikite su -1.");
					}
					if (pazym == -1 and i > 0)break;
					else if (pazym == -1 and i < 1) throw runtime_error("Neivedete nei vieno namu darbu pazymio!");
					else
					{
						laik.paz.push_back(pazym);
						i++;
					}
				}
				catch (runtime_error& e)
				{
					cerr << "Klaida: " << e.what() << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			tinka = false;
			cout << "Iveskite jo egzamino rezultata. (jei norite, kad butu sugeneruotas, rasykite -1)" << endl;
			while (!tinka)
			{
				try {
					cin >> laik.egrez;
					if (cin.fail() or (laik.egrez < 1 and laik.egrez != -1) or (laik.egrez > 10 and laik.egrez != -1))
					{
						throw runtime_error("Ivestas netinkamas simbolis/skaicius! Iveskite sveika skaiciu nuo 1 iki 10!");
					}
					else if (laik.egrez == -1)
					{
						rng(laik.egrez);
						break;
					}
					else break;
				}
				catch (const runtime_error& e)
				{
					cerr << "Klaida: " << e.what() << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}

			laik.ndvid = ndvid(laik.paz);
			laik.gal = galvid(laik.egrez, laik.ndvid);
			laik.med = mediana(laik.paz, laik.egrez);
			grupe.emplace_back(std::move(laik));
			laik.paz.clear();
		}
	}
	int sortpas = 0;
	string pasirn;
	if (gautteisinga(sortpas, "Pasirinkite, kaip norite surikiuoti (1 - Vardas, 2 - Pavarde, 3 - Mediana, 4 - Galutinis pazymys): ", 1, 4)){}
		high_resolution_clock::time_point start, end;
		switch (sortpas) {
		case 1:
			start = high_resolution_clock::now();
			sort(grupe.begin(), grupe.end(), sortVardu);
			end = high_resolution_clock::now();
			cout << "Surikiuota pagal vardus (abeceles tvarka)." << endl;
			pasirn = "vardus";
			break;
		case 2:
			start = high_resolution_clock::now();
			sort(grupe.begin(), grupe.end(), sortPav);
			end = high_resolution_clock::now();
			cout << "Surikiuota pagal pavardes (abeceles tvarka)." << endl;
			pasirn = "pavardes";
			break;
		case 3:
			start = high_resolution_clock::now();
			sort(grupe.begin(), grupe.end(), sortMed);
			end = high_resolution_clock::now();
			cout << "Surikiuota pagal mediana." << endl;
			pasirn = "mediana";
			break;
		case 4:
			start = high_resolution_clock::now();
			sort(grupe.begin(), grupe.end(), sortGal);
			end = high_resolution_clock::now();
			cout << "Surikiuota pagal galutini pazymi." << endl;
			pasirn = "galutini pazymi";
			break;
		default:
			cout << "Neteisingas pasirinkimas!" << endl;
			break;
		}
		veiklaik += end - start;
	cout << "Rusiavimo pagal "<<pasirn<<" laikas:" << duration<double>(end - start).count() << endl;
	int pas = 0;
	int pasmv = 0;
	if (gautteisinga(pas, "Ar isskirti studentus, kurie pazangus ir nepazangus [bus galimas tik isvedimas i faila!] (1) ar ne? (2)", 1, 2))
		switch (pas)
		{
		case 1:
			gautteisinga(pasmv, "Isvesti mediana(1), vidurki(2)?", 1, 2);
			if (grupe.empty())
			{
				cout << "Studentu nerasta! programa baigiama!";
				return 1;
			}
			else atrinkimas(grupe, nerdai, galiorka,pasmv,veiklaik);
			break;
		case 2:
			pas = 0;
			if (gautteisinga(pas, "I ekrana(1) ar i faila(2)?", 1, 2))
			{
				gautteisinga(pasmv, "Isvesti mediana(1), vidurki(2)?", 1, 2);
				if (grupe.empty())
				{
					cout << "Studentu nerasta! programa baigiama!";
					return 1;
				}
				else isvedimas(pas, pasmv, grupe);
			}
			break;
	}
	cout<<"Visos programos testo laikas: "<< veiklaik.count() << endl;
}