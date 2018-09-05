/*
	Name:    Marco Martinez
	Project: financialReport.cpp
	Purpose: Calculate and display a financial report in alphabetical order based on last name.
		 Format output according to assignment sheet.
	Date:    8/30/2018

	Software Change Record
	Date			Who				What
	8/30			Marco M.		Basic Structure (Input name & numbers, output name & calculated numbers)
	8/31			Marco M.		Segment input and processing sections into functions
	9/2			Marco M.		Implement accumulation for arrays
	9/3			Marco M.		Implement the sorting of data by last name and complete formatting of output text
*/

/*---Libraries---*/
#include <iostream>
#include <iomanip>
#include <string>

/*---Constant Declarations---*/
const int EMPS = 5;               // Controls amount of employs to enter
const float TAXRATE = 0.15F;      // Rate of tax as subject to law
const float OVERTIMERATE = 1.5F;  // 150% pay amount for overtime work
const int REGULARHOURS = 40;      // Number of hours in a normal work day

using namespace std;

/*---Function Declarations---*/
void getInfo(string firstName[], string lastName[], float payRate[], float hrsWkd[]);
string determineEmp(int value);
void calcInfo(string firstName[], string lastName[], string fullName[], float payRate[], float hrsWkd[], float grossPay[], float taxAmt[], float netPay[], float &totPayRate, float &totHrsWkd, float &totGrossPay, float &totTaxAmt, float &totNetPay, float &avgPayRate, float &avgHrsWkd, float &avgGrossPay, float &avgTaxAmt, float &avgNetPay);
void getTotals(float payRate[], float hrsWkd[], float grossPay[], float taxAmt[], float netPay[], float &totPayRate, float &totHrsWkd, float &totGrossPay, float &totTaxAmt, float &totNetPay);
float calcTotal(float values[]);
void getAvgs(float totPayRate, float totHrsWkd, float totGrossPay, float totTaxAmt, float totNetPay, float &avgPayRate, float &avgHrsWkd, float &avgGrossPay, float &avgTaxAmt, float &avgNetPay);
float calcAvg(float value);
void calcGrossPay(float payRate[], float hrsWkd[], float grossPay[]);
void calcTaxAmt(float grossPay[], float taxAmt[]);
void calcNetPay(float grossPay[], float taxAmt[], float netPay[]);
void sortInfo(string firstName[], string lastName[], float payRate[], float hrsWkd[], float grossPay[], float taxAmt[], float netPay[]);
void bubbleString(string valueString[], int i, int j);
void bubbleFloat(float valueFloat[], int i, int j);
void concantenateName(string firstName[], string lastName[], string fullName[]);
void displayInfo(string fullName[], float payRate[], float hrsWkd[], float netPay[], float totPayRate, float totHrsWkd, float totGrossPay, float totTaxAmt, float totNetPay, float avgPayRate, float avgHrsWkd, float avgGrossPay, float avgTaxAmt, float avgNetPay);

/*----The Main Module----*/
int main() {

	/*----Variable Declaration----*/
	/*--Employee Name Data--*/
	string  firstName[EMPS];
	string  lastName[EMPS];
	string  fullName[EMPS];

	/*--Employee Financials--   --Totals--     --Averages--*/				
	float   payRate[EMPS],	    totPayRate,	     avgPayRate,
		hrsWkd[EMPS],	    totHrsWkd,	     avgHrsWkd,
		grossPay[EMPS],	    totGrossPay,     avgGrossPay,
		taxAmt[EMPS],	    totTaxAmt,	     avgTaxAmt,
		netPay[EMPS],	    totNetPay,	     avgNetPay;

	/*---Body---*/
	getInfo(firstName, lastName, payRate, hrsWkd);
	calcInfo(firstName, lastName, fullName, payRate, hrsWkd, grossPay, taxAmt, netPay, totPayRate, totHrsWkd, totGrossPay, totTaxAmt, totNetPay, avgPayRate, avgHrsWkd, avgGrossPay, avgTaxAmt, avgNetPay);
	displayInfo(fullName, payRate, hrsWkd, netPay, totPayRate, totHrsWkd, totGrossPay, totTaxAmt, totNetPay, avgPayRate, avgHrsWkd, avgGrossPay, avgTaxAmt, avgNetPay);
}
	/*----Functions----*/

	/*I[X]			P[]			O[]*/
