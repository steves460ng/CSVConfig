#ifndef _CSVCONFIG_H_
#define _CSVCONFIG_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

#define CSV_KEY_TYPE vector<string>
#define CSV_PARAM_TYPE vector< vector<string> >
#define CSV_CONFIG_TYPE map<string, vector<string> >
#define CSV_DATA vector< vector<string> >

void load_csv_config(char * config_file, CSV_CONFIG_TYPE & p);
void save_csv_config(char * config_file, CSV_CONFIG_TYPE & p, char * sep=",");
bool check_csv_config_key(CSV_CONFIG_TYPE &p, char * key);

#endif