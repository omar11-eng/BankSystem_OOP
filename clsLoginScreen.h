#pragma once
#include "clsScreen.h"
#include"clsUser.h"
#include"Global.h"
#include"clsInputValidate.h"
#include"clsMainScreen.h"
class clsLoginScreen :
    protected clsScreen
{

private:

  static void _Login() {

      bool LoginFailed = false;

      do {

          if (LoginFailed)
          {
              cout << "\nInvalid UserName/Password !\n";
          }

          cout << "\nEnter UserName:";
          string UserName = clsInputValidate::ReadString();
          cout << "\nEnter Password:";
          string Password = clsInputValidate::ReadString();

          CurrentUser = clsUser::Find(UserName, Password);

          LoginFailed = CurrentUser.IsEmpty();

      } while (LoginFailed);

      clsMainScreen::ShowMainMenue();

    }

public:

  static void ShowLoginScreen() {
      system("cls");
      _DrawScreenHeader("\t  Login Screen");
      _Login();
    }


};

