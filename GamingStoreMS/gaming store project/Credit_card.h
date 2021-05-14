#pragma once
#include <vector>
#include <string>

using namespace std; 

class Credit_card
{
	string cardNum;
	double balance;
public:
	//Stetter and Getters 
	string get_cardNum() { return cardNum; }
	double get_balance() { return balance; }
	void set_cardNum(string cardNum) { this->cardNum = cardNum; }
	void set_balance(double balance) { this->balance = balance; }
};