#include <iostream>
#include "Classes.h"

using namespace std;

int main()
{
	system("clear");
	cout << "1. Reading matrices from the files \n";
	cout << "2. Inputing matrices  manually\n";
	cout << "enter 1,2:  ";
	char option;
	while (true)
	{
		cin >> option;
		if (option == '1' || option == '2')
			break;
		cout << "enter 1,2:  ";
	}

	// creating the matrices
	int r1,c1,r2,c2;
	if (option == '1')
	{
		Matrix A("u.txt");
		Matrix B("u.txt");
	}
	
	else if (option == '2')
	{
		system("clear");
		cout << "Enter rows and cols for Matrix A :  ";
		cin >> r1 >> c1;
		cout << "Enter rows and cols for Matrix B :  ";
		cin >> r2 >> c2;
	}
	Matrix A(r1,c1);
	A.setNumbers();
	Matrix B(r2,c2);
	B.setNumbers();


	system("clear");
	cout << "1.Add matrices\n";
	cout << "2.Substract matrices\n";
	cout << "3.Multiply matrices\n";
	cout << "4.Divide matrices\n";
	while (true)
	{
		cin >> option;
		if (option == '1' || option == '2' || option == '3' || option == '4')
			break;
		cout << "enter 1,2,3,4:  ";
	}

	if (option == '1')
	{
		Matrix C = A + B;
		C.saveToFile("new");
	}
	else if (option == '2')
	{
		Matrix C = A - B;
		C.saveToFile("new");
	}
	else if (option == '3')
	{
		Matrix C = A * B;
		C.saveToFile("new");
	}
	else if (option == '4')
	{
		Matrix C = A / B;
		C.saveToFile("new");
	}

	Matrix D = Matrix::readFromFile("new");

	system("clear");
	cout << "1.Is this matrix Symmetry?\n";
	cout << "2.Is this matrix Asymmetry?\n";
	cout << "3.Is this matrix upperTriangle/lowerTriangle/not?\n";
	cout << "Enter the option :  ";
	while (true)
	{
		cin >> option;
		if (option == '1' || option == '2' || option == '3')
			break;
		cout << "enter 1,2,3:  ";
	}

	if (option == '1')
	{
		if(D.isSymmetric())
			cout << "Symmetric\n";
		else 
			cout << "Not Symmetric\n";
	}
	else if (option == '2')
	{
		if(D.isASymmetric())
			cout << "ASymmetric\n";
		else 
			cout << "Not ASymmetric\n";
	}
	else if (option == '3')
	{
		if (D.isTriangle() == 1)
			cout << "Upper Triangle\n";
		if (D.isTriangle() == -1)
			cout << "Lower Trinagle\n";
		if (D.isTriangle() == 0)
			cout << "Not Triangle\n";
	}
}