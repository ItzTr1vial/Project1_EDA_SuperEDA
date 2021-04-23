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
 
	string pathArea = "D:\\tonif\\Universidade\\EDA\\Projeto\\areas.txt"; //"areas.txt";
	string pathProvider = "D:\\tonif\\Universidade\\EDA\\Projeto\\fornecedores.txt"; //"fornecedores.txt";
	string pathName = "D:\\tonif\\Universidade\\EDA\\Projeto\\nome.txt"; //"nome.txt";


	DataNeeded* interinData = new DataNeeded;  //structure that will contain all the arrays and data that we need to use the functions
	
	


	interinData->sizeofArea = calculateSizeofFile(pathArea);  //size of file area
	interinData->sizeofProvider = calculateSizeofFile(pathProvider);  //size of file providers
	interinData->sizeofName = calculateSizeofFile(pathName);  //size of file name
	interinData->areaArray = getContentFromFiles(pathArea, interinData->sizeofArea); //content of file area
	interinData->providerArray = getContentFromFiles(pathProvider, interinData->sizeofProvider); //content of file provider
	interinData->nameArray = getContentFromFiles(pathName, interinData->sizeofName); //content of file name
	interinData->numberofSectors = rand() % 5 + 8; //number of sectors the supermarket is going to have

	Sector* superEDA = new Sector[interinData->numberofSectors]; //array of structures with all the sectors in the supermarket
	Storage* supermarketStorage = new Storage;
	

	inicializeSectors(interinData, superEDA);  //function that inicializes all the sectors
	interinData->areasChoosen = getAreasChoosen(interinData, superEDA);  //add the array with the areas choosen in the inicialize Sector function to the structure to be used to create products
	
	supermarketStorage->inStorage = inicializeProducts(interinData); //function that inicializes the first 50 products
	supermarketStorage->numProducts = 50;
	interinData->numberofProductsToCreate = 10;
	


	menuSupermarket(interinData, superEDA, supermarketStorage);// Show the menu with the current display of the supermarket

	return 0;

}



