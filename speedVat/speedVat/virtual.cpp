#include "virtual.h"

financialDocument::financialDocument(const std::string& number, const int day, const int month, const int year, const subjectC& subjects) :
	number(number),
	day(day),
	month(month),
	year(year),
	subjects(subjects)
{
}

financialDocument::financialDocument(const financialDocument& toCopy) :
	number(toCopy.number),
	day(toCopy.day),
	month(toCopy.month),
	year(toCopy.year),
	subjects(toCopy.subjects)
{
}

std::string financialDocument::getNumber() const noexcept
{
	return number;
}

int financialDocument::getYear() const noexcept
{
	return year;
}

int financialDocument::getMonth() const noexcept
{
	return month;
}

int financialDocument::getDay() const noexcept
{
	return day;
}

std::string financialDocument::getDate() const noexcept
{
	return (std::to_string(day)+'.'+ std::to_string(month) + '.'+ std::to_string(year));
}

subjectC financialDocument::getSubjects() const noexcept
{
	return subjects;
}
