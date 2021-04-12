#pragma once
#include <string>
using namespace std;


struct DataNeeded  //this structure is gonna be used to pass all the data at once to the functions otherwise we need to pass all the parameters separatly
{
	int numberofSectors = 0;
	int sizeofArea = 0;
	int sizeofProvider = 0;
	int sizeofName = 0;
	int numberofProductsToCreate = 50; //50 because in the beggining you need to create 50 products, this will change as the program goes;
	string* areaArray = new string;
	string* providerArray = new string;
	string* nameArray = new string;
	string* areasChoosen = new string;
};


struct ProductSoldRecord  //we need to make a structure for the record of products sold, since they only need the name and price
{                         //and each sector contains an array of this scruture
	string name;
	int price;
};


struct Product
{
	string name; // Name of the product
	string area; // Product area must be equal to Sector area
	string provider; // The provider
	int price = 0; //must be multiple of 2 between 1 and 80 
};


struct Sector
{
	char sectorIdentifier = 0; //user input, we can make so it gets the letter from a char array like ['a', 'b', ...]!
	string area;  //the area that a given sector belongs
	string personInCharge = ""; // user input
	string* listOfProductSold; //the array containing all the products that are sold in the sector
	int maxNumberOfProducts = 0; // Max Number of products in each sector is between 5 and 10
	int quantityOfProducts = 0; //Number of products in the sector in that moment
	ProductSoldRecord* sectorRecord; //array containing the record of products sold in this sector

};


struct Storage
{

};

