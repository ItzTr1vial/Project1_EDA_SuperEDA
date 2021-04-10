#pragma once
#include <string>
using namespace std;

struct Product
{
	string* areaArray ; // Product area must be equal to Sector area
	int areaLenght=0;
	string* nameArray ; // Name of the product
	int nameLenght=0;
	string* providerArray ; // The provider
	int providerLenght = 0;

	int price = 0; //must be multiple of 2 between 1 and 80 
};

struct Sector
{
	char sectorIdentifier = 0;//user input
	string personInCharge="" ; // user input
	string* sectorArray ;
	int sectorLenght = 0;
	string* areaArray ;
	int areaLenght = 0;
	int maxOfProducts = 0;// Number of products in each sector is between 5 and 10
	int quantityOfProducts = 0 ;

};

void getProductAreaFromFiles(Product* product,string path); // get the respective area of the product
void getProductProviderFromFile(Product* product,string path); // get the respective provider of the product
void getProductNamesFromFile(Product* product,string path); // get the respective name of the product
void getSectorAreaFromFiles(Sector* sector,string path); // get the respetive area of the sector 
void getSectorAreaFromFile(Sector* sector,string path );