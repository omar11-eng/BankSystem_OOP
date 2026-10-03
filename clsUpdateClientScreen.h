#pragma once
#include "clsScreen.h"
class clsUpdateClientScreen :
    protected clsScreen
{

private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.Pincode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.Balance = clsInputValidate::ReadFloatNumber();
    }

public:

    static void UpdateClient() {

        if (!CheckAccessRight(clsUser::pUpdateClients)) {
            return;
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        cout << "\nEnter Account Number:";
        string AccountNumber = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nThis Client is not exist enter another account number:";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        Client.Print();

        cout << "\nUpdate Client:";
        cout << "\n____________________\n";

        _ReadClientInfo(Client);

        clsBankClient::enSaveStatus enSaveResult;

        enSaveResult = Client.Save();


        switch (enSaveResult) {
        case  clsBankClient::svSuccessed:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            Client.Print();
            break;
        }
        case clsBankClient::svFailed:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }

        }


    }


};

