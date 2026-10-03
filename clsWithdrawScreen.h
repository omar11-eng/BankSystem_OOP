#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
class clsWithdrawScreen :
    protected clsScreen
{


public:



    static void ShowWithdrawScreen() {

        _DrawScreenHeader("\t   Withdraw Screen");


        cout << "\nEnter Account Number:";
        string AccountNumber = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nThis Client is not exist enter another account number:";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        Client.Print();

        cout << "\nPlease enter amount for withdarw:";
        double Amount = clsInputValidate::ReadDblNumber();


        if (Amount <= Client.Balance) {

            char ask = 'y';

            cout << "\nAre you sure to do this transaction ? (y/n) ?";
            cin >> ask;

            if (tolower(ask) == 'y') {
                Client.Withdraw(Amount);
                cout << "\nMoney withdrawed successfully";
                cout << "\n\nYour Balance:" << Client.Balance << endl;
            }
            else 
            {
                cout << "\nThank you for using";
            }

        }

        else
        {
            cout << "\nYour Balance is not enough";
        }

    }



};

