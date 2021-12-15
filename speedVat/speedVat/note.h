#pragma once
#include <iostream>
#include <string>

#include "virtual.h"
#include "subject.h"

/// Klasa reprezentująca note korygującą
class correctingNote : public financialDocument
{
	std::string mistake; ///< błędne dane w fakturze
	std::string correct; ///< dane, na które błąd powinien zostać poprawiony
public:

	/** \brief Konstruktor noty
	* \param number numer noty
	* \param day dzień wystawienia noty
	* \param month miesiąc wystawienia noty
	* \param year rok wystawienia noty
	* \param subjects kontener podatników VAT z danymi wystawcy i nabywcy
	* \param mistake treść błędu na fakturze
	* \param correct tresć poprawki
	*/
	correctingNote(const std::string& number, const int day, const int month, const int year, const subjectC& subjects, const std::string& mistake, const std::string& correct);

	/** \brief Getter błędu
	* \result treść błędu na fakturze
	*/
	std::string getMistake() const noexcept;

	/** \brief Getter wartości właściwej
	* \result poprawienie błędu na fakturze
	*/
	std::string getCorrect() const noexcept;
};