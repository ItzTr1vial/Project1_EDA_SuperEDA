#pragma once
#include <string>
#include "Structs.h"
using namespace std;

int calculateSizeofFile(string path); //calculate the size of a given file

string* getContentFromFiles(string path, int sizeofFile); // get the respective area of the product

void saveDataNeededToFiles(const DataNeeded* internalData, const Filepaths* supermarketFilepathss); //save the structure DataNeeded to Files

void saveSectorsToFiles(const DataNeeded* internalData, const Sector* SuperEDA, const Filepaths* superMarketFilepaths); //save the structure SuperEDA to files

void saveStorageToFiles(const Storage* supermarketStorage, const Filepaths* superMarketFilepaths); //save the structure Storage to files

void loadDataNeededFromFiles(DataNeeded* internalData, Sector* superEDA, Filepaths* supermartketFilepath); //load the structure DataNeeded from Files

void loadSectorsFromFiles(DataNeeded* internalData, Sector* superEDA, Filepaths* supermarktetFilepaths); //load the structure SuperEDA from Files

void loadStorageFromFiles(Storage* supermarketStorage, Filepaths* supermarketFilepaths); //load the structure Storage from Files