#include "product.h"

product::product(const std::string& name, double netto, double vatWage) :
	name(name),
	netto(netto),
	vatWage(vatWage),
	price(netto* (1.0 + vatWage))
{
}

std::string product::getName() const noexcept
{
	return name;
}

double product::getNetto() const noexcept
{
	return netto;
}

double product::getVatWage() const noexcept
{
	return vatWage;
}

double product::getPrice() const noexcept
{
	return price;
}

void product::setName(const std::string& correct) noexcept
{
	this->name = correct;
}

void product::setNetto(const double correct) noexcept
{
	this->netto = correct;
	this->price = netto * (1.0 + vatWage);
}

void product::setVatWage(const double correct) noexcept
{
	this->vatWage = correct;
	this->price = netto * (1.0 + vatWage);
}

productC::productC() :
	products()
{
}

productC::productC(const productC& copy) :
	products(copy.products)
{
}

bool productC::fromFile(const std::string& fileName) noexcept
{
	std::ifstream file;
	file.open(fileName);
	if (!file)
		return false;

	char buffer[1024];
	while (file.getline(buffer, 1024))
	{
		std::stringstream stream(buffer);
		stream.getline(buffer, 1024, ';');
		std::string name(buffer);
		stream.getline(buffer, 1024, ';');
		double netto = atof(buffer);
		stream.getline(buffer, 1024, ';');
		double vatWage = atof(buffer);
		products.push_back(product(name, netto, vatWage));
	}
	file.close();
	return true;

}

bool productC::fromKeyboard(const std::string& name, const double netto, const double vatWage, const std::string& fileName) noexcept
{
	product newProduct(name, netto, vatWage);
	products.push_back(newProduct);
	return productC::saveData(fileName);
}

void productC::fromBuffer(char buffer[1024]) noexcept
{
	std::stringstream stream(buffer);
	stream.getline(buffer, 1024, ';');
	std::string name(buffer);
	stream.getline(buffer, 1024, ';');
	double netto = atof(buffer);
	stream.getline(buffer, 1024, ';');
	double vatWage = atof(buffer);
	products.push_back(product(name, netto, vatWage));
}

void productC::addNew(const product& newProd)
{
	products.push_back(newProd);
}

bool productC::saveData(const std::string& fileName) const noexcept
{
	std::ofstream file;
	file.open(fileName, std::ios_base::out | std::ios_base::app);
	if (!file)
		return false;
	auto toSave(products.back());
	file << toSave.getName() << ';';
	file << toSave.getNetto() << ';';
	file << toSave.getVatWage() << ';' << std::endl;
	file.close();
	return true;
}

bool productC::saveAll(const int option,  const std::string& fileName) const noexcept
{
	std::ofstream file;
	if (option == 1)
		file.open(fileName);
	else
		file.open(fileName, std::ios_base::out | std::ios_base::app);
	if (!file)
		return false;
	for (auto toSave : products)
	{
		file << toSave.getName() << ';';
		file << toSave.getNetto() << ';';
		file << toSave.getVatWage() << ';' << std::endl;
	}	
	file.close();
	return true;
}

int productC::getSize() const noexcept
{
	return products.size();
}

product productC::getProduct(const int which) const noexcept
{
	return products[which];
}

int productC::search(const std::string& wanted) const noexcept
{
	int i = 0;
	for (auto product : products)
	{
		if (wanted == product.getName())
			return i;
		++i;
	}
	return products.size();
}

void productC::repair(const int option, const int pointer, const std::string& correct, const std::string fileName)
{
	switch (option)
	{
	case 1:
		products[pointer].setName(correct);
		break;
	case 2:
		products[pointer].setNetto(std::stod(correct));
		break;
	case 3:
		products[pointer].setVatWage(std::stod(correct));
		break;
	default: break;
	}
	productC::saveAll(1, fileName);
}

