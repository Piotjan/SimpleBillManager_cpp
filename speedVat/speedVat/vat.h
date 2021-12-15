#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <WinBase.h>

#include "virtual.h"
#include "subject.h"
#include "product.h"
#include "note.h"

/// Klasa reprezentująca fakturę VAT
class VatInvoice : public financialDocument
{
	productC products; ///< kontener produktów, na które była wystawiona faktura
	std::vector<correctingNote> notes; ///< wektor not korygujących przypisanych do danej faktury
public:

	/** \brief Konstruktor faktury VAT
	* \param number numer faktury
	* \param day dzień wystawienia faktury
	* \param month miesiąc wystawienia faktury
	* \param year rok wystawienia faktury 
	* \param subjects kontener podatników VAT z danymi wystawcy i nabywcy
	* \param products kontener produktów, na które była wystawiona faktura
	*/
	VatInvoice(const std::string& number, const int day, const int month, const int year, const subjectC& subjects, const productC& products);

	/** \brief Konstruktor kopiujący faktury VAT
	* \param toCopy faktura do skopiowania
	*/
	VatInvoice(const VatInvoice& toCopy);

	/** \brief Getter produktów
	* \result kontener produktów, na które była wystawiona faktura
	*/
	productC getProducts() const noexcept;

	/** \brief Getter not korygujących
	* \result wektor not, które zostały dołączone do faktury
	*/
	std::vector<correctingNote> getNotes() const noexcept;

	/** \brief Getter ilości not korygujących
	* \result ilość not, które zostały dołączone do faktury
	*/
	int getNotesAmount() const noexcept;

	/** \brief Setter noty korygującej
	* \param note nota, która ma zostać dołączona do faktury
	* Metoda dodaje do wektora not nową, przekazaną pozycję.
	*/
	void setNote(const correctingNote& note) noexcept;
};


/// Klasa będąca kontenerem faktur
class vatInvoiceC : public container
{
	std::vector<VatInvoice> bills; ///< wektor faktur
public:

	/** \brief Konstruktor domyślny
	*/
	vatInvoiceC();

	/** \brief Wczytanie faktur z pliku
	* \param fileName Nazwa pliku, z którego ma być odczyt
	* Metoda pobiera dane z pliku i przetwarza je.
	* Następnie tworzy faktury vat, zapisując je w kontenerze.
	*/
	virtual bool fromFile(const std::string& fileName) noexcept;

	/** \brief Utworzenie faktury z danych od użytkownika
	* \param subjects kontener podatników VAT z danymi wystawcy i nabywcy
	* \param products kontener produktów, na które była wystawiona faktura
	* \param fileName nazwa pliku, w którym ma zostać zapisana nowa fakutra
	* Metoda przyjmue dane podane przez użytkownika.
	* Przetwarza je, odczytuje dzień wystawienia faktur i tworzy nową fakturę.
	* Nastepnien zapisuje ją w pliku.
	*/
	bool fromKeyboard(const subjectC& subjects, const productC& products, const std::string& fileName);

	/** \brief Zapisanie nowo dodanej faktury
	* \param fileName nazwa pliku, w którym ma zostać zapisana nowa fakutra
	* \result metoda zwraca false w przypadku błedu otwarcia pliku
	* Metoda dopisuje fakturę, znajdującą sie na końcu kontenera, do podanego pliku.
	*/
	virtual bool saveData(const std::string& fileName) const noexcept;

	/** \brief Zapisanie wszystkich faktur
	* \param fileName nazwa pliku, w którym mają zostać zapisane fakutry
	* \result metoda zwraca false w przypadku błędu otwarcia pliku
	* Metoda nadpisuje istniejący już plik.
	* Zapisywane są wszystkie faktury znajdujące się w kontenerze
	*/
	bool saveAll(const std::string& fileName) const noexcept;

	/** \brief Wyszukanie faktury
	* \param option zmienna przekazująca, czy wyszukanie ma nastapić po numerze faktury, NIPie nabywcy czy dacie wystawienia
	* \param wanted zmienna z szukaną wartością
	* \result wektor "wskażników"
	* Metoda porównuje wartość szukaną ze wszystkimi fakturami zapisanymi w konterze.
	* Jeżeli wartości są sobie równe, do wektora zapisywana jest pozycja pasującej faktury, w wektorze kontenera.
	*/
	std::vector<int> search(const int option, const std::string& wanted) const noexcept;

	/** \brief Getter faktury
	* \param which zmienna określająca, na której pozycji w wektorze znajduje się faktura, która ma zostać zwrócona
	* \result żądana faktura
	*/
	VatInvoice getBill(const int which) const noexcept;

	/** \breif Dodanie noty korygujacej do faktury
	* \param vatNumber numer faktury, do której wystawiona ma być nota
	* \param subjects kontener podatników VAT z danymi wystawcy i nabywcy
	* \param mistake treść błędu na fakturze
	* \param correct tresć poprawki
	* \param fileName nazwa pliku, w którym znajdują się faktura do której dodawana jest nota
	* Metoda wyszukuje fakturę po jej numerze.
	* Do znalezionej faktury dodawana jest nowa nota.
	* Nastepnie cały kontener jest nadpisywany do pliku.
	*/
	void addNote(const std::string& vatNumber, const subjectC& subjects, const std::string& mistake, const std::string& correct, const std::string& fileName) noexcept;

	/** \brief Getter wielkości kontenera
	* \result ilość faktur znajdujących się w kontenerze
	*/
	int getSize() const noexcept;
};

