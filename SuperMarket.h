#pragma once
#include"Files.h"
#include"Structs.h"



void inicializeSectors(DataNeeded* internalData, Sector* superEDA);  //function that initializes all the sectors

void getAreasChoosen(DataNeeded* internalData, const Sector* superEDA); //function to create an array with the areas used in the structure

Product* inicializeProducts(const DataNeeded* internalData); //function that initializes all the products

void display(const DataNeeded* internalData, Sector* SuperEDA, Storage* supermarketStorage);

void assignProductsToSectors(Sector* superEda, Storage* supermarketStorage, const DataNeeded* internalData);

void menuSupermarket(DataNeeded* internalData,Sector* superEda, Storage* supermarketStorage, Filepaths* supermarketFilepaths);// Menu

