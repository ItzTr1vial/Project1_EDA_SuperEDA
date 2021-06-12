#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include <fstream>
#include<iomanip>
#include "Files.h"
#include "Structs.h"
#include"SuperMarket.h"
#include "Management.h"



using namespace std;



void removeProduct(DataNeeded* internalData, nodeSector** superEDA, nodeProduct** storage)
{
	string str;
	int cont = 0; //cont to know how many products have been deleted
	cin.ignore();

	cout << "Digite o nome do produto a apagar: "; //askes the user for info
	getline(cin, str);

	nodeSector* tempSector = *superEDA; //creates a node to iterate by all sectors

	while (tempSector != nullptr) //loop to see all sectors
	{
		int count = 0; //count to keep track of the index on the product list
		nodeProduct* tempProduct = tempSector->oneSector.productsInTheSector;

		while (tempProduct != nullptr) //iterates by all products
		{
			if (tempProduct->oneProduct.name == str) //if it has the same name removes the product
			{
				removeProductSector(tempSector, &tempSector->oneSector.productsInTheSector, count);
				tempSector->oneSector.quantityOfProducts--;
				tempProduct = tempSector->oneSector.productsInTheSector;
				cont++;

				for (int i = 0; i < count; i++) //to go to that index on the list
				{
					tempProduct = tempProduct->next;
				}
			}
			else
			{
				count++;
				tempProduct = tempProduct->next;
			}

		}

		tempSector = tempSector->next;
	}



	nodeProduct* tempStorage = *storage; //does the same as above but in storage
	int count = 0;


	while (tempStorage != nullptr)
	{
		

		if (tempStorage->oneProduct.name == str)
		{
			removeProductStorage(internalData, storage, count);
			tempStorage = *storage;
			cont++;

			for (int i = 0; i < count; i++)
			{
				tempStorage = tempStorage->next;
			}

		}
		else
		{
			tempStorage = tempStorage->next;
			count++;
		}
	}

	cout << "Foram apagados " << cont << " produto(s)." << endl;

}



void updatePrice(nodeProduct** storage)
{
	cin.ignore();
	string str;
	int price = 0, cont = 0;
	bool sair = false;

	cout << "Digite o nome do produto de que quer atualizar o preço: ";
	getline(cin, str);

	cout << " " << endl;

	do
	{
		cout << "Qual o novo preço deste produto [valor entre 0-80 e divisivel por 2]: ";
		cin >> price;

		if (price > 0 && price <= 80 && price % 2 == 0) //if the value is in accordance to the rules continue
		{
			sair = true;
		}
		else
		{
			cout << "Digite um preco conforme as regras! " << endl;
		}

	} while (!sair);


	nodeProduct* tempProduct = *storage; //node to iterate by all products


	while (tempProduct != nullptr)
	{
		if (tempProduct->oneProduct.name == str) //if it has the same name updates the price
		{
			tempProduct->oneProduct.price = price;
			tempProduct->oneProduct.originalPrice = price;
			cont++;
		}

		tempProduct = tempProduct->next;
	}

	cout << "Foi atualizado o preço a " << cont << " produto(s)." << endl;
}



