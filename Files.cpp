#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"


int calculateSizeofFile(string path)
{
	int cont = 0;
	fstream file;
	file.open(path, ios::in);
	string line = "";

	if (file.is_open()) {

		while (getline(file, line)) {  // to know how many lines there are in the file so you can initialize the array with that value
			cont += 1;
		}
	}
	else{
		cout << "Erro ao abrir o ficheiro " << path << ". Verificar novamente a localização" << endl;
	}

	file.close();
	return cont;
}


string* getContentFromFiles(string path, int sizeofFile) {  //receives the path to the file and the number of lines in that file

	int cont = 0; //used in the while loop to store the lines in the index
	fstream file;
	file.open(path, ios::in);
	string line = " ";

	file.clear(); // when you read the entire page, like above, you need to use this to be able to get back to the beggining
	file.seekg(0, ios::beg);  //set possition of the file to the beggining

	string* arrayFileContent = new string[sizeofFile];  //the string array that will contain every line of the file
	
	if (file.is_open()) {

		while (getline(file, line))
		{
			arrayFileContent[cont] = line;  //put the values inside of the array, this displays a warning but just ignore it.
			cont++;
		}

	}
	else{
		cout << "Erro ao abrir o ficheiro " << path << ".Verificar novamente a localização."  << endl;
	}
	
	file.close();
	
	return arrayFileContent;

}



void saveDataNeededToFiles(const DataNeeded* internalData, const Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathDataNeeded, ios::out);
	file.clear();
	file.seekp(0, ios::beg);

	if (file.is_open())
	{
		file << internalData->numberofSectors << " " << internalData->sizeofAreasChoosen << " " << internalData->sizeofProvider << " "
			<< internalData->sizeofName << " " << internalData->numberofProductsToCreate; //saves the data thats not an array

		for (int i = 0; i < internalData->sizeofAreasChoosen; i++) //saves this array
		{
			file << internalData->areasChoosenArray[i] << endl;
		}

		for (int i = 0; i < internalData->sizeofProvider; i++) //saves this array
		{
			file << internalData->providerArray[i] << endl;
		}

		for (int i = 0; i < internalData->sizeofName; i++) //saves this array
		{
			file << internalData->nameArray[i] << endl;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}

	file.close();

}



void saveSectorsToFiles(const DataNeeded* internalData, nodeSector* SuperEDA, const Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathSectors, ios::out);
	file.clear();
	file.seekp(0, ios::beg);

	if (file.is_open())
	{
		nodeSector* tempSector = SuperEDA;


		while (tempSector != nullptr)
		{
			file << tempSector->oneSector.sectorIdentifier << " " << tempSector->oneSector.maxNumberOfProducts
				<< " " << tempSector->oneSector.quantityOfProducts << " " << tempSector->oneSector.cycles;  //saves the data that is not an array

			file << tempSector->oneSector.personInCharge << endl; //saves the name of the person in charge
			file << tempSector->oneSector.area << endl; //saves the area of the sector

			nodeProduct* tempProduct = tempSector->oneSector.productsInTheSector; //creates a temporary node to iterate the products

			while (tempProduct != nullptr)
			{
				file << tempProduct->oneProduct.area << endl;
				file << tempProduct->oneProduct.name << endl;
				file << tempProduct->oneProduct.provider << endl;
				file << tempProduct->oneProduct.price << " "
					<< tempProduct->oneProduct.discountState << " "
					<< tempProduct->oneProduct.originalPrice; //saves all the data of the products on the sector

				tempProduct = tempProduct->next;
			}


			tempSector = tempSector->next;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}

	file.close();

}



void saveStorageToFiles(DataNeeded* internalData, nodeProduct* storage, const Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathStorage, ios::out);
	file.clear();
	file.seekp(0, ios::beg);

	if (file.is_open())
	{
		nodeProduct* tempProduct = storage; //creates a node to iterate the products in storage

		file << internalData->numProductsInStorage; //saves the number of products that exist in storage

		while (tempProduct != nullptr)
		{
			file << tempProduct->oneProduct.area << endl;
			file << tempProduct->oneProduct.provider << endl;
			file << tempProduct->oneProduct.name << endl;
			file << tempProduct->oneProduct.price << " "
				<< tempProduct->oneProduct.discountState << " "
				<< tempProduct->oneProduct.originalPrice; //saves the data of the products in storage

			tempProduct = tempProduct->next;

		}

	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}

	file.close();
}



