#pragma once
#include"Files.h"
#include"Structs.h"

void inicializeSectors(const DataNeeded* interinData, Sector* superEDA);  //function that initializes all the sectors

string* getAreasChoosen(const DataNeeded* interinData, const Sector* superEDA); //function to create an array with the areas used in the structure

void inicializeProducts(const DataNeeded* interinData, Product* allProducts); //function that initializes all the products
