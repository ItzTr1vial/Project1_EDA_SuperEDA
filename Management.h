#pragma once

/*
void saveSuperMarket(const DataNeeded* internalData, const Sector* SuperEDA, const Storage* supermarketStorage, const Filepaths* supermarketFilepaths); // topic 3.4

void loadSuperMarket(DataNeeded* internalData, Sector* SuperEDA, Storage* supermarketStorage, Filepaths* supermarketFilepaths); // topic 3.5

void showSalesRegister(DataNeeded* internalData, Sector* superEDA); // topic 3.8

*/

void removeProduct(const DataNeeded* internalData, nodeSector** superEDA, nodeProduct** storage); //topic 3.1

void updatePrice(nodeProduct** storage); // topic 3.2

void discount(const DataNeeded* internalData, nodeSector** superEDA, nodeProduct** storage); // topic 3.3

void printProducts(DataNeeded* internalData, nodeSector** superEDA, nodeProduct** storage);

void createNewArea(DataNeeded* internalData); // topic 3.7

void managementMenu(DataNeeded* internalData, nodeSector** SuperEDA, nodeProduct** storage, Filepaths* supermarketFilepaths);


