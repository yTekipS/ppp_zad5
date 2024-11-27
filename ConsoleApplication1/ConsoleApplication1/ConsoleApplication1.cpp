﻿#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

struct Date
{
	int temp = 0;
	string data;
};

int main()
{
	srand(time(NULL));

	ifstream file("temperatury.txt");
	ofstream wyniki("wyniki.txt");
	ofstream sorted("sorted.txt");
	Date date;
	vector <Date> lines;
	const int  s = 10;
	string miasta[s] = { "Rzeszow ", "Krakow ", "Lwow ", "Hamburg ", "Londyn ", "Warszawa ", "Poznan ", "Lizbona ", "Moskwa ", "Wolka Grodziska "};
	lines.reserve(100);
	string line="";

	

	if (file.good() && wyniki.good() && sorted.good()) {
		while (!file.eof())
		{
			int flag = 0;
			file >> line;
			if (line != "") {

				date.data = line.substr(0, 10);
				date.temp = stoi(line.substr(11, 2));
				lines.emplace_back(date);
			}
		}

		Date h;

		int size = lines.size();
		for (int j = 0; j < size; j++) {
			for (int i = 1; i < size - j; i++) {
				if (lines[i].temp < lines[i - 1].temp) {
					h = lines[i];
					lines[i] = lines[i - 1];
					lines[i - 1] = h;
				} 
			}
		}

		float avr = 0;

		for (auto item : lines) {
			cout << item.data << ";" << item.temp << "\n";
			avr += item.temp; 
		}
		avr = avr / lines.size();

		wyniki << "Srednia temperatur wynosila: " << avr << "\n";

		int min = lines[0].temp;
		int i = 1;
		int counter = 1;
		while (min == lines[i].temp) {
			counter++;
			i++;
		}
		cout << "\nNajmniejsza temperatura mialo " << counter << " dni.\n";
		wyniki << "Najmniejsza temperatura wynosila " << lines[0].temp << ". Wystapila " << counter << " razy.\n";

		int max = lines[size-1].temp;
		int j = 0;
		int counterr = 1;
		while (max == lines[size-2-j].temp) {
			counterr++;
			j++;
		}
		cout << "\nNajwieksza temperatura mialo " << counterr << " dni.\n";
		wyniki << "Najwieksza temperatura wynosila " << lines[lines.size()-1].temp << ". Wystapila  " << counterr << " razy.\n";


		for (auto item : lines) {
			sorted << miasta[rand() % s] << item.data << ';' << item.temp << '\n';
		}
	}

	else cout << "File not open.";

	file.close();	 
	wyniki.close();
	sorted.close();
}
