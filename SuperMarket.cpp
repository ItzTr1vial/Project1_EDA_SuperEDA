#include<iostream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include "SuperMarket.h"
#include"Files.h"
#include"Structs.h"
#include"Management.h"



using namespace std;


Sector createOneSector(DataNeeded* internalData)
{
	Sector oneSector;
	
	static int sectorsAdded = 0;

	char characters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L' };    // array of characters that are going to give the sectors their letters
	string nome;
	char c = ' ';
	int indexArea = rand() % internalData->sizeofArea;



	oneSector.sectorIdentifier = characters[sectorsAdded++];
	oneSector.maxNumberOfProducts = rand() % 6 + 5;
	oneSector.quantityOfProducts = 0;
	oneSector.cycles = 0;
	oneSector.productsInTheSector = new nodeProduct;

	bool sair = false;

	do
	{
		cout << "Digite o nome do responsável da secção " << oneSector.sectorIdentifier << ": ";
		getline(cin, nome);

		if (nome != "\0") // in case the inserted name equals an empty string.
		{
			sair = true;
		}
		else
		{
			cout << "Não pode deixar este espaço em branco! " << endl;
			cout << " " << endl;
		}

	} while (!sair);


	oneSector.personInCharge = nome;  //adds the name given to the sector

	oneSector.area = internalData->areaArray[indexArea];  //going to the array area and choosing a random area for each sector
	internalData->areasChoosenArray[sectorsAdded] = internalData->areaArray[indexArea];

	system("cls");

	return oneSector;
}



nodeSector* inicializeSectors(DataNeeded* internalData) 
{   
	nodeSector* n;
	nodeSector* t;
	nodeSector* h;

	n = new nodeSector;
	t = n;
	h = n;

	for (int i = 0; i < internalData->numberofSectors; i++)
	{
		if (i == 0)
		{
			n->oneSector = createOneSector(internalData);
			n->next = NULL;
		}
		else
		{
			n = new nodeSector;
			n->oneSector = createOneSector(internalData);
			n->next = NULL;
			t->next = n;
			t = t->next;
		}
	}

	return h;
	
}



Product inicializeProducts(const DataNeeded* internalData)
{
	Product oneProduct;
	
	
	oneProduct.name = internalData->nameArray[rand() % internalData->sizeofName];  //chooses a random name from the array and gives it to the product
	oneProduct.area = internalData->areasChoosenArray[rand() % internalData->numberofSectors];  //chooses a random area only from the areas that have already been selected for the sectors
	oneProduct.provider = internalData->providerArray[rand() % internalData->sizeofProvider];  //chooses a random provider from the array and gives it to the product

	int price = rand() % 80 + 1;  //gives a random number between 1 and 80
		
	if (price % 2 != 0)  //if that number is and odd number it adds one so it becomes a multiple of 2
		price += 1;

	oneProduct.price = price; //gives that price for that product
	oneProduct.originalPrice = price; //holds the original price given in case of modification
		
	
	
	return oneProduct;
}



void updateProductNode(DataNeeded* internalData, nodeProduct* oneProductNode, int numberOfProductstoAdd)
{
	nodeProduct* n;

	for (int i = 0; i < numberOfProductstoAdd; i++)
	{
		if (oneProductNode == NULL)
		{
			nodeProduct* n = new nodeProduct;
			n->oneProduct = inicializeProducts(internalData);
			n->next = oneProductNode;
			oneProductNode = n;
		}
		else
		{
			nodeProduct* n = new nodeProduct;
			n->oneProduct = inicializeProducts(internalData);
			
			nodeProduct* t = oneProductNode;

			while (t->next == NULL)
			{
				t = t->next;
			}

			t->next = n;
			n->next = NULL;
		}
	}
}


