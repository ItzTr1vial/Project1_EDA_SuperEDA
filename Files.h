#pragma once
#include <string>
#include "Structs.h"
using namespace std;

int calculateSizeofFile(string path);

string* getContentFromFiles(string path, int sizeofFile); // get the respective area of the product