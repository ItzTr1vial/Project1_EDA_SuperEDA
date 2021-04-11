#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "Files.h"
#include "Structs.h"

using namespace std;

int main() {
	srand(time(NULL));
	locale::global(locale(""));

	//Numbers of sectors between 8 and 12 -> dyanmic array of sectors
	// Number of products between 5 and 10


	string pathArea ="D:\\tonif\\Universidade\\EDA\\Projeto\\Project1_EDA_SuperEDA-Develop\\areas.txt" ;
	string pathProvider = "D:\\tonif\\Universidade\\EDA\\Projeto\\Project1_EDA_SuperEDA-Develop\\fornecedores.txt";
	string pathName = "D:\\tonif\\Universidade\\EDA\\Projeto\\Project1_EDA_SuperEDA-Develop\\nome.txt";

	DataNeeded* interinData = new DataNeeded;  //structure that will contain all the arrays and data that we need to use the functions

	interinData->SizeofArea = calculateSizeofFile(pathArea);  //size of file area
	interinData->SizeofProvider = calculateSizeofFile(pathProvider);  //size of file providers
	interinData->SizeofName = calculateSizeofFile(pathName);  //size of file name
	interinData->areaArray = getContentFromFiles(pathArea, interinData->SizeofArea); //content of file area
	interinData->providerArray = getContentFromFiles(pathProvider, interinData->SizeofProvider); //content of file provider
	interinData->nameArray = getContentFromFiles(pathName, interinData->SizeofName); //content of file name

	return 0;

}