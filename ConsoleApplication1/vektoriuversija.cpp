#include "manolib.h"


bool sortVardu(const Stud& a, const Stud& b) {
	return a.var < b.var;
}

bool sortMed(const Stud& a, const Stud& b) {
	return a.med < b.med;
}

bool sortGal(const Stud& a, const Stud& b) {
	return a.gal < b.gal;
}
double mediana(const vector<int>& paz, double egrez)
{
	if (paz.empty())
	{
		cout << "Namu darbu pazymiu nera" << endl;
		return egrez;
	}
	vector<int> sorted_paz = paz;
	sort(sorted_paz.begin(), sorted_paz.end());
	int size = sorted_paz.size();
	double med;

	if (size % 2 == 0)
	{
		nth_element(sorted_paz.begin(), sorted_paz.begin() + size / 2 - 1, sorted_paz.end());
		double kaire = sorted_paz[size / 2 - 1];
		nth_element(sorted_paz.begin(), sorted_paz.begin() + size / 2, sorted_paz.end());
		double desine = sorted_paz[size / 2];
		med = (kaire + desine) / 2.0;
	}
	else
	{
		nth_element(sorted_paz.begin(), sorted_paz.begin() + size / 2, sorted_paz.end());
		med = sorted_paz[size / 2];
	}

	return (0.4*med)+(0.6*double(egrez));
}
double galvid(double egrez, double ndvd)
{
double galutinis = (0.6 * egrez) + (0.4 * ndvd);
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
void rng(vector<int>& paz)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> pazkiek(1, 10);
	uniform_int_distribution<int> pazym(1, 10);
	int pazymk = pazkiek(gen);
	cout << "Generuojami pazymiai..." << endl;
	for (int i = 0;i < pazymk;i++)
	{
		int pazy = pazym(gen);
		paz.push_back(pazy);
		cout << pazy << " ";
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
void skaitymas(vector<Stud>& grupe)
{
	Stud laik;
	ifstream in("kursiokai2.txt");
	if (!in)
	{
		cerr << "Nerastas failas!" << endl;
		return;
	}
	string temp;
	getline(in, temp);
	vector<future<Stud>> futures;
	while (getline(in, temp))
	{
		futures.push_back(std::async(std::launch::async, [temp]() -> Stud {
			Stud laik;
			istringstream iss(temp);
			iss >> laik.var >> laik.pav;
			int pazym;

			while (iss >> pazym)
			{
				laik.paz.push_back(pazym);
			}

			if (!laik.paz.empty())
			{
				laik.egrez = laik.paz.back();
				laik.paz.pop_back();
			}
			else
			{
				cerr << "Jokiu pazymiu nerasta mokiniui: " << laik.var << " " << laik.pav << "!" << endl;
			}
			laik.ndvid = ndvid(laik.paz);
			laik.gal = galvid(laik.egrez, laik.ndvid);
			laik.med = mediana(laik.paz, laik.egrez);

			return laik;
			}));
	}
	in.close();
	for (auto& fut : futures)
	{
		grupe.push_back(fut.get());
	}
}
void isvedimas(int pas, int pasmv, const vector<Stud>& grupe)
{
	switch (pas)
	{
	case 1:
		switch (pasmv)
		{
			case 1:
				cout << left << setw(15) << "Vardas" << setw(18) << "Pavarde" << setw(8) << "Galutinis (med.)" << endl;
				cout << string(52, '-') << endl;
				for (const auto& n : grupe)
					{
					cout << fixed << left << setw(15) << setprecision(2) << n.var << setw(18) << n.pav << setw(8) << n.med << endl;
					}
			break;
	
			case 2:
				cout << left << setw(15) << "Vardas" << setw(18) << "Pavarde" << setw(8) << "Galutinis (vid.)" << endl;
				cout << string(52, '-') << endl;
				for (const auto& n : grupe)
					{
					cout << fixed << left << setw(15) << setprecision(2) << n.pav << setw(18) << n.var << setw(8) << n.gal << endl;
					}
			break;
		}
		break;
	case 2:
		ofstream out("kursiokaiapdorotas.txt");
		switch (pasmv)
		{
		case 1:
			out << left << setw(15) << "Vardas" << setw(18) << "Pavarde" << setw(8) << "Galutinis (med.)" << endl;
			out << string(52, '-') << endl;
			for (const auto& n : grupe)
			{
				out << fixed << left << setw(15) << setprecision(2) << n.var << setw(18) << n.pav << setw(8) << n.med << endl;
			}
			break;

		case 2:
			out << left << setw(15) << "Vardas" << setw(18) << "Pavarde" << setw(8) << "Galutinis (vid.)" << endl;
			out << string(52, '-') << endl;
			for (const auto& n : grupe)
			{
				out << fixed << left << setw(15) << setprecision(2) << n.pav << setw(18) << n.var << setw(8) << n.gal << endl;
			}
			break;
		}
		out.close();
		break;
	}
}


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
	else{
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
			else if(pazym== -1 and i<1) cout << "Neivedete nei vieno namu darbu pazymio!";
			if ((pazym > 10 or pazym < 1) and pazym != - 2) cout << "Iveskite skaiciu nuo 1 iki 10!" << endl;
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
	cout << "Pasirinkite, kaip norite surikiuoti (1 - Vardas, 2 - Mediana, 3 - Galutinis pazymys): ";
	cin >> sortpas;
	switch (sortpas) {
	case 1:
		sort(grupe.begin(), grupe.end(), sortVardu);
		cout << "Surikiuota pagal vardus (abeceles tvarka)." << endl;
		break;
	case 2:
		sort(grupe.begin(), grupe.end(), sortMed);
		cout << "Surikiuota pagal mediana." << endl;
		break;
	case 3:
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
	cin >> pas;
	cout << "Isvesti mediana(1), vidurki(2)?" << endl;
	cin >> pasmv;
	isvedimas(pas, pasmv, grupe);
}