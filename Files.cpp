#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"


void getProductAreaFromFiles(Product* product,string path) {

	fstream file;
	file.open(path, ios::in);
	string line="";
	
	if (file.is_open()) {
		while (getline(file, line)) {
			product->areaLenght++;
				
		}
		product->areaArray = new string[product->areaLenght];

		file.seekg(0, ios::beg);// sets the position back to beggining
		int i = 0;
		while (getline(file,line))
		{
			product->areaArray[i] = line; //
			i++;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro "<< path <<" .Verificar novamente a localização"  << endl;
	}
	
	file.close();
}

void getProductProviderFromFile(Product* product, string path) {

	fstream file;
	file.open(path, ios::in);
	string line = "";

	if (file.is_open()) {
		while (getline(file, line)) {
			product->providerLenght++;
		}
		product->providerArray = new string[product->providerLenght];

		file.seekg(0, ios::beg);// sets the position back to beggining
		int i = 0;
		while (getline(file, line))
		{
			product->providerArray[i] = line; //inserts the content to the array
			i++;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << path << " .Verificar novamente a localização" << endl;
	}

	file.close();
}

void getProductNamesFromFile(Product* product, string path) {
	fstream file;
	file.open(path, ios::in);
	string line = "";

	if (file.is_open()) {
		while (getline(file, line)) {
			product->nameLenght++;
		}
		product->nameArray = new string[product->nameLenght];

		file.seekg(0, ios::beg);// sets the position back to beggining
		int i = 0;
		while (getline(file, line))
		{
			product->nameArray[i] = line; //inserts the content to the array
			i++;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << path << " .Verificar novamente a localização" << endl;
	}

	file.close();
}
void getSectorAreaFromFiles(Sector* sector, string path){
	fstream file;
	file.open(path, ios::in);
	string line = "";

	if (file.is_open()) {
		while (getline(file, line)) {
			sector->sectorLenght++;
		}
		sector->sectorArray = new string[sector->sectorLenght];

		file.seekg(0, ios::beg);// sets the position back to beggining
		int i = 0;
		while (getline(file, line))
		{
			sector->sectorArray[i] = line; //inserts the content to the array
			i++;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << path << " .Verificar novamente a localização" << endl;
	}

	file.close();
}

void getSectorAreaFromFiles(Sector* sector, string path){
	fstream file;
	file.open(path, ios::in);
	string line = "";

	if (file.is_open()) {
		while (getline(file, line)) {
			sector->areaLenght++;
		}
		sector->areaArray = new string[sector->areaLenght];

		file.seekg(0, ios::beg);// sets the position back to beggining
		int i = 0;
		while (getline(file, line))
		{
			sector->areaArray[i] = line; //inserts the content to the array
			i++;
		}
	}
	else
	{
		cout << "Erro ao abrir o ficheiro " << path << " .Verificar novamente a localização" << endl;
	}

	file.close();
}
