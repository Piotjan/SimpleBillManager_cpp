#include "vat.h"

VatInvoice::VatInvoice(const std::string& number, const int day, const int month, const int year, const subjectC& subjects, const productC& products) :
	financialDocument::financialDocument(number, day, month, year, subjects),
	products(products),
	notes()
{
}

VatInvoice::VatInvoice(const VatInvoice& toCopy) :
	financialDocument::financialDocument(toCopy),
	products(toCopy.products),
	notes(toCopy.notes)
{
}

productC VatInvoice::getProducts() const noexcept
{
	return products;
}

std::vector<correctingNote> VatInvoice::getNotes() const noexcept
{
	return notes;
}

int VatInvoice::getNotesAmount() const noexcept
{
	return notes.size();
}

void VatInvoice::setNote(const correctingNote& note) noexcept
{
	notes.push_back(note);
}

vatInvoiceC::vatInvoiceC() :
	bills()
{
}

bool vatInvoiceC::fromFile(const std::string& fileName) noexcept
{
	std::ifstream file;
	file.open(fileName);
	if (!file)
		return false;

	char buffer[1024];
	while (file.getline(buffer, 1024))
	{
		std::string number(buffer);
		file.getline(buffer, 1024);
		std::stringstream stream(buffer);
		stream.getline(buffer, 1024, ';');
		int day = atoi(buffer);
		stream.getline(buffer, 1024, ';');
		int month = atoi(buffer);
		stream.getline(buffer, 1024, ';');
		int year = atoi(buffer);

		file.getline(buffer, 1024);
		subjectC subjects;
		subjects.fromBuffer(buffer);
		file.getline(buffer, 1024);
		subjects.fromBuffer(buffer);

		productC products;
		file.getline(buffer, 1024);
		while (buffer[0] != '&')
		{
			products.fromBuffer(buffer);
			file.getline(buffer, 1024);
		}
		bills.push_back(VatInvoice(number, day, month, year, subjects, products));
		file.getline(buffer, 1024);
		if (buffer[0] == '&')
		{
			file.getline(buffer, 1024);
			while (buffer[0] != '&')
			{
				number = buffer;
				file.getline(buffer, 1024);
				std::stringstream stream(buffer);
				stream.getline(buffer, 1024, ';');
				day = atoi(buffer);
				stream.getline(buffer, 1024, ';');
				month = atoi(buffer);
				stream.getline(buffer, 1024, ';');
				year = atoi(buffer);

				file.getline(buffer, 1024);
				subjectC subjectsNote;
				subjectsNote.fromBuffer(buffer);
				file.getline(buffer, 1024);
				subjectsNote.fromBuffer(buffer);

				file.getline(buffer, 1024);
				stream.str(buffer);
				stream.getline(buffer, sizeof(buffer), ';');
				std::string mistake(buffer);
				stream.getline(buffer, 1024, ';');
				std::string correct(buffer);
				correctingNote newNote(number, day, month, year, subjectsNote, mistake, correct);
				bills.back().setNote(newNote);
				file.getline(buffer, 1024);
			}
			file.getline(buffer, 1024);
		}
	}
	file.close();
	return true;
}

bool vatInvoiceC::fromKeyboard(const subjectC& subjects, const productC& products, const std::string& fileName)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	int day = st.wDay;
	int month = st.wMonth;
	int year = st.wYear;
	int order = bills.size();
	std::string number("FV " + std::to_string(year) + '/' + std::to_string(month) + '/' + std::to_string(day) + '/' + std::to_string(order));
	VatInvoice newBill(number, day, month, year, subjects, products);
	bills.push_back(newBill);
	return vatInvoiceC::saveData(fileName);
}

bool vatInvoiceC::saveData(const std::string& fileName) const noexcept
{
	std::ofstream file;
	file.open(fileName, std::ios_base::out | std::ios_base::app);
	if (!file)
		return false;
	VatInvoice toSave(bills.back());
	file << toSave.getNumber() << std::endl;
	file << toSave.getDay() << ';' << toSave.getMonth() << ';' << toSave.getYear() << ';' << std::endl;
	subjectC subjects(toSave.getSubjects());
	subjects.saveAll(2, fileName);
	productC products(toSave.getProducts());
	products.saveAll(2, fileName);
	file << '&' << std::endl << '@' << std::endl;
	file.close();
	return true;
}

bool vatInvoiceC::saveAll(const std::string& fileName) const noexcept
{
	std::ofstream file;
	file.open(fileName);
	file.close();
	file.open(fileName, std::ios_base::out | std::ios_base::app);
	if (!file)
		return false;
	for (auto toSave : bills)
	{
		file << toSave.getNumber() << std::endl;
		file << toSave.getDay() << ';' << toSave.getMonth() << ';' << toSave.getYear() << ';' << std::endl;
		subjectC subjects(toSave.getSubjects());
		subjects.saveAll(2, fileName);
		productC products(toSave.getProducts());
		products.saveAll(2, fileName);
		file << '&' << std::endl;
		std::vector<correctingNote> noteSave(toSave.getNotes());
		if (noteSave.size() > 0)
		{
			file << '&' << std::endl;
			for (auto note : noteSave)
			{
				file << note.getNumber() << std::endl;
				file << note.getDay() << ';' << note.getMonth() << ';' << note.getYear() << ';' << std::endl;
				subjectC subjects(note.getSubjects());
				subjects.saveAll(2, fileName);
				file << note.getMistake() << ';' << note.getCorrect() << ';' << std::endl;
			}
			file << '&' << std::endl;
		}
		file << '@' << std::endl;
	}
	file.close();
	return true;
}

std::vector<int> vatInvoiceC::search(const int option, const std::string& wanted) const noexcept
{
	std::vector<int> positionBills;
	int i = 0;
	switch (option)
	{
	case 1:
	{
		for (auto bill : bills)
		{
			if (wanted == bill.getNumber())
				positionBills.push_back(i);
			++i;
		}
		break;
	}
	case 2:
	{
		for (auto bill : bills)
		{
			subjectC subjects(bill.getSubjects());
			subject search(subjects.getLast());
			if (wanted == search.getNIP())
				positionBills.push_back(i);
			++i;
		}
		break;
	}
	case 3:
	{
		for (auto bill : bills)
		{
			if (wanted == bill.getDate())
				positionBills.push_back(i);
			++i;
		}
		break;
	}
	default: break;
	}
	return positionBills;
}

VatInvoice vatInvoiceC::getBill(const int which) const noexcept
{
	return bills[which];
}

void vatInvoiceC::addNote(const std::string& vatNumber, const subjectC& subjects, const std::string& mistake, const std::string& correct, const std::string& fileName) noexcept
{
	std::vector<int> pointers(vatInvoiceC::search(1, vatNumber));
	int pointer = pointers[0];
	SYSTEMTIME st;
	GetSystemTime(&st);
	int day = st.wDay;
	int month = st.wMonth;
	int year = st.wYear;
	int order = bills[pointer].getNotesAmount();
	std::string number("NK " + std::to_string(year) + '/' + std::to_string(month) + '/' + std::to_string(day) + '/' + std::to_string(order));
	bills[pointer].setNote(correctingNote(number, day, month, year, subjects, mistake, correct));
	vatInvoiceC::saveAll(fileName);
}

int vatInvoiceC::getSize() const noexcept
{
	return bills.size();
}
