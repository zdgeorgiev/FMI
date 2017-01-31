#include "FigureUtils.h"

Rectangle* FigureUtils::parseRectangle(string figureSVGString)
{
	string parsedParams = convertSVGStringToStringArray(figureSVGString);
	int x, y, width, height;
	string color;

	const int rectangleParams = 5;
	string paramAsArray[rectangleParams];
	int paramIndex = 0;
	int tokenStartIndex = 0;

	for (size_t i = 0; i < rectangleParams; i++)
	{
		paramAsArray[paramIndex] = parsedParams.substr(tokenStartIndex, parsedParams.find(".", tokenStartIndex + 1) - tokenStartIndex);
		tokenStartIndex = parsedParams.find(".", tokenStartIndex + 1) + 1;
		paramIndex++;
	}

	x = atoi(paramAsArray[0].c_str());
	y = atoi(paramAsArray[1].c_str());
	width = atoi(paramAsArray[2].c_str());
	height = atoi(paramAsArray[3].c_str());
	color = paramAsArray[4];

	for (size_t i = 0; i < rectangleParams; i++)
	{
		paramAsArray[i].clear();
	}

	return new Rectangle(Point(x, y), width, height, color);
}

Circle* FigureUtils::parseCircle(string figureSVGString)
{
	string parsedParams = convertSVGStringToStringArray(figureSVGString);
	int x, y, radius;
	string color;

	const int circleParams = 4;
	string paramAsArray[circleParams];
	int paramIndex = 0;
	int tokenStartIndex = 0;

	for (size_t i = 0; i < circleParams; i++)
	{
		paramAsArray[paramIndex] = parsedParams.substr(tokenStartIndex, parsedParams.find(".", tokenStartIndex + 1) - tokenStartIndex);
		tokenStartIndex = parsedParams.find(".", tokenStartIndex + 1) + 1;
		paramIndex++;
	}

	x = atoi(paramAsArray[0].c_str());
	y = atoi(paramAsArray[1].c_str());
	radius = atoi(paramAsArray[2].c_str());
	color = paramAsArray[3];

	for (size_t i = 0; i < circleParams; i++)
	{
		paramAsArray[i].clear();
	}

	return new Circle(Point(x, y), radius, color);
}

Line* FigureUtils::parseLine(string figureSVGString)
{
	string parsedParams = convertSVGStringToStringArray(figureSVGString);
	int xStart, yStart, xEnd, yEnd;
	string color;

	const int lineParams = 5;
	string paramAsArray[lineParams];
	int paramIndex = 0;
	int tokenStartIndex = 0;

	for (size_t i = 0; i < lineParams; i++)
	{
		paramAsArray[paramIndex] = parsedParams.substr(tokenStartIndex, parsedParams.find(".", tokenStartIndex + 1) - tokenStartIndex);
		tokenStartIndex = parsedParams.find(".", tokenStartIndex + 1) + 1;
		paramIndex++;
	}

	xStart = atoi(paramAsArray[0].c_str());
	yStart = atoi(paramAsArray[1].c_str());
	xEnd = atoi(paramAsArray[2].c_str());
	yEnd = atoi(paramAsArray[3].c_str());
	color = paramAsArray[4];

	for (size_t i = 0; i < lineParams; i++)
	{
		paramAsArray[i].clear();
	}

	return new Line(Point(xStart, yStart), Point(xEnd, yEnd), color);
}

string FigureUtils::convertSVGStringToStringArray(string figureSVGString)
{
	int openPropertyTag = figureSVGString.find("\"");
	int closePropertyTag = figureSVGString.find("\"", openPropertyTag + 1);

	string param = figureSVGString.substr(openPropertyTag + 1, closePropertyTag - openPropertyTag - 1);

	string concatenatedParams;

	while (true)
	{
		concatenatedParams.append(param).append(".");
		openPropertyTag = figureSVGString.find("\"", closePropertyTag + 1);
		closePropertyTag = figureSVGString.find("\"", openPropertyTag + 1);
		param = figureSVGString.substr(openPropertyTag + 1, closePropertyTag - openPropertyTag - 1);

		if (openPropertyTag <= 0)
			break;
	}

	param.clear();

	return concatenatedParams.substr(0, concatenatedParams.length() - 1);
}
