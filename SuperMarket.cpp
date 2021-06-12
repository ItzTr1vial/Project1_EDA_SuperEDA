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
	oneSector.productsInTheSector = nullptr; //header for the linked list that will hold the products in that sector
	oneSector.productsSold = nullptr;
	oneSector.quantityOfProductsSold = 0;

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
	internalData->areasChoosenArray[sectorsAdded++] = oneSector.area; //adds the area that was choosen to the areasChoosenArray

	system("cls");

	return oneSector;
}



void inicializeSectors(DataNeeded* internalData, nodeSector** superEDA) 
{
	for (int i = 0; i < internalData->numberofSectors; i++)
	{
		if (i == 0) //for the first item on the linked list
		{
			nodeSector* novo = new nodeSector;
			novo->oneSector = createOneSector(internalData); //creates a sector
			novo->next = nullptr;
			*superEDA = novo;
		}
		else //for all the others
		{
			nodeSector* novo = new nodeSector; //creates a new node
			novo->oneSector = createOneSector(internalData); //creates a sector and adds it to the new node
			nodeSector* temp = *superEDA; //creates a temporary node that will receive the header address

			while (temp->next != nullptr) //loops trough all the items on the linked list until it points to a null pointer
			{
				temp = temp->next;
			}

			temp->next = novo; //adds the product to the end of the linked list
		}
    }
}



Product createOneProduct(const DataNeeded* internalData)
{
	Product oneProduct;
	
	
	oneProduct.name = internalData->nameArray[rand() % internalData->sizeofName];  //chooses a random name from the array and gives it to the product
	oneProduct.area = internalData->areasChoosenArray[rand() % internalData->sizeofAreasChoosen];  //chooses a random area only from the areas that have already been selected for the sectors
	oneProduct.provider = internalData->providerArray[rand() % internalData->sizeofProvider];  //chooses a random provider from the array and gives it to the product

	int price = rand() % 80 + 1;  //gives a random number between 1 and 80
		
	if (price % 2 != 0)  //if that number is and odd number it adds one so it becomes a multiple of 2
		price += 1;

	oneProduct.price = price; //gives that price for that product
	oneProduct.originalPrice = price; //holds the original price given in case of modification
		
	
	
	return oneProduct;
}



void inicializeStorage(DataNeeded* internalData, nodeProduct** oneProductNode)
{

	for (int i = 0; i < internalData->numberofProductsToCreate; i++)
	{
		if (i == 0)
		{
			nodeProduct* novo = new nodeProduct;
			novo->oneProduct = createOneProduct(internalData);
			novo->next = nullptr;
			*oneProductNode = novo;
		}
		else
		{
			nodeProduct* novo = new nodeProduct;
			novo->oneProduct = createOneProduct(internalData);
			nodeProduct* temp = *oneProductNode;

			while (temp->next != nullptr)
			{
				temp = temp->next;
			}

			temp->next = novo;
		}
	}

	internalData->numProductsInStorage = 50;
	internalData->numberofProductsToCreate = 10;
}



void updateStorage(DataNeeded* internalData, nodeProduct** oneProductNode)
{
	for (int i = 0; i < internalData->numberofProductsToCreate; i++)
	{
		if (oneProductNode == nullptr)
		{
			nodeProduct* novo = new nodeProduct;
			novo->oneProduct = createOneProduct(internalData);
			novo->next = nullptr;
			*oneProductNode = novo;
		}
		else
		{
			nodeProduct* novo = new nodeProduct;
			novo->oneProduct = createOneProduct(internalData);

			nodeProduct* iterator = *oneProductNode;

			while (iterator->next != nullptr)
			{
				iterator = iterator->next;
			}

			iterator->next = novo;
			novo->next = nullptr;
		}

		internalData->numProductsInStorage++;
	}
}



