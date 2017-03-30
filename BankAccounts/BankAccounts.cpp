// BankAccounts.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;


class BankAccount
{
	protected:
		float AccountNumber = 0;
		float InterestRate = 0;
		float Balance = 0;
		float Withdraw = 0;
		float Deposit = 0;
	public:

		virtual void inputDeposit(float Deposit)
		{
		
		}

		virtual bool inputWithdraw(float Withdraw)
		{
			return true;
		}
		virtual void InterestCalculation()
		{

		}
		
		virtual void Display() = 0;
};

class SavingsAccount:public BankAccount
{
	private:
		
	public:
		SavingsAccount();
		void InterestCalculation();
		void inputDeposit(float Deposit);
		bool inputWithdraw(float Withdraw);
		void Display();
};

SavingsAccount::SavingsAccount()
{
	AccountNumber++;
}



void SavingsAccount::InterestCalculation()
{
	if (Balance >= 10000)
		InterestRate = (.02/12); //monthly compounding
	else
		InterestRate = (.01/12);

	Balance = Balance * (1 + InterestRate);
}



void SavingsAccount::inputDeposit (float Deposit)
{
	//Deposit = tDeposit;
	Balance += Deposit;
	//InterestCalculation();
}



bool SavingsAccount::inputWithdraw(float Withdraw)
{

	if (Withdraw + 2 > Balance)
		return false;

	Balance = Balance - Withdraw - 2; //$2 fee included with a withdrawl
		return true;

}	


void SavingsAccount::Display() // display account details
{
	cout << "---------------------------------" << endl;
	cout << "------Account Details--------" << endl;
	cout << "Account Type: Savings" << endl;
	cout << "Account Number:" << AccountNumber << endl;
	cout << "Monthly Interest Rate:" << InterestRate << endl;
	cout << "Account Balance:" << Balance << endl;
	cout << "---------------------------------" << endl;	
}

class CheckingAccount:public BankAccount
{
	private:
	
	public:
		CheckingAccount();
		bool inputWithdraw(float Withdraw);
		void inputDeposit(float Deposit);
		void orderChecks();
		void Display();
};

CheckingAccount::CheckingAccount()
{
	AccountNumber = AccountNumber + 3;
}

bool CheckingAccount::inputWithdraw(float Withdraw)
{
	if (Withdraw - 5 - 2> Balance)
		return false;
	
	Balance = Balance - Withdraw - 2; //$2 fee included with a withdrawl
	if (Balance < 500)
		Balance = Balance - 5;

	return true;

}

void CheckingAccount::inputDeposit(float Deposit)
{
	Balance += Deposit;
}

void CheckingAccount::Display() // display account details
{
	cout << "---------------------------------" << endl;
	cout << "------Account Details--------" << endl;
	cout << "Account Type: Checking" << endl;
	cout << "Account Number:" << AccountNumber << endl;
	cout << "Account Balance:" << Balance << endl;
	cout << "---------------------------------" << endl;

}

void CheckingAccount::orderChecks()
{
	Balance -= 15;
}

class CDAccount:public BankAccount
{
	private:
		//int Years = 0;
	public:
		int Years = 0;
		CDAccount();
		bool inputWithdraw(float Withdraw);
		void inputEarlyWithdraw(float Withdraw);
		void inputDeposit(float Deposit);
		void InterestCalculation();
		void Display();
};

CDAccount::CDAccount()
{
	AccountNumber = AccountNumber + 2;
}

bool CDAccount::inputWithdraw(float Withdraw)
{
	if (Withdraw > Balance)
		return false;
	//if (Years != 0)
		//Withdraw = Withdraw * 1.10;

	Balance -= Withdraw;

	return true;
}

void CDAccount::inputEarlyWithdraw(float Withdraw)
{
	if(Years != 0)
		Withdraw = Withdraw * 1.10;

	if (Withdraw > Balance)
		return;
	Balance -= Withdraw;
}

void CDAccount::inputDeposit(float Deposit)
{
	Balance += Deposit;
	//InterestCalculation();
}

void CDAccount::InterestCalculation()
{
	if (Years > 5)
		InterestRate = .10/12;
	else InterestRate = .5/12;
	Balance = Balance * (1 + InterestRate);
}

void CDAccount::Display() // display account details
{
	cout << "---------------------------------" << endl;
	cout << "------Account Details--------" << endl;
	cout << "Account Type: Certificate of Deposit" << endl;
	cout << "Account Number:" << AccountNumber << endl;
	cout << "Monthly Interest Rate:" << InterestRate << endl;
	cout << "Account Balance:" << Balance << endl;
	cout << "---------------------------------" << endl;
}

int main(int argc, char *argv[])
{

	SavingsAccount SA1;
	BankAccount *ptr;
	ptr = &SA1;
	ptr->inputDeposit(10000); //Deposit to Savings Account
	CheckingAccount CA1;
	ptr = &CA1;
	ptr->inputDeposit(600);// Deposit in for Checking Account
	CDAccount CDA1;
	CDA1.Years = 3;
	ptr = &CDA1;
	ptr->inputDeposit(10000); // Deposit in Certificate of Deposit account
	ptr->InterestCalculation(); //Calculate month interest for 3 years Certificate of Deposit */
	ptr = &SA1;
	ptr->InterestCalculation(); //Calculate Savings Account Interest Rate
	ptr->Display(); // Display Savings Account
	ptr = &CA1;
	ptr->Display(); // Display Checking Account
	ptr = &CDA1;
	ptr->Display(); // Display Certificate of Deposit*/
	ptr = &CA1;
	CA1.orderChecks(); // Order Checks for Checking Account
	ptr->inputWithdraw(200); // Withdraw from Checking Account*/
	ptr = &SA1;
	ptr->inputWithdraw(1000); // Withdraw from Saving Account
	CDA1.inputEarlyWithdraw(2000);
	ptr = &CDA1;
	ptr->Display(); // Display Certificate of Deposit*/
	ptr = &SA1;
	ptr->Display(); // Display Savings Account
	ptr = &CA1;
	ptr->Display(); // Display Checking Account

    return 0;
}
