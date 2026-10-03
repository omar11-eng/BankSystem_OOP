#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
class clsDepositScreen :
    protected clsScreen
{

public:



    static void ShowDepositScreen() {

        _DrawScreenHeader("\t   Deposit Screen");


        cout << "\nEnter Account Number:";
        string AccountNumber = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nThis Client is not exist enter another account number:";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        Client.Print();

        cout << "\nPlease enter amount for deposit:";
        double Amount = clsInputValidate::ReadDblNumber();

        char ask = 'y';

        cout << "\nAre you sure to do this transaction ? (y/n) ?";
        cin >> ask;

        if (tolower(ask) == 'y') {
            Client.Deposit(Amount);
            cout << "\nMoney deposited successfully";
            cout << "\n\nYour Balance:" << Client.Balance<<endl;
        }
        else {
            cout << "\nThank you for using";
        }


    }


};

