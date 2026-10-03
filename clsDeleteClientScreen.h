#pragma once
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
class clsDeleteClientScreen :
    protected clsScreen
{


public:


    static void DeleteClient() {

        if (!CheckAccessRight(clsUser::pDeleteClient)) {
            return;
        }

        _DrawScreenHeader("\tDelete Client Screen");

        cout << "\nEnter Account Number:";
        string AccountNumber = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nThis Client is not exist enter another account number:";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        Client.Print();

        cout << "\n\nAre you sure  for delete this client ? (y/n) ?";

        char ask = 'n';
        cin >> ask;

        if (tolower(ask) == 'y') {

            if (Client.Delete()) {

                cout << "\nClient Deleted Successfully\n";
                Client.Print();

            }
            else {
                cout << "\nError Client was not deleted\n";
            }


        }
        else {
            cout << "\nOperation Canceled\n\n";
        }


    }



};

