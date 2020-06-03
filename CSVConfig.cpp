#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <map>

#include <stdio.h>
#include <string.h>

#include "CSVConfig.h"

using namespace std;

class CSVWriter
{
    public:
        CSVWriter(){
            this->firstRow = true;
            this->seperator = ";";
            this->columnNum = -1;
            this->valueCount = 0;
        }

        CSVWriter(int numberOfColums){
            this->firstRow = true;
            this->seperator = ";";
            this->columnNum = numberOfColums;
            this->valueCount = 0;
        }

        CSVWriter(string seperator){
            this->firstRow = true;
            this->seperator = seperator;
            this->columnNum = -1;
            this->valueCount = 0;
        }

        CSVWriter(string seperator, int numberOfColums){
            this->firstRow = true;
            this->seperator = seperator;
            this->columnNum = numberOfColums;
            this->valueCount = 0;
            cout << this->seperator << endl;
        }

        CSVWriter& add(const char *str){
            return this->add(string(str));
        }

        CSVWriter& add(char *str){
            return this->add(string(str));
        }

        CSVWriter& add(string str){
            //if " character was found, escape it
            size_t position = str.find("\"",0);
            bool foundQuotationMarks = position != string::npos;
            while(position != string::npos){
                str.insert(position,"\"");
                position = str.find("\"",position + 2);
            }
            if(foundQuotationMarks){
                str = "\"" + str + "\"";
            }else if(str.find(this->seperator) != string::npos){
                //if seperator was found and string was not escapted before, surround string with "
                str = "\"" + str + "\"";
            }
            return this->add<string>(str);
        }

        template<typename T>
        CSVWriter& add(T str){
            if(this->columnNum > -1){
                //if autoNewRow is enabled, check if we need a line break
                if(this->valueCount == this->columnNum ){
                    this->newRow();
                }
            }
            if(valueCount > 0)
                this->ss << this->seperator;
            this->ss << str;
            this->valueCount++;

            return *this;
        }

        template<typename T>
        CSVWriter& operator<<(const T& t){
            return this->add(t);
        }

        void operator+=(CSVWriter &csv){
            this->ss << endl << csv;
        }

        string toString(){
            return ss.str();
        }

        friend ostream& operator<<(std::ostream& os, CSVWriter & csv){
            return os << csv.toString();
        }

        CSVWriter& newRow(){
            if(!this->firstRow || this->columnNum > -1){
                ss << endl;
            }else{
                //if the row is the first row, do not insert a new line
                this->firstRow = false;
            }
            valueCount = 0;
            return *this;
        }

        bool writeToFile(string filename){
            return writeToFile(filename,false);
        }

        bool writeToFile(string filename, bool append){
            ofstream file;
            if(append)
                file.open(filename.c_str(),ios::out | ios::app);
            else
                file.open(filename.c_str(),ios::out | ios::trunc);
            if(!file.is_open())
                return false;
            if(append)
                file << endl;
            file << this->toString();
            file.close();
            return file.good();
        }

        void enableAutoNewRow(int numberOfColumns){
            this->columnNum = numberOfColumns;
        }

        void disableAutoNewRow(){
            this->columnNum = -1;
        }
    protected:
        bool firstRow;
        string seperator;
        int columnNum;
        int valueCount;
        stringstream ss;

};

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

template <typename K, typename V> 
map<K, V> vectorToMap(vector<K> key, vector<V> value)
{
	map<K, V> ret_map;

	if (key.size() == value.size())
	{
		typename vector<K>::iterator it;
		typename vector<V>::iterator dt;
		for(it = key.begin(), dt = value.begin(); it != key.end(); it++, dt++)
		{
			ret_map.insert( make_pair (*it, *dt));
		}
	}
	return ret_map;
}

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
			if (strlen(data[rows].at(cols).c_str()) != 0)
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
			} // if (strlen(data[rows].at(cols).c_str()) != 0)
		}
		param.push_back(vec_cols);

	}

	p = vectorToMap<string, vector<string> >(key, param);
}

void save_csv_config(char * config_file, CSV_CONFIG_TYPE & p, char * sep)
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

bool check_csv_config_key(CSV_CONFIG_TYPE &p, char * key)
{
	if(p.find(key) == p.end())
		return false;
	return true;
}