//	Input values: none.
//
//	Output values: Strings: (firstName[], lastName[])
//                 	Floats:  (payRate[], hrsWkd[])
//
//	Input/ Output values: none.
//
//	Purpose:
//
//	This function outputs text requesting the user to input values for four different arrays.
//	It then records that information into each of the four arrays.
//	It also utilizes determineEmp to determine which employee is being entered.
//	This array utilizes the constant EMPS as a reference for the number of employees.
//
void getInfo(string firstName[], string lastName[], float payRate[], float hrsWkd[]) {
	for (int i = 0; i < EMPS; i++) {
		cout << "Please enter the " << determineEmp(i) << " employee's first name here: ";
		cin >> firstName[i];

		cout << "Please enter the " << determineEmp(i) << " employee's last name here: ";
		cin >> lastName[i];

		cout << "Please enter the " << determineEmp(i) << " employee's hourly pay here: ";
		cin >> payRate[i];

		cout << "Please enter the " << determineEmp(i) << " employee's number of worked hours: ";
		cin >> hrsWkd[i];

		cout << endl;
	}
}

/*I[]			P[X]			O[]*/
//	Input values: Int: value.
//
//	Output values: String: return string.
//                 
//	Input/ Output values: none.
//
//	Purpose:
//
//	This function inputs the value of a loop and utilizes that value to
//	determine which employee the user is attempting to enter.
//
string determineEmp(int value) {
	if (value == 0)
		return "first";
	else if (value == 1)
		return "second";
	else if (value == 2)
		return "third";
	else if (value == 3)
		return "fourth";
	else if (value == 4)
		return "fifth";
}

/*I[]			P[X]			O[]*/
//	Input values: Strings: (firstName[], lastName[]).
//
//	Output values: none.
//                 
//	Input/ Output values: Floats: (payRate[], fhrsWkd[], grossPay[], taxAmt[], netPay[], totPayRate, totHrsWkd, totGrossPay,
//                                 totTaxAmt, totNetPay, avgPayRate, avgHrsWkd, avgGrossPay, avgTaxAmt, avgNetPay).
//						  String: fullName[].
//	Purpose:
//	
//	This function is a hub function for various subfunctions. 
//	This function is intended to segment the entirety of the calculations for the program.
//
void calcInfo(string firstName[], string lastName[], string fullName[], float payRate[], float hrsWkd[], float grossPay[], float taxAmt[], float netPay[], float &totPayRate, float &totHrsWkd, float &totGrossPay, float &totTaxAmt, float &totNetPay, float &avgPayRate, float &avgHrsWkd, float &avgGrossPay, float &avgTaxAmt, float &avgNetPay) {
	calcGrossPay(payRate, hrsWkd, grossPay);
	calcTaxAmt(grossPay, taxAmt);
	calcNetPay(grossPay, taxAmt, netPay);
	getTotals(payRate, hrsWkd, grossPay, taxAmt, netPay, totPayRate, totHrsWkd, totGrossPay, totTaxAmt, totNetPay);
	getAvgs(totPayRate, totHrsWkd, totGrossPay, totTaxAmt, totNetPay, avgPayRate, avgHrsWkd, avgGrossPay, avgTaxAmt, avgNetPay);
	sortInfo(firstName, lastName, payRate, hrsWkd, grossPay, taxAmt, netPay);
	concantenateName(firstName, lastName, fullName);
}

/*I[]			P[X]			O[]*/
//	Input values: Floats: (payRate[], fhrsWkd[], grossPay[], taxAmt[], netPay[]).
//
//	Output values: Floats: (totPayRate, totHrsWkd, totGrossPay,totTaxAmt, totNetPay).
//                 
//	Input/ Output values: none.
//                           
//	Purpose:
//	
//	This function gathers all of the total values in a compact way for assignment.
//	This function is reliant upon calcTotal as calcTotal processes the values.
//
void getTotals(float payRate[], float hrsWkd[], float grossPay[], float taxAmt[], float netPay[], float &totPayRate, float &totHrsWkd, float &totGrossPay, float &totTaxAmt, float &totNetPay) {
	totPayRate = calcTotal(payRate);
	totHrsWkd = calcTotal(hrsWkd);
	totGrossPay = calcTotal(grossPay);
	totTaxAmt = calcTotal(taxAmt);
	totNetPay = calcTotal(netPay);
}

