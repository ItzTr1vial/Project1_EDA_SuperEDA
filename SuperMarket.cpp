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
	int indexArea = rand() % internalData->sizeofArea; //will keep the index of the area that was choosen from that array



	oneSector.sectorIdentifier = characters[sectorsAdded]; //pick the sector identifier and then moves to the next one
	oneSector.maxNumberOfProducts = rand() % 6 + 5; //picks a max number of products that the sector can hold
	oneSector.quantityOfProducts = 0; 
	oneSector.cycles = 0;
	oneSector.productsInTheSector = new nodeProduct; //header for the linked list that will hold the products in that sector

	//ask the user for a the name of the manager of the sector
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
	internalData->areasChoosenArray[sectorsAdded++] = internalData->areaArray[indexArea]; //adds the area that was choosen to the areasChoosenArray

	system("cls");

	return oneSector;
}



nodeSector* inicializeSectors(DataNeeded* internalData, nodeSector* superEDA) 
{
	for (int i = 0; i < internalData->numberofSectors; i++)
	{
		if (superEDA == nullptr) //for the first item on the linked list
		{
			nodeSector* novo = new nodeSector;
			novo->oneSector = createOneSector(internalData); //creates a sector
			novo->next = nullptr;
			superEDA = novo;
		}
		else //for all the others
		{
			nodeSector* novo = new nodeSector; //creates a new node
			novo->oneSector = createOneSector(internalData); //creates a sector and adds it to the new node
			nodeSector* temp = superEDA; //creates a temporary node that will receive the header address

			while (temp->next != nullptr) //loops trough all the items on the linked list until it points to a null pointer
			{
				temp = temp->next;
			}

			temp->next = novo; //adds the product to the end of the linked list
		}
    }

	return superEDA;
}



Product createOneProduct(const DataNeeded* internalData)
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



nodeProduct* updateStorage(DataNeeded* internalData, nodeProduct* oneProductNode)
{

	for (int i = 0; i < internalData->numberofProductsToCreate; i++)
	{
		if (oneProductNode == nullptr)
		{
			nodeProduct* novo = new nodeProduct;
			novo->oneProduct = createOneProduct(internalData);
			novo->next = nullptr;
			oneProductNode = novo;
		}
		else
		{
			nodeProduct* novo = new nodeProduct;
			novo->oneProduct = createOneProduct(internalData);
			nodeProduct* temp = oneProductNode;

			while (temp->next != nullptr)
			{
				temp = temp->next;
			}

			temp->next = novo;
		}
	}

	internalData->numProductsInStorage += internalData->numberofProductsToCreate;
	internalData->numberofProductsToCreate = 10;
	return oneProductNode;
}



void display(const DataNeeded* internalData, nodeSector* superEDA, nodeProduct* storage) //function that displays what is needed
{
	
	cout << setfill(' ') << endl; //uses spaces to fill 

	nodeSector* temp = superEDA;

	while (temp->next != nullptr)
	{
		cout << left << setw(8) << "Sector: " << left << setw(4) << temp->oneSector.sectorIdentifier << " | "
			<< left << setw(13) << "Responsavel: " << left << setw(22) << temp->oneSector.personInCharge << " | "
			<< left << setw(12) << "Capacidade: " << left << setw(5) << temp->oneSector.maxNumberOfProducts << " | "
			<< left << setw(10) << "Produtos: " << left << setw(5) << temp->oneSector.quantityOfProducts << " | "
			<< left << setw(6) << "Area: " << left << setw(20) << temp->oneSector.area << endl;

		nodeProduct* tempProduct = temp->oneSector.productsInTheSector;

		for (int i =0; i<temp->oneSector.quantityOfProducts; i++)
		{
			cout << left << setw(8) << "Produto: " << left << setw(20) << tempProduct->oneProduct.name << " | "
				<< left << setw(7) << "Preço: " << left << setw(4) << tempProduct->oneProduct.price << endl;

			tempProduct = tempProduct->next;
		}

		cout << "-----------------------------------------------------------------------------------------------------------" << endl;

		temp = temp->next;
	}


	cout << " " << endl;
	cout << " " << endl;
	cout << "Armazem: " << endl;
	cout << " " << endl;

	nodeProduct* tempStorage = storage;

	while (tempStorage->next != nullptr)
	{
		cout << left << setw(6) << "Nome: " << left << setw(22) << tempStorage->oneProduct.name << " | "
			<< left << setw(6) << "Area: " << left << setw(20) << tempStorage->oneProduct.area << " | "
			<< left << setw(7) << "Preço: " << left << setw(4) << tempStorage->oneProduct.price << endl;

		tempStorage = tempStorage->next;
	}

	cout << " " << endl;
	cout << " " << endl;
}



void verifyProductSell(nodeSector* superEDA, const DataNeeded* internalData) //function that will verify all the products sold
{
	nodeSector* tempSector = superEDA;

	while (tempSector->next != nullptr)
	{
		int numProductsAdded = 0; //number of Products added

		tempSector = tempSector->next;
		nodeProduct* tempProduct = tempSector->oneSector.productsInTheSector;
		
		while (tempProduct->next != nullptr)
		{
			if (rand() % 3 == 0)
			{
				//function to add the product to the binary search tree, retirar o produto da lista ligada
			}
		}

	}
}