void discount(const DataNeeded* internalData, nodeSector** superEDA, nodeProduct** storage)
{
	string str;
	int cycle = 0, discountPercentage = 0;
	bool sair = false;


	cout << "Digite a duraçao da campanha: ";
	cin >> cycle;
	cin.ignore();

	nodeSector* tempSector = *superEDA; //node to iterate by all sectors


	cout << "Digite a area em que quer começar a campanha de descontos: ";
	getline(cin, str);


	sair = false;


	do //asks for the discount percentage
	{
		cout << "Digite a percentagem de desconto: ";
		cin >> discountPercentage;

		if (discountPercentage > 0 && discountPercentage < 100)
		{
			sair = true;
		}
		else
		{
			cout << "Digite um número no intervalo (0-100): " << endl;
		}
		cin.clear();
	} while (!sair);


	nodeSector* tempSector1 = *superEDA;


	while (tempSector1 != nullptr)
	{
		nodeProduct* tempProduct = tempSector1->oneSector.productsInTheSector;

		while (tempProduct != nullptr)
		{
			if (!tempProduct->oneProduct.discountState)
			{
				if (tempProduct->oneProduct.area == str)
				{
					tempProduct->oneProduct.discountState = true;
					tempProduct->oneProduct.price -= (tempProduct->oneProduct.price * discountPercentage / 100);
				}
			}
			else
			{
				cout << "Já existe uma campanha de descontos nesta area! " << endl;
				break;
			}

			tempProduct = tempProduct->next;
		}

		tempSector1 = tempSector1->next;
	}


	nodeProduct* tempProduct1 = *storage;


	while (tempProduct1 != nullptr)
	{
		if (tempProduct1->oneProduct.area == str)
		{
			if (!tempProduct1->oneProduct.discountState)
			{
				tempProduct1->oneProduct.discountState = true;
				tempProduct1->oneProduct.price -= (tempProduct1->oneProduct.price * discountPercentage / 100);
			}
		}

		tempProduct1 = tempProduct1->next;
	}
}



void saveSuperMarket(DataNeeded* internalData, nodeSector** SuperEDA, nodeProduct** supermarketStorage, const Filepaths* supermarketFilepath) //calls the functions in files.cpp to save the data
{
	saveDataNeededToFiles(internalData, supermarketFilepath);
	saveSectorsToFiles(internalData, *SuperEDA, supermarketFilepath);
	saveStorageToFiles(internalData, *supermarketStorage, supermarketFilepath);
}



void loadSuperMarket(DataNeeded* internalData, nodeSector** SuperEDA, nodeProduct** storage, Filepaths* supermarketFilepath)
{
	char opcao = ' ';
	bool sair = false;
	string str;

	do //menu to know if the users want to load files from a custom location or the predifinition
	{
		cout << " " << endl;
		cout << "Usar documentos nos locais predefinidos ou quer usar outros locais? " << endl;
		cout << "(1). Usar locais predefinidos" << endl;
		cout << "(2). Outros locais" << endl;
		cout << "(3). Sair" << endl;
		cout << "Digite a sua opção: ";
		cin >> opcao;
		cout << " " << endl;

		cin.ignore();

		switch (opcao)
		{
		case'1':
			sair = true;
			break;
		case'2':
			cout << "Local do ficheiro dataNeeded: ";
			getline(cin, str);
			supermarketFilepath->pathDataNeeded = str;

			cout << "Local do ficheiro sectors: ";
			getline(cin, str);
			supermarketFilepath->pathSectors = str;

			cout << "Local do ficheiro storage: ";
			getline(cin, str);
			supermarketFilepath->pathStorage = str;

			sair = true;
			break;
		case'0':
			sair = true;
			break;
		default:
			cout << "Digite uma opção válida!" << endl;
			break;
		}
	} while (!sair);


	//calls the funtions from files.cpp to load the data 
	loadDataNeededFromFiles(internalData, *SuperEDA, supermarketFilepath);
	*SuperEDA = loadSectorsFromFiles(internalData, *SuperEDA, supermarketFilepath);
	*storage = loadStorageFromFiles(internalData, *storage, supermarketFilepath);
}



