#include "dequeh.h"

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
double mediana(const vector<int>& paz, double egrez, string var)
{
	if (paz.empty())
	{
		cerr << "Namu darbu pazymiu nerasta mokiniui " << var << endl;
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
vector<Stud> processBatch(const vector<string>& lines) {
	vector<Stud> batchResults;
	batchResults.reserve(lines.size());

	for (const auto& line : lines) {
		Stud laik;
		istringstream iss(line);
		iss >> laik.var >> laik.pav;

		int pazym;
		while (iss >> pazym) {
			laik.paz.push_back(pazym);
		}

		if (!laik.paz.empty()) {
			laik.egrez = laik.paz.back();
			laik.paz.pop_back();
		}

		laik.ndvid = ndvid(laik.paz);
		laik.gal = galvid(laik.egrez, laik.ndvid);
		laik.med = mediana(laik.paz, laik.egrez, laik.var);
		batchResults.push_back(laik);
	}
	return batchResults;
}

void skaitymas(deque<Stud>& grupe, duration<double>& veiklaik) {
	int pasi = 0;
	cout << "Pasirinkite faila (1 - 1000; 2 - 10000; 3 - 100000; 4 - 1000000; 5 - 10000000): " << endl;

	while (true) {
		cin >> pasi;
		if (cin.fail() || pasi < 1 || pasi > 5) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Netinkamas pasirinkimas. Bandykite dar kartą." << endl;
		}
		else {
			break;
		}
	}

	string failopav = to_string(static_cast<int>(pow(10, pasi + 2)));
	if (!failasegzistuoja(failopav)) {
		cerr << "Klaida: failas " << failopav << " neegzistuoja!" << endl;
		return;
	}

	ifstream in(failopav, ios::in | ios::ate); // atidarom gale paziureti failo dydi
	if (!in) {
		cerr << "Nepavyko atidaryti failo!" << endl;
		return;
	}

	size_t fileSize = in.tellg(); // gaunam failo dydi
	in.seekg(0, ios::beg); // einam i prieky failo

	cout << "Failas atidarytas: " << failopav << endl;
	auto start = high_resolution_clock::now();

	const size_t BUFFER_SIZE = 64 * 1024 * 1024;
	vector<char> buffer(min(fileSize, BUFFER_SIZE));

	string header;
	getline(in, header);

	vector<future<vector<Stud>>> futures;
	vector<string> lines;

	while (in.read(buffer.data(), buffer.size()) || in.gcount() > 0) {
		stringstream ss(string(buffer.data(), in.gcount()));
		string line;

		while (getline(ss, line)) {

			auto trim = [](const string& str) -> string {
				size_t first = str.find_first_not_of(" \t");
				size_t last = str.find_last_not_of(" \t");
				return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
				};
			stringstream lineStream(line);
			string vardas, pavarde, grade;

			lineStream >> vardas;
			vardas = trim(vardas);

			lineStream >> pavarde;
			pavarde = trim(pavarde);

			getline(lineStream, grade);

			if (!vardas.empty() && !pavarde.empty()) {
				lines.push_back(line);
			}
			if (lines.size() >= 100000) {
				futures.push_back(async(launch::async, processBatch, lines));
				lines.clear();
			}
		}
	}

	in.close();

	// imam likusias eil
	if (!lines.empty()) {
		futures.push_back(async(launch::async, processBatch, lines));
	}

	// surenkam rezultatus
	for (auto& fut : futures) {
		vector<Stud> batch = fut.get();
		grupe.insert(grupe.end(), batch.begin(), batch.end());
	}

	auto end = high_resolution_clock::now();
	veiklaik += end - start;
	cout << "Failo skaitymo laikas: " << duration<double>(end - start).count() << " s" << endl;
}

void isvedimas(int pas, int pasmv, const deque<Stud>& grupe)
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
	out << left << setw(25) << "Vardas" << setw(25) << "Pavarde";
	for (int i = 1;i <= kiekpaz;i++)
	{
		out << setw(6) << ("ND" + to_string(i));
	}
	out << setw(10) << "Egzaminas\n";
	for (int i = 1;i <= irasuk;i++)
	{
		ostringstream eil;
		eil << left << setw(25) << ("VardasNR" + to_string(i)) << setw(25) << ("PavardeNR" + to_string(i));
		for (int j = 0;j < kiekpaz;j++)
		{
			eil << setw(6) << pazym(gen);
		}
		eil << setw(10) << pazym(gen);
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
void atrinkimas(deque<Stud>& grupe, deque<Stud>& nerdai, list<Stud>& galiorka, int pasmv, duration<double>& veiklaik)
{
	auto pasis = (pasmv == 1) ?
		[](const Stud& s) { return s.med; } :
		[](const Stud& s) { return s.gal; };

	string pasir = (pasmv == 1) ? "Mediana" : "Galutinis";

	auto start1 = high_resolution_clock::now();
	for (const auto& n : grupe)
	{
		if (n.gal >= 5) nerdai.push_back(n);
		else galiorka.push_back(n);
	}
	grupe.clear();
	grupe = deque<Stud>();
	auto end1 = high_resolution_clock::now();
	veiklaik += end1 - start1;
	cout << "Atskyrimo i dvi grupes veikimo laikas panaikinant originalu vektoriu: " << duration<double>(end1 - start1).count() << endl;
	///auto start2 = high_resolution_clock::now();
	ofstream outp("nerdai.txt");
	outp << fixed << setprecision(2) << left << setw(25) << "Vardas" << setw(25) << "Pavarde" << setw(6) << pasir << endl;
	for (const auto& n : nerdai)
	{
		outp << left << setw(25) << n.var << setw(25) << n.pav << setw(6) << pasis(n);
		outp << endl;
	}
	///auto end2 = high_resolution_clock::now();
	///veiklaik += end2 - start2;
	///cout << "Nerdu irasymo i faila veikimo laikas: " << duration<double>(end2 - start2).count() << endl;
	///auto start3 = high_resolution_clock::now();
	ofstream outf("galiorka.txt");
	outf << fixed << setprecision(2) << left << setw(25) << "Vardas" << setw(25) << "Pavarde" << setw(6) << pasir << endl;
	for (const auto& n : galiorka)
	{
		outf << left << setw(25) << n.var << setw(25) << n.pav << setw(6) << pasis(n);
		outf << endl;
	}
	///auto end3 = high_resolution_clock::now();
	///veiklaik += end3 - start3;
	///cout << "Galiorkos irasymo i faila veikimo laikas:  " << duration<double>(end3 - start3).count() << endl;
}

