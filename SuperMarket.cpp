#include<iostream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include "SuperMarket.h"
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

		cout << "Digite o nome do responsável da secção " << superEDA[i].sectorIdentifier << ": ";
		getline(cin, nome);
		
			if (nome == "\0") { // in case the inserted name equals an empty string.
				cout << "Insira novamente um nome válido!" << endl;
				getline(cin, nome);
			}
		
		superEDA[i].personInCharge = nome;  //asking the user for the name of the responsable for each section

		superEDA[i].area = interinData->areaArray[rand() % interinData->sizeofArea];  //going to the array area and choosing a random area for each sector
		
	}
	system("CLS");
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
void initializeStorage(Product* allProducts) { // give 50 random products to the store, WILL NEED TO BE WORKED LATER BECAUSE OF THE RESTRICTIONS NWO WE HAVE A BASE I guess

	cout << "\nArmazém\n" <<endl;
	
	for (int i = 0; i < 50; i++)
	{
		cout << "Produto: " << allProducts[i].name << " | " <<
			"Área: " << allProducts[i].area << " | " <<
			"Preço: " << allProducts[i].price << endl;

	}
}
 
void menuSupermarket(const DataNeeded* interinData, Sector* superEda, Product* allProducts) { // it will need debug on the sewitch case


	for (int i = 0; i < interinData->numberofSectors; i++) {
		cout << "Sector:" << setw(3) << superEda[i].sectorIdentifier << setw(10) << " | " <<
			"Responsável:" << setw(3) << superEda[i].personInCharge << setw(10) << " | " <<
			"Capacidade:" << setw(3) << superEda[i].maxNumberOfProducts << setw(10) << " | " <<
			"Produtos:" << setw(3) << superEda[i].quantityOfProducts << setw(10) << "| " <<
			"Área:" << setw(3) << superEda[i].area << endl;
		// atribution from storage so sector missing
	}
	bool left = false;
	while (!left)
	{
		initializeStorage(allProducts); // i think its working yeahhh
		char option;
		cout << "Insira a seua opção:" << endl;
		cout << "(s)eguinte" << setfill('*') << setw(15) << "(g)estão" << endl;
		cout << "Selecione a sua opção" << endl;
		cin >> option;
		switch (option)
		{
		case 's':
			// buy funtions must be done
			break;
		case 'g':
			//management menu
			break;

		default:
			cout << "Inseriu uma opção inválida";
			left = true;
			break;

		}
	}
}

