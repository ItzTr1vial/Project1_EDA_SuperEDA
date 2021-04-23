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
		superEDA[i].maxNumberOfProducts = rand() % 6 + 5;  //giving a max numbers of products between 5 and 10 to each
		superEDA[i].productsInTheSector = new Product[superEDA[i].maxNumberOfProducts];
		superEDA[i].quantityOfProducts = 0;
		superEDA[i].sectorRecord = new ProductSoldRecord[1];
		superEDA[i].sectorRecord[0].name = " ";
		superEDA[i].sectorRecord[0].price = 0;
		superEDA[i].quantityOfProductsSold = 0;

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



Product* inicializeProducts(const DataNeeded* interinData)
{
	Product* allProducts = new Product[interinData->numberofProductsToCreate];
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
	
	return allProducts;
}



void display(const DataNeeded* interinData, Sector* SuperEDA, Storage* supermarketStorage) //function that displays what is needed
{
	
	cout << setfill(' ') << endl; //uses spaces to fill 

	for (int i = 0; i < interinData->numberofSectors; i++) //displays the sectors of the supermarket
	{
		cout << left << setw(8) << "Sector: " << left << setw(4) << SuperEDA[i].sectorIdentifier << " | " 
			 << left << setw(13) << "Responsavel: " << left << setw(22) << SuperEDA[i].personInCharge << " | " 
			 << left << setw(12) << "Capacidade: " << left << setw(5) << SuperEDA[i].maxNumberOfProducts << " | " 
			 << left << setw(10) << "Produtos: " << left << setw(5) << SuperEDA[i].quantityOfProducts << " | "  
			 << left << setw(6) << "Area: " << left << setw(20) << SuperEDA[i].area << endl;

		for (int j = 0; j < SuperEDA[i].quantityOfProducts; j++) //displays the products inside those sectors
		{
			cout << left << setw(8) << "Produto: " << left << setw(20) <<SuperEDA[i].productsInTheSector[j].name << " | " 
				 << left << setw(7) << "Preço: " << left << setw(4) << SuperEDA[i].productsInTheSector[j].price << endl;
		}

		cout << "-------------------------------------------------------------------------------------------------------------------------" <<  endl;
	}

	cout << "Armazem: " << endl;

	for (int i = 0; i < supermarketStorage->numProducts; i++) //displays the products in storage
	{
		cout << left << setw(6) << "Nome: " << left << setw(22) << supermarketStorage->inStorage[i].name << " | "
			 << left << setw(6) << "Area: " << left << setw(20) << supermarketStorage->inStorage[i].area << " | "
			 << left << setw(7) << "Preço: " << left << setw(4) <<supermarketStorage->inStorage[i].price <<  endl;
	}
}



void addProductsToRecord(Product productsold, Sector* superEDA, int x) //function that adds the products to the record of products sold of a given sector
{
	ProductSoldRecord* internRecord = new ProductSoldRecord[superEDA[x].quantityOfProductsSold + 1]; //internal array
	
	for (int i = 0; i < superEDA[x].quantityOfProductsSold; i++) //loop to pass the products already stored in the original array to this onw
	{
		internRecord[i] = superEDA[x].sectorRecord[i];
	}

	internRecord[superEDA[x].quantityOfProductsSold].name = productsold.name; //adds that products name to the internal array
	internRecord[superEDA[x].quantityOfProductsSold].price = productsold.price; //adds the products price to the internal array

	delete[] superEDA[x].sectorRecord; //dealocates the memory on the original vector

	superEDA[x].sectorRecord = new ProductSoldRecord[superEDA[x].quantityOfProductsSold]; //alocates the memory with the updated number of products sold
	superEDA[x].sectorRecord = internRecord; //passes the information of the internal array to the original array
	superEDA[x].quantityOfProductsSold++; //increases the number of products sold

}



Product* removeProductFromSector(Sector* superEDA, int x)
{
	int cont1 = 0, cont2 = superEDA[x].quantityOfProductsSold; //conts needed 
	Product* internProduct = new Product[superEDA[x].maxNumberOfProducts]; //creates a temporary array

	for (int i = 0; i < superEDA[x].quantityOfProducts; i++) //loops through all the products
	{
		if (rand() % 3 != 0) //has a 75% chance of keeping the product, its the same as 25% of being sold
		{
			internProduct[cont1] = superEDA[x].productsInTheSector[i]; // if the product is kept it is put in the internal array
			cont1 += 1; 
		}
		else
		{
			addProductsToRecord(superEDA[x].productsInTheSector[i], superEDA, x); //if the product is not kept it is added to the record of products sold
		}
	}
	
	superEDA[x].quantityOfProducts = cont1; //updates the number of products in the sector
	return internProduct; //returns the updates array with all the products

}



