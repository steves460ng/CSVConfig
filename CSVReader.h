#ifndef _CSVREADER_H_
#define _CSVREADER_H_

#include <iostream>
#include <fstream>
#include <vector>

#include <stdio.h>
#include <string.h>

using namespace std;

#define CSV_DATA vector< vector<string> >

// Thx : )
// Author : Hosang 
// https://hahaite.tistory.com/1
void trim(string &str)
{
	int n;
	int aw; // all white space
	n = str.find_first_not_of("\t\v\n ");
	if ( n != string::npos )
		str.replace(0, n,"");
	
	n = str.find_last_not_of("\t\v\n ");
	if ( n != string::npos )
		str.replace(n+1, str.length()-n,"");
	
	aw = 0;
	for(int i = 0; i < str.length(); i++)
	{
		if(str.c_str()[i] == ' ')
			aw++;
	}
	
	if(aw == (str.length()))
		str = "";
}

// Thx : )
// Author : paxdiablo @ stackoverflow
// https://stackoverflow.com/users/14860/paxdiablo
char *paxtok (char *str, char *seps) {
    static char *tpos, *tkn, *pos = NULL;
    static char savech;

    // Specific actions for first and subsequent calls.
    if (str != NULL) {
        // First call, set pointer.
        pos = str;
        savech = 'x';
    } else {
        // Subsequent calls, check we've done first.
        if (pos == NULL)
            return NULL;
		
        // Then put character back and advance.
        while (*pos != '\0')
            pos++;
        *pos++ = savech;
    }

    // Detect previous end of string.
    if (savech == '\0')
        return NULL;

    // Now we have pos pointing to first character.
    // Find first separator or nul.
    tpos = pos;
    while (*tpos != '\0') {
        tkn = strchr (seps, *tpos);
        if (tkn != NULL)
            break;
        tpos++;
    }

    savech = *tpos;
    *tpos = '\0';

    return pos;
}

CSV_DATA csvReader(string csvfile, char * sep=",", char * sub_str="x")
{
	CSV_DATA ret;
	ifstream csv(csvfile);
	
	string buf;

	int row = 0;	
	char colbuf[1024];

	while(csv.peek() != EOF)
	{
		row = 0;
		
		// column data vector
		vector<string> row_cols;
		getline(csv, buf);
	
		// get row
		memset(colbuf, '\0', 1024);
		strcpy(colbuf, buf.c_str());

		// extrect column
		char * col = paxtok(colbuf, sep);
		while(col != NULL)
		{
			string tmp(col);
			trim(tmp);
			row_cols.push_back(tmp);
			
			if(row_cols[row].length() == 0)
			{
				string st(sub_str);
				row_cols[row] = st;
			}
			row++;
			col = paxtok(NULL, sep);
		}
		
		// push row
		ret.push_back(row_cols);
	}
	return ret;
}
#endif