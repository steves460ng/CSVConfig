#ifndef _VECTORTOMAP_H_
#define _VECTORTOMAP_H_

#include <vector>
#include <map>
#include <iostream>

using namespace std;

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

#endif