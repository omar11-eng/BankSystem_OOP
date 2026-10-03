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

  static bool _Login() {

      short counter = 3;
      bool LoginFailed = false;

      do {

          if (LoginFailed)
          {
              counter--;
              cout << "\nInvalid UserName/Password !\n";
              cout << "\nYou have "<<counter<<" trails to login\n";
          }

          if (counter < 1) {
              cout << "\nYou are locked after 3 trails";
              return false;
          }

          cout << "\nEnter UserName:";
          string UserName = clsInputValidate::ReadString();
          cout << "\nEnter Password:";
          string Password = clsInputValidate::ReadString();

          CurrentUser = clsUser::Find(UserName, Password);

          LoginFailed = CurrentUser.IsEmpty();

      } while (LoginFailed);

      CurrentUser.AddRegisteretionToFile(CurrentUser);
      clsMainScreen::ShowMainMenue();
      return true;

    }

public:

  static bool ShowLoginScreen() {
      system("cls");
      _DrawScreenHeader("\t  Login Screen");
     return _Login();
    }


};

