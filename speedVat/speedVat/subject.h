#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

/// Klasa abstrakcyjna kontener
class container
{
public:

	/** \brief Wczytanie danych z pliku
	* \param fileName nazwa pliku z danymi
	* Metoda ma sczytywać dane z pliku.
	*/
	virtual bool fromFile(const std::string& fileName) noexcept = 0;

	/** \brief Zapisanie ostatniej pozycji z wektora do pliku
	* \param fileName nazwa pliku, do którego dopisane mają zostać dane
	* Metoda ma dopisywać ostatnia pozycję z wektora do pliku.
	*/
	virtual bool saveData(const std::string& fileName) const noexcept = 0;
};


/// Klasa reprezentujaca adres
class address
{
	std::string street; ///< nazwa ulicy
	std::string numberHouse; ///< numer domu i mieszkania
	std::string city; ///< nazwa miasta
	std::string postcode; ///< kod pocztowy
public:

	/** \brief Konstruktor adresu
	* \param street nazwa ulicy
	* \param numberHouse numer domu i mieszkania
	* \param city nazwa miasta
	* \param postcode kod pocztowy
	*/
	address(const std::string& street, const std::string& numberHouse, const std::string& city, const std::string& postcode);

	/** \brief Konstruktor kopiujący adresu
	* \param toCopy adres do skopiowania
	*/
	address(const address& toCopy);

	/** \brief Getter nazwy ulicy
	* \result nazwa ulicy w adresie
	*/
	std::string getStreet() const noexcept;

	/** \brief Getter numeru domu i mieszkania
	* \result numer domu i mieszkania w adresie
	*/
	std::string getNumberHouse() const noexcept;

	/** \brief Getter nazwy miasta
	* \result nazwa miasta w adresie
	*/
	std::string getCity() const noexcept;

	/** \brief Getter kodu pocztowego
	* \result kod pocztowy w adresie
	*/
	std::string getPostcode() const noexcept;

	/** \brief Setter nazwy ulicy
	* \param correct nowa nazwa ulicy
	*/
	void setStreet(const std::string& correct) noexcept;

	/** \brief Setter numeru domu i mieszkania
	* \param correct nowe numery domu i mieszkania
	*/
	void setNumberHouse(const std::string& correct) noexcept;

	/** \brief Setter nazwy miasta
	* \param correct nowa nazwa miasta
	*/
	void setCity(const std::string& correct) noexcept;

	/** \brief Setter kod pocztowego
	* \param correct nowy kod pocztowy
	*/
	void setPostcode(const std::string& correct) noexcept;
};


/// Klasa reprezentująca podatnika VAT
class subject
{
	std::string name; ///< nazwa podatnika
	std::string NIP; ///< numer NIP podatnika
	address _address; ///< adres podatnika
public:

	/** \brief Konstruktor produktu
	* \param name nazwa podatnika
	* \param NIP numer NIP podatnika
	* \param _address adres podatnik
	*/
	subject(const std::string& name, const std::string& NIP, const address& _address);

	/** \brief Konstruktor kopiujący podatnika VAT
	* \param copy podatnik do skopiowania
	*/
	subject(const subject& copy);

	/** \brief Getter NIPu
	* \result NIP podatnika
	*/
	std::string getNIP() const noexcept;

	/** \brief Getter nazwy
	* \result nazwa podatnika
	*/
	std::string getName() const noexcept;

	/** \brief Setter nazwy podatnika VAT
	* \param correct nowa nazwa podatnika
	*/
	void setName(const std::string& correct) noexcept;

	/** \brief Setter NIPu podatnika VAT
	* \param correct nowy NIP podatnika
	*/
	void setNIP(const std::string& correct) noexcept;

	/** \brief Setter nazwy uicy adresu podatnika VAT
	* \param correct nowa ulicy adresu podatnika
	* Metoda wywołuje setter klasy adres.
	*/
	void setStreet(const std::string& correct) noexcept;

	/** \brief Setter numeru ulicy i mieszkania adresu podatnika VAT
	* \param correct nowy numer ulicy i mieszkania adresu podatnika
	* Metoda wywołuje setter klasy adres.
	*/
	void setNumberHouse(const std::string& correct) noexcept;

	/** \brief Setter nazwy miasta adresu podatnika VAT
	* \param correct nowa nazwa miasta adresu podatnika
	* Metoda wywołuje setter klasy adres.
	*/
	void setCity(const std::string& correct) noexcept;

	/** \brief Setter kodu pocztowego adresu podatnika VAT
	* \param correct nowy kod pocztowy adresu podatnika
	* Metoda wywołuje setter klasy adres.
	*/
	void setPostcode(const std::string& correct) noexcept;

	/** \brief Getter adresu
	* \result adres podatnika
	*/
	address getAddress() const noexcept;
};

/// Klasa będąca kontenerem podatników VAT
class subjectC : public container
{
	std::vector<subject> subjects; ///<wektor podatników
public:

	/** \brief Konstruktor domyślny
	*/
	subjectC();

