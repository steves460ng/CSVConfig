#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

#include "CSVConfig.h"

int main()
{
	CSV_CONFIG_TYPE p;
	
	load_csv_config("teaching.csv", p);
	
	// Load 
	printf(">>> %0.3f : %s\n", atof(p["AX00_ELV_UP"].at(0).c_str()), p["AX00_ELV_UP"].at(4).c_str());
	
	// modify
	p["AX00_ELV_UP"][0] = "1979";
	
	// save
	save_csv_config("teaching.csv", p);

	return 0;
}