/*I[]			P[X]			O[]*/
//	Input values: Floats: (values[]).
//
//	Output values: Float: return total.
//                 
//	Input/ Output values: none.
//                           
//	Purpose:
//	
//	This function accumulates the values with each element of an array and stores it within total.
//	This function is reliant upon accurate data being received from getTotals.
//
float calcTotal(float values[]) {
	float total = 0.0;

	for (int i = 0; i < EMPS; i++) {
		total += values[i];
	}

	return total;
}

/*I[]			P[X]			O[]*/
//	Input values: Floats: (totPayRate, totHrsWkd, totGrossPay, totTaxAmt, totNetPay).
//
//	Output values: Floats: (avgPayRate, avgHrsWkd, avgGrossPay, avgTaxAmt, avgNetPay).
//                 
//	Input/ Output values: none.
//                           
//	Purpose:
//	
//	This function gathers all average values in a compact way for assignment.
//	This function is reliant upon accurate data being received from calcAvg.
//
void getAvgs(float totPayRate, float totHrsWkd, float totGrossPay, float totTaxAmt, float totNetPay, float &avgPayRate, float &avgHrsWkd, float &avgGrossPay, float &avgTaxAmt, float &avgNetPay) {
	avgPayRate = calcAvg(totPayRate);
	avgHrsWkd = calcAvg(totHrsWkd);
	avgGrossPay = calcAvg(totGrossPay);
	avgTaxAmt = calcAvg(totTaxAmt);
	avgNetPay = calcAvg(totNetPay);
}

/*I[]			P[X]			O[]*/
//	Input values: Floats: value.
//
//	Output values: Float: return value.
//                 
//	Input/ Output values: none.
//                           
//	Purpose:
//	
//	This function utilizes the accumulate value and the number of employees to calculate the average.
//	This function is reliant upon accurate data being received from getAvgs.
//
float calcAvg(float value) {
	value /= EMPS;

	return value;
}

/*I[]			P[X]			O[]*/
//	Input values: Floats: (payRate[], hrsWkd[]).
//
//	Output values: Float: grossPay[].
//                 
//	Input/ Output values: none.
//                           
//	Purpose:
//	
//	This function calculates the gross pay of the employee by multiplying the pay rate by hours worked.
//	This function also determines whether the employee has earned overtime and calculates it into gross pay if necessary.
//
void calcGrossPay(float payRate[], float hrsWkd[], float grossPay[]) {
	for (int i = 0; i < EMPS; i++) {
		if (hrsWkd[i] <= REGULARHOURS) {
			grossPay[i] = hrsWkd[i] * payRate[i];
		}
		else {
			grossPay[i] = REGULARHOURS * payRate[i];
			grossPay[i] += (hrsWkd[i] - REGULARHOURS) * payRate[i] * OVERTIMERATE;
		}
	}
}

/*I[]			P[X]			O[]*/
//	Input values: Float: grossPay[].
//
//	Output values: Float: taxAmt[].
//                 
//	Input/ Output values: none.
//                           
//	Purpose:
//	
//	This function calculates the tax amount which is dependent upon the constant TAXRATE.
//	This function stores that value in taxAmt.
//
void calcTaxAmt(float grossPay[], float taxAmt[]) {
	for (int i = 0; i < EMPS; i++) {
		taxAmt[i] = grossPay[i] * TAXRATE;
	}
}

/*I[]			P[X]			O[]*/
//	Input values: Floats: (grossPay[], taxAmt[]).
//
//	Output values: Float: netPay[].
//                 
//	Input/ Output values: none.
//                           
//	Purpose:
//	
//	This function calculates the net pay amount.
//	This function stores that value in netPay[].
//
void calcNetPay(float grossPay[], float taxAmt[], float netPay[]) {
	for (int i = 0; i < EMPS; i++) {
		netPay[i] = grossPay[i] - taxAmt[i];
	}
}

/*I[]			P[X]			O[]*/
//	Input values: none.
//
//	Output values: none.
//                 
//	Input/ Output values: Strings: (firstName, lastName).
//						  Floats: (payRate, hrsWkd, grossPay, taxAmt, netPay).
//
//	Purpose:
//	
//	This function sorts all arrays simultaneously through bubblesort.
//	This function is reliant upon bubbleString and bubbleFloat to allow for accurate data synchronization.
//
void sortInfo(string firstName[], string lastName[], float payRate[], float hrsWkd[], float grossPay[], float taxAmt[], float netPay[]) {

	for (int i = 1; i < EMPS; i++)
	{
		for (int j = 0; j < EMPS - 1; j++)
		{
			if (lastName[j] > lastName[j + 1])
			{
				bubbleString(lastName, i, j);
				bubbleString(firstName, i, j);

				bubbleFloat(payRate, i, j);
				bubbleFloat(hrsWkd, i, j);
				bubbleFloat(grossPay, i, j);
				bubbleFloat(taxAmt, i, j);
				bubbleFloat(netPay, i, j);
			}
		}
	}
}