void loadDataNeededFromFiles(DataNeeded* internalData, nodeSector* superEDA, Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathDataNeeded, ios::in);
	file.clear();
	file.seekg(0, ios::beg);


	string str;

	if (file.is_open())
	{
		//deletes the arrays that contain the data
		delete[] internalData->areasChoosenArray;
		delete[] internalData->providerArray;
		delete[] internalData->nameArray;


		file >> internalData->numberofSectors >> internalData->sizeofAreasChoosen >> internalData->sizeofProvider
			>> internalData->sizeofName >> internalData->numberofProductsToCreate; //loads the data that is not in an array

		//allocates the memory needed for the arrays
		internalData->areasChoosenArray = new string[internalData->sizeofAreasChoosen];
		internalData->providerArray = new string[internalData->sizeofProvider];
		internalData->nameArray = new string[internalData->sizeofName];


		for (int i = 0; i < internalData->sizeofAreasChoosen; i++) //loads the data into the first array
		{
			getline(file, str);
			internalData->areasChoosenArray[i] = str;
		}

		for (int i = 0; i < internalData->sizeofProvider; i++) //loads the data into the second array
		{
			getline(file, str);
			internalData->providerArray[i] = str;
		}

		for (int i = 0; i < internalData->sizeofName; i++) //loads the data into the third array
		{
			getline(file, str);
			internalData->nameArray[i] = str;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}

	file.close();
}



nodeSector* loadSectorsFromFiles(DataNeeded* internalData, nodeSector* superEDA, Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathSectors, ios::in);
	file.clear();
	file.seekg(0, ios::beg);

	string str = " ";

	nodeSector* tempSector = superEDA; //creates an node to help to delete the sectors

	while (superEDA != nullptr) //loop to delete all sectors
	{
		superEDA = tempSector->next;
		delete tempSector;
		tempSector = superEDA;
	}


	if (file.is_open())
	{
		

		nodeSector* superEDA = nullptr;

		for (int i = 0; i < internalData->numberofSectors; i++) //loop to see every sector
		{
			if (superEDA == nullptr) //for the first Sector node 
			{
				nodeSector* novo = new nodeSector; //creates a node to hold the new data
				
				file >> novo->oneSector.sectorIdentifier >> novo->oneSector.maxNumberOfProducts
					>> novo->oneSector.quantityOfProducts >> novo->oneSector.cycles; //loads all the data that is in an array an is not a string

				getline(file, str);
				novo->oneSector.personInCharge = str; //loads the name of the person in charge

				getline(file, str);
				novo->oneSector.area = str; //loads the area of the sector

				novo->oneSector.productsInTheSector = nullptr;

				for (int j = 0; j < novo->oneSector.quantityOfProducts; j++) //loop to see every product in the sector
				{
					if (novo->oneSector.productsInTheSector == nullptr) //for the first product
					{
						nodeProduct* novoProduto = new nodeProduct; //creates a node to hold the data

						getline(file, str);
						novoProduto->oneProduct.area = str;

						getline(file, str);
						novoProduto->oneProduct.name = str;

						getline(file, str);
						novoProduto->oneProduct.provider = str;

						file >> novoProduto->oneProduct.price >> novoProduto->oneProduct.discountState
							>> novoProduto->oneProduct.originalPrice;

						novoProduto->next = nullptr;

						novo->oneSector.productsInTheSector = novoProduto; //puts the product in first

					}
					else
					{
						nodeProduct* novoProduto = new nodeProduct; //creates a node to hold the data

						getline(file, str);
						novoProduto->oneProduct.area = str;

						getline(file, str);
						novoProduto->oneProduct.name = str;

						getline(file, str);
						novoProduto->oneProduct.provider = str;

						file >> novoProduto->oneProduct.price >> novoProduto->oneProduct.discountState
							>> novoProduto->oneProduct.originalPrice;

						nodeProduct* tempProduct = novo->oneSector.productsInTheSector; //creates a node to iterate the products until the last one

						while (tempProduct->next != nullptr) //loop to get to the last product
						{
							tempProduct = tempProduct->next;
						}

						tempProduct->next = novoProduto;
					}
				}

				novo->next = nullptr;
				superEDA = novo; //adds the sector to the head

			}
			else //to add at the end
			{
				nodeSector* novo = new nodeSector;

				file >> novo->oneSector.sectorIdentifier >> novo->oneSector.maxNumberOfProducts
					>> novo->oneSector.quantityOfProducts >> novo->oneSector.cycles; //loads all the data that is in an array an is not a string

				getline(file, str);
				novo->oneSector.personInCharge = str; //loads the name of the person in charge

				getline(file, str);
				novo->oneSector.area = str; //loads the area of the sector

				novo->oneSector.productsInTheSector = nullptr;

				for (int j = 0; j < novo->oneSector.quantityOfProducts; j++) //loop to see all products, same as above
				{
					if (novo->oneSector.productsInTheSector == nullptr)
					{
						nodeProduct* novoProduto = new nodeProduct;

						getline(file, str);
						novoProduto->oneProduct.area = str;

						getline(file, str);
						novoProduto->oneProduct.name = str;

						getline(file, str);
						novoProduto->oneProduct.provider = str;

						file >> novoProduto->oneProduct.price >> novoProduto->oneProduct.discountState
							>> novoProduto->oneProduct.originalPrice;

						novoProduto->next = nullptr;

						novo->oneSector.productsInTheSector = novoProduto;

					}
					else
					{
						nodeProduct* novoProduto = new nodeProduct;

						getline(file, str);
						novoProduto->oneProduct.area = str;

						getline(file, str);
						novoProduto->oneProduct.name = str;

						getline(file, str);
						novoProduto->oneProduct.provider = str;

						file >> novoProduto->oneProduct.price >> novoProduto->oneProduct.discountState
							>> novoProduto->oneProduct.originalPrice;

						nodeProduct* tempProduct = novo->oneSector.productsInTheSector;

						while (tempProduct->next != nullptr)
						{
							tempProduct = tempProduct->next;
						}

						tempProduct->next = novoProduto;
					}
				}

				nodeSector* tempSector = superEDA;

				while (tempSector->next != nullptr)
				{
					tempSector = tempSector->next;
				}

				tempSector->next = novo;
			}
		}

		return superEDA;


	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}




	file.close();
}



