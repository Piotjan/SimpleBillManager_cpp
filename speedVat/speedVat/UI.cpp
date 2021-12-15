#include "UI.h"

speedVat::speedVat()
{
}

void speedVat::loadData(const std::string& fileSub, const std::string& fileProd, const std::string& fileVat)
{
	if (!_subject.fromFile(fileSub))
	{
		std::cout << "SpeedVat" << std::endl << std::endl;
		std::cout << "Przy pierwszym uruchomieniu wprowadz dane wystawcy." << std::endl;
		system("PAUSE");
		speedVat::subjectKeyboard(fileSub);
	}
	_product.fromFile(fileProd);
	_bills.fromFile(fileVat);
}

int speedVat::start() const noexcept
{
	system("CLS");
	std::cout << "SpeedVat - program do obslugi faktur" << std::endl << std::endl;
	std::cout << "1 - Faktury" << std::endl;
	std::cout << "2 - Wystawienie noty" << std::endl;
	std::cout << "3 - Produkty" << std::endl;
	std::cout << "4 - Podatnicy VAT" << std::endl;
	std::cout << "5 - Ustawienia danych wystawcy" << std::endl;
	std::cout << "12 - Zakonczenie pracy z porogramem" << std::endl << std::endl;
	std::cout << "Wybor opcji: ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	return std::stoi(choiceS);
}

int speedVat::vat() const noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "1 - Wystawienie faktury (UWAGA! Nabywca musi znajdowac sie w bazie!)" << std::endl;
	std::cout << "2 - Wyszukiwania faktur" << std::endl;
	std::cout << "3 - Wyswietl wszystkie faktury" << std::endl;
	std::cout << "4 - Powrot" << std::endl << std::endl;
	std::cout << "Wybor opcji: ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	return std::stoi(choiceS);
}

int speedVat::products() const noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "1 - Lista produktow" << std::endl;
	std::cout << "2 - Dodanie produktu" << std::endl;
	std::cout << "3 - Wyszukanie produktu" << std::endl;
	std::cout << "4 - Korekta danych produktu" << std::endl;
	std::cout << "5 - Powrot" << std::endl << std::endl;
	std::cout << "Wybor opcji: ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	return std::stoi(choiceS);
}

int speedVat::subjects() const noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl;
	std::cout << "1 - Lista podatnikow" << std::endl;
	std::cout << "2 - Dodanie podatnika" << std::endl;
	std::cout << "3 - Wyszukanie podatnika" << std::endl;
	std::cout << "4 - Korekta danych podatnika" << std::endl;
	std::cout << "5 - Powrot" << std::endl << std::endl;
	std::cout << "Wybor opcji: ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	return std::stoi(choiceS);
}

void speedVat::vatViewAll() const noexcept
{
	system("CLS");
	for (int i = 0; i < _bills.getSize(); ++i)
	{
		VatInvoice bill(_bills.getBill(i));
		speedVat::vatView(bill);
	}
	system("PAUSE");
}

void speedVat::vatView(const VatInvoice& bill) const noexcept
{
	std::cout << "Faktura nr " << bill.getNumber() << std::endl;
	std::cout << "Wystawiono dnia " << bill.getDate() << std::endl;
	subjectC subjects(bill.getSubjects());
	std::cout << "Wystawca:" << std::endl;
	speedVat::subjectView(subjects.getOwner());
	std::cout << "Nabywca:" << std::endl;
	speedVat::subjectView(subjects.getLast());
	productC products(bill.getProducts());
	std::cout << "Produkty:" << std::endl;
	for (int i = 0; i < products.getSize(); ++i)
	{
		speedVat::productView(products.getProduct(i));
	}
	if (bill.getNotesAmount() > 0)
	{
		std::vector<correctingNote> notes(bill.getNotes());
		for (auto note : notes)
		{
			std::cout << std::endl;
			std::cout << "Noty korygujace:" << std::endl << std::endl;
			std::cout << note.getNumber() << std::endl;
			std::cout << "Wystawiono dnia: " << note.getDate() << std::endl;
			std::cout << "Wystawca:" << std::endl;
			subjectC subjects(bill.getSubjects());
			speedVat::subjectView(subjects.getOwner());
			std::cout << std::endl << "Nabywca:" << std::endl;
			speedVat::subjectView(subjects.getLast());
			std::cout << std::endl;
			std::cout << "Tresc bledna: " << note.getMistake() << std::endl;
			std::cout << "Tresc prawidlowa: " << note.getCorrect() << std::endl;
		}
	}
	std::cout << "-------------------------------------" << std::endl;
}

