#include "manolib.h"

bool failasegzistuoja(const string& failopav)
{
	ifstream failas(failopav);
	return failas.good();
}
bool sortVardu(const Stud& a, const Stud& b) {
	return a.var < b.var;
}
bool sortPav(const Stud& a, const Stud& b) {
	return a.pav < b.pav;
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
		cerr << "Namu darbu pazymiu nera" << endl;
		return egrez;
	}
	vector<int> sorted_paz = paz;
	size_t size = sorted_paz.size();
	nth_element(sorted_paz.begin(), sorted_paz.begin() + size / 2, sorted_paz.end());
	double med = sorted_paz[size / 2];
	if (size % 2 == 0)
	{
		nth_element(sorted_paz.begin(), sorted_paz.begin() + size / 2 - 1, sorted_paz.end());
		med = (med + sorted_paz[size / 2 - 1]) / 2.0;
	}
	return (0.4 * med) + (0.6 * double(egrez));
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
	for (double pazym : paz)
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
	paz.reserve(paz.size() + pazymk);
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
	int pasi = 0;
	cout << "Pasirinkite, koki faila norit atidaryti (1 - 1000 studentu; 2 - 10000 studentu; 3 - 100000 studentu)" << endl;
	while (true) {
		cin >> pasi;
		if (cin.fail() || (pasi != 1 && pasi != 2 && pasi != 3)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Neteisingas pasirinkimas. Iveskite 1, 2 arba 3" << endl;
		}
		else {
			break;
		}
	}
	string failopav;
	switch (pasi)
	{
	case 1:
		failopav = "1000";
		break;
	case 2:
		failopav = "10000";
		break;
	case 3:
		failopav = "100000";
		break;
	}
	if (!failasegzistuoja(failopav))
	{
		cerr << "Klaida: failas " << failopav << " neegzistuoja nurodytoje vietoje!" << endl;
		return;
	}
	ifstream in(failopav);
	if (!in)
	{
		cerr << ("Nepavyko atidaryti failo!") << endl;
		return;
	}
	cout << "Failas atidarytas.";
	string temp;
	getline(in, temp);
	vector<future<Stud>> futures;
	while (getline(in, temp))
	{
		futures.push_back(std::async(std::launch::async, [temp]() -> Stud {
			try {
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
					throw runtime_error("Jokiu pazymiu nerasta mokiniui: " + laik.var + " " + laik.pav + "!");
					cout << endl;
				}
				laik.ndvid = ndvid(laik.paz);
				laik.gal = galvid(laik.egrez, laik.ndvid);
				laik.med = mediana(laik.paz, laik.egrez);
				return laik;
			}
			catch (const runtime_error& e)
			{
				cerr << "Klaida: " << e.what() << endl;
			}
			catch (const exception& e)
			{
				cerr << "Nenumatyta klaida: " << e.what() << endl;
			}
			return Stud();
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
			out << left << setw(15) << "Pavarde" << setw(18) << "Vardas" << setw(8) << "Galutinis (vid.)" << endl;
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
bool gautteisinga(int& input, const string& prompt, int min, int max) {
	cout << prompt;
	while (true) {
		cin >> input;
		if (cin.fail() || input < min || input > max) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Ivestas neteisingas simbolis/skaicius. Prasome ivesti reiksme tarp " << min << " ir " << max << ": ";
		}
		else {
			return true;
		}
	}
}
void failogen(const string& failopav, int irasuk)
{
	ofstream out(failopav);
	if (!out)
	{
		cerr << "Klaida! Neatidarytas failas " << failopav << endl;
		return;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> pazymk(1, 20);
	uniform_int_distribution<int> pazym(1, 10);

	const size_t bufferSize = 20000;
	vector<string> buffer;
	buffer.reserve(bufferSize);
	///int kiekpaz = pazymk(gen);
	int kiekpaz = 10;
	out << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
	for (int i = 1;i <= kiekpaz;i++)
	{
		out <<setw(6)<<( "ND" + to_string(i) );
	}
	out <<setw(10)<< "Egzaminas\n";
	for (int i = 1;i <= irasuk;i++)
	{
		ostringstream eil;
		eil << left << setw(15) << ("VardasNR" + to_string(i)) << setw(15) << ("PavardeNR" + to_string(i));
		for (int j = 0;j < kiekpaz;j++)
		{
			eil <<setw(6) << pazym(gen);
		}
		eil <<setw(10)<< pazym(gen);
		eil << endl;
		buffer.push_back(eil.str());

		if (buffer.size() >= bufferSize)
		{
			for (const auto& line : buffer)
			{
				out << line;
			}
			buffer.clear();
		}
	}
	for (const auto& eil : buffer) {
		out << eil;
	}


	out.close();
}
void atrinkimas(vector<Stud>& grupe, deque<Stud>& nerdai, list<Stud>& galiorka, int pasmv)
{
	auto pasis = (pasmv == 1) ?
		[](const Stud& s) { return s.med; } :
		[](const Stud& s) { return s.gal; };

	string pasir = (pasmv == 1) ? "Mediana" : "Galutinis";

	for (const auto& n : grupe)
	{
		if (n.gal >= 5) nerdai.push_back(n);
		else galiorka.push_back(n);
	}
	grupe.clear();
	grupe = vector<Stud>();
	ofstream outp("nerdai.txt");
	outp << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(6) << pasir << endl;
	for (const auto& n : nerdai)
	{
		outp << left << setw(15) << n.var << setw(15) << n.pav << setw(6) << pasis;
		outp << endl;
	}
	ofstream outf("galiorka.txt");
	outf << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(6) << pasir;
	for (const auto& n : nerdai)
	{
		outf << left << setw(15) << n.var << setw(15) << n.pav << setw(6) << pasis;
		outf << endl;
	}
}