/*
void display(const DataNeeded* internalData, Sector* SuperEDA, Storage* supermarketStorage) //function that displays what is needed
{
	
	cout << setfill(' ') << endl; //uses spaces to fill 

	for (int i = 0; i < internalData->numberofSectors; i++) //displays the sectors of the supermarket
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

	cout << " " << endl;
	cout << " " << endl;
	cout << "Armazem: " << endl;
	cout << " " << endl;

	for (int i = 0; i < supermarketStorage->numProducts; i++) //displays the products in storage
	{
		cout << left << setw(6) << "Nome: " << left << setw(22) << supermarketStorage->inStorage[i].name << " | "
			 << left << setw(6) << "Area: " << left << setw(20) << supermarketStorage->inStorage[i].area << " | "
			 << left << setw(7) << "Preço: " << left << setw(4) <<supermarketStorage->inStorage[i].price <<  endl;
	}

	cout << " " << endl;
	cout << " " << endl;
}



/*void addProductsToRecord(Product productsold, Sector* superEDA, int x) //function that adds the products to the record of products sold of a given sector
{
	ProductSoldRecord* internRecord = new ProductSoldRecord[superEDA[x].quantityOfProductsSold + 1]; //internal array
	
	for (int j = 0; j < superEDA[x].quantityOfProductsSold; j++) //loop to pass the products already stored in the original array to this onw
	{
		internRecord[j] = superEDA[x].sectorRecord[j];
	}

	internRecord[superEDA[x].quantityOfProductsSold].name = productsold.name; //adds that products name to the internal array
	internRecord[superEDA[x].quantityOfProductsSold].price = productsold.price; //adds the products price to the internal array

	delete[] superEDA[x].sectorRecord; //dealocates the memory on the original vector

	superEDA[x].sectorRecord = new ProductSoldRecord[superEDA[x].quantityOfProductsSold]; //alocates the memory with the updated number of products sold
	superEDA[x].sectorRecord = internRecord; //passes the information of the internal array to the original array
	superEDA[x].quantityOfProductsSold++; //increases the number of products sold

}




void verifyProductSell(Sector* superEDA, const DataNeeded* internalData) //function that will verify all the products sold
{
	for (int i = 0; i < internalData->numberofSectors; i++) //loop to see all the sector
	{
		int cont1 = 0; //conts needed 
		Product* internProduct = new Product[superEDA[i].maxNumberOfProducts]; //creates a temporary array

		for (int j = 0; j < superEDA[i].quantityOfProducts; j++) //loop that goes through all products
		{
			if (rand() % 3 == 0) //product has a 25%chance of being sold
			{
				//addProductsToRecord(superEDA[i].productsInTheSector[j], superEDA, i); 
			}
			else
			{
				internProduct[cont1] = superEDA[i].productsInTheSector[j];
				cont1 += 1;
			}
			
		}

		delete[] superEDA[i].productsInTheSector;
		superEDA[i].quantityOfProducts = cont1; //updates the number of products in the sector

		superEDA[i].productsInTheSector = new Product[superEDA[i].maxNumberOfProducts];

		for (int j = 0; j < superEDA[i].quantityOfProducts; j++) //updates the products in the sector
		{
			superEDA[i].productsInTheSector[j] = internProduct[j];
		}
		
		delete[] internProduct;
	}
}



void createNewProducts(Storage* supermarketStorage, const DataNeeded* internalData) //function to create new products
{

	Product* internManagement = new Product[internalData->numberofProductsToCreate + supermarketStorage->numProducts]; //internal array that will receive all the products in storage
	Product* internManagement1 = new Product[internalData->numberofProductsToCreate]; //internal array that will receive all the new Products
	int cont = 0, cont1 = supermarketStorage->numProducts; //conts needed


	for (int i = 0; i < cont1; i++) //loop to take all the products out of storage
	{
		internManagement[i] = supermarketStorage->inStorage[i];
	}
	
	internManagement1 = inicializeProducts(internalData); //to create the 10 new Products

	delete[] supermarketStorage->inStorage; //dealocates the memory in the storage
	supermarketStorage->inStorage = new Product[supermarketStorage->numProducts + internalData->numberofProductsToCreate]; //allocates the storage necessary 
	supermarketStorage->inStorage = internManagement; //receives the elements from the first array

	for (int i = supermarketStorage->numProducts; i < cont1 + internalData->numberofProductsToCreate; i++)
	{
		supermarketStorage->inStorage[supermarketStorage->numProducts++] = internManagement1[cont++]; //receives the elements from the second array
	}

}



void assignProductsToSectors(Sector* superEDA, Storage* supermarketStorage, const DataNeeded* internalData)
{
	int cont1 = 0, cont2 = 0, cont3 = 0;  //conts used in this function
	bool sair = false; //variable for exiting
	Product* internalproduct = new Product[supermarketStorage->numProducts]; //array for internal use

	do
	{
		for (int i = 0; i < internalData->numberofSectors; i++) //used for checking in all the sectors
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

			if (i == internalData->numberofSectors-1)  //if it has checked all the sectors and didn´t find one available passes to the next product
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



void verifyDiscount(Sector* superEDA, Storage* supermarketStorage, const DataNeeded* internalData) //verifies every cycle if a given campain has ended
{
	for (int i = 0; i < internalData->numberofSectors; i++) //loops through all the sectors
	{
		if (superEDA[i].cycles > 1) //if the cycle is bigger that one it just decreses its value by one
		{
			superEDA[i].cycles--;
		}
		else if (superEDA[i].cycles == 1) //if the cycle is equal to one it ends the campain
		{
			for (int j = 0; j < superEDA[i].quantityOfProducts; j++) //loops through the products in the sector
			{
				superEDA[i].productsInTheSector[j].discountState = false; 
				superEDA[i].productsInTheSector[j].price = superEDA[i].productsInTheSector[j].originalPrice; //restores the price
			}

			for (int j = 0; j < supermarketStorage->numProducts; j++) //loops trough all the products in storage
			{
				if (supermarketStorage->inStorage[j].discountState == true) //checks if a given products in in a campaign
				{
					supermarketStorage->inStorage[j].discountState = false;
					supermarketStorage->inStorage[j].price = supermarketStorage->inStorage[j].originalPrice; //restores the price to the original
				}
				
			}

			superEDA[i].cycles--; //decreses the cycle by one
		}
	}
}

 

void menuSupermarket(DataNeeded* internalData, Sector* superEDA, Storage* supermarketStorage, Filepaths* supermarketFilepaths)  // it will need debug on the switch case
{
	
	bool sair = false;

	do
	{
		display(internalData, superEDA, supermarketStorage); //function that displays the status of the supermarket

		char option;
		cout << "Insira a seua opção:" << endl;
		cout << " " << endl;
		cout << "Pressione (s) para seguinte, (g) para gestão ou (0) para terminar o programa: ";
		cin >> option;

		switch (option)
		{
		case 's':
			verifyProductSell(superEDA, internalData);
			createNewProducsts(supermarketStorage, internalData);
			assignProductsToSectors(superEDA, supermarketStorage, internalData);
			verifyDiscount(superEDA, supermarketStorage, internalData);
			break;
		case 'g':
			managementMenu(internalData, superEDA, supermarketStorage, supermarketFilepaths);
			break;
		case'0':
			sair = true;
			cout << "Obrigado por usar o nosso programa! " << endl;
			break;
		default:
			cout << "Inseriu uma opção inválida!" << endl;
			break;

		}
	} while (!sair);
		
	
}

*/