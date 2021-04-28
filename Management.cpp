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



void alphabeticalOrder(Product* allProducts, int size)
{
	int cont1 = 0, cont2 = 0, cont3 = 0; //cont1 holds the index being used, cont2 is used to check every character and cont3 to hold how many products we have gone through
	int* positions = new int[size]; //array that will hold all the indexes used
	bool sair = false, stop = false;
	Product oneProduct;

	cout << " " << endl;
	cout << "Ordem alfabetica: " << endl;
	cout << " " << endl;

	for (int i = 0; i < size; i++) //turn uppercase letters into lowercase
	{
		if (allProducts[i].name[0] < 91 && allProducts[i].name[0] > 64)
		{
			allProducts[i].name[0] += 32;
		}
	}

	do	
	{
		cont1 = 0;
		cont2 = 0;


		for (int i = 0; i < size; i++) //goes through all the products
		{
			stop = false;

			for (int j = 0; j < cont3; j++) //checks if the index has already been used
			{
				if (cont1 == positions[j])
				{
					cont1 += 1;
				}

				if (i == positions[j])
				{
					stop = true;
					break;
				}
			}


			oneProduct = allProducts[cont1];
			


			if (stop) //if the index has already been used, skip
			{
				continue;
			}
			else 
			{

				if (oneProduct.name[cont2] < allProducts[i].name[cont2]) //if the characters from the first come before
				{
					cont2 = 0;
					continue;
				}
				else if (oneProduct.name == allProducts[i].name) //if they are equal
				{
					continue;
				}
				else if (oneProduct.name[cont2] == allProducts[i].name[cont2]) //if only the character is equal
				{
					cont2 += 1;
					i -= 1;
				}
				else
				{
					cont1 = i;
					oneProduct = allProducts[cont1]; //if the character from the second one comes before
					cont2 = 0;
				}
			}

		}

		positions[cont3++] = cont1; //stores that index to be avoided next time

		cout << left << setw(6) << "Nome: " << left << setw(22) << oneProduct.name << " | "
			<< left << setw(6) << "Fornecedor: " << left << setw(30) << oneProduct.provider << " | "
			<< left << setw(7) << "Preço: " << left << setw(4) << oneProduct.price << endl;


		if (cont3 == size) //if we have checked everyproduct skip
		{
			sair = true;
		}

	} while (!sair);

}



void priceOrder(Product* allProducts, int size)
{
	int cont1 = 0, cont2 = 0, cont3 = 0;  //cont1 holds the index being used, cont2 is used to check every character and cont3 to hold how many products we have gone through
	int* positions = new int[size]; //array that will hold all the indexes used
	bool sair = false, stop = false;
	Product oneProduct;

	cout << " " << endl;
	cout << "Ordenado por Preço: " << endl;
	cout << " " << endl;

	do
	{
		cont1 = 0;


		for (int i = 0; i < size; i++) //goes through all the products
		{
			stop = false;

			for (int j = 0; j < cont3; j++) //checks if the index has already been used
			{
				if (cont1 == positions[j])
				{
					cont1 += 1;
				}

				if (i == positions[j])
				{
					stop = true;
					break;
				}
			}

			oneProduct = allProducts[cont1];


			if (stop) //if the index has already been used, skip
			{
				continue;
			}
			else
			{
				if (oneProduct.price > allProducts[i].price) //if the price from the first one is bigger 
				{
					cont1 = i;
					oneProduct = allProducts[cont1];
				}
			}

		}

		positions[cont3++] = cont1; //holds all the indexes already used

		cout << left << setw(6) << "Nome: " << left << setw(22) << oneProduct.name << " | "
			<< left << setw(6) << "Fornecedor: " << left << setw(30) << oneProduct.provider << " | "
			<< left << setw(7) << "Preço: " << left << setw(4) << oneProduct.price << endl;


		if (cont3 == size) //if it checked all the products exit
		{
			sair = true;
		}

	} while (!sair);
}



void printProducts(DataNeeded* internalData, Sector* superEDA, Storage* supermarketStorage)
{
	int size = supermarketStorage->numProducts; //gets the number of products in storage
	int cont = 0;
	bool sair = false;
	char opcao = ' ';

	for (int i = 0; i < internalData->numberofSectors; i++) //checks how many products there are in all the sectors combined and adds them to the number we already had
	{
		size += superEDA[i].quantityOfProducts;
	}

	Product* allProducts = new Product[size]; //creates an array that will hold all the products

	for (int i = 0; i < internalData->numberofSectors; i++) //puts all the products we had in the sectors in the array
	{
		for (int j = 0; j < superEDA[i].quantityOfProducts; j++)
		{
			allProducts[cont++] = superEDA[i].productsInTheSector[j];
		}
	}

	for (int i = 0; i < supermarketStorage->numProducts; i++) //puts all the products we had in storage in the array
	{
		allProducts[cont++] = supermarketStorage->inStorage[i];
	}


	do //meny with the choices
	{
		cout << " " << endl;
		cout << "Deseja ter os produtos ordenados por nome ou preço? " << endl;
		cout << "(1). Por Nome" << endl;
		cout << "(2). Por Preço" << endl;
		cout << "(0). Sair" << endl;
		cout << "Digite a sua opcao: ";
		cin >> opcao;

		switch (opcao)
		{
		case'1':
			alphabeticalOrder(allProducts, size);
			break;
		case'2':
			priceOrder(allProducts, size);
			break;
		case'0':
			sair = true;
			cout << "Escolheu a opção sair! " << endl;
			break;
		default:
			cout << "Digite uma opção válida" << endl;
			cout << " " << endl;
			break;
		}

	} while (!sair);
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



void changeArea(DataNeeded* internalData, Sector* superEDA)
{
	char c = ' ';
	bool sair = false;
	string str;

	do
	{
		cout << "Digite a letra do sector que deseja alterar a area (maiusculas): ";
		cin >> c;
		cout << " " << endl;

		cin.ignore();

		for (int i = 0; i < internalData->numberofSectors; i++) //checks if there is a sector with that identifier
		{
			if (c == superEDA[i].sectorIdentifier)
			{
				sair = true;
			}
		}

		if (!sair)
		{
			cout << "Esse setor não existe, por favor digite um identificador de setor existente! " << endl;
			cout << " " << endl;
		}

	} while (!sair);


	sair = false;
	

	for (int i = 0; i < internalData->numberofSectors; i++) //loops through every sector
	{
		if (superEDA[i].sectorIdentifier == c) //checks for a sector with that identifier
		{
			cout << "Possiveis areas:  " << endl;

			for (int j = 0; j < internalData->sizeofAreasChoosen; j++) //displays all the areas you can choose
			{
				cout << " -" << " " << internalData->areasChoosenArray[j] << endl;
			}

			 
			do //asks for an area and checks to see if it is acceptable
			{
				cout << "Digite a sua opcao: ";
				getline(cin, str);

				for (int j = 0; j < internalData->sizeofAreasChoosen; j++)
				{
					if (str == internalData->areasChoosenArray[j])
					{
						sair = true;
					}	
				}

				if (!sair)
				{
					cout << "Digite uma das opcoes acima! " << endl;
					cout << " " << endl;
				}

			} while (!sair);
			

	
			internalData->areasChoosenArray[i] = str;
			superEDA[i].area = str;

			delete[] superEDA[i].productsInTheSector; //clears the products of the sector
			superEDA[i].productsInTheSector = new Product[superEDA[i].maxNumberOfProducts];
			superEDA[i].quantityOfProducts = 0;
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
		cout << "(9). Alterar area" << endl;
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
		case'9':
			changeArea(internalData, SuperEDA);
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