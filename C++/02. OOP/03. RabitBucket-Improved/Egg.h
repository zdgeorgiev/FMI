#pragma once

#ifndef _EGG_HEADER_INCLUDED_
#define _EGG_HEADER_INCLUDED_

class Egg
{
public:
	Egg(const char* name, int size);
	Egg();
	Egg(const Egg& rhs);

	~Egg();

	Egg& Egg::operator=(const Egg& rhs);

	Egg operator+(int size) const;
	Egg operator-(int size) const;
	Egg operator*(int size) const;
	Egg operator/(int size) const;

	void operator+=(int size);
	void operator-=(int size);

	bool operator==(const Egg& rhs) const;
	bool operator!=(const Egg& rhs) const;

	bool operator>=(const Egg& rhs) const;
	bool operator>(const Egg& rhs) const;
	bool operator<=(const Egg& rhs) const;
	bool operator<(const Egg& rhs) const;

	void setName(const char* name);
	const char* getName() const;

	void setSize(const int size);
	const int getSize() const;

	void print() const;

private:
	char name[32];
	int size;
};
#endif
