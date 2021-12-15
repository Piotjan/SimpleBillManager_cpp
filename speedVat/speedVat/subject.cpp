#include "subject.h"

address::address(const std::string& street, const std::string& numberHouse, const std::string& city, const std::string& postcode) :
	street(street),
	numberHouse(numberHouse),
	city(city),
	postcode(postcode)
{
}

address::address(const address& toCopy) :
	street(toCopy.street),
	numberHouse(toCopy.numberHouse),
	city(toCopy.city),
	postcode(toCopy.postcode)
{
}

std::string address::getStreet() const noexcept
{
	return street;
}

std::string address::getNumberHouse() const noexcept
{
	return numberHouse;
}

std::string address::getCity() const noexcept
{
	return city;
}

std::string address::getPostcode() const noexcept
{
	return postcode;
}

void address::setStreet(const std::string& correct) noexcept
{
	this->street = correct;
}

void address::setNumberHouse(const std::string& correct) noexcept
{
	this->numberHouse = correct;
}

void address::setCity(const std::string& correct) noexcept
{
	this->city = correct;
}

void address::setPostcode(const std::string& correct) noexcept
{
	this->postcode = correct;
}



subject::subject(const std::string& name, const std::string& NIP, const address& _address) :
	name(name),
	NIP(NIP),
	_address(_address)
{
}

subject::subject(const subject& copy) :
	name(copy.name),
	NIP(copy.NIP),
	_address(copy._address)
{
}

std::string subject::getNIP() const noexcept
{
	return NIP;
}

std::string subject::getName() const noexcept
{
	return name;
}

void subject::setName(const std::string& correct) noexcept
{
	this->name = correct;
}

void subject::setNIP(const std::string& correct) noexcept
{
	this->NIP = correct;
}

void subject::setStreet(const std::string& correct) noexcept
{
	_address.setStreet(correct);
}

void subject::setNumberHouse(const std::string& correct) noexcept
{
	_address.setNumberHouse(correct);
}

void subject::setCity(const std::string& correct) noexcept
{
	_address.setCity(correct);
}

void subject::setPostcode(const std::string& correct) noexcept
{
	_address.setPostcode(correct);
}

address subject::getAddress() const noexcept
{
	return _address;
}

subjectC::subjectC() :
	subjects()
{
}

subjectC::subjectC(const subjectC& copy) :
	subjects(copy.subjects)
{
}

bool subjectC::fromFile(const std::string& fileName) noexcept
{
	std::ifstream file;
	file.open(fileName);
	if (!file)
		return false;

	char buffer[1024];
	while (file.getline(buffer, 1024))
	{
		this->fromBuffer(buffer);
	}
	file.close();
	return true;
}

void subjectC::fromBuffer(char buffer[1024]) noexcept
{
	std::stringstream stream(buffer);
	stream.getline(buffer, 1024, ';');
	std::string name(buffer);
	stream.getline(buffer, 1024, ';');
	std::string NIP(buffer);
	stream.getline(buffer, 1024, ';');
	std::string street;
	street = buffer;
	stream.getline(buffer, 1024, ';');
	std::string numberHouse(buffer);
	stream.getline(buffer, 1024, ';');
	std::string city(buffer);
	stream.getline(buffer, 1024, ';');
	std::string postcode(buffer);
	address newAddress(street, numberHouse, city, postcode);
	subjects.push_back(subject(name, NIP, newAddress));
}

bool subjectC::fromKeyboard(const std::string& NIP, const std::string& name, const std::string& street, const std::string& numberHouse, const std::string& city, const std::string& postcode, const std::string fileName)
{
	address newAddr(street, numberHouse, city, postcode);
	subject newSub(NIP, name, newAddr);
	subjects.push_back(newSub);
	return subjectC::saveData(fileName);
}

void subjectC::addNew(const subject& newSub)
{
	subjects.push_back(newSub);
}

bool subjectC::saveData(const std::string& fileName) const noexcept
{
	std::ofstream file;
	file.open(fileName, std::ios_base::out | std::ios_base::app);
	if (!file)
		return false;
	auto toSave(subjects.back());
	file << toSave.getName() << ';';
	file << toSave.getNIP() << ';';
	address saveAddress (toSave.getAddress());
	std::string street(saveAddress.getStreet());
	if (street.length() > 0)
		file << street;
	else
		file << '-';
	file << ';';
	file << saveAddress.getNumberHouse() << ';';
	file << saveAddress.getCity() << ';';
	file << saveAddress.getPostcode() << ';';
	file << std::endl;
	file.close();
	return true;
}

bool subjectC::saveAll(const int option, const std::string& fileName) const noexcept
{
	std::ofstream file;
	if (option == 1)
		file.open(fileName);
	else
		file.open(fileName, std::ios_base::out | std::ios_base::app);
	if (!file)
		return false;
	for (auto toSave : subjects)
	{
		file << toSave.getName() << ';';
		file << toSave.getNIP() << ';';
		address saveAddress(toSave.getAddress());
		std::string street(saveAddress.getStreet());
		if (street.length() > 0)
			file << street;
		else
			file << '-';
		file << ';';
		file << saveAddress.getNumberHouse() << ';';
		file << saveAddress.getCity() << ';';
		file << saveAddress.getPostcode() << ';';
		file << std::endl;
	}
	
	file.close();
	return true;
}

subject subjectC::getOwner() const noexcept
{
	return subjects.front();
}

subject subjectC::getLast() const noexcept
{
	return subjects.back();
}

int subjectC::getSize() const noexcept
{
	return subjects.size();
}

subject subjectC::getSubject(const int pointer) const noexcept
{
	return subjects[pointer];
}

subject subjectC::search(const std::string& wanted) const noexcept
{
	for (auto sub : subjects)
	{
		if (wanted == sub.getNIP())
			return sub;
	}
}

std::vector<int> subjectC::search(const int option, std::string& wanted) const noexcept
{
	std::vector<int> pointers;
	int i = 0;
	switch (option)
	{
	case 1:
		for (auto subject : subjects)
		{
			if (wanted == subject.getName())
				pointers.push_back(i);
			++i;
		}
		break;
	case 2:
		for (auto subject : subjects)
		{
			if (wanted == subject.getNIP())
				pointers.push_back(i);
			++i;
		}
		break;
	default: break;
	}
	return pointers;
}

void subjectC::repair(const int option, const int pointer, const std::string& correct, const std::string& fileName)
{
	switch (option)
	{
	case 1:
		subjects[pointer].setName(correct);
		break;
	case 2:
		subjects[pointer].setNIP(correct);
		break;
	case 3:
		subjects[pointer].setStreet(correct);
		break;
	case 4:
		subjects[pointer].setNumberHouse(correct);
		break;
	case 5:
		subjects[pointer].setCity(correct);
		break;
	case 6:
		subjects[pointer].setPostcode(correct);
		break;
	default: break;
	}
	subjectC::saveAll(1, fileName);
}
