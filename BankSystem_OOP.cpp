#include <iostream>
#include"clsString.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsUtil.h"
#include<iomanip>
#include"clsMainScreen.h"
#include"clsLoginScreen.h"
using namespace std;


int main()
{
	while (true) 
	{
		if (!clsLoginScreen::ShowLoginScreen())
			break;
	}

    system("pause>0");
	return 0;

}

