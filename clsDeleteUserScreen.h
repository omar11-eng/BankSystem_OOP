#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsUser.h"
class clsDeleteUserScreen :
    protected clsScreen
{


public:


    static void DeleteClient() {

        _DrawScreenHeader("\tDelete User Screen");

        cout << "\nEnter UserName:";
        string UserName = clsInputValidate::ReadString();


        while (!clsUser::IsUserExist(UserName)) {

            cout << "\nThis User is not exist enter another UserName:";
            UserName = clsInputValidate::ReadString();

        }

        clsUser User = clsUser::Find(UserName);

        User.Print();

        cout << "\n\nAre you sure  for delete this User ? (y/n) ?";

        char ask = 'n';
        cin >> ask;

        if (tolower(ask) == 'y') {

            if (User.Delete()) {

                cout << "\nUser Deleted Successfully\n";
                User.Print();

            }
            else {
                cout << "\nError User was not deleted\n";
            }


        }
        else {
            cout << "\nOperation Canceled\n\n";
        }


    }



};

