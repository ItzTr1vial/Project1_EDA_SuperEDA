#include <iostream>
#include <fstream>
#include <string>
#include "Files.h"


void getProductAreaFromFiles(string path, Product* product) {

	ifstream file(path);
	string line="";
	int size = 0;
	if (file.is_open()) {
		while (getline(file, line)) {
			//product->area = line;
			size++;
		}
		product->area = new string[size];

	}

	std::cout << product->area<< "\n" << std::endl;
	file.close();
}