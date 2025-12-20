#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void welcome_message() {
	cout << "Welcome!" << endl;
	cout << "This project demonstrates basic programming concepts in C++."
		<< endl << "2025638" << endl << "2025018" << endl << "2025567" << endl << endl;
}

void display_menu() {
	cout << "==========================================" << endl;
	cout << "      Stock trading analysis system      " << endl;
	cout << "==========================================" << endl;
	cout << "1. Load stock data:" << endl;
	cout << "2. Display all stocks" << endl;
	cout << "3. analyze stocks" << endl;
	cout << "4. Exit" << endl << endl;
}

void display_secondary_menu() {
	cout << "-------------------------------" << endl;
	cout << "      Stock analysis options      " << endl;
	cout << "-------------------------------" << endl;
	cout << "1. Display highest price stock" << endl;
	cout << "2. Display lowest price stock" << endl;
	cout << "3. Display average price of stocks" << endl;
}

int  get_menu_choice() {
	int choice;
	cout << "Enter your choice: ";
	cin >> choice;
	while (choice < 1 || choice > 4) {
		cout << "Invalid choice. Please enter a number between 1 and 4: ";
		cin >> choice;
	}
	return choice;
}

void open_file(fstream& file) {
	string filename;
	while (true) {
		cout << "Enter the filename to load stock data: ";
		cin >> filename;
		file.open(filename, ios::in);
		if (file.is_open()) {
			cout << "File opened successfully." << endl;
			break;
		}
		else {
			cout << "Error opening file. Please try again." << endl;
		}
	}

}

int countStocksInFile(ifstream& fin) {
	string line;
	int counter = -1;  //-1 because first line is headings
	while (getline(fin, line)) {
		counter++;
	}
	fin.clear(); //clears eof flag
	fin.seekg(0);  //reset pointer to beginning of file for future use
	return counter;
}

int countdaysinfile(fstream& fin) {
	int counter = 0;
	char ch;
	char previous_ch;  //using prev to check spaces
	ch = fin.get();
	previous_ch = ch;
	while (fin.get(ch)) {
		if (ch == '\n') {  //only read 1 column
			break;
		}
		if (previous_ch == ' ' && ch != ' ' && ch != 'S') { //detects start of new entry
			counter++;
		}
		previous_ch = ch;
	}
	fin.clear();
	fin.seekg(0);
	return counter;
}

void readstocknames(fstream& fin, string stocknames[], int numstocks) {
	char ch;
	string temp = "";
	int counter = 0;
	while (fin.get(ch)) {
		if (ch == '\n') {  //skips first line as they are headings
			break;
		}
	}
	while (fin.get(ch) && counter < numstocks) {
		if (ch == ' ') {  //store name when string detected
			stocknames[counter] = temp;
			counter++;
			temp = "";  //reset temporary variable for next stock name
			while (ch != '\n' && fin.get(ch)); //skip to next line
		}
		if (ch != '\n' && ch != ' ') {
			temp = temp + ch; //building string
		}

	}
	fin.clear();
	fin.seekg(0);
}


void readstockprices(fstream& fin, double prices[][],