nodeProduct* loadStorageFromFiles(DataNeeded* internalData, nodeProduct* storage, Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathStorage, ios::in);
	file.clear();
	file.seekg(0, ios::beg);

	string str;

	nodeProduct* tempStorage = storage; //creates a node to help delete storage

	while (storage != nullptr) //loop to delete storage
	{
		storage = tempStorage->next;
		delete tempStorage;
		tempStorage = storage;
	}

	if (file.is_open())
	{
		nodeProduct* storage = nullptr; //creates the node that will be returned to the head

		file >> internalData->numProductsInStorage; //loads the number of products



		for (int i = 0; i < internalData->numProductsInStorage; i++) //loads all the products into storage
		{
			if (storage == nullptr) //for the first product
			{
				nodeProduct* novoProduto = new nodeProduct; //creates a node to hold the data

				getline(file, str);
				novoProduto->oneProduct.area = str;

				getline(file, str);
				novoProduto->oneProduct.provider = str;

				getline(file, str);
				novoProduto->oneProduct.name = str;

				file >> novoProduto->oneProduct.price >> novoProduto->oneProduct.discountState
					>> novoProduto->oneProduct.originalPrice;

				novoProduto->next = nullptr;
				storage = novoProduto; //adds the product to the head
			}
			else //add the product at the end
			{
				nodeProduct* novoProduto = new nodeProduct; 

				getline(file, str);
				novoProduto->oneProduct.area = str;

				getline(file, str);
				novoProduto->oneProduct.provider = str;

				getline(file, str);
				novoProduto->oneProduct.name = str;

				file >> novoProduto->oneProduct.price >> novoProduto->oneProduct.discountState
					>> novoProduto->oneProduct.originalPrice;

				nodeProduct* tempProduct = storage; //creates node to iterate all the products 

				while (tempProduct->next != nullptr) //loop to get to the last product
				{
					tempProduct = tempProduct->next;
				}

				tempProduct->next = novoProduto;
			}

		}

		return storage; //returns storage to the head
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}

	file.close();
}