nodeProduct* removeProductBeggining(nodeProduct* storage)
{
	nodeProduct* tempProduct = new nodeProduct;
	tempProduct = storage->next;
	delete storage;
	return tempProduct;
}


nodeProduct* removeProductEnd(nodeProduct* storage)
{
	nodeProduct* tempProduct = new nodeProduct;
	tempProduct = storage;

	while (tempProduct->next->next != nullptr)
	{
		tempProduct = tempProduct->next;
	}

	delete tempProduct->next;
	tempProduct->next = nullptr;

	return storage;
}



nodeProduct* removeProductMiddle(const DataNeeded* internalData, nodeProduct* storage, int indexInStorage)
{
	nodeProduct* tempProduct = new nodeProduct;
	nodeProduct* tempProduct1 = new nodeProduct;
	tempProduct = storage;
	tempProduct1 = storage;
	int count = 0;

	while(count != (indexInStorage-1))
	{
		tempProduct = tempProduct->next;
		tempProduct1 = tempProduct1->next;
		count++;
	}

	tempProduct1 = tempProduct1->next->next;
	delete tempProduct->next;
	tempProduct->next = tempProduct1;

	return storage;
}



nodeProduct* removeProductStorage(const DataNeeded* internalData, nodeProduct* storage, int indexInStorage)
{
	if (indexInStorage > internalData->numProductsInStorage)
	{
		return storage;
	}
	else if (indexInStorage == 0)
	{
		return removeProductBeggining(storage);
	}
	else if (indexInStorage == internalData->numProductsInStorage - 1)
	{
		return removeProductEnd(storage);
	}
	else
	{
		return removeProductMiddle(internalData, storage, indexInStorage);
	}
}


nodeProduct* insertProductBeggining(nodeSector* tempSectors, Product productStorage)
{
	nodeProduct* novo = new nodeProduct;
	novo->oneProduct = productStorage;
	novo->next = nullptr;
	return novo;
}



nodeProduct* storageToSector(const DataNeeded* internalData, nodeSector* tempSectors, Product productStorage)
{	
	if (tempSectors->oneSector.quantityOfProducts == 0)
	{
		return insertProductBeggining(tempSectors, productStorage);
	}
	else
	{
		nodeProduct* novo = new nodeProduct;
		novo->oneProduct = productStorage;
		nodeProduct* tempProduct = tempSectors->oneSector.productsInTheSector;

		while (tempProduct->next != nullptr)
		{
			tempProduct = tempProduct->next;
		}

		tempProduct->next = novo;

		return tempSectors->oneSector.productsInTheSector;
	}
}



nodeProduct* assignProductsToSectors(const DataNeeded* internalData, nodeSector* superEDA, nodeProduct* storage)
{
	nodeProduct* tempStorage = storage;

	int numProductsadded = 0;
	int indexInStorage = 0;



	do
	{
		nodeSector* tempSectors = superEDA;
		bool productAdded = false;
		
		while (tempSectors != nullptr)
		{
			if (tempSectors->oneSector.area == tempStorage->oneProduct.area) //checks if the product area is equal to the sector area
			{
				if (tempSectors->oneSector.maxNumberOfProducts > tempSectors->oneSector.quantityOfProducts) // check if there is space in that sector
				{
					tempSectors->oneSector.productsInTheSector = storageToSector(internalData, tempSectors, tempStorage->oneProduct);
					storage = removeProductStorage(internalData, storage, indexInStorage);
					tempStorage = storage;
					tempSectors->oneSector.quantityOfProducts += 1; //increases the quantity of products of that sector
					numProductsadded += 1;
					productAdded = true;
					break;
				}
				else
				{
					tempSectors = tempSectors->next;
				}
			}
			else
			{
				tempSectors = tempSectors->next;
			}

		}

		if (!productAdded)
		{
			tempStorage = tempStorage->next;
			indexInStorage++;
		}


	} while (numProductsadded != 10 && tempStorage != nullptr);

	return storage;
	//remember to update the number of products in storage
	//a maneira com acedemos a lista de produtos dentro do setor esta errada
}



void menuSupermarket(DataNeeded* internalData, nodeSector* superEDA, nodeProduct* Storage, Filepaths* supermarketFilepaths)  // it will need debug on the switch case
{

	bool sair = false;

	do
	{
		display(internalData, superEDA, Storage); //function that displays the status of the supermarket

		char option;
		cout << "Insira a seua opção:" << endl;
		cout << " " << endl;
		cout << "Pressione (s) para seguinte, (g) para gestão ou (0) para terminar o programa: ";
		cin >> option;

		switch (option)
		{
		case 's':
			//verifyProductSell(superEDA, internalData);
			updateStorage(internalData, Storage);
			Storage = assignProductsToSectors(internalData, superEDA, Storage);
			//verifyDiscount(superEDA, supermarketStorage, internalData);
			break;
		case 'g':
			//managementMenu(internalData, superEDA, supermarketStorage, supermarketFilepaths);
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



       Remember to call the function updateStorage in every cicle!!!!!




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


*/