void printProducts(DataNeeded* internalData, nodeSector** superEDA, nodeProduct** storage)
{
	cout << setfill(' ') << endl; //uses spaces to fill

	nodeSector* temp = *superEDA;

	while (temp->next != nullptr)
	{
		nodeProduct* tempProduct = temp->oneSector.productsInTheSector;

		for (int i = 0; i < temp->oneSector.quantityOfProducts; i++)
		{
			cout << left << setw(6) << "Nome: " << left << setw(22) << tempProduct->oneProduct.name << " | "
				<< left << setw(6) << "Area: " << left << setw(20) << tempProduct->oneProduct.area << " | "
				<< left << setw(7) << "Preço: " << left << setw(4) << tempProduct->oneProduct.price << endl;

			tempProduct = tempProduct->next;
		}

		temp = temp->next;
	}

	nodeProduct* tempStorage = *storage;

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



void createNewArea(DataNeeded* internalData)
{
	cin.ignore();

	string* updateArea = new string[internalData->sizeofAreasChoosen + 1]; //array that will contain all the areas used in out program and the new one

	for (int i = 0; i < internalData->sizeofAreasChoosen; i++) //puts all the areas being used to the array
	{
		updateArea[i] = internalData->areasChoosenArray[i];
	}

	cout << "Digite o nome da nova area a criar: ";
	getline(cin, updateArea[internalData->sizeofAreasChoosen]); //puts the new area to the array


	delete[] internalData->areasChoosenArray;
	internalData->areasChoosenArray = new string[internalData->sizeofAreasChoosen];

	internalData->areasChoosenArray = updateArea;
	internalData->sizeofAreasChoosen++; //increases the size of the array

}



void printBST(productSoldRegistBST* oneProductRegister, int nivel)
{
	productSoldRegistBST* tempBST1 = oneProductRegister;

	if (tempBST1 == nullptr)
	{
		cout << endl;
		return;
	}

	printBST(tempBST1->right, nivel++);

	cout << left << setw(6) << "Nome: " << left << setw(22) << tempBST1->productsSold.nome << " | "
		<< left << setw(7) << "Preço: " << left << setw(4) << tempBST1->productsSold.price;

	printBST(tempBST1->left, nivel++);
}



void showSalesRegister(DataNeeded* internalData, nodeSector** superEDA)
{
	cin.ignore();

	string str;

	cout << "Digite o nome do responsavel: ";
	getline(cin, str);

	nodeSector* tempSector = *superEDA;

	for (int i = 0; i < internalData->numberofSectors; i++) //goes through all the sectors
	{
		int nivel = 0;

		if (tempSector->oneSector.personInCharge == str) //checks which sector has a person with that name and displays all the products sold
		{
			cout << " " << endl;
			cout << " " << endl;
			cout << tempSector->oneSector.personInCharge << endl;
			cout << " " << endl;
			cout << "-----------------------------------------------------------------" << endl;

			productSoldRegistBST* tempBST = tempSector->oneSector.productsSold;

			
			printBST(tempBST, nivel);
			


			cout << "-----------------------------------------------------------------" << endl;
		}

		tempSector = tempSector->next;
	}
}



void managementMenu(DataNeeded* internalData, nodeSector** SuperEDA, nodeProduct** storage, Filepaths* supermarketFilepaths)
{
	bool sair = false;
	char opcoes = ' ';



	do
	{
		cout << " " << endl;
		cout << "****" << " Bem Vindo Gestor " << "****" << endl;
		cout << "(1). Remover produto" << endl;
		cout << "(2). Atualizar preço" << endl;
		cout << "(3). Iniciar campanha" << endl;
		cout << "(4). Gravar supermercado" << endl;
		cout << "(5). Carregar supermercado" << endl;
		cout << "(6). Imprimir produtos" << endl;
		cout << "(7). Criar nova area" << endl;
		cout << "(8). Mostrar registo de vendas" << endl;
		cout << "(0). Sair" << endl;
		cout << "Digite a sua opcão: ";
		cin >> opcoes;

		cout << " " << endl;

		switch (opcoes)
		{
		case '1':
			removeProduct(internalData, SuperEDA, storage);
			break;
		case'2':
			updatePrice(storage);
			break;
		case'3':
			discount(internalData, SuperEDA, storage);
			break;
		case'4':
			saveSuperMarket(internalData, SuperEDA, storage, supermarketFilepaths);
			break;
		case'5':
			loadSuperMarket(internalData, SuperEDA, storage, supermarketFilepaths);
			break;
		case'6':
			printProducts(internalData, SuperEDA, storage);
			break;
		case'7':
			createNewArea(internalData);
			break;
		case'8':
			showSalesRegister(internalData, SuperEDA);
			break;
		case'0':
			cout << "Digitou a opcao sair!" << endl;
			sair = true;
			break;
		default:
			cout << "Digitou um valor inválido, introduza um dos valores a cima";
			break;
		}
	} while (!sair);
}

