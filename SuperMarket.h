#pragma once

#include"Files.h"


void inicializeSectors(DataNeeded* internalData, nodeSector** superEDA);  //function that initializes all the sectors

Product createOneProduct(const DataNeeded* internalData); //function that initializes all the products

void inicializeStorage(DataNeeded* internalData, nodeProduct** oneProductNode);

void display(const DataNeeded* internalData, nodeSector* superEDA, nodeProduct* storage);

void removeProductSector(nodeSector* tempSector, nodeProduct** productNode, int indexSector);

void removeProductStorage(DataNeeded* internalData, nodeProduct** storage, int indexInStorage);

nodeProduct* assignProductsToSectors(const DataNeeded* internalData, nodeSector** superEDA, nodeProduct** storage);

void menuSupermarket(DataNeeded* internalData, nodeSector* superEDA, nodeProduct* Storage, Filepaths* supermarketFilepaths);// Menu