void display(const DataNeeded* internalData, nodeSector* superEDA, nodeProduct* storage) //function that displays what is needed
{
	
	cout << setfill(' ') << endl; //uses spaces to fill 

	nodeSector* temp = superEDA;

	while (temp != nullptr)
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

	while (tempStorage != nullptr)
	{
		cout << left << setw(6) << "Nome: " << left << setw(22) << tempStorage->oneProduct.name << " | "
			<< left << setw(6) << "Area: " << left << setw(20) << tempStorage->oneProduct.area << " | "
			<< left << setw(7) << "Preço: " << left << setw(4) << tempStorage->oneProduct.price << endl;

		tempStorage = tempStorage->next;
	}

	cout << " " << endl;
	cout << " " << endl;
}



void removeProductSector(nodeSector* tempSector, nodeProduct** productNode, int indexSector)
{
	if (indexSector > tempSector->oneSector.quantityOfProducts)
	{
		cout << "Impossível, o index é maior que o número de produtos no setor";
	}
	else if (indexSector == 0)
	{
		if (productNode == nullptr)
		{
			productNode = nullptr;
		}
		else
		{
			nodeProduct* aux = *productNode;
			*productNode = aux->next;
			delete aux;
		}
	}
	else if (indexSector == tempSector->oneSector.quantityOfProducts - 1)
	{
		nodeProduct* iterator = *productNode;

		while (iterator->next->next != nullptr)
		{
			iterator = iterator->next;
		}

		delete iterator->next;
		iterator->next = nullptr;
	}
	else
	{
		nodeProduct* aux1 = *productNode;
		nodeProduct* aux2 = *productNode;
		int count = 0;

		while (count != (indexSector - 1))
		{
			aux1 = aux1->next;
			aux2 = aux2->next;
			count++;
		}

		aux2 = aux2->next->next;
		delete aux1->next;
		aux1->next = aux2;
	}
}



void addProductToBST(productSoldRegistBST** root, nodeProduct* productNode)
{
	productSoldRegistBST* temp = *root;
	
	if (temp == nullptr)
	{
		productSoldRegistBST* novo = new productSoldRegistBST;
		novo->productsSold.nome = productNode->oneProduct.name;
		novo->productsSold.price = productNode->oneProduct.price;
		novo->left = nullptr;
		novo->right = nullptr;
		*root = novo;
	}
	else if (productNode->oneProduct.price < temp->productsSold.price)
	{
		addProductToBST(&temp->left, productNode);
	}
	else
	{
		addProductToBST(&temp->right, productNode);
	}
}



void verifyProductSell(nodeSector** superEDA, const DataNeeded* internalData) //functi.on that will verify all the products sold
{
	nodeSector* tempSector = *superEDA;

	while (tempSector != nullptr)
	{ 
		int count = 0;
		nodeProduct* tempProduct = tempSector->oneSector.productsInTheSector;
		
		while (tempProduct != nullptr)
		{
			if (rand() % 3 == 0)
			{
				addProductToBST(&tempSector->oneSector.productsSold, tempProduct);
				removeProductSector(tempSector, &tempSector->oneSector.productsInTheSector, count);
				tempSector->oneSector.quantityOfProducts--;
				tempProduct = tempSector->oneSector.productsInTheSector;
				tempSector->oneSector.quantityOfProductsSold++;

				for (int i = 0; i < count; i++)
				{
					tempProduct = tempProduct->next;
				}
			}
			else if (tempProduct != nullptr)
			{
				count++;
				tempProduct = tempProduct->next;
			}
		}

		tempSector = tempSector->next;

	}
}



