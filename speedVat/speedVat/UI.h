/**@file*/
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "virtual.h"
#include "note.h"
#include "product.h"
#include "subject.h"
#include "vat.h"

/// klasa odpowiadająca za kontakt z użytkownikiem, wywołująca odpowiednie metody i zarządzająca zmiennymi "globalnymi"
class speedVat
{
	subjectC _subject; ///< kontener zawierający wektor podatników
	productC _product; ///< kontener zawierający wektor produktów
	vatInvoiceC _bills; ///< kontener zawierający wektor faktur
public:
	/** \brief Konstruktor domyślny
	*/
	speedVat();

	/** \brief Metoda startowa 
	* \param fileSub nazwa pliku z podatnikami VAT
	* \param fileProd nazwa pliku z produktami
	* \param fileVat nazwa pliku z fakturami
	* 
	* Metoda wywołująca metody odpowiedzialne za wczytanie do kontenerów danych z pliku.
	* Jeżeli program został uruchomiony po raz pierwszy, pobiera dane wystawcy faktur.	*
	*/
	void loadData(const std::string& fileSub, const std::string& fileProd, const std::string& fileVat);

	/** \brief Ekran startowy
	* \return wybór użytkownika
	* Metoda wyświetla ekran startowy programu.
	* Pobiera wybór użytkownika i zwraca jego wartość w postaci zmiennej typu int. 
	*/
	int start() const noexcept;

	/** \brief Ekran faktury
	* \return wybór użytkownika
	* Metoda wyświetla możliwe opcje działań związanych z fakturami.
	* Pobiera wybór użytkownika i zwraca jego wartość w postaci zmiennej typu int.
	*/
	int vat() const noexcept;

	/** \brief Ekran produktów
	* \return wybór użytkownika
	* Metoda wyświetla możliwe opcje działań związanych z produktami.
	* Pobiera wybór użytkownika i zwraca jego wartość w postaci zmiennej typu int.
	*/
	int products() const noexcept;

	/** \brief Ekran podatników VAT
	* \return wybór użytkownika
	* Metoda wyświetla możliwe opcje działań związanych z podatnikami VAT.
	* Pobiera wybór użytkownika i zwraca jego wartość w postaci zmiennej typu int.
	*/
	int subjects() const noexcept;


	/** \brief Wyświetlenie wszystkich faktur
	* Metoda wywołuję metodę, wyświetlającą podaną fakturę VAT dla wszystkich elementów głównego kontenera.
	*/
	void vatViewAll() const noexcept;

	/** \brief Waświetlenie faktury
	* \param bill faktura do wyświetlenia
	* Metoda wyświetla podaną fakturę.
	*/
	void vatView(const VatInvoice& bill) const noexcept;

	/** \brief Ekran tworzenia faktury
	* \param fileName nazwa pliku, w którym ma zostać zapisana nowa faktura
	* Metoda wyświetla, jakie informacje są niezbedne do utworzenia nowej faktury.
	* Następnie pobiera od użytkownika potrzebne dane.
	* Na koniec wywołuje metodę odpowiedzialną za stworzenie nowej faktury.
	*/
	void vatKeyboard(const std::string& fileName) noexcept;

	/** \brief Ekran wyszukiwania faktur
	* Metoda pobiera od użytkiwnika informacje na temat poszukiwanej faktury.
	* Następnie wywołuje metodę wyświetlającą znalezione faktury.
	*/
	void vatSearch() const noexcept;

	/** \brief Ekran tworzenia not korygujących
	* \param fileName nazwa pliku, w którym ma zostać zapisana nowa nota
	* Metoda wyświetla, jakie informacje są niezbedne do utworzenia nowej noty.
	* Następnie pobiera od użytkownika potrzebne dane.
	* Na koniec wywołuje metodę odpowiedzialną za stworzenie nowej noty.
	*/
	void noteKeyboard(const std::string& fileName) noexcept;

