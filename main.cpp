#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

#include "CSVConfig.h"

int main()
{
	CSV_CONFIG_TYPE p;
	
	load_csv_config("test.csv", p);
	
	// Load 
	printf(">>> %0.3f : %s\n", atof(p["key1"].at(0).c_str()), p["key1"].at(3).c_str());
	
	// modify
	p["key100"][0] = "1979";
	p["key10"][1] = "1818";
	p["key1"][2] = "8.888";
	
	// save
	save_csv_config("test.csv", p);

	return 0;
}