	/** \brief Konstruktor kopiujący podatnika
	* \param copy produkt do skopiowania
	*/
	subjectC(const subjectC& copy);

	/** \brief Wczytanie podatników z pliku
	* \param fileName Nazwa pliku, z którego ma być odczyt
	* Metoda podpowiada za poprawne sczytanie danych z pliku.
	* Ponadto wywołuje metodę tworzącą nowego podatnika.
	* Na koniec zapisuje nowy element w kontenerze.
	*/
	virtual bool fromFile(const std::string& fileName) noexcept;

	/** \brief Stworzenie nowego podatnika z surowych danych z pliku
	* \param buffer dane odzczytane z pliku
	* Metoda przetwarza dane odczytane prosto z pliku i tworzy nowego podatnika.
	*/
	void fromBuffer(char buffer[1024]) noexcept;

	/** \brief Utworzenie podatnika z danych od użytkownika
	* \param NIP numer NIP podatnika
	* \param name nazwa podatnika
	* \param street nazwa ulicy
	* \param numberHouse numer domu i mieszkania
	* \param city nazwa miasta
	* \param postcode kod pocztowy
	* \param fileName nazwa pliku, w którym ma zostać zapisana nowy podatnik
	* Metoda przyjmue dane podane przez użytkownika.
	* Przetwarza je i tworzy nowego podatnika.
	* Nastepnien zapisuje go w pliku.
	*/
	bool fromKeyboard(const std::string& NIP, const std::string& name, const std::string& street, const std::string& numberHouse, const std::string& city, const std::string& postcode, const std::string fileName);
	
	/** \brief Dodanie istniejącego podatnika do wektora
	* \param newSub podatnik, który ma zostać dodany
	* Metoda dodaje do kontenera nowego podatnika, który został już wcześniej utworzony.
	*/
	void addNew(const subject& newSub);

	/** \brief Zapisanie nowo dodanego podatnika
	* \param fileName nazwa pliku, w którym ma zostać zapisany nowy podatnik
	* \result metoda zwraca false w przypadku błędu otwarcia pliku
	* Metoda dopisuje podatnika, znajdujący się na końcu kontenera, do podanego pliku.
	*/
	virtual bool saveData(const std::string& fileName) const noexcept;

	/** \brief Zapisanie wszystkich podatników
	* \param option infomracja, czy dane mają zostać dopisane do pliku, czy plik ma zostać nadpisany
	* \param fileName nazwa pliku, w którym mają zostać zapisani podatnicy
	* \result metoda zwraca false w przypadku błędu otwarcia pliku
	* Zapisywani są wszyscy podatnicy znajdujące się w kontenerze
	*/
	bool saveAll(const int option, const std::string& fileName) const noexcept;

	/** \brief Getter wystawcy faktur
	* \result pierwszy podatnik znajdujących się w kontenerze
	*/
	subject getOwner() const noexcept;

	/** \brief Getter ostatniego podatnika w kontenerze
	* \result ostatni podatnik znajdujących się w kontenerze
	*/
	subject getLast() const noexcept;

	/** \brief Getter wielkości kontenera
	* \result ilość podatników znajdujących się w kontenerze
	*/
	int getSize()const noexcept;

	/** \brief Getter podatnika
	* \param which zmienna określająca, na której pozycji w wektorze znajduje się podatnik, który ma zostać zwrócony
	* \result żądany produkt
	*/
	subject getSubject(const int pointer)const noexcept;

	/** \brief Wyszukanie podatnika
	* \param wanted zmienna z szukaną wartością
	* \result pozycja, na której poszukiwany podatnik znajduje się w wektorze
	* Metoda porównuje wartość szukaną z numerami NIP wszystkich podatników zapisanymi w konterze.
	* Jeżeli szukany numer i NIP podatnika są takie same, metoda zwraca "wskaźnik" produkt.
	*/
	subject search(const std::string& wanted) const noexcept;

	/** \brief Wyszukanie podatnika
	* \param option zmienna przekazująca, czy wyszukanie ma nastapić po nazwie podatnika czy jego numerze NIP
	* \param wanted zmienna z szukaną wartością
	* \result wektor "wskażników"
	* Metoda porównuje wartość szukaną ze wszystkimi pdatnikami zapisanymi w konterze.
	* Jeżeli wartości są sobie równe, do wektora zapisywana jest pozycja pasującego podatnika, w wektorze kontenera.
	*/
	std::vector<int> search(const int option, std::string& wanted) const noexcept;

	/** \brief Zmiana wartości danego podatnika
	* \param option zmienna informująca, który element podatnika należy zmienić
	* \param pointer zmienna z numerem miejsca danego produktu w wektorze głównego kontenera
	* \param correct nowa wartość do podmiany
	* \param fileName nazwa pliku, w ktorym znajduje się poprawiany podatnik
	* Metoda przy pomocy setterów zmienia wartości konkretnej pozycji wektora.
	* Następnie nadpisuje plik z produktami.
	*/
	void repair(const int option, const int pointer, const std::string& correct, const std::string& fileName);
};