void removeProductStorage(DataNeeded* internalData, nodeProduct** storage, int indexInStorage)
{
	if (indexInStorage > internalData->numProductsInStorage)
	{
		cout << "Impossível, o index é maior que o número de produtos no armazem";
	}
	else if (indexInStorage == 0)
	{
		if (storage == nullptr)
		{
			storage = nullptr;
		}
		else
		{
			nodeProduct* aux = *storage;
			*storage = aux->next;
			delete aux;
		}
	}
	else if (indexInStorage == internalData->numProductsInStorage - 1)
	{
		nodeProduct* iterator = *storage;

		while (iterator->next->next!=nullptr)
		{
			iterator = iterator->next;
		}

		delete iterator->next;
		iterator->next = nullptr;
	}
	else
	{
		nodeProduct* aux1 = *storage;
		nodeProduct* aux2 = *storage;
		int count = 0;

		while (count != (indexInStorage - 1))
		{
			aux1 = aux1->next;
			aux2 = aux2->next;
			count++;
		}

		aux2 = aux2->next->next;
		delete aux1->next;
		aux1->next = aux2;
	}

	internalData->numProductsInStorage--;
}



void storageToSector(nodeSector* tempSectors, Product productStorage)
{	
	if (tempSectors->oneSector.quantityOfProducts == 0)
	{
		nodeProduct* novo = new nodeProduct;
		novo->oneProduct = productStorage;
		novo->next = nullptr;
		tempSectors->oneSector.productsInTheSector = novo;
	}
	else
	{
		nodeProduct* novo = new nodeProduct;
		novo->oneProduct = productStorage;
		nodeProduct* iterator = tempSectors->oneSector.productsInTheSector;

		while (iterator->next != nullptr)
		{
			iterator = iterator->next;
		}

		iterator->next = novo;
	}
}



void assignProductsToSectors(DataNeeded* internalData, nodeSector** superEDA, nodeProduct** storage)
{
	nodeProduct* tempStorage = *storage;

	int numProductsadded = 0;
	int indexInStorage = 0;



	do
	{
		nodeSector* tempSectors = *superEDA;
		bool productAdded = false;
		
		while (tempSectors != nullptr)
		{
			if (tempSectors->oneSector.area == tempStorage->oneProduct.area) //checks if the product area is equal to the sector area
			{
				if (tempSectors->oneSector.maxNumberOfProducts > tempSectors->oneSector.quantityOfProducts) // check if there is space in that sector
				{
					storageToSector(tempSectors, tempStorage->oneProduct);
					removeProductStorage(internalData, storage, indexInStorage);
					tempStorage = *storage;

					for (int i = 0; i < indexInStorage; i++)
					{
						tempStorage = tempStorage->next;
					}

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

	//remember to update the number of products in storage
	//a maneira com acedemos a lista de produtos dentro do setor esta errada
}



void verifyDiscount(nodeSector* superEDA, nodeProduct* storage, const DataNeeded* internalData) //verifies every cycle if a given campain has ended
{
	nodeSector* tempSector = superEDA;

	while (tempSector != nullptr)
	{
		if (tempSector->oneSector.cycles > 1)
		{
			tempSector->oneSector.cycles--;
		}
		else if (tempSector->oneSector.cycles == 1)
		{
			nodeProduct* tempProduct = tempSector->oneSector.productsInTheSector;

			while (tempProduct != nullptr)
			{
				tempProduct->oneProduct.discountState = false;
				tempProduct->oneProduct.price = tempProduct->oneProduct.originalPrice;

				tempProduct = tempProduct->next;
			}


			nodeProduct* tempProduct1 = storage;

			while (tempProduct1 != nullptr)
			{
				if (tempProduct1->oneProduct.discountState)
				{
					tempProduct1->oneProduct.discountState = false;
					tempProduct1->oneProduct.price = tempProduct1->oneProduct.originalPrice;
				}

				tempProduct1 = tempProduct1->next;
			}
		}

		tempSector = tempSector->next;
	}
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
			verifyProductSell(&superEDA, internalData);
			updateStorage(internalData, &Storage);
			assignProductsToSectors(internalData, &superEDA, &Storage);
			verifyDiscount(superEDA, Storage, internalData);
			break;
		case 'g':
			managementMenu(internalData, &superEDA, &Storage, supermarketFilepaths);
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


*/