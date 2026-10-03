#pragma once
#include "clsScreen.h"
#include"clsBankClient.h"
#include<iomanip>
#include"clsInputValidate.h"
class clsAddUserScreen :
    protected clsScreen
{
    private:


        static short _ReadPermissionsToSet()
        {

            int Permissions = 0;
            char Answer = 'n';


            cout << "\nDo you want to give full access? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                return -1;
            }

            cout << "\nDo you want to give access to : \n ";

            cout << "\nShow Client List? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {


                Permissions += clsUser::enPermissions::pListClients;
            }

            cout << "\nAdd New Client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pAddNewClient;
            }

            cout << "\nDelete Client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pDeleteClient;
            }

            cout << "\nUpdate Client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pUpdateClients;
            }

            cout << "\nFind Client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pFindClient;
            }

            cout << "\nTransactions? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pTranactions;
            }

            cout << "\nManage Users? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pManageUsers;
            }

            return Permissions;

        }

        static void _ReadUserInfo(clsUser& User)
        {
            cout << "\nEnter FirstName: ";
            User.FirstName = clsInputValidate::ReadString();

            cout << "\nEnter LastName: ";
            User.LastName = clsInputValidate::ReadString();

            cout << "\nEnter Email: ";
            User.Email = clsInputValidate::ReadString();

            cout << "\nEnter Phone: ";
            User.Phone = clsInputValidate::ReadString();

            cout << "\nEnter Password: ";
            User.Password = clsInputValidate::ReadString();

            cout << "\nEnter Permissions: ";
            User.Permissions = _ReadPermissionsToSet();
        }



    public:


        static void  AddUser() {

            _DrawScreenHeader("\tAdd New User Screen", "");


            cout << "\nEnter UserName:";
            string UserName = clsInputValidate::ReadString();


            while (clsUser::IsUserExist(UserName)) {

                cout << "\nThis User is already exist enter another UserName:";
                UserName = clsInputValidate::ReadString();

            }

            clsUser NewUser = clsUser::GetAddNewUser(UserName);

            _ReadUserInfo(NewUser);

            clsUser::enSaveStatus enSaveResult;

            enSaveResult = NewUser.Save();


            switch (enSaveResult) {

            case  clsUser::svSuccessed:
                cout << "\nUser Added Successfully :-)\n";
                NewUser.Print();
                break;

            case clsUser::svFailed:
                cout << "\nError User was not saved because it's Empty";
                break;

            case clsUser::svAlreadyExist:

                cout << "\nError User was not saved because it's Exist";
                break;
            }



        }

};

