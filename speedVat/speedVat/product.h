#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "subject.h"

/// Klasa reprezentująca produkt
class product
{
	std::string name; ///< nazwa produktu
	double netto; ///< cena netto produktu
	double vatWage; ///< stawka podatku VAT na danym produkcie
	double price; ///< cena brutto produktu
public:

	/** \brief Konstruktor produktu
	* \param name nazwa produktu
	* \param netto cena netto produktu
	* \param vatWage stawka podatku VAT na danym produkcie
	*/
	product(const std::string& name, double netto, double vatWage);

	/** \brief Getter nazwy produktu
	* \result nazwa produktu
	*/
	std::string getName() const noexcept;

	/** \brief Getter ceny netto
	* \result cena netto produktu
	*/
	double getNetto() const noexcept;

	/** \brief Getter stawki vat
	* \result wysokość stawki podatku VAT produktu
	*/
	double getVatWage() const noexcept;

	/** \brief Getter ceny brutto
	* \result cena brutto produktu
	*/
	double getPrice() const noexcept;

	/** \brief Setter nazwy produktu
	* \param correct nowa nazwa produktu
	*/
	void setName(const std::string& correct) noexcept;

	/** \brief Setter ceny netto
	* \param correct nowa cena netto
	* Metoda ponadto oblicza i ustawia nową cenę brutto
	*/
	void setNetto(const double correct) noexcept;

	/** \brief Setter stawki VAT
	* \param correct nowa stawka VAT
	* Metoda ponadto oblicza i ustawia nową cenę brutto
	*/
	void setVatWage(const double correct) noexcept;
};

/// Klasa będąca kontenerem produktów
class productC : public container
{
	std::vector<product> products; ///<wektor produktów
public:

	/** \brief Konstruktor domyślny
	*/
	productC();

	/** \brief Konstruktor kopiujący produktu
	* \param copy produkt do skopiowania
	*/
	productC(const productC& copy);

	/** \brief Wczytanie produktów z pliku
	* \param fileName Nazwa pliku, z którego ma być odczyt
	* Metoda podpowiada za poprawne sczytanie danych z pliku.
	* Ponadto wywołuje metodę tworzącą nowy produkt.
	* Na koniec zapisuje nowy element w kontenerze.
	*/
	virtual bool fromFile(const std::string& fileName) noexcept;

	/** \brief Utworzenie produktu z danych od użytkownika
	* \param name nazwa produktu
	* \param netto cena netto produktu
	* \param vatWage stawka podatku VAT na danym produkcie
	* \param fileName nazwa pliku, w którym ma zostać zapisana nowy produkt
	* Metoda przyjmue dane podane przez użytkownika.
	* Przetwarza je i tworzy nowy produkt.
	* Nastepnien zapisuje ją w pliku.
	*/
	bool fromKeyboard(const std::string& name, const double netto, const double vatWage, const std::string& fileName) noexcept;

	/** \brief Stworzenie nowego produktu z surowych danych z pliku
	* \param buffer dane odzczytane z pliku
	* Metoda przetwarza dane odczytane prosto z pliku i tworzy nowy produkt.
	*/
	void fromBuffer(char buffer[1024]) noexcept;

	/** \brief Dodanie istniejącego produktu do wektora
	* \param newProd produkt, który ma zostać dodany
	* Metoda dodaje do kontenera nowy produkt, który został już wcześniej utworzony.
	*/
	void addNew(const product& newProd);

	/** \brief Zapisanie nowo dodanego produktu
	* \param fileName nazwa pliku, w którym ma zostać zapisany nowy produkt
	* \result metoda zwraca false w przypadku błędu otwarcia pliku
	* Metoda dopisuje produkt, znajdujący się na końcu kontenera, do podanego pliku.
	*/
	virtual bool saveData(const std::string& fileName) const noexcept;

	/** \brief Zapisanie wszystkich produktów
	* \param option infomracja, czy dane mają zostać dopisane do pliku, czy plik ma zostać nadpisany
	* \param fileName nazwa pliku, w którym mają zostać zapisane produkty
	* \result metoda zwraca false w przypadku błędu otwarcia pliku
	* Zapisywane są wszystkie produkty znajdujące się w kontenerze
	*/
	bool saveAll(const int option, const std::string& fileName) const noexcept;

	/** \brief Getter wielkości kontenera
	* \result ilość produktów znajdujących się w kontenerze
	*/
	int getSize() const noexcept;

	/** \brief Getter produktu
	* \param which zmienna określająca, na której pozycji w wektorze znajduje się produkt, który ma zostać zwrócony
	* \result żądany produkt
	*/
	product getProduct(const int which) const noexcept;

	/** \brief Wyszukanie produktu
	* \param wanted zmienna z szukaną wartością
	* \result pozycja, na której poszukiwany produkt znajduje się w wektorze
	* Metoda porównuje wartość szukaną ze wszystkimi produktami zapisanymi w konterze.
	* Jeżeli nazwa produktu i szukana są takie same, metoda zwraca "wskaźnik" produkt.
	*/
	int search(const std::string& wanted) const noexcept;

	/** \brief Zmiana wartości danego produktu
	* \param option zmienna informująca, który element produktu należy zmienić
	* \param pointer zmienna z numerem miejsca danego produktu w wektorze głównego kontenera
	* \param correct nowa wartość do podmiany
	* \param fileName nazwa pliku, w ktorym znajduje się poprawiany produkt
	* Metoda przy pomocy setterów zmienia wartości konkretnej pozycji wektora.
	* Następnie nadpisuje plik z produktami.
	*/
	void repair(const int option, const int pointer, const std::string& correct, const std::string fileName);

};