	/** \brief Waświetlenie podantnika VAT
	* \param sub opdatnik do wyświetlenia
	* Metoda wyświetla dane podanego podatnika.
	*/
	void subjectView(const subject& sub) const noexcept;

	/** \brief Wyświetlenie wszystkich podatników VAT
	* Metoda wywołuję metodę, wyświetlającą podanego podatnika VAT dla wszystkich elementów głównego kontenera.
	*/
	void subjectViewAll()const noexcept;

	/** \brief Ekran wyszukiwania podatników VAT
	* Metoda pobiera od użytkiwnika informacje na temat poszukiwanego podatnika.
	* Następnie wywołuje metodę wyświetlającą znalezionych podatników.
	*/
	void subjectSearch() const noexcept;

	/** \brief Ekran dodawania podatnika VAT
	* \param fileName nazwa pliku, w którym ma zostać zapisany nowy podatnik
	* Metoda wyświetla, jakie informacje są niezbedne do dodania nowego podatnika.
	* Następnie pobiera od użytkownika potrzebne dane.
	* Na koniec wywołuje metodę odpowiedzialną za dodanie nowego podatnika
	*/
	void subjectKeyboard(const std::string& fileName) noexcept;

	/** \brief Ekran zmiany danych istniejącego podatnika VAT
	* \param fileName nazwa pliku, w którym mają zostać zapisane nowe dane
	* Metoda, wg danych otrzymanych od użytkownika, wyszukuje danego podatnika.
	* Następnie pobiera dane, który element ma zostać zmieniony i na co.
	* Końcowo wywołuje metody odpowiedzialne za właściwą zmianę.
	*/
	void subjectRepair(const std::string& fileName) noexcept;

	/** \brief Waświetlenie produktu
	* \param sub opdatnik do wyświetlenia
	* Metoda wyświetla dane podanego produktu
	*/
	void productView(const product& prod) const noexcept;

	/** \brief Wyświetlenie wszystkich produtków
	* Metoda wywołuję metodę, wyświetlającą podany produkt dla wszystkich elementów głównego kontenera.
	*/
	void productViewAll() const noexcept;

	/** \brief Wyświetlenie nazw produktów w systemie
	* Metoda wywołuję metodę, wyświetlającą nazwę podanego produktu dla wszystkich elementów głównego kontenera.
	*/
	void productViewNames() const noexcept;

	/** \brief Ekran wyszukiwania produktów
	* Metoda pobiera od użytkiwnika informacje na temat poszukiwanego produktu.
	* Następnie wywołuje metodę wyświetlającą znaleziony produkt.
	*/
	void productSearch() const noexcept;

	/** \brief Ekran dodawania produktów
	* \param fileName nazwa pliku, w którym ma zostać zapisany nowy produkt
	* Metoda wyświetla, jakie informacje są niezbedne do dodania nowego podatnika.
	* Następnie pobiera od użytkownika potrzebne dane.
	* Na koniec wywołuje metodę odpowiedzialną za dodanie nowego produktu.
	*/
	void productKeyboard(const std::string& fileName);

	/** \brief Ekran zmiany danych istniejącego produktu
	* \param fileName nazwa pliku, w którym mają zostać zapisane nowe dane
	* Metoda, wg danych otrzymanych od użytkownika, wyszukuje dany produkt.
	* Następnie pobiera dane, który element ma zostać zmieniony i na co.
	* Końcowo wywołuje metody odpowiedzialne za właściwą zmianę.
	*/
	void productRepair(const std::string& filename);

	/** \brief Ekran zmiany danych wystawcy faktur
	* \param fileName nazwa pliku, w którym majaą zostać zapisane nowe dane
	* Metoda pobiera dane, który element ma zostać zmieniony i na co.
	* Następnie wywołuje metody odpowiedzialne za właściwą zmianę.
	*/
	void correctOwner(const std::string& fileName);
};