void verifyProductSell(Sector* superEDA, const DataNeeded* interinData) //function that will verify all the products sold
{
	for (int i = 0; i < interinData->numberofSectors; i++) //loop to see all the sector
	{
		superEDA[i].productsInTheSector = removeProductFromSector(superEDA, i); //calls the function that will check all the products in this sector
	}
}



void createNewProducsts(Storage* supermarketStorage, const DataNeeded* interinData) //function to create new products
{

	Product* internManagement = new Product[interinData->numberofProductsToCreate + supermarketStorage->numProducts]; //internal array that will receive all the products in storage
	Product* internManagement1 = new Product[interinData->numberofProductsToCreate]; //internal array that will receive all the new Products
	int cont = 0, cont1 = supermarketStorage->numProducts; //conts needed


	for (int i = 0; i < cont1; i++) //loop to take all the products out of storage
	{
		internManagement[i] = supermarketStorage->inStorage[i];
	}
	
	internManagement1 = inicializeProducts(interinData); //to create the 10 new Products

	delete[] supermarketStorage->inStorage; //dealocates the memory in the storage
	supermarketStorage->inStorage = new Product[supermarketStorage->numProducts + interinData->numberofProductsToCreate]; //allocates the storage necessary 
	supermarketStorage->inStorage = internManagement; //receives the elements from the first array

	for (int i = supermarketStorage->numProducts; i < cont1 + interinData->numberofProductsToCreate; i++)
	{
		supermarketStorage->inStorage[supermarketStorage->numProducts++] = internManagement1[cont++]; //receives the elements from the second array
	}

}



void assignProductsToSectors(Sector* superEDA, Storage* supermarketStorage, const DataNeeded* interinData)
{
	int cont1 = 0, cont2 = 0, cont3 = 0;  //conts used in this function
	bool sair = false; //variable for exiting
	Product* internalproduct = new Product[supermarketStorage->numProducts]; //array for internal use

	do
	{
		for (int i = 0; i < interinData->numberofSectors; i++) //used for checking in all the sectors
		{
			if (superEDA[i].area == supermarketStorage->inStorage[cont2].area) //checks if the product area is equal to the sector area
			{
				if (superEDA[i].maxNumberOfProducts > superEDA[i].quantityOfProducts) // check if there is space in that sector
				{
					superEDA[i].productsInTheSector[superEDA[i].quantityOfProducts] = supermarketStorage->inStorage[cont2]; //adds the product to the sector
					superEDA[i].quantityOfProducts += 1; //increases the quantity of products of that sector
					cont1 += 1;
					cont2 += 1;
					break;
				}
			}

			if (i == interinData->numberofSectors-1)  //if it has checked all the sectors and didn´t find one available passes to the next product
			{
				internalproduct[cont3] = supermarketStorage->inStorage[cont2]; //passes that product to an internal array
				cont2 += 1;
				cont3 += 1;
			}

			if (cont2 == supermarketStorage->numProducts) //if it has checked all the products it gives the instruction to exit
			{
				sair = true;
				break;
			}
		}


	} while (cont1 != 10 && !sair);


	for (int i = cont2; i < supermarketStorage->numProducts; i++) //deletes the products that have been retrived from storage
	{
		internalproduct[cont3] = supermarketStorage->inStorage[i];
		cont3 += 1;
	}

	delete[] supermarketStorage->inStorage; //deletes the storage (since it has already been passes to the internal storage to work with)

	supermarketStorage->inStorage = internalproduct; //receives the storage with all the updates
	supermarketStorage->numProducts -= cont1; //takes the number of products that have been taken out

}

 

void menuSupermarket(const DataNeeded* interinData, Sector* superEDA, Storage* supermarketStorage) { // it will need debug on the switch case

	while (true)
	{
		display(interinData, superEDA, supermarketStorage); //function that displays the things

		char option;
		cout << "Insira a seua opção:" << endl;
		cout << "(s)eguinte" << setfill('*') << setw(15) << "(g)estão" << endl;
		cout << "Selecione a sua opção" << endl;
		cin >> option;
		switch (option)
		{
		case 's':
			verifyProductSell(superEDA, interinData);
			createNewProducsts(supermarketStorage, interinData);
			assignProductsToSectors(superEDA, supermarketStorage, interinData);
			break;
		case 'g':
			//management menu
			break;

		default:
			cout << "Inseriu uma opção inválida";
			break;

		}
	}
}