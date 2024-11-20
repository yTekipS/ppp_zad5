#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Date
{
	int temp;
	string data;
};

int main()
{
	ifstream file("temperatury.txt");
	Date date;
	vector <Date> lines;
	lines.reserve(100);
	string line="";

	if (file.good()) {
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

		for (auto& item : lines) {
			cout << item.data << ";" << item.temp << "\n";
		}
	}

	else cout << "File not open.";

	file.close();	 
}