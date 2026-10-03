#pragma once
#include"clsString.h"
#include<vector>
#include<fstream>
#include<string>
#include "clsPerson.h"
#include"clsDate.h"
class clsUser :
    public clsPerson
{

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    short _Permissions;
    bool _MarkForDelete = false;

    static clsUser _ConvertLineToUserObject(string Line) {

        vector<string>vUserInfo = clsString::Split(Line,"#//#");

        return  clsUser(UpdateMode, vUserInfo[0], vUserInfo[1], vUserInfo[2], vUserInfo[3], vUserInfo[4], vUserInfo[5],stoi( vUserInfo[6]));

        
    }
    static string _ConvertUserObjectToLine(clsUser User,string Seperator="#//#") {
        string Line = "";
        Line = User.FirstName + Seperator;
        Line += User.LastName + Seperator;
        Line += User.Email + Seperator;
        Line += User.Phone + Seperator;
        Line += User.UserName() + Seperator;
        Line += User.Password + Seperator;
        Line += to_string(User.Permissions);
        return Line;
    }
    static vector<clsUser> _LoadDataFromFile() {
        fstream MyFile;
        vector<clsUser>vUsers;

        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open()) {
            string Line;

            while (getline(MyFile, Line)) {
                vUsers.push_back(_ConvertLineToUserObject(Line));
            }

            MyFile.close();
        }

        return vUsers;
    }
    static void _SaveDataToFile(vector<clsUser>vUsers) {
        fstream MyFile;

        MyFile.open("Users.txt", ios::out);

        if (MyFile.is_open()) {
            string Line;

            for (clsUser& User : vUsers) {
                if (User._MarkForDelete == false) {
                    Line = _ConvertUserObjectToLine(User);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }
    }
    static void _AddLineToFile(string Line) {
        fstream MyFile;

        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open()) {
            MyFile << Line << endl;
        }
        MyFile.close();

    }
    void _Update() {
        vector<clsUser>vUsers = _LoadDataFromFile();

        for (clsUser& User : vUsers) {
            if (User.UserName() == UserName()) {
                User = *this;
                break;
            }
        }

        _SaveDataToFile(vUsers);

    }
    void _AddNewUser() {
        _AddLineToFile(_ConvertUserObjectToLine(*this));
    }
    static clsUser _GetEmptyUser() {
        return clsUser(EmptyMode, "", "", "", "", "", "", 0);
    }
    string _PrepareLoginLine(string Seperator="#//#") {
        string Line = clsDate::DateAndTime() + Seperator + UserName() + Seperator + Password + Seperator + to_string(Permissions);
        return Line;
    }


public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
    };

    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, short Permissions
    ) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty() {
        return _Mode == EmptyMode;
    }


    // Setters
  
    void SetPassword(string Password)
    {
        _Password = Password;
    }

    void SetPermissions(short Permissions)
    {
        _Permissions = Permissions;
    }

    // Getters
    string UserName()
    {
        return _UserName;
    }

    string GetPassword()
    {
        return _Password;
    }

    short GetPermissions()
    {
        return _Permissions;
    }

    __declspec(property(get = GetPassword, put = SetPassword)) string Password;
    __declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;




    void Print()
    {
        cout << "\nUser Info:\n";
        cout << "\n____________________________________________\n\n";
        cout << "First Name    : " << FirstName << endl;
        cout << "Last Name     : " << LastName << endl;
        cout << "Email         : " << Email << endl;
        cout << "Phone         : " << Phone << endl;
        cout << "UserName      : " << UserName() << endl;
        cout << "Password      : " << Password << endl;
        cout << "Permissions   : " << Permissions << endl;
        cout << "____________________________________________\n";

    }

    static clsUser Find(string UserName) {
        vector<clsUser> vUser = _LoadDataFromFile();

        for (clsUser& User : vUser) {
            if (User.UserName() == UserName) {
                return User;
                break;
            }
        }
        return _GetEmptyUser();
    }

    static clsUser Find(string UserName,string Password) {
        vector<clsUser> vUser = _LoadDataFromFile();

        for (clsUser& User : vUser) {
            if (User.UserName() == UserName && User.Password==Password) {
                return User;
                break;
            }
        }
        return _GetEmptyUser();
    }

    static bool IsUserExist(string AccountNumber) {

        clsUser User = clsUser::Find(AccountNumber);
        return (!User.IsEmpty());
    }


    bool Delete() {

        vector<clsUser>vUsers = _LoadDataFromFile();

        for (clsUser& U : vUsers) {
            if (U.UserName() == _UserName) {
                U._MarkForDelete = true;
                break;
            }
        }
        _SaveDataToFile(vUsers);
        *this = _GetEmptyUser();
        return true;
    }

    enum enSaveStatus { svSuccessed = 0, svFailed = 1, svAlreadyExist = 2 };

    enSaveStatus Save() {
        switch (_Mode) {
        case UpdateMode:

            _Update();

            return svSuccessed;

        case AddMode:
            if (clsUser::IsUserExist(UserName())) {
                return svAlreadyExist;
            }
            else {

                _AddNewUser();

                _Mode = UpdateMode;

                return svSuccessed;
            }


        case EmptyMode:

            return svFailed;

            break;

        }
    }


    static clsUser GetAddNewUser(string UserName) {
        return clsUser(AddMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetUsersList() {
        return _LoadDataFromFile();
    }

     bool CheckPermissions(enPermissions Permission) {
         if (this->Permissions == eAll)
             return true;
         if ((this->Permissions & Permission) == Permission)
             return true;
         else
             return false;
    }

     void AddRegisteretionToFile(clsUser User,string Seperator="#//#") {
         string Line = _PrepareLoginLine();
         fstream MyFile;

         MyFile.open("LoginRegisters.txt", ios::out | ios::app);


         if (MyFile.is_open()) {
             MyFile << Line << endl;
         }

         MyFile.close();
     }

};

