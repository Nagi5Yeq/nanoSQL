#include <iostream>
#include <string>
#include "BufferManager.hpp"
#include "CatalogManager.hpp"
#include "IndexCatalogPage.hpp"
#include "TableInfo.hpp"
#include "BPTree.hpp"
#include "Table.hpp"
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

	cout << ">>> ";
	while (1) {
		yyparse();
	}


	return 0;
}
