#pragma once
#include "clsScreen.h"
#include"clsBankClient.h"
#include<iomanip>
#include"clsInputValidate.h"
class clsAddClientScreen :
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


    static void  AddClient() {

        if(!CheckAccessRight(clsUser::eAll)){
            return;
        }

        _DrawScreenHeader("\tAdd New Client Screen", "");


        cout << "\nEnter Account Number:";
        string AccountNumber = clsInputValidate::ReadString();


        while (clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nThis Client is already exist enter another account number:";
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient NewClient = clsBankClient::GetAddNewClient(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveStatus enSaveResult;

        enSaveResult = NewClient.Save();


        switch (enSaveResult) {

        case  clsBankClient::svSuccessed:
            cout << "\nClient Added Successfully :-)\n";
            NewClient.Print();
            break;

        case clsBankClient::svFailed:
            cout << "\nError account was not saved because it's Empty";
            break;

        case clsBankClient::svAlreadyExist:

            cout << "\nError account was not saved because it's Exist";
            break;
        }



    }


};

