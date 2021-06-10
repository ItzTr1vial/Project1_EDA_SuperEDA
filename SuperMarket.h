#pragma once

#include"Files.h"


nodeSector* inicializeSectors(DataNeeded* internalData, nodeSector* superEDA);  //function that initializes all the sectors

Product createOneProduct(const DataNeeded* internalData); //function that initializes all the products

nodeProduct* updateStorage(DataNeeded* internalData, nodeProduct* oneProductNode);

void display(const DataNeeded* internalData, nodeSector* superEDA, nodeProduct* storage);

nodeProduct* assignProductsToSectors(const DataNeeded* internalData, nodeSector* superEDA, nodeProduct* storage);

void menuSupermarket(DataNeeded* internalData, nodeSector* superEDA, nodeProduct* Storage, Filepaths* supermarketFilepaths);// Menu


