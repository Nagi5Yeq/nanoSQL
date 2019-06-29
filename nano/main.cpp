#include <iostream>
#include <string>
#include "BufferManager.hpp"
#include "CatalogManager.hpp"
#include "IndexManager.hpp"
#include "RecordManager.hpp"
#include "y.tab.h"
extern int yyparse();


using namespace std;

int main(int argc, const char * argv[]) {

	BufferManager bm;

	if (!bm.indexCatalogFileIsExist("", ""))
	{
		IndexCatalogPage indexPage;
		indexPage.writeInitialPage();
	}

	cout << "nanoSQL> ";
	while (1) {
		yyparse();
	}


	return 0;
}
