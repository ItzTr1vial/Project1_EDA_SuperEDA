#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "Files.h"
#include "Structs.h"
#include"SuperMarket.h"


using namespace std;



int main() {
	srand(time(NULL));
	locale::global(locale(""));

	Filepaths* supermarketFilepaths = new Filepaths; //structure that will hold all the filepaths
	DataNeeded* internalData = new DataNeeded;  //structure that will contain all the arrays and data that we need to use the functions

	
	//filepaths
	supermarketFilepaths->pathAreas = "areas.txt";
	supermarketFilepaths->pathProviders = "fornecedores.txt";
	supermarketFilepaths->pathNames = "nome.txt";
	supermarketFilepaths->pathSectors = "sectors.txt";
	supermarketFilepaths->pathStorage = "storage.txt";
	supermarketFilepaths->pathDataNeeded = "dataNeeded.txt";


	internalData->sizeofArea = calculateSizeofFile(supermarketFilepaths->pathAreas);  //size of file area
	internalData->sizeofProvider = calculateSizeofFile(supermarketFilepaths->pathProviders);  //size of file providers
	internalData->sizeofName = calculateSizeofFile(supermarketFilepaths->pathNames);  //size of file name
	internalData->areaArray = getContentFromFiles(supermarketFilepaths->pathAreas, internalData->sizeofArea); //content of file area
	internalData->providerArray = getContentFromFiles(supermarketFilepaths->pathProviders, internalData->sizeofProvider); //content of file provider
	internalData->nameArray = getContentFromFiles(supermarketFilepaths->pathNames, internalData->sizeofName); //content of file name
	internalData->numberofSectors = rand() % 5 + 8; //number of sectors the supermarket is going to have
	internalData->numberofProductsToCreate = 50; //number of products to create initialy


	nodeSector* superEDA;
	nodeProduct* Storage;

	superEDA = inicializeSectors(internalData);  //function that inicializes all the sectors
	updateProductNode(internalData, Storage, 50);


	delete[] internalData->areaArray; //since we already choose which areas to use this array is no longer needed
	
	/*
	supermarketStorage->inStorage = inicializeProducts(internalData); //function that inicializes the first 50 products
	supermarketStorage->numProducts = 50; //number of products created in the beggining
	internalData->numberofProductsToCreate = 10; //numbers of products to create each time after that

	menuSupermarket(internalData, superEDA, supermarketStorage, supermarketFilepaths);// Show the menu with the current display of the supermarket

	delete[] superEDA;
	delete supermarketStorage;
	delete internalData;
	delete supermarketFilepaths;

	return 0;

	*/

}



