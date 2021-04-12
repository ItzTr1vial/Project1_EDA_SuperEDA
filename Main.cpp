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

	string pathArea = "D:\\tonif\\Universidade\\EDA\\Projeto\\Project1_EDA_SuperEDA-Develop\\areas.txt";
	string pathProvider = "D:\\tonif\\Universidade\\EDA\\Projeto\\Project1_EDA_SuperEDA-Develop\\fornecedores.txt";
	string pathName = "D:\\tonif\\Universidade\\EDA\\Projeto\\Project1_EDA_SuperEDA-Develop\\nome.txt";

	DataNeeded* interinData = new DataNeeded;  //structure that will contain all the arrays and data that we need to use the functions

	interinData->sizeofArea = calculateSizeofFile(pathArea);  //size of file area
	interinData->sizeofProvider = calculateSizeofFile(pathProvider);  //size of file providers
	interinData->sizeofName = calculateSizeofFile(pathName);  //size of file name
	interinData->areaArray = getContentFromFiles(pathArea, interinData->sizeofArea); //content of file area
	interinData->providerArray = getContentFromFiles(pathProvider, interinData->sizeofProvider); //content of file provider
	interinData->nameArray = getContentFromFiles(pathName, interinData->sizeofName); //content of file name
	interinData->numberofSectors = rand() % 5 + 8; //number of sectors the supermarket is going to have

	Sector* superEDA = new Sector[interinData->numberofSectors]; //array of structures with all the sectors in the supermarket
	Product* allProducts = new Product[50]; //array with the first 50 products

	inicializeSectors(interinData, superEDA);  //function that inicializes all the sectors

	interinData->areasChoosen = getAreasChoosen(interinData, superEDA);  //add the array with the areas choosen in the inicialize Sector function to the structure to be used to create products

	inicializeProducts(interinData, allProducts); //function that inicializes all the products that are going to be used
	
	return 0;

}