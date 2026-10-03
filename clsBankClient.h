#pragma once
#include"clsString.h"
#include<vector>
#include<fstream>
#include<string>
#include "clsPerson.h"
#include"clsDate.h"
#include"Global.h"
class clsBankClient :
    public clsPerson
{

private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    enMode _Mode;

    string _AccountNumber;
    string _Pincode;
    double _Balance;
    bool _MarkForDelete = false;


    struct stTransferInfo;

    static stTransferInfo _ConvertLineToTransferInfoRecord(string Line, string Seperator = "#//#")
    {
        stTransferInfo TransferInfo;


        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        TransferInfo.DateTime = LoginRegisterDataLine[0];
        TransferInfo.FromAccountNumber = LoginRegisterDataLine[1];
        TransferInfo.ToAccountNumber = LoginRegisterDataLine[2];
        TransferInfo.Amount = stoi(LoginRegisterDataLine[3]);
        TransferInfo.Client1BalanceAfter = stoi(LoginRegisterDataLine[4]);
        TransferInfo.Client2BalanceAfter = stoi(LoginRegisterDataLine[5]);
        TransferInfo.UserName = LoginRegisterDataLine[6];



        return TransferInfo;

    }


    static clsBankClient _ConvertLineToClientObject(string Line) {

        vector<string>vClientInfo = clsString::Split(Line, "#//#");

        return clsBankClient(UpdateMode, vClientInfo[0], vClientInfo[1], vClientInfo[2], vClientInfo[3], vClientInfo[4],
            vClientInfo[5], stod(vClientInfo[6]));


    }

    static string _ConvertClientObjectToLine(clsBankClient Client,string Seperator="#//#") {
        string Line = "";
        Line = Client.FirstName + Seperator;
        Line += Client.LastName + Seperator;
        Line += Client.Email + Seperator;
        Line += Client.Phone + Seperator;
        Line += Client.AccountNumber() + Seperator;
        Line += Client.Pincode + Seperator;
        Line += to_string(Client.Balance);

        return Line;
    }

    static vector<clsBankClient> _LoadDataFromFile() {

        vector<clsBankClient>vClients;

        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);
        
        if (MyFile.is_open()) {

            string Line;

            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;
    }

    static void _SaveDataToFile(vector<clsBankClient>vClients) {

        fstream MyFile;


        MyFile.open("Clients.txt", ios::out);

        string Line;


        if (MyFile.is_open()) {


            for (clsBankClient &C : vClients) {
                if (C.MarkForDelete() == false) {
                    Line = _ConvertClientObjectToLine(C);
                    MyFile << Line << endl;
                }
            }
            MyFile.close();
        }

    }

    static void _AddDataLineToFile(string Line) {

        fstream MyFile;

        MyFile.open("Clients.txt", ios::out | ios::app);


        if (MyFile.is_open()) {
            MyFile << Line << endl;
        }
        MyFile.close();
    }

    void _Update() {

        vector<clsBankClient>vClients = _LoadDataFromFile();

        for (clsBankClient &C : vClients) {

            if (C.AccountNumber() == AccountNumber()) {
                C = *this;
                break;
            }


        }

        _SaveDataToFile(vClients);
    }

    void _AddNewClient() {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    static clsBankClient _GetEmptyBankClient() {
        return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
    }
    string _PrepareTransferLine(clsBankClient ToClient,double Amount,string Seperator = "#//#") {

        string Line = clsDate::DateAndTime() + Seperator + AccountNumber() + Seperator + ToClient.AccountNumber() + Seperator +
            to_string( Amount) + Seperator +to_string( Balance) + 
            Seperator +to_string( ToClient.Balance) + Seperator + CurrentUser.UserName();
        return Line;
    }

public:


    // Constructor
    clsBankClient(enMode Mode,string FirstName,string LastName,string Email,string Phone,string AccountNumber,string Pincode,double Balance
    ) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _Pincode = Pincode;
        _Balance = Balance;
    }


    struct stTransferInfo {
        string DateTime;
        string FromAccountNumber;
        string ToAccountNumber;
        double Amount;
        double Client1BalanceAfter;
        double Client2BalanceAfter;
        string UserName;
    };

    bool IsEmpty() {
        return _Mode == EmptyMode;
    }



    // Setters
    void SetPincode(string Pincode)
    {
        _Pincode = Pincode;
    }

    void SetBalance(double Balance)
    {
        _Balance = Balance;
    }

    // Getters
    string AccountNumber()
    {
        return _AccountNumber;
    }

    string GetPincode()
    {
        return _Pincode;
    }

    double GetBalance()
    {
        return _Balance;
    }

    bool MarkForDelete() {
        return _MarkForDelete;
    }

    // Properties

    __declspec(property(get = GetPincode, put = SetPincode))
        string Pincode;

    __declspec(property(get = GetBalance, put = SetBalance))
        double Balance;

    void Print()
    {
        cout << "\nClient Info:\n";
        cout << "\n____________________________________________\n\n";
        cout << "First Name    : " << FirstName << endl;
        cout << "Last Name     : " << LastName << endl;
        cout << "Email         : " << Email << endl;
        cout << "Phone         : " << Phone << endl;
        cout << "Account Number: " << AccountNumber() << endl;
        cout << "Pincode       : " << Pincode << endl;
        cout << "Balance       : " << Balance << endl;
        cout << "____________________________________________\n";

    }


    static clsBankClient Find(string AccountNumber) {

        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open()) {

            string Line;

            while (getline(MyFile, Line)) {

                clsBankClient Client = _ConvertLineToClientObject(Line);

                if (Client.AccountNumber() == AccountNumber) {
                    MyFile.close();
                    return Client;
                }
          }

            MyFile.close();


        }


        return _GetEmptyBankClient();

    }


    static clsBankClient Find(string AccountNumber,string Pincode) {

        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);

        if (MyFile.is_open()) {

            string Line;

            while (getline(MyFile, Line)) {

                clsBankClient Client = _ConvertLineToClientObject(Line);

                if (Client.AccountNumber() == AccountNumber && Client.Pincode==Pincode) {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();


        }


        return _GetEmptyBankClient();

    }

    enum enSaveStatus { svSuccessed = 0, svFailed = 1, svAlreadyExist = 2 };

    bool Delete() {

        vector<clsBankClient>vClients = _LoadDataFromFile();

        for (clsBankClient& C : vClients) {
            if (C.AccountNumber() == _AccountNumber) {
                C._MarkForDelete = true;
                break;
            }
        }
        _SaveDataToFile(vClients);
        *this = _GetEmptyBankClient(); 
        return true;
    }

    enSaveStatus Save() {

        switch (_Mode) {

        case EmptyMode:

            return svFailed;

            break;

        case UpdateMode:

            _Update();

            return svSuccessed;
            break;
            
           
        case AddNewMode:

            if (clsBankClient::IsClientExist(AccountNumber())) {
                return svAlreadyExist;
            }
            else {

                _AddNewClient();

                _Mode = UpdateMode;

                return svSuccessed;
            }

        }

    }

    static clsBankClient GetAddNewClient(string AccountNumber) {
        return clsBankClient(AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector<clsBankClient> GetClientsList() {
        return _LoadDataFromFile();
    }

    static double GetTotalBalances() {
        vector<clsBankClient>vClients = _LoadDataFromFile();
        double Balances = 0;
        for (clsBankClient& C : vClients) {
            Balances += C.Balance;
        }
        return Balances;
    }
    
    static bool IsClientExist(string AccountNumber) {

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        return (!Client.IsEmpty());
    }


    void Deposit(double Amount) {
        _Balance += Amount;
        Save();
    }
    void Withdraw(double Amount) {
        _Balance -= Amount;
        Save();
    }

    bool Transfer(double Amount, clsBankClient& ToClient) {
        if (Amount > Balance)
            return false;
        else {
            Withdraw(Amount);
            ToClient.Deposit(Amount);
            return true;
        }
    }

    void AddTransferLog(clsBankClient ToClient,double Amount, string Seperator = "#//#") {
        string Line = _PrepareTransferLine(ToClient,Amount);
        fstream MyFile;

        MyFile.open("TransferLog.txt", ios::out | ios::app);


        if (MyFile.is_open()) {
            MyFile << Line << endl;
        }

        MyFile.close();
    }


    static  vector <stTransferInfo> GetLoginRegisterList()
    {
        vector <stTransferInfo> vTransferRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stTransferInfo TrasnferReord;

            while (getline(MyFile, Line))
            {

                TrasnferReord = _ConvertLineToTransferInfoRecord(Line);

                vTransferRecord.push_back(TrasnferReord);

            }

            MyFile.close();

        }

        return vTransferRecord;

    }


};

