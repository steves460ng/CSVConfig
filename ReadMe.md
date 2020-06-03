## CSVConfig Functions 
first column is Key and after are values.

for example
~~~
X_AXIS_KEEP_POSITION,107.9,20,200,200,X axis keep position config
"X_AXIS_KEEP_POSITION" is key and 107.9,20,200,200... are values.

And You can use it like this.

CSV_CONFIG_TYPE config;
load_csv_config("config.csv", config);

// position_value = 107.9
double position_value = atof(config["X_AXIS_KEEP_POSITION"].at(0).c_str());

In my case, the last column is used as a comment.
"X axis keep position config" <- this

You can use it in your own form. : )
~~~

## CSVWriter Class: CSV Writer C++ Library
Author : al-eax

https://github.com/al-eax

https://github.com/al-eax/CSVWriter

## Function csvReader : Simple CSV file reader
read csv file after return to
~~~
  vector< vector<string> >
~~~
format

## Function vectorToMap : 2 vector merge to 1 map
~~~
vector<string> key;
vecotr<int> value;  
~~~
to
~~~
map<string, int> output;
~~~