/*I[]			P[X]			O[]*/
//	Input values: Ints: (I, J).
//
//	Output values: none.
//                 
//	Input/ Output values: String: valueString.						  
//
//	Purpose:
//	
//	This function compares and sorts strings.
//	This function is reliant upon sortInfo for accurate array and integer information.
//
void bubbleString(string valueString[], int i, int j) {
	string temp;
	temp = valueString[j];
	valueString[j] = valueString[j + 1];
	valueString[j + 1] = temp;
}

/*I[]			P[X]			O[]*/
//	Input values: Ints: (I, J).
//
//	Output values: none.
//                 
//	Input/ Output values: FLoat: valueFloat.						  
//
//	Purpose:
//	
//	This function compares and sorts floating point values.
//	This function is reliant upon sortInfo for accurate array and integer information.
//
void bubbleFloat(float valueFloat[], int i, int j) {
	float temp;
	temp = valueFloat[j];
	valueFloat[j] = valueFloat[j + 1];
	valueFloat[j + 1] = temp;
}

/*I[]			P[X]			O[]*/
//	Input values: Strings: (firstName[], lastName[]).
//
//	Output values: none.
//                 
//	Input/ Output values: String: fullName.						  
//
//	Purpose:
//	
//	This function concanetnates names.
//	This function is requires accurate first name and last name values.
//
void concantenateName(string firstName[], string lastName[], string fullName[]) {
	for (int i = 0; i < EMPS; i++) {
		fullName[i] = lastName[i] + ", " + firstName[i];
	}
}

/*I[]			P[]				O[X]*/
//	Input values: String: fullName[].
//				  Floats: (payRate[], hrsWkd[],  netPay[], 
//						  totPayRate, totHrsWkd, totGrossPay, totTaxAmt, totNetPay, 
//                        avgPayRate, avgHrsWkd, avgGrossPay, avgTaxAmt, avgNetPay)
//
//	Output values: none.
//                 
//	Input/ Output values: none.						  
//
//	Purpose:
//	
//	This function formats and outputs the financial report.
//	
//
void displayInfo(string fullName[], float payRate[], float hrsWkd[],  float netPay[], float totPayRate, float totHrsWkd, float totGrossPay, float totTaxAmt, float totNetPay, float avgPayRate, float avgHrsWkd, float avgGrossPay, float avgTaxAmt, float avgNetPay) {
	cout << endl;
	cout << left << setw(25) << "Employee" << setw(12) << "Pay" << setw(12) << "Hours" << setw(12) << "Gross" << setw(12) << "Tax" << setw(12) << "Net" << endl;
	cout << left << setw(25) << "Name" << setw(12) << "Rate" << setw(12) << "Worked" << setw(12) << "Pay" << setw(12) << "Amount" << setw(12) << "Pay" << endl;
	cout << left << setw(25) << "========" << setw(12) << "====" << setw(12) << "======" << setw(12) << "===== " << setw(11) << "======" << setw(11) << "======" << endl;
	cout << endl;
	
	for (int i = 0; i < EMPS; i++) {
		cout << left << setw(25) << fullName[i] 
			 << setprecision(2) << fixed << right
			 << setw(5) << payRate[i]
			 << setw(13) << hrsWkd[i]
			 << setw(12) << " "
			 << setw(12) << " "
			 << setw(11) << netPay[i] << endl;
	}
	cout << endl;

	cout << left << setw(25) << "Totals" << fixed << right << setw(5) << totPayRate << setw(13) << totHrsWkd << setw(12) << totGrossPay << setw(12) << totTaxAmt << setw(11) << totNetPay << endl;
	cout << left << setw(25) << "Averages" << fixed << right << setw(5) << avgPayRate << setw(13) << avgHrsWkd << setw(12) << avgGrossPay << setw(12) << avgTaxAmt << setw(11) << avgNetPay << endl;

	system("pause>nul");
}
