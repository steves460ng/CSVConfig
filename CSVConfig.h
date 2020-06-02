#ifndef _CSVCONFIG_H_
#define _CSVCONFIG_H_

#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

#include "vectorToMap.h"
#include "CSVReader.h"
#include "CSVWriter.h"

using namespace std;

#define CSV_KEY_TYPE vector<string>
#define CSV_PARAM_TYPE vector< vector<string> >
#define CSV_CONFIG_TYPE map<string, vector<string> >

void load_csv_config(char * config_file, CSV_CONFIG_TYPE & p)
{
	CSV_DATA data;
	data = csvReader(config_file);

	CSV_KEY_TYPE key;
	CSV_PARAM_TYPE param;
	vector<string> vec_cols;		
	string dummy_str;

	for (int rows = 0; rows < data.size(); rows++)
	{	
		vec_cols.clear();
		for(int cols = 0; cols < data[rows].size(); cols++)
		{
			// label
			if (cols == 0)
			{
				dummy_str = data[rows].at(cols);
				key.push_back(dummy_str);
			}
			// comment
			else
			{
				
				dummy_str = data[rows].at(cols);
				vec_cols.push_back(dummy_str);
			}
		}
		param.push_back(vec_cols);

	}

	p = vectorToMap<string, vector<string> >(key, param);
}

void save_csv_config(char * config_file, CSV_CONFIG_TYPE & p, char * sep=",")
{
	CSVWriter csv(sep);
	vector<string> keys;
	
	// Extract keys from map
	for(map<string, vector<string> >::iterator it = p.begin(); it != p.end(); ++it) 
	  keys.push_back(it->first);
	
	for(int rows = 0; rows < keys.size(); rows++)
	{
		csv.newRow() << keys[rows].c_str();
		for(int cols = 0; cols < p[keys[rows].c_str()].size(); cols++)
		{
			csv << p[keys[rows].c_str()].at(cols).c_str();
		}
	}
	csv.writeToFile(config_file);
}

#endif