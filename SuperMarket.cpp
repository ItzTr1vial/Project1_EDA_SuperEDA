#include<iostream>
#include<string>
#include<stdlib.h>
#include"Files.h"
#include"Structs.h"

using namespace std;


void inicializeSectors(const DataNeeded* interinData, Sector* superEDA) //using the const just for precaution to not change the original values 
{                                                                      
	char characters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};    // array of characters that are going to give the sectors their letters
	string nome;

	for (int i = 0; i < interinData->numberofSectors; i++)
	{
		superEDA[i].sectorIdentifier = characters[i];  //giving the sectores their letters
		superEDA[i].maxNumberOfProducts = rand() % 6 + 5;  //giving a max numbers of products between 5 and 10 to each sector

		cout << "Digite o nome do responsavel da seccao " << superEDA[i].sectorIdentifier << ": ";
		getline(cin, nome);
		superEDA[i].personInCharge = nome;  //asking the user for the name of the responsable for each section

		superEDA[i].area = interinData->areaArray[rand() % interinData->sizeofArea];  //going to the array area and choosing a random area for each sector
	}

}

string* getAreasChoosen(const DataNeeded* interinData, const Sector* superEDA)
{
	string* areasChoosen = new string[interinData->numberofSectors];  //string that will contain the areas choosen

	for (int i = 0; i < interinData->numberofSectors; i++)
	{
		areasChoosen[i] = superEDA[i].area;
	}

	return areasChoosen;
}



void inicializeProducts(const DataNeeded* interinData, Product* allProducts)
{

	for (int i = 0; i < interinData->numberofProductsToCreate; i++)
	{
		allProducts[i].name = interinData->nameArray[rand() % interinData->sizeofName];  //chooses a random name from the array and gives it to the product
		allProducts[i].area = interinData->areasChoosen[rand() % interinData->numberofSectors];  //chooses a random area only from the areas that have already been selected for the sectors
		allProducts[i].provider = interinData->providerArray[rand() % interinData->sizeofProvider];  //chooses a random provider from the array and gives it to the product

		int price = rand() % 80 + 1;  //gives a random number between 1 and 80
		
		if (price % 2 != 0)  //if that number is and odd number it adds one so it becomes a multiple of 2
			price += 1;

		allProducts[i].price = price; //gives that price for that product
	}
}


