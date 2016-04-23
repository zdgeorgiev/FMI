#pragma once

#ifndef _BUCKET_UTILS_INCLUDE_
#define	_BUCKET_UTILS_INCLLUDE_

#include "Bucket.h";
#include <iostream>

using namespace std;

class BucketUtils
{
public:
	static Bucket* deserializeFromFile(const char* source);
	static void serializeToFile(const Bucket& bucket, const char* destination);
	static void createReport(const Bucket& bucket, ostream& os);
};

#endif
