#pragma once
#include"Files.h"
#include"Structs.h"



void inicializeSectors(const DataNeeded* interinData, Sector* superEDA);  //function that initializes all the sectors

string* getAreasChoosen(const DataNeeded* interinData, const Sector* superEDA); //function to create an array with the areas used in the structure

void display(const DataNeeded* interinData, Sector* SuperEDA, Storage* supermarketStorage);

Product* inicializeProducts(const DataNeeded* interinData); //function that initializes all the products

void assignProductsToSectors(Sector* superEda, Storage* supermarketStorage, const DataNeeded* interinData);

void menuSupermarket(const DataNeeded* interinData,Sector* superEda, Storage* supermarketStorage);// Menu

