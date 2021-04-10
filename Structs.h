#pragma once
#include <string>
using namespace std;

struct Product
{
	string areaArray; // Product area must be equal to Sector area
	int areaLenght = 0;
	string nameArray; // Name of the product
	int nameLenght = 0;
	string providerArray; // The provider
	int providerLenght = 0;

	int price = 0; //must be multiple of 2 between 1 and 80 
};

struct Sector
{
	char sectorIdentifier = 0; //user input, we can make so it gets the letter from a char array like ['a', 'b', ...]!
	string personInCharge = ""; // user input
	string sectorArray;
	int sectorLenght = 0;
	string areaArray;
	int areaLenght = 0;
	int maxOfProducts = 0; // Number of products in each sector is between 5 and 10
	int quantityOfProducts = 0;

};