void speedVat::vatKeyboard(const std::string& fileName) noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "NIP nabywcy: ";
	std::string NIP;
	std::getline(std::cin, NIP);
	subject issuer(_subject.search(NIP));
	system("CLS");
	std::cout << "Znaleziony nabywca to:" << std::endl;
	speedVat::subjectView(issuer);
	std::cout << std::endl << "Kontynuowaæ? (1 - TAK, 2 - NIE): ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	if (choiceS == "2")
		return;
	subjectC subs;
	subs.addNew(_subject.getOwner());
	subs.addNew(issuer);

	system("CLS");
	std::cout << "Wybierz z listy produkty, ktore maja znalezc sie na fakturze." << std::endl;
	productC newProds;
	int choice = 0;
	while (choice < _product.getSize())
	{
		speedVat::productViewNames();
		std::cout << std::endl << "Produkt nr: ";
		std::getline(std::cin, choiceS);
		choice = std::stoi(choiceS) - 1;
		if (choice < _product.getSize())
		{
			product newProd(_product.getProduct(choice));
			newProds.addNew(newProd);
		}		
	}
	_bills.fromKeyboard(subs, newProds, fileName);
}

void speedVat::vatSearch() const noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Wyszukaj fakturê po:" << std::endl;
	std::cout << "1. Numerze faktury" << std::endl;
	std::cout << "2. Numerze NIP nabywcy" << std::endl;
	std::cout << "3. Dacie wystawienia" << std::endl << std::endl;
	std::cout << "Wybor: ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	std::cout << "Poszukiwany: ";
	std::string wanted;
	std::getline(std::cin, wanted);
	std::vector<int> pointers(_bills.search(std::stoi(choiceS), wanted));
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Znalezione faktury:" << std::endl;
	for (auto pointer : pointers)
	{
		speedVat::vatView(_bills.getBill(pointer));
	}
	system("PAUSE");
}

void speedVat::noteKeyboard(const std::string& fileName) noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Nr faktury do korekcji: ";
	std::string vatNumber;
	std::getline(std::cin, vatNumber);
	std::cout << "NIP nabywcy: ";
	std::string NIP;
	std::getline(std::cin, NIP);
	std::cout << "Tresc bledna: ";
	std::string mistake;
	std::getline(std::cin, mistake);
	std::cout << "Tresc poprawna: ";
	std::string correct;
	std::getline(std::cin, correct);
	subjectC subjects;
	subjects.addNew(_subject.getOwner());
	std::vector<int> pointers(_subject.search(2, NIP));
	int pointer = pointers[0];
	subjects.addNew(_subject.getSubject(pointer));
	_bills.addNote(vatNumber, subjects, mistake, correct, fileName);
}

void speedVat::subjectView(const subject& sub) const noexcept
{
	std::cout << sub.getName() << std::endl;
	std::cout << "NIP: " << sub.getNIP() << std::endl;
	address addr(sub.getAddress());
	std::cout << "Adres:" << std::endl;
	std::cout << addr.getStreet() << " " << addr.getNumberHouse() << std::endl;
	std::cout << addr.getCity() << " " << addr.getPostcode() << std::endl;
}

void speedVat::subjectViewAll() const noexcept
{
	system("CLS");
	std::cout << "SeedVat" << std::endl << std::endl;
	for (int i = 1; i < _subject.getSize(); ++i)
	{
		speedVat::subjectView(_subject.getSubject(i));
		std::cout << std::endl;
	}
	std::cout << std::endl;
	system("PAUSE");
}

void speedVat::subjectSearch() const noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Wyszukaj podatnika po:" << std::endl;
	std::cout << "1 - Nazwie" << std::endl;
	std::cout << "2 - Numerze NIP" << std::endl << std::endl;
	std::cout << "Wybor: ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	std::cout << "Poszukiwany: ";
	std::string wanted;
	std::getline(std::cin, wanted);

	std::vector<int> pointers(_subject.search(std::stoi(choiceS), wanted));
	system("CLS");
	std::cout << "Znalezieni podatnicy:" << std::endl << std::endl;
	for (auto pointer : pointers)
	{
		std::cout << "Pozycja na liscie: " << pointer << "." << std::endl;
		speedVat::subjectView(_subject.getSubject(pointer));
	}
	system("PAUSE");
}

void speedVat::subjectKeyboard(const std::string& fileName) noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Nazwa firmy: ";
	std::string name;
	std::getline(std::cin, name);
	std::cout << "NIP: ";
	std::string NIP;
	std::getline(std::cin, NIP);
	std::cout << "Ulica: ";
	std::string street;
	std::getline(std::cin, street);
	std::cout << "Nr domu/mieszkania: ";
	std::string numberHouse;
	std::getline(std::cin, numberHouse);
	std::cout << "Miasto: ";
	std::string city;
	std::getline(std::cin, city);
	std::cout << "Kod pocztowy: ";
	std::string postcode;
	std::getline(std::cin, postcode);
	_subject.fromKeyboard(name, NIP, street, numberHouse, city, postcode, fileName);
}

