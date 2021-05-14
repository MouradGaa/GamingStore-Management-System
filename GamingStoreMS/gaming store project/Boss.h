#pragma once
#include "employee.h" 
#include "Customer.h"

class boss:public employee, public Customer {
public : 
	void Add_employee(); // function for adding new employee
	void Del_employee(); // function for deleting an employee
	void menu(string name) ; // menu 
};