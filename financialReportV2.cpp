/*
  Name:    Marco Martinez
  Project: financialReport2.cpp
  Purpose: This is the financial report rethought with structures in mind.
  Date:    9/7/2018

  Software Change Record
  Date            Who                   What

*/
/*---Libraries---*/
#include <iostream>  // Allows cin, cout
#include <iomanip>	 // Allows setw, setprecision, fixed
#include <string>	 // Allows strings
#include <cctype>    // Allows isalpha
#include <algorithm> // Allows all_of

/*---Constant Definition---*/
#define EMPNUM 5             // Controls amount of employees to enter
#define TAXRATE 0.15F        // Rate of tax as subject to law
#define OVERTIMERATE 1.5F    // 150% pay amount for overtime work
#define REGULARHOURS 40      // Number of hours in a normal work day

/*---Structure Definitions---*/
struct employeeRecord {
	std::string  fullName;
	float        payRate,
				 hrsWkd,
				 grossPay,
				 taxAmt,
				 netPay;
} employee[EMPNUM];

struct accumulators {
	float	totPayRate,
			totHrsWkd,
			totGrossPay,
			totTaxAmt,
			totNetPay;
} total;

/*---Function Declarations---*/
void printReportHeadings();
void initializeAccumulators();
void inputEmployeeData();
std::string validateString(std::string name); 
float validateFloat(float value);
void calculateGross();
void calculateTax();
void calculateNet();
void accumulate();
void sortData();
void printReport();

/*---Main---*/
int main() { 
	printReportHeadings();
	initializeAccumulators();
	inputEmployeeData();
	calculateGross();
	calculateTax();
	calculateNet();
	accumulate();
	sortData();
	printReport();

	std::cin.get();
}

/*---Function Definitions---*/
void printReportHeadings() {
	std::cout << "Welcome to my financial report program!" << std::endl;
	std::cout << std::endl;
}

void initializeAccumulators() {
	total.totPayRate = 0.00F;
	total.totHrsWkd = 0.00F;
	total.totGrossPay = 0.00F;
	total.totTaxAmt = 0.00F;
	total.totNetPay = 0.00F;
}

void inputEmployeeData() {
	std::string firstName;
	std::string lastName;

	for (int i = 0; i < EMPNUM; i++) {
		std::cout << "Please enter the employee's first name here: ";
		std::cin >> firstName;
		firstName = validateString(firstName);

		std::cout << "Please enter the employee's last name here: ";
		std::cin >> lastName;
		lastName = validateString(lastName);

		employee[i].fullName = lastName + ", " + firstName;

		std::cout << "Please enter the employee's hourly pay here: ";
		std::cin >> employee[i].payRate;
		employee[i].payRate = validateFloat(employee[i].payRate);
			
		std::cout << "Please enter the employee's number of worked hours: ";
		std::cin >> employee[i].hrsWkd;
		employee[i].hrsWkd = validateFloat(employee[i].hrsWkd);

		std::cout << std::endl;
	}
}

std::string validateString(std::string name) {
	int i = 0;

	while (!(std::all_of(name.begin(), name.end(), [](char c) { return (std::isalpha(c)); }))) {
		std::cout << "Please enter with alphabetical characters only: ";
		std::cin >> name;

		if ((std::all_of(name.begin(), name.end(), [](char c) { return (std::isalpha(c)); })))
			return name;
		else if (i >= 2)
			return name = "Default";

		i++;
	}

	return name;
}

float validateFloat(float value) {
	int i = 0;

	while (value < 0) {
		std::cout << "Please enter a value greater than or equal to zero: ";
		std::cin >> value;

		if (value >= 0)
			return value;
		else if (i >= 2)
			return value = 0.00F;

		i++;
	}

	return value;
}

void calculateGross() {
	for (int i = 0; i < EMPNUM; i++) {
		if (employee[i].hrsWkd <= REGULARHOURS) {
			employee[i].grossPay = employee[i].payRate * employee[i].hrsWkd;
		}
		else {
			employee[i].grossPay = REGULARHOURS * employee[i].payRate;
			employee[i].grossPay += (employee[i].hrsWkd - REGULARHOURS) * employee[i].payRate * OVERTIMERATE;
		}
	}
}

void calculateTax() {
	for (int i = 0; i < EMPNUM; i++) {
		employee[i].taxAmt = employee[i].grossPay * TAXRATE;
	}
}

void calculateNet() {
	for (int i = 0; i < EMPNUM; i++) {
		employee[i].netPay = employee[i].grossPay - employee[i].taxAmt;
	}
}

void accumulate() {
	for (int i = 0; i < EMPNUM; i++) {
		total.totPayRate += employee[i].payRate;
		total.totHrsWkd += employee[i].hrsWkd;
		total.totGrossPay += employee[i].grossPay;
		total.totTaxAmt += employee[i].taxAmt;
		total.totNetPay += employee[i].netPay;
	}
}

void sortData() {
	employeeRecord temp;

	for (int i = 1; i < EMPNUM; i++)
	{
		for (int j = 0; j < EMPNUM - 1; j++)
		{
			if (employee[j].fullName > employee[j + 1].fullName)
			{
				temp = employee[j];
				employee[j] = employee[j + 1];
				employee[j + 1] = temp;
			}
		}
	}
}

void printReport() {
	std::cout << std::endl;
	std::cout << std::left << std::setw(25) << "Employee" << std::setw(12) << "Pay" << std::setw(12) << "Hours" << std::setw(12) << "Gross" << std::setw(12) << "Tax" << std::setw(12) << "Net" << std::endl;
	std::cout << std::left << std::setw(25) << "Name" << std::setw(12) << "Rate" << std::setw(12) << "Worked" << std::setw(12) << "Pay" << std::setw(12) << "Amount" << std::setw(12) << "Pay" << std::endl;
	std::cout << std::left << std::setw(25) << "========" << std::setw(12) << "====" << std::setw(12) << "======" << std::setw(12) << "===== " << std::setw(11) << "======" << std::setw(11) << "======" << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < EMPNUM; i++) {
		std::cout << std::left << std::setw(25) << employee[i].fullName << std::setprecision(2) << std::fixed << std::right
																					  << std::setw(5)  << employee[i].payRate
																					  << std::setw(13) << employee[i].hrsWkd
																				      << std::setw(12) << employee[i].grossPay
																					  << std::setw(12) << employee[i].taxAmt
																					  << std::setw(11) << employee[i].netPay << std::endl;
	}
	std::cout << std::endl;

	std::cout << std::left << std::setw(24) << "Totals"   << std::fixed << std::right << std::setw(5)  << total.totPayRate 
																					  << std::setw(13) << total.totHrsWkd 
																				      << std::setw(12) << total.totGrossPay 
																					  << std::setw(12) << total.totTaxAmt 
																					  << std::setw(11) << total.totNetPay << std::endl;

	std::cout << std::left << std::setw(25) << "Averages" << std::fixed << std::right << std::setw(5)  << total.totPayRate / 5
																					  << std::setw(13) << total.totHrsWkd / 5
																					  << std::setw(12) << total.totGrossPay / 5
																					  << std::setw(12) << total.totTaxAmt / 5
																					  << std::setw(11) << total.totNetPay / 5 << std::endl;
}