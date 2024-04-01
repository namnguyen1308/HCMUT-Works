#include "kNN.hpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
void tc1155()
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");
Dataset dataset_extract = dataset.extract();
dataset_extract.getShape(nRows, nCols);
cout << "Dataset extract shape: " << nRows << "x" << nCols << endl;
}
int main() {
    tc1155();
    
   _CrtDumpMemoryLeaks();
   return 0;
}
