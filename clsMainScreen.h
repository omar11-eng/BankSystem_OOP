#pragma once
#include<iomanip>
#include<iostream>
#include "clsScreen.h"
#include"clsUtil.h"
#include"clsInputValidate.h"
#include"clsClientsListScreen.h"
#include"clsAddClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsTransactionsScreen.h"
#include"clsManageUsersScreen.h"
#include"Global.h"
class clsMainScreen : protected clsScreen
{

private:

	enum enMainMenueOptions {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7, eExit = 8
	};


	static short _ReadMainMenuChoose() {

        cout << setw(37) << left << "" << "Choose what you want to do [1-8] : ";
		short Choice;
		Choice = clsInputValidate::ReadIntNumberBetween(1, 8);
		return Choice;
	}

    static void _Logout() {
        CurrentUser = clsUser::Find("", "");
    }

	static  void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowClientsListScreen() {
        clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientScreen() {
        clsAddClientScreen::AddClient();
	}

    static void _ShowDeleteClientScreen() {
        clsDeleteClientScreen::DeleteClient();
    }
	
    static void _ShowUpdateClientScreen() {
        clsUpdateClientScreen::UpdateClient();
	}
		
    static void _ShowFindClientScreen() {
        clsFindClientScreen::FindClient();
	}
	
    static void _ShowTransactionsScreen() {
        clsTransactionsScreen::ShowTransactionsMenu();
	}
	
    static void _ShowManageUsersScreen() {
        clsManageUsersScreen::ShowManageUsersMenu();
	}
	
    static void _ShowEndScreen() {
        _Logout();
	}

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowClientsListScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _ShowEndScreen();
            break;
        }

    }


    public:

        static void ShowMainMenue()
        {

            system("cls");
            _DrawScreenHeader("\t\tMain Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
            cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
            cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
            cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
            cout << setw(37) << left << "" << "\t[5] Find Client.\n";
            cout << setw(37) << left << "" << "\t[6] Transactions.\n";
            cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
            cout << setw(37) << left << "" << "\t[8] Logout.\n";
            cout << setw(37) << left << "" << "===========================================\n";

            _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenuChoose());
        }

};







