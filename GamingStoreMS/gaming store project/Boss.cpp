#include "Boss.h"

extern stock stk; 


void boss::Add_employee() { // Add new employee
    system("cls");
    Person newperson; // Define new person object
    string name, pwd;
    cout << "Please input the username you want to register :" << endl;
    cin >> name; // Input username
    for (size_t i = 0; i < stk.user_vect.size(); i++)
        if (stk.user_vect[i].Get_name() == name) { // If find that employee name
            if (stk.user_vect[i].Get_type() != 0) { // Check type
                cout << "This employee already exists ! " << endl;
                Sleep(1000);
                return;
            }
            else {
                cout << "Please input your password" << endl; 
                cin >> pwd; // Input password
                stk.user_vect[i].Set_name(name);
                stk.user_vect[i].Set_Password(pwd);
                stk.user_vect[i].Set_type(2); // change type from 0 (invalid) to 2 (employee)
                cout << "Adding new employee successfully ! " << endl; 
                Sleep(2000);
                employee::print_user(); // output employee to users files
                return;
            }
        }
    cout << "Please input your password" << endl; 
    cin >> pwd;
    newperson.Set_name(name);
    newperson.Set_Password(pwd);
    newperson.Set_type(2);
    stk.user_vect.push_back(newperson); // Add user to stk.user_vect
    cout << "Adding new employee succeded ! " << endl;
    Sleep(1000);
    employee::print_user(); // Output employee to users file 
}

void boss::Del_employee()
{
    system("cls");
    int choice;
    string name;
    cout << "Please input the name of the employee you want to delete" << endl;
    cin >> name; // Input the user name
    for (size_t i = 0; i < stk.user_vect.size(); i++)
        if (stk.user_vect[i].Get_name() == name) { // If find that user name
            if (stk.user_vect[i].Get_type() != 0) { 
                stk.user_vect[i].Set_type(0);
                cout << "Deleting employee succeeded !user " << endl;
                Sleep(3000);
                employee::print_user();
                return;
            }
        }
    cout << "This employee does not exist ! " << endl; // employee does not exist in the users file
    Sleep(1000);

};
void boss::menu(string name) {
    int choice;
    int stop = 0;
    while (1) {
        system("cls");
        cout << "Welcome boss " << name <<" !"<<endl;
        cout << "CHOOSE AN OPTION : " << endl;
        while (1) { // operations list
            cout << "1 --> Add new employee" << endl;
            cout << "2 --> Delete employee" << endl;
            cout << "3 --> Add new product" << endl;
            cout << "4 --> Delete product" << endl;
            cout << "5 --> Change product information" << endl;
            cout << "6 --> List all products" << endl;
            cout << "7 --> List products by category" << endl;
            cout << "8 --> List products by name" << endl;
            cout << "9 --> List products by Manufacturer/Developer" << endl;
            cout << "10 --> Show product detailed information" << endl;
            cout << "11 --> Add credit card" << endl; 
            cout << "0 ----- Exit;" << endl;
            try {
                cin >> choice;
                if (choice < 0 || choice > 11) throw 1;
            }
             catch(int err)// If invalid index
             { 
                cerr << endl << "Invalid index !" << endl;
                Sleep(1500);
            }
            break;
        }
        switch (choice) {
        case 1:
            Add_employee(); // Add employee
            break;
        case 2:
            Del_employee(); // Delete employee
            break;
        case 3:
            add_product(); // Add new products
            break;
        case 4:
            remove_product(); // Delete product
            break;
        case 5 : 
            change_info(); // Change product information
            break;
        case 6:
            employee::Display_Merch(); // display all products
            break;
        case 7:
            employee::Display_MerchC(); // display products by category
            break;
        case 8:
            employee::Display_Merch_name(); // display products by name
            break;
        case 9:
            employee::Display_Merch_Manuf(); // display products by manufacturer
            break;
        case 10:
            employee::Display_info(); // display detailed information 
            break;
        case 11:
            add_card(); 
        case 0:
            stop = 1;
            break;
        }
        if (stop) break;
    }

}