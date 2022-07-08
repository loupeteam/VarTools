/*******************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: VarTools
 * File: varRefresh.c
 * Author: Lawrence
 * Created: April 9, 2020
 ********************************************************************
 * Implementation of library VarTools
 ********************************************************************/
unsigned long bur_heap_size = 0xFFFFFF;

#include <bur/plctypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

#include "varToolsInternal.h"
#include "VarTools.h"

#ifdef __cplusplus
};
#endif

#include "varCache.h"
#include <string>
#include <algorithm>
#include "string.h"

using namespace varTools;
using namespace std;

Cache::Cache(void)
{
}

Cache::~Cache()
{
}


/////////////////////////////////
// DEBUG
/////////////////////////////////

size_t Cache::size() {
	return _cache.size();
}

size_t Cache::capacity() {
	return _cache.capacity();
}

void Cache::clear() {
	auto it = _cache.begin();
	while (it != _cache.end())
    {
        // remove cache items that do not have alias
        if (it->alias.empty())
        {
            // `erase()` invalidates the iterator, use returned iterator
            it = _cache.erase(it);
        }
        // Notice that the iterator is incremented only on the else part
        else {
			// If we can not remove cache item, clean it instead
			it->address = 0;
			it->authorization.clear();
			it->dimension = 0;
			//it->lastAccessed = 0;
			it->length = 0;
			it->subscribers.clear();
			it->type = VAR_TYPE_STRUCT;
			it->value.clear();

            ++it;
        }
    }
}

void Cache::forceClear() {
	_cache.clear(); // Note: This may not resize vector
}


////////////////////////////////
// PUBLIC
////////////////////////////////


const char* Cache::getValue(char* varName) {
	cacheItem_typ* cacheItem = _getCacheItem(varName);
	if(!cacheItem) cacheItem = _addVariable(varName);
	_updateCacheItem(cacheItem);
	return cacheItem->value.c_str();
}

const char* Cache::getInfo(char* varName, varVariable_typ& var) {
	cacheItem_typ* cacheItem = _getCacheItem(varName);
	if(!cacheItem) cacheItem = _addVariable(varName);
	_updateCacheItem(cacheItem);
	var.address = (unsigned long)cacheItem->address;
	var.dataType = cacheItem->type;
	var.dimension = cacheItem->dimension;
	var.length = cacheItem->length;
	strncpy(var.name, cacheItem->variable.c_str(), sizeof(var.name)-1);
	strncpy(var.value, cacheItem->value.c_str(), sizeof(var.value)-1);
	return cacheItem->value.c_str();
}

void Cache::addAlias(char* varName, char* alias) {
	cacheItem_typ* cacheItem = _getCacheItem(varName);
	if(!cacheItem) { 
		cacheItem = _addVariable(varName, alias);
	}
	else {
		cacheItem->alias = alias;
	}
}

void Cache::subscribe(char* varName, cacheSubscribeLink_typ& link) {
	
}

void Cache::subscribe(varVariable_typ& var, cacheSubscribeLink_typ& link) {

}

void Cache::addVariable(char* varName) {
	cacheItem_typ* cacheItem = _getCacheItem(varName);
	if(!cacheItem) { 
		cacheItem = _addVariable(varName);
	}
}

bool Cache::inCache(char* varName) {
	cacheItem_typ* cacheItem = _getCacheItem(varName);
	return cacheItem != NULL;
}

///////////////////////////////////
// PRIVATE
//////////////////////////////////

cacheItem_typ *Cache::_addVariable(char *varName)
{
	cacheItem_typ cacheItem;
	cacheItem.variable = varName;
	_updateCacheItem(&cacheItem);

	switch (_sortMode)
	{
	case CACHE_SORT_CONTINUOS:
		// TODO: Implement
		// We need to add in alphabetic order
		break;

	case CACHE_SORT_COMMAND:
		_isSorted = false;
		// Fall through so we add item to cache, unsorted

	case CACHE_SORT_NONE:
	default:
		_cache.push_back(cacheItem);
		break;
	}
}

cacheItem_typ *Cache::_addVariable(char *varName, char *alias)
{
	varTools::cacheItem_typ *cacheItem = _addVariable(varName);
	cacheItem->alias = alias;
}

cacheItem_typ *Cache::_getCacheItem(char *varName) 
{
	// auto is_match = [](cacheItem_typ i){ return (i.variable == varName) || (i.alias == varName); };
	auto is_match = [](cacheItem_typ i){ return (i.variable == "varName"); };
	auto it = find_if(_cache.begin(), _cache.end(), is_match);
	return it == _cache.end() ? NULL : &(*it);
}

void Cache::_updateCacheItem(cacheItem_typ* item)
{
	varVariable_typ var = {};

	if (item->address)
	{
		var.address = (unsigned long)item->address;
		var.dataType = (unsigned long)item->type;
		var.length = item->length;
	}
	else
	{
		strncpy(var.name, item->variable.c_str(), sizeof(var.name) - 1);
	}

	varGetValue((unsigned long)&var);

	item->address = (void*)var.address;
	item->value = var.value;
	item->type = (VAR_TYPE_enum)var.dataType;
	item->length = var.length;
	item->dimension = var.dimension;
	item->lastAccessed = _getCurrentTime();
}

cacheTime Cache::_getCurrentTime(void)
{
	return 0; // TODO: Populated this. Maybe just use ms after boot. clock_ms?
}
