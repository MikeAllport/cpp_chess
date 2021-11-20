#ifndef MAP_HELPER
#define MAP_HELPER

#include <map>

template<class K, class V>
bool MapKeyExists(const std::map<K, V>& map, K key)
{
    return map.find(key) != map.end();  
}

#endif