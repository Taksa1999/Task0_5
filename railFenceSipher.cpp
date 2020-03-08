#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool railFenceSipher(unsigned int keyLength, string filename) {
	int firstSpace, secondSpace;
	unsigned int nowPos;
	string line, sipher;
	ifstream file_input(filename);
	ofstream file_output(filename.substr(0, filename.rfind(".")) + "Siphered.txt");
	bool lastWasSecondSpace;
	
	if (!file_input.is_open())
		return false;			
	if (!file_output.is_open())
		return false;

	file_input.seekg(0, ios::end);
	if (file_input.tellg() / 2 < keyLength)
		return false;

	file_input.seekg(0);
	while (getline(file_input, line)) {
		sipher = "";
		for (int i = 0; i < keyLength; i++) {
			nowPos = i;
			lastWasSecondSpace = true;
			firstSpace = (keyLength - 1) * 2 - (i * 2);
			secondSpace = i * 2;
			if (firstSpace == 0 or secondSpace == 0) {
				firstSpace = (keyLength - 1) * 2;
				secondSpace = firstSpace;
			}
			while (line.length() > nowPos) {
				sipher += line[nowPos];
				nowPos += (lastWasSecondSpace) ? firstSpace : secondSpace;
				lastWasSecondSpace = !lastWasSecondSpace;
			}
		}
		file_output << sipher << endl;
	}
	file_input.close();
	file_output.close();
	return true;
}