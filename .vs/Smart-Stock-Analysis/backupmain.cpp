//THIS IS A BACKUP CODE OF PREVIOUS VERSION



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

int countStocksInFile(fstream& fin) {
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

const int MAX_DAYS = 365;
const int MAX_STOCKS = 50;

void readstocknames(fstream& fin, string(&stocknames)[MAX_STOCKS], int numstocks) {
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

void readstockprices(fstream& fin, double(&prices)[MAX_DAYS][MAX_STOCKS], int numdays, int numstocks) {
	for (int i = 0; i < MAX_DAYS; i++) {
		for (int j = 0; j < MAX_STOCKS; j++) {
			prices[i][j] = -1;
		}
	}

	char ch;
	double price;
	while (fin.get(ch)) {
		if (ch == '\n') {  //skips first line as they are headings
			break;
		}
	}
	for (int x = 0; x < numstocks; x++) {
		while (fin.get(ch)) {
			if (ch == ' ') { //skips first word in each row
				break;
			}
		}
		for (int y = 0; y < numdays; y++) {
			fin >> price;
			prices[y][x] = price;
		}
	}
	fin.clear();
	fin.seekg(0);
}

void displayalldata(string stocknames[MAX_STOCKS], double prices[MAX_DAYS][MAX_STOCKS], int numdays, int numstocks) {
	cout << "Stocks:";
	for (int x = 0; x < numstocks; x++) {
		cout << " " << stocknames[x]; //header line
	}
	cout << endl;
	for (int x = 0; x < numdays; x++) {
		cout << "Day" << x + 1 << ":";
		for (int y = 0; y < numstocks; y++) {
			cout << "     " << prices[x][y];
		}
		cout << endl;
	}
}

//global varibale
int const MAXDAYS = 365;
//FUNCTIONS

//Average Price
double averageprice(double price[], int numdays) {
	//variables
	double avg, total = 0;
	//calculating total
	for (int x = 0; x < numdays; x++) {
		total = total + price[x];
	}
	//calculating average
	avg = total / numdays;
	return avg;
}
//percentage profit/loss
double profitloss(double price[], int numdays) {
	//variables
	double day1, daylast, perc;
	day1 = price[0];
	daylast = price[numdays - 1];
	perc = ((daylast - day1) / day1) * 100;//calculating percent profitloss
	return perc;
}

//profitdays
int profitdays(double price[], int numdays) {
	//variables
	int dayprofit = 0;
	//comparing current day to previous day to see if it profit
	if (numdays == 0 || numdays == 1) {
		dayprofit = 0;//no day can profit if the data is only for a day or zero days
	}
	else {
		for (int x = 1; x < numdays; x++) {
			//starting from index1 so we can compare it to prev day
			if (price[x] > price[x - 1]) {
				dayprofit += 1;
			}
		}
	}
	return dayprofit;
}

//lossdays
int lossdays(double price[], int numdays) {
	//variables
	int dayloss = 0;
	//comparing current day to previous day to see if it profit
	if (numdays == 0 || numdays == 1) {
		dayloss = 0;//no day can loss if the data is only for a day or zero days
	}
	else {
		for (int x = 1; x < numdays; x++) {
			//starting from index1 so we can compare it to prev day
			if (price[x] < price[x - 1]) {
				dayloss += 1;
			}
		}
	}
	return dayloss;
}

//returns the trend profit loss graph follows
string generaltrend(double price[], int numdays) {
	string trend;
	int profit, loss, stable;
	//calculating profit loss and stable days
	profit = profitdays(price, numdays);
	loss = lossdays(price, numdays);
	stable = numdays - profit - loss;
	//conditions to see what the general trend is
	if (profit > loss && profit > stable) {
		trend = "up";
	}
	else if (loss > stable && loss > profit) {
		trend = "down";
	}
	else {
		trend = "stable";
	}
	return trend;
}

//Recommendation to buy hold or avoid
string reccomend(double price[], int numdays) {
	//variables
	string decide, trend;
	int profit, loss, stable;
	//calculating profit loss and stable days
	profit = profitdays(price, numdays);
	loss = lossdays(price, numdays);
	stable = numdays - profit - loss;
	//trend
	trend = generaltrend(price, numdays);
	if (profit > loss && trend == "up") {
		decide = "BUY";
	}
	else if (loss > profit && trend == "down") {
		decide = "AVOID";
	}
	else {
		decide = "HOLD";
	}

	return decide;
}

//best stock
string BestStock(string stockNames[], double pricestocks[MAX_DAYS][MAX_STOCKS], int numStocks, int numDays) {
	string best = stockNames[0]; // initially set first stock as best
	double bestperc, currentperc;
	double price1[MAX_DAYS];
	// fill first stock's prices (column 0)
	for (int x = 0; x < numDays; x++) {
		price1[x] = pricestocks[x][0];
	}
	bestperc = profitloss(price1, numDays);
	for (int i = 1; i < numStocks; i++) {
		double price2[MAX_DAYS];
		for (int x = 0; x < numDays; x++) {
			price2[x] = pricestocks[x][i]; // i-th stock column
		}
		currentperc = profitloss(price2, numDays);
		if (currentperc > bestperc) {
			best = stockNames[i];
			bestperc = currentperc;
		}
	}
	return best;
}

//worst stock
string WorstStock(string stockNames[], double pricestocks[MAX_DAYS][MAX_STOCKS], int numStocks, int numDays) {
	string worst = stockNames[0]; // initially set first stock as worst
	double worstperc, currentperc;
	double price1[MAX_DAYS];
	for (int x = 0; x < numDays; x++) {
		price1[x] = pricestocks[x][0];
	}
	worstperc = profitloss(price1, numDays);
	for (int i = 1; i < numStocks; i++) {
		double price2[MAX_DAYS];
		for (int x = 0; x < numDays; x++) {
			price2[x] = pricestocks[x][i];
		}
		currentperc = profitloss(price2, numDays);
		if (currentperc < worstperc) {
			worst = stockNames[i];
			worstperc = currentperc;
		}
	}
	return worst;
}


//saving report in file
void saveReport(string filename, string stockNames[], string recommendation[], int numStocks) {
	ofstream myfile(filename, ios::app);
	if (myfile.is_open()) {
		for (int i = 0; i < numStocks; i++) {
			myfile << stockNames[i] << "," << recommendation[i] << "\n";
		}
	}
	else {
		cout << "file did not open" << endl;
	}
	myfile.close();
}

int main() {
	fstream stockFile;
	string stockNames[MAX_STOCKS];
	double prices[MAX_DAYS][MAX_STOCKS];
	string recommendation[MAX_STOCKS];
	int numStocks = 0, numDays = 0;
	int choice;
	welcome_message();
	do {
		display_menu();
		choice = get_menu_choice();
		switch (choice) {
		case 1: // Load stock data
			open_file(stockFile);
			// Count stocks and days
			numStocks = countStocksInFile(stockFile);
			numDays = countdaysinfile(stockFile);
			// Read stock names and prices
			readstocknames(stockFile, stockNames, numStocks);
			readstockprices(stockFile, prices, numDays, numStocks);
			cout << "Data loaded successfully!\n";
			stockFile.close();
			break;
		case 2: // Display all stocks
			if (numStocks > 0 && numDays > 0) {
				displayalldata(stockNames, prices, numDays, numStocks);
			}
			else {
				cout << "No data loaded yet. Please load stock data first.\n";
			}
			break;

		case 3: // Analyze stocks
			if (numStocks > 0 && numDays > 0) {
				// Generate recommendations for each stock
				for (int s = 0; s < numStocks; s++) {
					double priceCol[MAX_DAYS];
					for (int d = 0; d < numDays; d++) {
						priceCol[d] = prices[d][s]; // day, stock format
					}
					recommendation[s] = reccomend(priceCol, numDays);
				}
				cout << "Best Stock: " << BestStock(stockNames, prices, numStocks, numDays) << endl;
				cout << "Worst Stock: " << WorstStock(stockNames, prices, numStocks, numDays) << endl;
				string filename;
				cout << "Enter filename to save report: ";
				cin >> filename;
				saveReport(filename, stockNames, recommendation, numStocks);
				cout << "Report saved successfully!\n";
			}
			else {
				cout << "No data loaded yet. Please load stock data first.\n";
			}
			break;

		case 4: // Exit
			cout << "Exiting program. Goodbye!\n";
			break;
		}
	} while (choice != 4);
	return 0;
}
