#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;


//global varibale
int const MAXDAYS= 100;
//FUNCTIONS

//Average Price
double averageprice(double price[], int numdays){
	
	//variables
	double avg, total = 0;
	
	//calculating total
	for(int x=0; x<numdays; x++){
		total = total + price[x];
	}
	
	//calculating average
	avg = total/numdays;
		
	return avg;
}

//percentage profit/loss
double profitloss(double price[], int numdays){
	//variables
	double day1,daylast,perc;
	
	day1 = price[0];
	daylast = price[numdays-1];
	
	perc = ((daylast-day1)/day1)*100;//calculating percent profitloss
	
	return perc;
}

//profitdays
int profitdays(double price[], int numdays){
	//variables
	int dayprofit=0;
	
	//comparing current day to previous day to see if it profit
	
	if(numdays == 0 || numdays ==1 ){
		dayprofit = 0;//no day can profit if the data is only for a day or zero days
	}
	else{
		for(int x=1; x<numdays; x++){
			//starting from index1 so we can compare it to prev day
			if(price[x]>price[x-1]){
				dayprofit += 1;
			}
		}
	}
		
	
	
	return dayprofit;
}

//lossdays
int lossdays(double price[], int numdays){
	//variables
	int dayloss=0;
	
	//comparing current day to previous day to see if it profit
	
	if(numdays == 0 || numdays ==1 ){
		dayloss = 0;//no day can loss if the data is only for a day or zero days
	}
	else{
		for(int x=1; x<numdays; x++){
			//starting from index1 so we can compare it to prev day
			if(price[x]<price[x-1]){
				dayloss += 1;
			}
		}
	}
		
	
	
	return dayloss;
}

//returns the trend profit loss graph follows
string generaltrend(double price[], int numdays){
	string trend;
	int profit,loss,stable;
	
	//calculating profit loss and stable days
	profit = profitdays(price, numdays);
	loss = lossdays(price, numdays);
	stable = numdays - profit - loss;
	
	//conditions to see what the general trend is
	if(profit>loss && profit>stable){
		trend = "up";
	}
	else if(loss>stable && loss>profit){
		trend = "down";
	}
	else{
		trend = "stable";
	}
	
	
	return trend;
}

//Recommendation to buy hold or avoid
string reccomend(double price[], int numdays){
	//variables
	string decide,trend;
	int profit, loss, stable;
	
	//calculating profit loss and stable days
	profit = profitdays(price, numdays);
	loss = lossdays(price, numdays);
	stable = numdays - profit - loss;
	
	//trend
	trend= generaltrend(price, numdays);
	
	if(profit > loss && trend == "up"){
		decide = "BUY";
	}
	else if(loss>profit && trend == "down"){
		decide = "AVOID";
		
	}else{
		decide= "HOLD";
	}
	
	return decide;
}

//best stock
string BestStock(string stockNames[], double pricestocks[][MAXDAYS],int numStocks, int numDays){
	
	string best = stockNames[0];//initially set first stock as best
	double bestperc,currentperc;
	int const size = numDays;
	double price1[size];
	for(int x=0;x<numDays;x++){//making bestperc initially set to first stock	
		price1[x] = pricestocks[0][x];
	}
	bestperc = profitloss(price1, numDays);//initially setting first stock to be the worst
		
	for(int i=1; i<numStocks; i++){
		double price2[size];
		for(int x=0;x<numDays;x++){
			price2[x] = pricestocks[i][x];	
		}
		currentperc = profitloss(price2, numDays);//sets current iteration to current percentage
		if(currentperc>bestperc){//if current stock has done more profit then previous stock
			best = stockNames[i];//set best stock to current stock
			bestperc=currentperc;// switch the current percentage in to bestpercentage for next loop
		}
		//else it would keep the same name so no need to write its function
		
		
	}
	
	
	
	return best;
}

//worst stock
string WorstStock(string stockNames[], double pricestocks[][MAXDAYS],int numStocks, int numDays){
	
	string worst = stockNames[0];//initially set first stock as worst
	double worstperc,currentperc;
	int const size = numDays;
	double price1[size];
	for(int x=0;x<numDays;x++){//filling up price1 array with first stock		
		price1[x] = pricestocks[0][x];	
	}
	worstperc = profitloss(price1, numDays);//initially setting first stock to be the worst
		
	for(int i=1; i<numStocks; i++){
		double price2[size];
		for(int x=0;x<numDays;x++){
			price2[x] = pricestocks[i][x];
			
		}currentperc = profitloss(price2, numDays);//sets current iteration to current percentage
		if(currentperc<worstperc){//if current stock has done less profit then previous stock
			worst = stockNames[i];//set worst stock to current stock
			worstperc=currentperc;// switch the current percentage in to worst percentage for next loop
		}
		//else it would keep the same name so no need to write its function
		
		
	}
	
	
	
	return worst;
}

//saving report in file
void saveReport(string filename, string stockNames[],string recommendation[], int numStocks){
	
	ofstream myfile(filename,ios::app);
	
	if(myfile.is_open()){
		for(int i=0; i<numStocks; i++){
			myfile << stockNames[i] << "," << recommendation[i] << "\n";				
		}
				
	}else{
		cout<<"file did not open"<<endl;
	}
	
	myfile.close();
}



int main(){
	
	return 0;
}
