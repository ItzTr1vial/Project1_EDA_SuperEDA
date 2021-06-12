#pragma once
#include <string>
#include "Structs.h"


using namespace std;

int calculateSizeofFile(string path); //calculate the size of a given file

string* getContentFromFiles(string path, int sizeofFile); // get the respective area of the product

void saveDataNeededToFiles(const DataNeeded* internalData, const Filepaths* supermarketFilepathss); //save the structure DataNeeded to Files

void saveSectorsToFiles(const DataNeeded* internalData, nodeSector* SuperEDA, const Filepaths* supermarketFilepaths); //save the structure SuperEDA to files

void saveStorageToFiles(DataNeeded* internalData, nodeProduct* storage, const Filepaths* supermarketFilepaths); //save the structure Storage to files

void loadDataNeededFromFiles(DataNeeded* internalData, nodeSector* superEDA, Filepaths* supermartketFilepath); //load the structure DataNeeded from Files

nodeSector* loadSectorsFromFiles(DataNeeded* internalData, nodeSector* superEDA, Filepaths* supermarketFilepaths); //load the sectors from files

nodeProduct* loadStorageFromFiles(DataNeeded* internalData, nodeProduct* storage, Filepaths* supermarketFilepaths); //load the structure Storage from Files
