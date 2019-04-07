// LabD_4a.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
//#include "Human.h"
#include <string>

class OverflowException {
public:
	OverflowException() {
		std::cout << std::endl << "Exception created!" << std::endl;
	}
	OverflowException(const OverflowException&) {
		std::cout << "Exception copied!" << std::endl;
	}
	~OverflowException() {
		std::cout << "Exception finished!" << std::endl;
	}
};

class Human {
protected:
	std::string Name;
	double Gender;
	int Birth_Date;
public:
	Human();
	Human(std::string, char,int);
	virtual ~Human() {
		// std::cout << "Message from the \"Human\" - destroyed!" << std::endl;
	}

	std::string Get_Name() const {
		return Name;
	}

	std::string Set_Name(std::string name) {
		this->Name = name;
	}
	char Get_Gender() const;
	void Set_Gender(char);

	//int Get_BirthDate() const;
	//void Set_BirthDate(int);

	int Get_BirthDate() const
	{
		return Birth_Date;
	}

	int Set_BirthDate(int birth_date) 
	{
		this-> Birth_Date = birth_date;
	}


	virtual void Print() const;
};

class Employee : public Human {
private:
	double Salary;
public:
	Employee() : Human(), Salary(NULL) {
	}
	Employee(std::string, char, int,double);
	
	virtual ~Employee() {
		// std::cout << std::endl << "Message from the \"Employee\" - destroyed!" << std::endl;
	}
	unsigned int GetSalary() const {
		return Salary;
	}
	void SetSalary(double PSalary) {
		this->Salary = PSalary;
	}
	virtual void Print() const;
};

class Firm {
private:
	typedef Employee* WorkerPointer;
	WorkerPointer *Workers;
	static const unsigned int DEFAULT_MAX_LENGTH;
	unsigned int MaxLength;
	unsigned int Length;
	unsigned int MaxSalary;
public:
	Firm() : MaxLength(DEFAULT_MAX_LENGTH), Length(0), MaxSalary(0) {
		Workers = new WorkerPointer[MaxLength];
	}
	Firm(unsigned int MaxLength, unsigned int WorkerSalary) : MaxLength(MaxLength), Length(0) {
		this->MaxSalary = WorkerSalary;
		Workers = new WorkerPointer[MaxLength];
	}
	~Firm();
	static unsigned int GetDefaultMaxLength() {
		return DEFAULT_MAX_LENGTH;
	}
	int GetMaxLength() const {
		return MaxLength;
	}
	int GetLength() const {
		return Length;
	}
	void AddNode(const Employee&);
	void Print() const;
};
const unsigned int Firm::DEFAULT_MAX_LENGTH = 5;

Human::Human() : Name(""), Gender('m'),Birth_Date(0) {
}
Human::Human(std::string name, char gender,int birth_date) : Name(name) {
	Gender = gender; 
	Birth_Date = birth_date;
}
inline char Human::Get_Gender() const {
	return Gender;
}
inline void Human::Set_Gender(char gender) {
	this->Gender = gender;
}
inline void Human::Print() const {
	std::cout << "Name = " << Name << ", Gender = " << Get_Gender() << ", birth date = " << std::to_string(Birth_Date);
}

Employee::Employee(std::string name, char gender, int birth_date, double PSalary) : Human(name, gender,birth_date) {
	Salary = PSalary;
}
inline void Employee::Print() const {
	Human::Print();
	std::cout << ", Salary = " << Salary;
}

Firm::~Firm() {
	for (unsigned int i = 0; i < Length; i++)
		delete Workers[i];
	delete[] Workers;
}
void Firm::Print() const {
	std::cout << "\nMax salary in the list: " << MaxSalary << "." << std::endl
		<< "List0's nodes:" << std::endl;
	for (unsigned int i = 0; i < Length; i++) {
		std::cout << (i + 1) << ". ";
		Workers[i]->Print();
		std::cout << "." << std::endl;
	}
}
void Firm::AddNode(const Employee& WorkerList) {
	if (Length == MaxLength)
		throw OverflowException();
	else
		Workers[Length++] = new Employee(
			WorkerList.Get_Name(), WorkerList.Get_Gender(), WorkerList.Get_BirthDate(), WorkerList.GetSalary()
		);
}

void main(void) {
	Firm *List0 = new Firm(4, 1);
	Employee *D1 = new Employee("Asdf", 'm', 12,33);
	
	Employee  D2("John", 'm', 12, 34);
	Employee  D3("Sarah", 'f', 12, 35);
	Employee  D4("Vasya", 'm', 12, 36);
	

	try {
		List0->AddNode(*D1);
	
		std::cout << "\nNew workers have been added to the list successfully!" << std::endl;
	}



	catch (const OverflowException&) {
		std::cout << "*** Error: maximal length exceeded ! ***" << std::endl;
	}
	catch (...) {
		std::cout << "Unknown Error !" << std::endl;
	}
	delete D1;

	std::cout << "\n\nDefault maximal length (from CLASS): " <<
		Firm::GetDefaultMaxLength() << "." << std::endl;
	std::cout << "Default maximal length (from OBJECT): " <<
		Firm::GetDefaultMaxLength() << "." << std::endl;
	std::cout << "Maximal length: " << List0->GetMaxLength() << "." << std::endl;
	std::cout << "Current length: " << List0->GetLength() << "." << std::endl;

	try {
		List0->AddNode(D2);
		std::cout << "\nNew worker has been added successfully!" << std::endl;
	}
	catch (const OverflowException&) {
		std::cout << "*** Error: maximal length exceeded ! ***" << std::endl;
	}
	catch (...) {
		std::cout << "Unknown Error !" << std::endl;
	}

	try {
		List0->AddNode(D3);
		std::cout << "\nNew worker has been added successfully!" << std::endl;
	}
	catch (const OverflowException&) {
		std::cout << "*** Error: maximal length exceeded! ***" << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error !" << std::endl;
	}

	try {
		List0->AddNode(D4);
		std::cout << "\nNew worker has been added successfully!" << std::endl;
	}
	catch (const OverflowException&) {
		std::cout << "*** Error: maximal length exceeded ! ***" << std::endl;
	}
	catch (...) {
		std::cout << "Unknown Error !" << std::endl;
	}

	List0->Print();

	delete List0;

	//while (kbhit())
	//	getch();
	//getch();
}