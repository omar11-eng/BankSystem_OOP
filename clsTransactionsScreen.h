#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include "clsTotalBalance.h"
#include"clsMainScreen.h"
#include"clsTransferScreen.h"
#include"clsTransferLogScreen.h"
class clsTransactionsScreen :
    protected clsScreen
{

private:

    enum enTransactions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTrasferLog = 5, eMainMenu = 6 };

    static short _ReadChoice() {
        short choice;
        cout << setw(37) << left << "" << "Choose what you want to do [1-6] : ";
        choice = clsInputValidate::ReadIntNumberBetween(1, 6);
        return choice;
    }

    static void _ShowDepositScreen() {
        clsDepositScreen::ShowDepositScreen();
    }
    static void _ShowWithdrawScreen() {
        clsWithdrawScreen::ShowWithdrawScreen();
    }
    static void _ShowTotalBalancesScreen() {
        clsTotalBalance::ShowTotalBalancesScreen();
    }
    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen() {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    
    static  void _GoBackToTranscationMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";

        system("pause>0");
        ShowTransactionsMenu();
    }

    static void _PerfromTransactionOption(enTransactions Transaction)
    {
        switch (Transaction) {


        case eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTranscationMenu();
            break;

        case eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTranscationMenu();
            break;

        case eTotalBalances:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTranscationMenu();
            break;

        case eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTranscationMenu();
            break;

        case eTrasferLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTranscationMenu();
            break;

        case eMainMenu:
            break;
        }
    }

    

public:


    static void ShowTransactionsMenu()
    {

        if (!CheckAccessRight(clsUser::pTranactions)) {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t\tTransactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tTransactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromTransactionOption((enTransactions)_ReadChoice());
    }



};

