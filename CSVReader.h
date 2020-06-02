#ifndef _CSVREADER_H_
#define _CSVREADER_H_

#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <string.h>

using namespace std;

#define CSV_DATA vector< vector<string> >

CSV_DATA csvReader(string csvfile, char * sep=",")
{
	CSV_DATA ret;
	ifstream csv(csvfile);
	
	string buf;

	int row = 0;	
	char colbuf[1024];

	while(csv.peek() != EOF)
	{
		// column data vector
		vector<string> row_cols;
		getline(csv, buf);
	
		// get row
		memset(colbuf, '\0', 1024);
		strcpy(colbuf, buf.c_str());

		// extrect column
		char * col = strtok(colbuf, sep);
		while(col != NULL)
		{
			string tmp(col);
			row_cols.push_back(tmp);
			col = strtok(NULL, sep);
		}
		// push row
		ret.push_back(row_cols);
	}
	return ret;
}
#endif