#pragma once
#include <iostream>
#include <string>

#include "subject.h"

/// Klasa wirtualna reprezentująca dokument finansowy (faktury i noty)
class financialDocument
{
	std::string number; ///< numer dokumentu
	int day; ///< dzień wystawienia dokumentu
	int month; ///< miesiąc wystawienia dokumentu
	int year; ///< rok wystawienia dokumentu
	subjectC subjects; ///< kontener z wystawcą i nabywcą
protected:

	/** \brief Konstruktor dokumentu finansowego
	* \param number numer dokumentu
	* \param day dzień wystawienia dokumentu
	* \param month miesiąc wystawienia dokumentu
	* \param year rok wystawienia dokumentu
	* \param subjects kontener podatników VAT z danymi wystawcy i nabywcy
	*/
	financialDocument(const std::string& number, const int day, const int month, const int year, const subjectC& subjects);

	/** \brief Konstruktor kopiujący dokumentu finansowego
	* \param toCopy faktura do skopiowania
	*/
	financialDocument(const financialDocument& toCopy);
public:

	/** \brief Getter numeru dokumentu
	* \result numer dokumentu
	*/
	std::string getNumber() const noexcept;

	/** \brief Getter roku wystawienia dokumentu
	* \result rok wystawienia dokumentu
	*/
	int getYear() const noexcept;

	/** \brief Getter miesiąca wystawienia dokumentu
	* \result miesiąc wystawienia dokumentu
	*/
	int getMonth() const noexcept;

	/** \brief Getter dnia wystawienia dokumentu
	* \result dzień wystawienia dokumentu
	*/
	int getDay() const noexcept;

	/** \brief Getter daty wystawienia dokumentu
	* \result data wystawienia dokumentu
	*/
	std::string getDate() const noexcept;

	/** \brief Getter kontenera podatników w dokumencie
	* \result kontener podatników w dokumencie
	*/
	subjectC getSubjects() const noexcept;
};