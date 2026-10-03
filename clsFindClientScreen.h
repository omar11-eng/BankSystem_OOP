#pragma once
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
class clsFindClientScreen :
    protected clsScreen
{

public:

    static void FindClient() {

        if (!CheckAccessRight(clsUser::pFindClient)) {
            return;
        }

        _DrawScreenHeader("\tFind Client Screen");

        cout << "Enter AccountNumber:";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber)) {
            cout << "\nAccountNumber is not correct enter another one :";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        Client.Print();


    }


};

