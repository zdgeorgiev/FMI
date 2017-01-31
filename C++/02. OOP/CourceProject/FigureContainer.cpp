#include "FigureContainer.h"

FigureContainer::FigureContainer()
{
	this->figures = new Figure*[5];

	this->containerSize = 2;
	this->elementsCount = 0;
}

FigureContainer::~FigureContainer()
{
	for (size_t i = 0; i < this->getSize(); i++)
	{
		delete this->figures[i];
	}
	delete[] this->figures;
}

Figure& FigureContainer::operator[](int index) const
{
	return *this->figures[index];
}

FigureContainer & FigureContainer::operator=(const FigureContainer & rhs)
{
	if (this != &rhs)
	{
		this->elementsCount = rhs.elementsCount;
		this->containerSize = rhs.containerSize;

		for (size_t i = 0; i < this->getSize(); i++)
		{
			delete this->figures[i];
		}
		delete[] this->figures;

		this->figures = new Figure*[rhs.containerSize];

		for (size_t i = 0; i < this->elementsCount; i++)
		{
			*this->figures[i] = rhs[i];
		}
	}

	return *this;
}

FigureContainer::FigureContainer(const FigureContainer & rhs)
{
	this->elementsCount = rhs.elementsCount;
	this->containerSize = rhs.containerSize;

	for (size_t i = 0; i < this->getSize(); i++)
	{
		delete this->figures[i];
	}
	delete[] this->figures;

	this->figures = new Figure*[rhs.containerSize];

	for (size_t i = 0; i < this->elementsCount; i++)
	{
		*this->figures[i] = rhs[i];
	}
}

bool FigureContainer::addFigure(string shape, string rawParams)
{
	if (elementsCount == containerSize)
		addTwiceMoreSpace();

	if (!strcmp("rectangle", shape.c_str()))
		this->figures[this->elementsCount] = FigureUtils::parseRectangle(rawParams);
	else if (!strcmp("circle", shape.c_str()))
		this->figures[this->elementsCount] = FigureUtils::parseCircle(rawParams);
	else if (!strcmp("line", shape.c_str()))
		this->figures[this->elementsCount] = FigureUtils::parseLine(rawParams);
	else
	{
		cout << "Application do not maintain " << shape << " class" << endl;
		return false;
	}

	this->elementsCount++;
	return true;
}

void FigureContainer::removeAt(int index)
{
	if (this->elementsCount == 0)
		cout << "Figures list is empty" << endl;
	if (index < 0 || index >= elementsCount)
		cout << "Index " << index + 1 << " is not valid. Should be in range [1..." << this->elementsCount << "]" << endl;
	else
	{
		string figureName = (*this->figures[index]).getName();
		cout << "Erased a " << figureName << " (" << index + 1 << ")" << endl;

		//Shift left all remaining elements
		for (size_t j = index + 1; j < this->elementsCount; j++)
		{
			this->figures[j - 1] = this->figures[j];
		}

		this->elementsCount--;

		if (this->elementsCount * 2 < this->containerSize)
			this->removeHalfSpace();
	}
}

void FigureContainer::addTwiceMoreSpace()
{
	Figure** newContainer = new Figure*[this->containerSize * 2];

	for (size_t i = 0; i < this->elementsCount * 2; i++)
	{
		newContainer[i] = new Figure();
	}

	for (size_t i = 0; i < this->elementsCount; i++)
	{
		newContainer[i] = this->figures[i];
	}

	this->figures = newContainer;
	this->containerSize *= 2;
}

void FigureContainer::removeHalfSpace()
{
	Figure** newContainer = new Figure*[this->containerSize / 2];

	for (size_t i = 0; i < this->elementsCount; i++)
	{
		newContainer[i] = this->figures[i];
	}

	this->figures = newContainer;
	this->containerSize /= 2;
}

int FigureContainer::getSize() const
{
	return this->elementsCount;
}
