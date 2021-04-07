#pragma once
#include <string>
using namespace std;

struct Product
{
	string area = ""; // Product area must be equal to Sector area
	string name = " "; // Name of the product
	string provider = " "; // The provider 
	int price = 0; // 
};

struct Sector
{
	char sectorIdentifier = 0;
	string personInCharge = " ";
	string array = " ";
	string area = " ";
	// array of products how to implement?? What type of data it will be?
};

void getProductAreaFromFiles(string path); // get the respective area of the product
void getProviderFromFile(string path); // get the respective provider of the product
void getNamesFromFile(string path); // get the respective name of the product
void getSectorAreaFromFiles(string path); // get the respetive area of the sector 