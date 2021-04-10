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
	else
	{
		cout << "Erro ao abrir o ficheiro " << path << " .Verificar novamente a localização" << endl;
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
	else
	{
		cout << "Erro ao abrir o ficheiro "<< path <<" .Verificar novamente a localização"  << endl;
	}
	
	file.close();
	
	return arrayFileContent;

}
