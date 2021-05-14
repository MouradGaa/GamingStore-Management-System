#include "Customer.h" 

 extern stock stk; 
 


void Customer::purchase()
{
    system("cls");
    string barcode, temp;
    cout << "Please input the barcode of the product that you want to purchase : " << endl;
    cin >> barcode; // Input the barcode 
    for (size_t i = 0; i < stk.Merch_vect.size(); i++)
        if (stk.Merch_vect[i].Get_barcode() == barcode) { // If find that barcode 
            cout << "There are " << stk.Merch_vect[i].Get_quantity() << " pieces of this product, how many do you want to buy?  " << endl;
            while (true) {
                try {
                    cin >> temp; // Input how many the customer wants to buy
                    if (!IsAllDigit(temp)) throw 20;
                        break;
                }
                catch (int err) {
                    cout << "Pleass input a digital number ! " << endl;
                }
            }
            if (stoi(temp) > stk.Merch_vect[i].Get_quantity()) { // quantity < how many the cutomer wants to buy 
                cout << "the quantity is less than what you are willing to purchase " << endl;
                Sleep(2000);
            }
            else 
            {
                cout << "Please enter your credit card number " << endl;
                string cardnum; 
                cin >> cardnum;  // input credit card number 
                // check credit card
                for (size_t j = 0; j < stk.Card_vect.size(); j++)
                    if (stk.Card_vect[j].get_cardNum() == cardnum)
                    {
                        cout << "Your balance is : " << stk.Card_vect[j].get_balance()<< " Euros" << endl;
                        cout << "Total purchase is :" << stoi(temp) * calculate_discount(stk.Merch_vect[i].Get_price(), stk.Merch_vect[i].Get_discount()) << " Euros" << " (Discount:" << stk.Merch_vect[i].Get_discount() << "%)" << endl;
                        Sleep(2000);
                        // check balance > quantity*price(+discount)
                        if (stk.Card_vect[j].get_balance() >= (stoi(temp)*calculate_discount(stk.Merch_vect[i].Get_price(), stk.Merch_vect[i].Get_discount())))
                        {
                            
                            stk.Merch_vect[i].Set_quantity(stk.Merch_vect[i].Get_quantity() - stoi(temp)); // Decrease the number of this product in the stock
                            stk.Card_vect[j].set_balance(stk.Card_vect[j].get_balance() - (stoi(temp) * calculate_discount(stk.Merch_vect[i].Get_price(), stk.Merch_vect[i].Get_discount()))); // decrease balance in credit card
                            cout << "Buying " << stoi(temp) <<" that product succeeded !" << endl;
                            Sleep(3000); 
                            print_merch(); // update merch file 
                            print_card();  // update  credit card file 
                            return; 
                        }
                       cout << "unsufficient balance ! " << endl;
                       Sleep(1000); 
                       return; 
                    }
                cout << "invalid credit card ! " << endl;
                Sleep(1000);
                return; 
            }
            
        }
    cout << "Product not found !" << endl; // product not found 
    Sleep(1000);
}
void Customer::refund()
{
    system("cls");
    string barcode, temp;
    cout << "Please input the barcode of the product you want to refund" << endl;
    cin >> barcode; // Input the barcode number
    for (size_t i = 0; i < stk.Merch_vect.size(); i++)
        if (stk.Merch_vect[i].Get_barcode() == barcode) { // If find that barcode number
            cout << "How many pieces do you want to refund ?" << endl;
            while (1) {
                try {
                    cin >> temp; // Input how many the customer wants to refund
                    if (!IsAllDigit(temp)) throw 20;
                    break;
                }
                catch (int err) { cerr << "Pleass input a digital number !" << endl; }
            }
            cout << "Please enter your credit card number " << endl;
            string cardnum;
            cin >> cardnum; // input credit card 
            // check credit card
            for (size_t j = 0; j < stk.Card_vect.size(); j++)
                if (stk.Card_vect[j].get_cardNum() == cardnum)
                {
                    stk.Merch_vect[i].Set_quantity(stk.Merch_vect[i].Get_quantity() + stoi(temp)); // Increase the number of the product in stock
                    stk.Card_vect[j].set_balance(stk.Card_vect[j].get_balance() + (stoi(temp) * calculate_discount(stk.Merch_vect[i].Get_price(), stk.Merch_vect[i].Get_discount()))); // increase balance in credit card 
                    cout << "Refund " << stoi(temp) << " of " << stk.Merch_vect[i].Get_Name()<<" ("<< (stoi(temp) * calculate_discount(stk.Merch_vect[i].Get_price(), stk.Merch_vect[i].Get_discount())) << " Euros) succeeded ! " << endl;
                    Sleep(3000);
                    print_merch(); // update merch file 
                    print_card(); // update credit card file 
                    return;
                }
            cout << "invalid credit card ! " << endl;
            Sleep(1000);
            return;
        }
    cout << "Product not found !" << endl; // 
    Sleep(1000);
}

