#pragma once
#include "clsScreen.h"
#include"clsInputValidate.h"
#include"clsString.h"
#include"clsCurrency.h"
class clsFindCurrencyScreen :
    protected clsScreen
{

private:
    static string _ReadCountryName() {
        string Name;
        cout<<"\nEnter Country Name:";
        Name = clsInputValidate::ReadString();
        return Name;
    }

    static string _ReadCountryCode() {
        string Code;
        cout << "\nEnter Country Code:";
        Code = clsInputValidate::ReadString();
        return Code;
    }


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

public:

    static void ShowFindCurrencyScreen() {

        _DrawScreenHeader("\t  Find Currency Screen");


        short Choose;
        cout << "\nFind by [1] Code or [2] Country : ";
        Choose = clsInputValidate::ReadIntNumberBetween(1, 2);

        

        if (Choose == 1) {
            string Code = _ReadCountryCode();
            clsCurrency Currency = clsCurrency::FindByCode(Code);
            _ShowResults(Currency);
        }
        else {
            string Name = _ReadCountryName();
            clsCurrency Currency = clsCurrency::FindByCountry(Name);
            _ShowResults(Currency);

        }



    }



};

