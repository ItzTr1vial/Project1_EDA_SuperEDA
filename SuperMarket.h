#pragma once

#include"Files.h"


nodeSector* inicializeSectors(DataNeeded* internalData);  //function that initializes all the sectors

Product inicializeProducts(const DataNeeded* internalData); //function that initializes all the products

void updateProductNode(DataNeeded* internalData, nodeProduct* oneProductNode, int numberOfProductstoAdd);

/*

void display(const DataNeeded* internalData, Sector* SuperEDA, Storage* supermarketStorage);

void assignProductsToSectors(Sector* superEda, Storage* supermarketStorage, const DataNeeded* internalData);

void menuSupermarket(DataNeeded* internalData,Sector* superEda, Storage* supermarketStorage, Filepaths* supermarketFilepaths);// Menu

*/

