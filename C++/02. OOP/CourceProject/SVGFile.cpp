#include "SVGFile.h"

const string SVGFile::SVG_FILE_HEADER =
		"<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\"http\://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">";

SVGFile::SVGFile(string content) : SVGFile()
{
	this->parseContent(content);
}

SVGFile::SVGFile()
{
	this->figures = new FigureContainer();
}

SVGFile::~SVGFile()
{
	delete this->figures;
}

void SVGFile::printFigures() const
{
	for (int i = 0; i < (*this->figures).getSize(); i++)
	{
		cout << i + 1 << ". ";
		(*this->figures)[i].print();
	}
}

void SVGFile::createFigure(string figure, string params)
{
	if ((*figures).addFigure(figure, params))
	{
		cout << "Successfully created " << figure << " (" << (*this->figures).getSize() << ")" << endl;
	}
}

void SVGFile::eraseFigure(int figureIndex)
{
	(*this->figures).removeAt(figureIndex - 1);
}

void SVGFile::translateFigure(int index, int horizontal, int vertical) const
{
	if ((*this->figures).getSize() == 0)
		cout << "Figures list is empty" << endl;
	if (index < 0 || index >= (*this->figures).getSize())
	{
		cout << "Index " << index + 1 << " is not valid. Should be in range [1..." << (*this->figures).getSize() << "]" << endl;
		return;
	}
	
	(*this->figures)[index].translate(horizontal, vertical);
	cout << "Figure " << index + 1 << " successfully translated" << endl;
}

void SVGFile::translateAllFigures(int horizontal, int vertical) const
{
	for (size_t i = 0; i < (*this->figures).getSize(); i++)
		translateFigure(i, horizontal, vertical);

	cout << "Translated all figures" << endl;
}

void SVGFile::printAllFiguresWithinCircle(const Circle & circle) const
{
	bool isInsideSomething = false;

	for (size_t i = 0; i < (*this->figures).getSize(); i++)
	{
		string figureName = (*this->figures)[i].getName();
		string figureSVGString = (*this->figures)[i].toSVGString();

		bool currentFigureIsInside = false;

		if (!figureName.find("circle"))
		{
			Circle* circle2 = FigureUtils::parseCircle(figureSVGString);
			currentFigureIsInside = GeometryUtils::isInsideCircle(*circle2, circle);
		}
		else if (!figureName.find("rectangle"))
		{
			Rectangle* rectangle = FigureUtils::parseRectangle(figureSVGString);
			currentFigureIsInside = GeometryUtils::isInsideCircle(*rectangle, circle);
		}
		else if (!figureName.find("line"))
		{
			Line* line = FigureUtils::parseLine(figureSVGString);
			currentFigureIsInside = GeometryUtils::isInsideCircle(*line, circle);
		}
		else
			cout << "Invalid figure " << figureName << endl;

		if (currentFigureIsInside)
		{
			cout << i + 1 << ". ";
			(*this->figures)[i].print();
			isInsideSomething = true;
		}
	}
	
	if (!isInsideSomething)
	{
		cout << "No figures are located within ";
		circle.print();
	}
}

void SVGFile::printAllFiguresWithinRectangle(const Rectangle & rectangle) const
{
	bool isInsideSomething = false;

	for (size_t i = 0; i < (*this->figures).getSize(); i++)
	{
		string figureName = (*this->figures)[i].getName();
		string figureSVGString = (*this->figures)[i].toSVGString();

		bool currentFigureIsInside = false;

		if (!figureName.find("circle"))
		{
			Circle* circle = FigureUtils::parseCircle(figureSVGString);
			currentFigureIsInside = GeometryUtils::isInsideRectangle(*circle, rectangle);
		}
		else if (!figureName.find("rectangle"))
		{
			Rectangle* rectangle2 = FigureUtils::parseRectangle(figureSVGString);
			currentFigureIsInside = GeometryUtils::isInsideRectangle(*rectangle2, rectangle);
		}
		else if (!figureName.find("line"))
		{
			Line* line = FigureUtils::parseLine(figureSVGString);
			currentFigureIsInside = GeometryUtils::isInsideRectangle(*line, rectangle);
		}
		else
			cout << "Invalid figure " << figureName << endl;

		if (currentFigureIsInside)
		{
			cout << i + 1 << ". ";
			(*this->figures)[i].print();
			isInsideSomething = true;
		}
	}

	if (!isInsideSomething)
	{
		cout << "No figures are located within ";
		rectangle.print();
	}
}

string SVGFile::getContent() const
{
	string content;

	content.append(SVG_FILE_HEADER).append("\n");

	content.append("<svg>").append("\n");

	for (size_t i = 0; i < (*this->figures).getSize(); i++)
	{
		content.append("\t").append((*this->figures)[i].toSVGString()).append("\n");
	}

	content.append("</svg>").append("\n");

	return content;
}

void SVGFile::parseContent(string content)
{
	string svgFiguresContent = content.substr(content.find("<svg>", 0));

	char* temp = _strdup(svgFiguresContent.c_str());

	char* figures = strtok(temp, "\n");

	//remove the <svg> tag
	figures = strtok(NULL, "\n");

	while (strcmp(figures, "</svg>"))
	{
		string figureSVGString = string(figures);

		// If starts with tab
		if(!figureSVGString.find("\t"))
			figureSVGString = figureSVGString.substr(figureSVGString.find("\t") + 1);

		// Remove the enlosing figure tag
		figureSVGString = figureSVGString.substr(1, figureSVGString.length() - 3);

		if (!figureSVGString.find("circle"))
			(*this->figures).addFigure("circle", figureSVGString);
		else if (!figureSVGString.find("rect"))
			(*this->figures).addFigure("rectangle", figureSVGString);
		else if (!figureSVGString.find("line"))
			(*this->figures).addFigure("line", figureSVGString);
		else
			cout << "Invalid class (Application doesnt handle it)" << endl;

		figures = strtok(NULL, "\n");

		figureSVGString.clear();
	}

	figures = new char[0];
	delete figures;
	delete temp;
	svgFiguresContent.clear();
}
