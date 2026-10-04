#pragma once
#include "clsScreen.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"
class clsCurrencyExchangeScreen :
    protected clsScreen
{
private:

    static void _PrintCurrency(clsCurrency Currency,short Num)
    {
        cout << "\nCurrency"<<Num<<" Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }


    static float _CurrencyCalculator(float Amount,clsCurrency Currency1, clsCurrency Currency2) {
        if (Currency2.CurrencyCode() == "USD") {
            return Amount / Currency1.Rate();
        }
        if (Currency1.CurrencyCode() == "USD") {
            return Amount * Currency2.Rate();
        }
        if (Currency1.CurrencyCode() == Currency2.CurrencyCode()) {
            return Amount;
        }
        else {
            return (Amount / Currency1.Rate()) * Currency2.Rate();
        }
    }


    static void _ShowResults(float Amount, clsCurrency Currency1, clsCurrency Currency2) {

        float Exchange = _CurrencyCalculator(Amount, Currency1, Currency2);

        if (Currency2.CurrencyCode() == "USD") {
            _PrintCurrency(Currency1,1);
            cout << "\n";
            cout << Amount << " " << Currency1.CurrencyCode() << " = " << Exchange << " " << Currency2.CurrencyCode();
            return;


        }
        if (Currency1.CurrencyCode() == "USD") {
            _PrintCurrency(Currency2,2);
            cout << "\n";
            cout << Amount << " " << Currency1.CurrencyCode() << " = " << Exchange << " " << Currency2.CurrencyCode();
            return;


        }
        if (Currency1.CurrencyCode() == Currency2.CurrencyCode()) {

            _PrintCurrency(Currency1,1);
            cout << "\n";
            cout << Amount << " " << Currency1.CurrencyCode() << " = " << Exchange << " " << Currency2.CurrencyCode();
            return;
        }
        else {
            _PrintCurrency(Currency1,1);
            _PrintCurrency(Currency2,2);
            cout << "\n";
            cout << Amount << " " << Currency1.CurrencyCode() << " = " << Exchange << " " << Currency2.CurrencyCode();
            return;

        }

    }


public:

    static void ShowCurrencyExchangeScreen() {


        char ask = 'y';

        while (tolower(ask) == 'y') {

            system("cls");

            _DrawScreenHeader("\t  Currency Exchange Screen");


            string Code;

            cout << "\nEnter Currency1 Code: ";
            Code = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExist(Code)) {
                cout << "\nInvalid Code ,Enter Correct Code : ";
                Code = clsInputValidate::ReadString();
            }

            clsCurrency Currency1 = clsCurrency::FindByCode(Code);


            cout << "\nEnter Currency2 Code: ";
            Code = clsInputValidate::ReadString();

            while (!clsCurrency::IsCurrencyExist(Code)) {
                cout << "\nInvalid Code ,Enter Correct Code : ";
                Code = clsInputValidate::ReadString();
            }

            clsCurrency Currency2 = clsCurrency::FindByCode(Code);

            float Amount;
            cout << "\nEnter Amount to Exchange:";
            Amount = clsInputValidate::ReadFloatNumber();


            _ShowResults(Amount, Currency1, Currency2);

            cout << "\n\nDo you want to do another Exchange (y/n) ? ";
            cin >> ask;

        }

        
    }

};

