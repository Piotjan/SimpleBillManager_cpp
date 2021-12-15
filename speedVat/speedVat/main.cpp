#include<iostream>

#include "UI.h"

int main()
{
	std::string fileSub("subjects.txt");
	std::string fileProd("products.txt");
	std::string fileVat("bills.txt");
	int choice = 0;
	
	speedVat program;
	program.loadData(fileSub, fileProd, fileVat);
	while (choice != 12)
	{
		choice = program.start();
		switch (choice)
		{
		case 1:
			while (choice != 4)
			{
				choice = program.vat();
				switch (choice)
				{
				case 1:
					program.vatKeyboard(fileVat);
					break;
				case 2:
					program.vatSearch();
					break;
				case 3:
					program.vatViewAll();
					break;
				default: break;
				}
			}
			break;
		case 2:
			program.noteKeyboard(fileVat);
			break;
		case 3:
			choice = 0;
			while (choice != 5)
			{
				choice = program.products();
				switch (choice)
				{
				case 1: 
					program.productViewAll();
					break;
				case 2:
					program.productKeyboard(fileProd);
					break;
				case 3:
					program.productSearch();
					break;
				case 4:
					program.productRepair(fileProd);
					break;
				default: break;
				}
			}
			break;

		case 4:
			choice = 0;
			while (choice != 5)
			{
				choice = program.subjects();
				switch (choice)
				{
				case 1:
					program.subjectViewAll();
					break;
				case 2:
					program.subjectKeyboard(fileSub);
					break;
				case 3:
					program.subjectSearch();
					break;
				case 4:
					program.subjectRepair(fileSub);
					break;
				default: break;
				}
			}
			break;
		case 5:
			program.correctOwner(fileSub);
			break;
		default: break;
		}
	}

	return 0;
}