#pragma once
#include<iomanip>
#include<iostream>
#include"clsUser.h"
#include"Global.h"
#include"clsDate.h"
using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {


        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        cout << "\n\t\t\t\t\tUser:" << CurrentUser.UserName();
        cout << "\n\t\t\t\t\tDate:" << clsDate::DateToString(clsDate::GetSystemDate())<<"\n\n";


    }

public:

    static bool CheckAccessRight(clsUser::enPermissions Permissions) {
        if (!CurrentUser.CheckPermissions(Permissions)) {
            cout << "\t\t\t\t\t____________________________________________\n";
            cout << "\n\t\t\t\t\t\tAccess Denied! Contact your admin\n";
            cout << "\t\t\t\t\t____________________________________________\n";
            return false;

        }
        else
            return true;
    }


};

