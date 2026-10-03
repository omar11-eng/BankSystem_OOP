#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsListUsersScreen.h"
#include"clsAddUserScreen.h"
#include"clsAddUserScreen.h"
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include"clsFindUserScreen.h"
#include"clsMainScreen.h"
class clsManageUsersScreen :
    protected clsScreen
{

private:

    enum enManageUsers { eAllUsers = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu = 6 };

    static short _ReadChoice() {
        short choice;
        cout << setw(37) << left << "" << "Choose what you want to do [1-6] : ";
        choice = clsInputValidate::ReadIntNumberBetween(1, 6);
        return choice;
    }

    static void _ShowAllUsersScreen() {
        clsListUsersScreen::ShowUsersList();
    }
    static void _ShowAddUserScreen() {
        clsAddUserScreen::AddUser();
    }
    static void _ShowDeleteUserScreen() {
        clsDeleteUserScreen::DeleteClient();
    }
    static void _ShowUpdateUserScreen() {
        clsUpdateUserScreen::UpdateUser();
    }
    static void _ShowFindUserScreen() {
        clsFindUserScreen::FindUser();
    }
    static  void _GoBackToMangeUsersMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menue...\n";

        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _PerfromManageUsersMenueOption(enManageUsers Transaction)
    {
        switch (Transaction) {


        case eAllUsers:
            system("cls");
            _ShowAllUsersScreen();
            _GoBackToMangeUsersMenu();
            break;

        case eAddUser:
            system("cls");
            _ShowAddUserScreen();
            _GoBackToMangeUsersMenu();
            break;

        case eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToMangeUsersMenu();
            break;

        case eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToMangeUsersMenu();
            break;

        case eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToMangeUsersMenu();
            break;

        case eMainMenu:
         
            break;
        }
    }



public:


    static void ShowManageUsersMenu()
    {

        if (!CheckAccessRight(clsUser::pManageUsers)) {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t\Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tManage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromManageUsersMenueOption((enManageUsers)_ReadChoice());
    }



};

