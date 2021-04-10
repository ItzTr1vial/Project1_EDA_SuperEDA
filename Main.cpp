#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "Files.h"
using namespace std;

int main() {
	srand(time(NULL));
	locale::global(locale(""));

	//Numbers of sectors between 8 and 12 -> dyanmic array of sectors
	// Number of products between 5 and 10

	string pathArea ="E:\\EDA\\Projeto1_EDA_SuperEDA\\Project1_EDA_SuperEDA\\areas.txt" ;
	Product product;
	getProductAreaFromFiles(pathArea, &product); // why the &?? The struct must stay cause it will be import to the project because we need to load and also save. So we must work with their reference(address) in order to do that.
	
	
	return 0;
}