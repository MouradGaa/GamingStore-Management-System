#pragma once
#include <iostream>
#include "Person.h"
#include "stock.h"
#include "Credit_card.h"
using namespace std; 

class Customer : public Person
{

public :

	// methods
	void purchase() ; // buy a product 
	void refund() ; // refund
	void print_card();  // print credit card to file 
	void add_card(); // add credit card 
	double calculate_discount(double price, double discount); // mini function that calculates discount 
	void menu(); 
};