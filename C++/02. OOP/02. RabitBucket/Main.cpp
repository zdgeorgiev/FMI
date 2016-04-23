#include <iostream>

#include "Bucket.h"
#include "Egg.h"
#include "BucketUtils.h"

using namespace std;

int main()
{
	Bucket* b = new Bucket("pesho");
	
	if (!b)
	{
		delete b;
		return 1;
	}

	//Add four eggs
	(*b).addEgg(Egg("first", 1));
	(*b).addEgg(Egg("second", 2222));
	(*b).addEgg(Egg("third", 3));
	(*b).addEgg(Egg("fourth", 4));

	// Should be 4
	cout << "Size : " << (*b).getSize() << endl;

	//Add one more
	(*b).addEgg(Egg("fifth", 5));

	// Should be 8
	cout << "Size : " << (*b).getSize() << endl;

	// Remove 2
	(*b).removeEgg("first");
	(*b).removeEgg("fifth");

	// Should be 4
	cout << "Size : " << (*b).getSize() << endl;

	// Should print only 2,3,4
	cout << "=========Bucket=========" << endl;
	(*b).print();

	cout << "=========REPORT BEFORE SERIALIZATION=========" << endl;
	BucketUtils::createReport((*b), cout);

	//Save the bucket as binary
	char fileName[100];
	strcpy(fileName, (*b).getOwner());
	strcat(fileName, "_serialized.dat");
	BucketUtils::serializeToFile((*b), fileName);

	//Delete the bucket
	delete b;

	//Load the bucket from the binary
	Bucket* deserialized = BucketUtils::deserializeFromFile("pesho_serialized.dat");

	cout << "=========REPORT AFTER DESERIALIZATION=========" << endl;

	//Create report for the bucket
	BucketUtils::createReport((*deserialized), cout);

	delete deserialized;

	system("pause");
	return 0;
}