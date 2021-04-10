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
	
	int sizeofArea = calculateSizeofFile(pathArea);  //get the size of this file
	int sizeofProvider = calculateSizeofFile(pathProvider);  //get the size of this file
	int sizeofName = calculateSizeofFile(pathName); //get the size of this file

	string* contentofArea = getContentFromFiles(pathArea, sizeofArea);  
	string* contentofProvider = getContentFromFiles(pathProvider, sizeofProvider);
	string* contentofName = getContentFromFiles(pathName, sizeofName);               //this are the string with the content of the files we will be using

	
	return 0;



}