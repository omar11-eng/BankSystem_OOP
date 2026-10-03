#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
class clsTransferScreen :
    protected clsScreen
{

private:


    static string ReadAccountNumber(string prompt) {
        string AccountNumber;



        cout << prompt;
        AccountNumber = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nClient is not exist enter another one:";
            AccountNumber = clsInputValidate::ReadString();


        }

        return AccountNumber;
    }
   

    static double ReadAmount(clsBankClient FromClient) {
        double Amount;
        cout << "\n\nEnter Trasnfer Amount:";
        Amount = clsInputValidate::ReadDblNumber();

        while (Amount>FromClient.Balance) {
            cout << "\n\nAmount Exceeds Avilable Balance, Enter Another Amount:";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

    static void _PrintClientCard(clsBankClient Client) {
        cout << "\n\nClient Card:";
        cout << "\n_________________________________\n";
        cout << "\nFull Name: " << Client.FullName();
        cout << "\nAccount Number: " << Client.AccountNumber();
        cout << "\nBalance: " << Client.Balance;
        cout << "\n_________________________________\n";
    }


public:

    static void ShowTransferScreen() {


        _DrawScreenHeader("\t   Transfer Screen");

        string AccountNumber;

        AccountNumber = ReadAccountNumber("\nEnter Account Number transfer From:");
        

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _PrintClientCard(Client1);



        AccountNumber = ReadAccountNumber("\nEnter Account Number transfer To:");

        clsBankClient Client2 = clsBankClient::Find(AccountNumber);

        _PrintClientCard(Client2);

        double Amount;

        Amount = ReadAmount(Client1);
        

        char ask;
        cout << "\nAre you sure to do this operation (y/n) ? ";
        cin >> ask;

        if (tolower(ask) == 'y') 
        {

            if (Client1.Transfer(Amount,Client2))
            {

                cout << "\n\nTransfer Done Successfully";

                _PrintClientCard(Client1);
                _PrintClientCard(Client2);

                Client1.AddTransferLog(Client2, Amount);
            }
            else 
            {
                cout << "\nTransfer Failed";
            }

        }
        else 
        {
            cout << "\nThank you for using";
        }


    }








};

