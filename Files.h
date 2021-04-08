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
	
	int maxOfProducts = 0;// Number of products in each sector is between 5 and 10
	int quantityOfProducts = 0 ;

};

void getProductAreaFromFiles(string path,Product* product); // get the respective area of the product
void getProviderFromFile(string path,Product* product); // get the respective provider of the product
void getNamesFromFile(string path,Product* product); // get the respective name of the product
void getSectorAreaFromFiles(string path,Product* product); // get the respetive area of the sector 