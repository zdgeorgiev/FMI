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

	Egg a("q", 1);
	Egg b("b", 2);

	Egg newEgg;
	newEgg = b + 1;
	cout << newEgg.getSize() << endl;

	b += 1;
	cout << b.getSize() << endl;
	cout << (b == newEgg ? "true" : "false") << endl;
	cout << (b + 1 == newEgg ? "true" : "false") << endl;
	b.setName("new");
	cout << (b == newEgg ? "true" : "false") << endl;

	cout << (Egg("abcd", 1) > Egg("abcde", 2) ? "true" : "false") << endl;
	cout << (Egg("abcde", 1) <= Egg("abcde", 2) ? "true" : "false") << endl;

	a += 1;
	a * 10;
	cout << a.getSize() << endl;

	Bucket buckettt;
	buckettt.addEgg(a);
	buckettt.addEgg(b);
	buckettt.addEgg(Egg("dasadsads", 2));
	buckettt.addEgg(Egg("3wqeqqe", 12));
	buckettt.addEgg(Egg("hthfghf", 5435));
	buckettt.addEgg(Egg("zczxcz", 666666666));
	buckettt.addEgg(Egg("yujyyujyj", 662));

	cout << buckettt[0].getName() << " " << buckettt[0].getSize() << endl;
	cout << buckettt[6].getName() << " " << buckettt[6].getSize() << endl;
	cout << buckettt["zczxcz"].getSize() << endl;

	Bucket b1;
	b1.addEgg(Egg("a", 1));
	b1.addEgg(Egg("e", 2));
	b1.addEgg(Egg("c", 3));
	Bucket b2;
	b2.addEgg(Egg("d", 4));
	b2.addEgg(Egg("e", 2));
	b2.addEgg(Egg("f", 6));

	Bucket a2 = b1 % b2;
	a2.print();

	cout << "......................" << endl;

	b2 %= b1;
	b2.print();

	system("pause");
	return 0;
}