void speedVat::subjectRepair(const std::string& fileName) noexcept
{
	speedVat::subjectSearch();
	std::cout << std::endl << "Podatnik do korekty danych (nr pozycji): ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	system("CLS");
	int pointer = std::stoi(choiceS);
	speedVat::subjectView(_subject.getSubject(pointer));
	std::cout << std::endl << "Element do poprawy:" << std::endl;
	std::cout << "1 - Nazwa" << std::endl;
	std::cout << "2 - NIP" << std::endl;
	std::cout << "3 - Ulica" << std::endl;
	std::cout << "4 - Nr domu/mieszkania" << std::endl;
	std::cout << "5 - Miasto" << std::endl;
	std::cout << "6 - Kod pocztowy" << std::endl;
	std::cout << "7 - Powrot" << std::endl << std::endl;
	std::cout << "Wybor: ";
	std::getline(std::cin, choiceS);
	if (choiceS == "7")
		return;
	std::cout << "Poprawne: ";
	std::string correct;
	std::getline(std::cin, correct);
	_subject.repair(std::stoi(choiceS), pointer, correct, fileName);
}

void speedVat::productView(const product& prod) const noexcept
{
	std::cout << std::setw(20);
	std::cout << prod.getName();
	std::cout << std::setw(15);
	std::cout << prod.getNetto();
	std::cout << std::setw(15); 
	std::cout << prod.getVatWage() * 100 << '%';
	std::cout << std::setw(15) << std::setprecision(2);
	std::cout << prod.getPrice() << std::endl;
}

void speedVat::productViewAll() const noexcept
{
	system("CLS");
	std::cout << std::setw(15);
	std::cout << "Nazwa" << "Netto" << "Stawka Vat" << "Brutto" << std::endl;
	for (int i = 0; i < _product.getSize(); ++i)
	{
		speedVat::productView(_product.getProduct(i));
	}
	system("PAUSE");
}

void speedVat::productViewNames() const noexcept
{
	for (int i = 0; i < _product.getSize(); ++i)
	{
		product prod(_product.getProduct(i));
		std::cout << i + 1 << ". " << prod.getName() << std::endl;
	}
	std::cout << _product.getSize() + 1 << " - Zakonczenie dodawania produktow" << std::endl;
}

void speedVat::productSearch() const noexcept
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Nazwa szukanego produktu: ";
	std::string name;
	std::getline(std::cin, name);
	int pointer = _product.search(name);
	if (pointer < _product.getSize())
		speedVat::productView(_product.getProduct(pointer));
	else
		std::cout << "Nie znaleziono danego produktu." << std::endl;
	system("PAUSE");
}

void speedVat::productKeyboard(const std::string& fileName)
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Nazwa produktu: ";
	std::string name;
	std::getline(std::cin, name);
	std::cout << "Cena netto: ";
	std::string nettoS;
	std::getline(std::cin, nettoS);
	std::cout << "Stawka Vat: ";
	std::string vatWageS;
	std::getline(std::cin, vatWageS);
	_product.fromKeyboard(name, std::stod(nettoS), std::stod(vatWageS), fileName);
}

void speedVat::productRepair(const std::string& fileName)
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Nazwa produktu do zamiany: ";
	std::string name;
	std::getline(std::cin, name);
	int pointer = _product.search(name);
	if (pointer == _product.getSize())
	{
		std::cout << "Podanego produktu nie ma w bazie." << std::endl;
		system("PAUSE");
		return;
	}
	std::cout << "Znaleziony produkt: " << std::endl;
	speedVat::productView(_product.getProduct(pointer));
	std::cout << "Do poprawy: " << std::endl;
	std::cout << "1 - Nazwa" << std::endl;
	std::cout << "2 - Cena netto" << std::endl;
	std::cout << "3 - Stawka Vat" << std::endl;
	std::cout << "4 - Powrot" << std::endl << std::endl;
	std::cout << "Wybor: ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	if (choiceS == "4")
		return;
	std::cout << "Wersja poprawna: ";
	std::string correct;
	std::getline(std::cin, correct);
	_product.repair(std::stoi(choiceS), pointer, correct, fileName);
}
void speedVat::correctOwner(const std::string& fileName)
{
	system("CLS");
	std::cout << "SpeedVat" << std::endl << std::endl;
	std::cout << "Obecna dane wystawcy:" << std::endl;
	speedVat::subjectView(_subject.getOwner());
	std::cout << std::endl << "Do poprawy:" << std::endl;
	std::cout << std::endl << "Element do poprawy:" << std::endl;
	std::cout << "1 - Nazwa" << std::endl;
	std::cout << "2 - NIP" << std::endl;
	std::cout << "3 - Ulica" << std::endl;
	std::cout << "4 - Nr domu/mieszkania" << std::endl;
	std::cout << "5 - Miasto" << std::endl;
	std::cout << "6 - Kod pocztowy" << std::endl;
	std::cout << "7 - Powrot" << std::endl << std::endl;
	std::cout << "Wybor: ";
	std::string choiceS;
	std::getline(std::cin, choiceS);
	if (choiceS == "7")
		return;
	std::cout << "Poprawne: ";
	std::string correct;
	std::getline(std::cin, correct);
	_subject.repair(std::stoi(choiceS), 0, correct, fileName);
}