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



void saveSectorsToFiles(const DataNeeded* internalData, const Sector* SuperEDA, const Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathSectors, ios::out);
	file.clear();
	file.seekp(0, ios::beg);

	if (file.is_open())
	{
		for (int i = 0; i < internalData->numberofSectors; i++)
		{
			file << SuperEDA[i].sectorIdentifier << " " << SuperEDA[i].maxNumberOfProducts 
				<< " " << SuperEDA[i].quantityOfProducts << " " << SuperEDA[i].quantityOfProductsSold
				<< " " << SuperEDA[i].cycles;  //saves the data that is not an array

			file << SuperEDA[i].personInCharge << endl; //saves the name of the person in charge
			file << SuperEDA[i].area << endl; //saves the area of the sector

			for (int j = 0; j < SuperEDA[i].quantityOfProducts; j++) //saves the array of products
			{
				file << SuperEDA[i].productsInTheSector[j].area << endl;
				file << SuperEDA[i].productsInTheSector[j].name << endl;
				file << SuperEDA[i].productsInTheSector[j].provider << endl;
				file << SuperEDA[i].productsInTheSector[j].price << " " 
					<< SuperEDA[i].productsInTheSector[j].discountState << " "
				<< SuperEDA[i].productsInTheSector[j].originalPrice;
			}

			for (int j = 0; j < SuperEDA[i].quantityOfProductsSold; j++) //saves the array of products sold
			{
				file << SuperEDA[i].sectorRecord[j].name << endl;
				file << SuperEDA[i].sectorRecord[j].price;
				
			}
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}

	file.close();

}



void saveStorageToFiles(const Storage* supermarketStorage, const Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathStorage, ios::out);
	file.clear();
	file.seekp(0, ios::beg);

	if (file.is_open())
	{
		file << supermarketStorage->numProducts; //saves the number of products that exist in storage
		
		for (int i = 0; i < supermarketStorage->numProducts; i++) //saves all the products in storage
		{
			file << supermarketStorage->inStorage[i].area << endl;
			file << supermarketStorage->inStorage[i].provider << endl;
			file << supermarketStorage->inStorage[i].name << endl;
			file << supermarketStorage->inStorage[i].price << " "
				<< supermarketStorage->inStorage[i].discountState << " "
				<< supermarketStorage->inStorage[i].originalPrice;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}

	file.close();
}



void loadDataNeededFromFiles(DataNeeded* internalData, Sector* superEDA, Filepaths* supermarketFilepaths)
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



void loadSectorsFromFiles(DataNeeded* internalData, Sector* superEDA, Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathSectors, ios::in);
	file.clear();
	file.seekg(0, ios::beg);

	string str = " ";

	if (file.is_open())
	{

		delete[] superEDA; //deletes the array that contains every information about the sectors
		Sector* superEDA = new Sector[internalData->numberofSectors]; //allocates the memory needed
		

		for (int i = 0; i < internalData->numberofSectors; i++)
		{

			file >> superEDA[i].sectorIdentifier >> superEDA[i].maxNumberOfProducts 
				>> superEDA[i].quantityOfProducts >> superEDA[i].quantityOfProductsSold
				>> superEDA[i].cycles; //loads all the data that is in an array an is not a string

			getline(file, str);
			superEDA[i].personInCharge = str; //loads the name of the person in charge

			getline(file, str);
			superEDA[i].area = str; //loads the area of the sector

			superEDA[i].productsInTheSector = new Product[superEDA[i].maxNumberOfProducts]; //allocates the memory needed for the products
			superEDA[i].sectorRecord = new ProductSoldRecord[superEDA[i].quantityOfProductsSold]; //allocates the memory needed for the record of products sold



			for (int j = 0; j < superEDA[i].quantityOfProducts; j++) //loads the products into the sectores
			{
				getline(file, str);
				superEDA[i].productsInTheSector[j].area = str;

				getline(file, str);
				superEDA[i].productsInTheSector[j].name = str;

				getline(file, str);
				superEDA[i].productsInTheSector[j].provider = str;

				file >> superEDA[i].productsInTheSector[j].price >> superEDA[i].productsInTheSector[j].discountState
				>> superEDA[i].productsInTheSector[j].originalPrice;
				
			}

			for (int j = 0; j < superEDA[i].quantityOfProductsSold; j++) //loads the data of the products sold
			{
				getline(file, str);
				superEDA[i].sectorRecord[j].name = str;
				file >> superEDA[i].sectorRecord[j].price;
			}
		}

		
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}




	file.close();
}



void loadStorageFromFiles(Storage* supermarketStorage, Filepaths* supermarketFilepaths)
{
	fstream file;
	file.open(supermarketFilepaths->pathStorage, ios::in);
	file.clear();
	file.seekg(0, ios::beg);

	string str;

	if (file.is_open())
	{
		delete[] supermarketStorage->inStorage; //deletes the previous storage

		file >> supermarketStorage->numProducts; //loads the number of products

		supermarketStorage->inStorage = new Product[supermarketStorage->numProducts]; //alocates all the memory needed
		
		for (int i = 0; i < supermarketStorage->numProducts; i++) //loads all the products into storage
		{
			getline(file, str);
			supermarketStorage->inStorage[i].area = str;

			getline(file, str);
			supermarketStorage->inStorage[i].provider = str;

			getline(file, str);
			supermarketStorage->inStorage[i].name = str;

			file >> supermarketStorage->inStorage[i].price >> supermarketStorage->inStorage[i].discountState
				>> supermarketStorage->inStorage[i].originalPrice;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << supermarketFilepaths->pathDataNeeded << ". Verificar a localização." << endl;
	}

	file.close();
}