void Customer::print_card()
{
    ofstream fout;
    try
    {
        fout.open("creditcards.txt"); 
        if (!fout) throw 20;
    }
    // if can't open file throw an exception
    catch (int e)
    {
        cerr << "can't open creditcards.txt file ! " << endl;
    }
    for (size_t i = 0; i < stk.Card_vect.size(); i++) // write credit card inforamtion in file 
        fout << stk.Card_vect[i].get_cardNum()<< "|" << stk.Card_vect[i].get_balance()<< endl;
    fout.close(); // Close creditcards.txt

}
void Customer::add_card()
{
    system("cls");
    Credit_card card ; // define a credit card object 
    string num, balance;
    while (1) {
        cout << "Please input the number of the card that you want to add" << endl;
        try {
            cin >> num; // Input card number 
            if (!IsAllDigit(num)) throw 20;
            break;
        }
        catch (int err) {
            cerr << "Invalid card number !" << endl << endl;  // if invalid card throw exception 
            }
    }
    for (size_t i = 0; i < stk.Card_vect.size(); i++)
        if (stk.Card_vect[i].get_cardNum() == num)// If find that credit card
        {
            cout << "Credit card exists !";
            Sleep(1500); 
            return; 
        };
    cout << "Please input your balance" << endl;
    while (1) {
        try {
            cin >> balance;
            if (!IsAllDigit(balance)) throw 20;
            break;
        }
        catch (int err)
        {
            cerr << "invalid number ! " << endl << endl;
        }
    }
    card.set_cardNum(num);
    card.set_balance(stod(balance));
    stk.Card_vect.push_back(card); // add new card to card vector 
    cout << "Adding credit card successfully !" << endl;
    Sleep(3000); 
    print_card();  // update credit card file 
   
}
double Customer::calculate_discount(double price, double discount) 
{
    return price - ((price * discount) / 100);  // calculate discount 
}

void Customer::menu() {
    char command;
    int stop = 0;
    while (1) {
        system("cls");
        cout << "Welcome dear customer " << endl;
        cout << "CHOOSE AN OPTION " << endl;
        while (1) { // The operation list
            cout << "1 --> Purchase a product" << endl;
            cout << "2 --> Refund" << endl;
            cout << "3 --> List all products" << endl;
            cout << "4 --> List products by category" << endl;
            cout << "5 --> List products by name" << endl;
            cout << "6 --> List products by Manufacturer/Developer" << endl;
            cout << "7 --> Show product detailed information" << endl;
            cout << "8 --> Add credit card" << endl; 
            cout << "0 --> Exit;" << endl;
            cin >> command;
            if ('0'< command and command > '8') {
                cout << endl << "invalid index !"<< endl;
            }
            else break;
        }
        switch (command) {
        case '1' :
            purchase(); // purchase product 
            break;
        case '2' :
            refund(); // refund product 
            break;
        case '3' :
            Display_Merch(); // List all products
            break;
        case '4' :
            Display_MerchC(); // List products by category
            break;
        case '5' :
            Display_Merch_name(); // List products by name 
            break;
        case '6' :
           Display_Merch_Manuf(); // List products by Manufacturer/Developer
            break;
        case '7' :
            Display_info(); // List detailed information
            break;
        case '8' :
            add_card(); // add credit card 
            break; 
        case '0' :
            stop = 1;
            cout << "Have a nice day ! " << endl;
            Sleep(1000);
            break;
        }
        if (stop) break;
    }

};