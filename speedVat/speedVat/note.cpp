#include "note.h"

correctingNote::correctingNote(const std::string& number, const int day, const int month, const int year, const subjectC& subjects, const std::string& mistake, const std::string& correct) :
	financialDocument::financialDocument(number, day, month, year, subjects),
	mistake(mistake),
	correct(correct)
{
}

std::string correctingNote::getMistake() const noexcept
{
	return mistake;
}

std::string correctingNote::getCorrect() const noexcept
{
	return correct;
}
