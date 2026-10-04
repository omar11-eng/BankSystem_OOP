#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsCurrency.h"
class clsUpdateCurrencyScreen :
    protected clsScreen
{
private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

    static float _ReadNewRate() {
        float NewRate;

        cout << "\nUpdate Currency Rate:";
        cout << "\n____________________________\n";
        cout << "\nEnter New Rate: ";
        NewRate = clsInputValidate::ReadFloatNumber();
        return NewRate;
    }


public:

    static void ShowUpdateCurrencyScreen() {

        _DrawScreenHeader("\t   Update Rate Screen");

        string Code;

        cout << "\nEnter Country Code: ";
        Code = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(Code)) {
            cout << "\nInvalid Code ,Enter Correct Code : ";
            Code = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(Code);
        _ShowResults(Currency);

        char ask;
        cout << "\nAre you sure to update this currency (y/n) ? ";
        cin >> ask;

        if (tolower(ask) == 'y') 
        {

            float NewRete = _ReadNewRate();
            Currency.UpdateRate(NewRete);
            cout << "\nCurrency Rate Updated Successfully";
            _PrintCurrency(Currency);

        }
        else 
        {
            cout << "\nThank You For Using";

        }

    }


};

