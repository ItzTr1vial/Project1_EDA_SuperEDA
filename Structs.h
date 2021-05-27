#pragma once
#include <string>
using namespace std;


struct Filepaths  //structure to contain all the files
{ 
	string pathAreas = "";
	string pathProviders = "";
	string pathNames = "";
	string pathSectors = "";
	string pathStorage = "";
	string pathDataNeeded = "";
};



struct DataNeeded  //this structure is gonna be used to pass all the data at once to the functions otherwise we need to pass all the parameters separatly
{
	int numberofSectors = 0; //contains the number of sectors of the supermarket
	int sizeofArea = 0; //contains the size of the array area
	int sizeofProvider = 0; //contains the size of the array provideer
	int sizeofName = 0; //contains the size of the array name
	int sizeofAreasChoosen = 0; //contains the size of the array that has all the areas being used
	int numberofProductsToCreate = 0; //contains the number of products to create in each cycle
	int numProductsInStorage = 0;
	string* areaArray = new string; //array that will keep all the areas from the file
	string* providerArray = new string; //array that will keep all providers from the file
	string* nameArray = new string; //array that will keep all the names from the file
	string* areasChoosenArray = new string; //array that will contain only the areas that are being used
};



struct Product
{
	string name = ""; // Name of the product
	string area = ""; // Product area must be equal to Sector area
	string provider = ""; // The provider
	int price = 0; //must be multiple of 2 between 1 and 80 
	int originalPrice = 0; //will keep the original price given, independent of the discounts
	bool discountState = false; //will keep track if the product is already in discount or not
};



struct Sector
{
	char sectorIdentifier = 0; //user input, we can make so it gets the letter from a char array like ['a', 'b', ...]!
	string area = "";  //the area that a given sector belongs
	string personInCharge = ""; // user input
	int maxNumberOfProducts = 0; // Max Number of products in each sector is between 5 and 10
	int quantityOfProducts = 0; //Number of products in the sector in that moment
	nodeProduct* productsInTheSector; //array with all the products in the sector
	int cycles = 0; //used to keep track of discount cycles
};



struct nodeSector
{
	Sector oneSector;
	nodeSector* next = NULL;
};



struct nodeProduct 
{
	Product oneProduct;
	nodeProduct* next = NULL;
};




