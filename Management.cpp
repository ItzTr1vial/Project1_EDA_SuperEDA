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

/*

void removeProduct(const DataNeeded* internalData, Sector* superEDA, Storage* supermarketStorage)
{
	string str; 
	int cont = 0; //cont to know how many products have been deleted
	cin.ignore();

	cout << "Digite o nome do produto a apagar: ";
	getline(cin, str);

	for (int i = 0; i < internalData->numberofSectors; i++) //loop that goes through all the sectors
	{
		Product* internproduct = new Product[superEDA[i].quantityOfProducts];
		int cont1 = 0; //cont that increases to put the products in the array
		int cont2 = superEDA[i].quantityOfProducts; //cont to hold the quantity of products

		for (int j = 0; j < cont2; j++)
		{

			if (str != superEDA[i].productsInTheSector[j].name) //if the name is different the product is kept
			{
				internproduct[cont1++] = superEDA[i].productsInTheSector[j];
			}
			else //else it decreases the number of products
			{
				superEDA[i].quantityOfProducts--;
				cont++;
			}
		}

		delete[] superEDA[i].productsInTheSector;
		superEDA[i].productsInTheSector = new Product[superEDA[i].maxNumberOfProducts];
		superEDA[i].productsInTheSector = internproduct;
	}

	Product* internproduct = new Product[supermarketStorage->numProducts];
	int cont1 = 0; //cont that increases to put the products in the array
	int cont2 = supermarketStorage->numProducts; //cont to hold the number of products in storage

	for (int i = 0; i < cont2; i++)
	{
		if (str != supermarketStorage->inStorage[i].name) //if the name is different the product is kept
		{
			internproduct[cont1++] = supermarketStorage->inStorage[i];
		}
		else //else it decreases the number of products
		{
			supermarketStorage->numProducts--;
			cont++;
		}
	}

	delete[] supermarketStorage->inStorage;
	supermarketStorage->inStorage = new Product[supermarketStorage->numProducts];
	supermarketStorage->inStorage = internproduct;

	
	cout << "Foram apagados " << cont << " produto(s)." << endl;

}



void updatePrice(Storage* supermarketStorage)
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
	

	for (int i = 0; i < supermarketStorage->numProducts; i++) //checks for all the products in storage
	{
		if (str == supermarketStorage->inStorage[i].name) //if it has the same name the price is updated
		{
			supermarketStorage->inStorage[i].price = price;
			cont += 1;
		}
	}

	cout << "Foi atualizado o preço a " << cont << " produto(s)." << endl;
}



void discount(const DataNeeded* internalData, Sector* superEDA, Storage* supermarketStorage)
{
	cin.ignore();

	string str;
	int cycle = 0, discountPercentage = 0;
	bool sair = false;



	cout << "Digite a duraçao da campanha: ";
	cin >> cycle;

	cin.ignore();


	do //asks and check to see if the area is acceptable;
	{

		cout << "Digite a area em que quer começar a campanha de descontos: ";
		getline(cin, str);

		for (int i = 0; i < internalData->sizeofAreasChoosen; i++) //loops through all the number os areas
		{
			if (str == internalData->areasChoosenArray[i]) //if the sector belongs to that area it update the number of cycles it will be in discount
			{
				superEDA[i].cycles = cycle;
				sair = true;
			}
		}

		if (!sair)
		{
			cout << "Essa area não existe, digite uma area existente! " << endl;
		}

		cin.clear();

	} while (!sair);


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
	} while (!sair);


	for (int i = 0; i < internalData->numberofSectors; i++) //loops through all the sectors
	{
		for (int j = 0; j < superEDA[i].quantityOfProducts; j++) //checks each product in the sector
		{
			if (!superEDA[i].productsInTheSector[j].discountState) //if there isnt a promotion already it proceeds to make the changes
			{
				if (superEDA[i].productsInTheSector[j].area == str)
				{
					superEDA[i].productsInTheSector[j].discountState = true;
					superEDA[i].productsInTheSector[j].price -= (superEDA[i].productsInTheSector[j].price * discountPercentage / 100);
				}
			}
			else //else it displays an error message
			{
				cout << "Já existe uma campanha de descontos nesta area! " << endl;
				break;
			}
			
		}
	}


	for (int i = 0; i < supermarketStorage->numProducts; i++) //loops through all the products in storage
	{
		if (supermarketStorage->inStorage[i].area == str) //if the product belongs to that area
		{
			if (!supermarketStorage->inStorage[i].discountState) //checks if the product already has a promotion, if not proceeds to make the changes
			{
				supermarketStorage->inStorage[i].discountState = true;
				supermarketStorage->inStorage[i].price -= (supermarketStorage->inStorage[i].price * discountPercentage / 100);
			}
		}
	}
}



void saveSuperMarket(const DataNeeded* internalData, const Sector* SuperEDA, const Storage* supermarketStorage, const Filepaths* supermarketFilepath) //calls the functions in files.cpp to save the data
{
	saveDataNeededToFiles(internalData, supermarketFilepath);
	saveSectorsToFiles(internalData, SuperEDA, supermarketFilepath);
	saveStorageToFiles(supermarketStorage, supermarketFilepath);
}



void loadSuperMarket(DataNeeded* internalData, Sector* SuperEDA, Storage* supermarketStorage, Filepaths* supermarketFilepath)
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
	loadDataNeededFromFiles(internalData, SuperEDA, supermarketFilepath);
	loadSectorsFromFiles(internalData, SuperEDA, supermarketFilepath);
	loadStorageFromFiles(supermarketStorage, supermarketFilepath);
}





void printProducts(DataNeeded* internalData, nodeSector* superEDA, nodeProduct* storage)
{
cout << setfill(' ') << endl; //uses spaces to fill

	nodeSector* temp = superEDA;

	while (temp->next != nullptr)
	{
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



void showSalesRegister(DataNeeded* internalData, Sector* superEDA)
{
	cin.ignore();

	string str;
	
	cout << "Digite o nome do responsavel: ";
	getline(cin, str);

	for (int i = 0; i < internalData->numberofSectors; i++) //goes through all the sectors
	{
		if (superEDA[i].personInCharge == str) //checks which sector has a person with that name and displays all the products sold
		{
			cout << " " << endl;
			cout << " " << endl;
			cout << superEDA[i].personInCharge << endl;
			cout << " " << endl;
			cout << "-----------------------------------------------------------------" << endl;

			for (int j = 0; j < superEDA[i].quantityOfProductsSold; j++)
			{
				cout << left << setw(6) << "Nome: " << left << setw(22) << superEDA[i].sectorRecord[j].name << " | "
					<< left << setw(7) << "Preço: " << left << setw(4) << superEDA[i].sectorRecord[j].price << endl;
			}

			cout << "-----------------------------------------------------------------" << endl;
		}
	}
}




void managementMenu(DataNeeded* internalData, Sector* SuperEDA, Storage* supermarketStorage, Filepaths* supermarketFilepaths)
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
			removeProduct(internalData, SuperEDA, supermarketStorage);
			break;
		case'2':
			updatePrice(supermarketStorage);
			break;
		case'3':
			discount(internalData, SuperEDA, supermarketStorage);
			break;
		case'4':
			saveSuperMarket(internalData, SuperEDA, supermarketStorage, supermarketFilepaths);
			break;
		case'5':
			loadSuperMarket(internalData, SuperEDA, supermarketStorage, supermarketFilepaths);
			break;
		case'6':
			printProducts(internalData, SuperEDA, supermarketStorage);
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

*/