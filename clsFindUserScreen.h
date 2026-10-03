#pragma once
#include "clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"
class clsFindUserScreen :
    protected clsScreen
{


public:

    static void FindUser() {

        _DrawScreenHeader("\tFind User Screen");

        cout << "Enter UserName:";
        string UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName)) {
            cout << "\nUserName is not correct enter another one :";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        User.Print();


    }




};

