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

// varCache.h
#ifndef VAR_CACHE_H // include guard
#define VAR_CACHE_H

//unsigned long bur_heap_size = 0xFFFFFF;

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


#include <string>
#include <vector>

namespace varTools
{
	typedef unsigned long cacheTime;

	struct cacheSubscribeLink_typ { // TODO: This type is not implemented yet
		int dummy;
	};
	
	struct cacheSubscribe_typ {
		cacheSubscribeLink_typ* link;
	};
	
	struct cacheAuth_typ {
		std::string userToken; // TODO: We can probably define the size of the string here
	};

	enum cacheSortMode_enum {
		CACHE_SORT_NONE,
		CACHE_SORT_CONTINUOS,
		CACHE_SORT_COMMAND
	};
	
	struct cacheItem_typ {
		std::string variable;
		std::string alias;
		std::string value;
		VAR_TYPE_enum type;
		void* address = 0; // This needs to be initialized to 0
		size_t length;
		size_t dimension;
		cacheTime lastAccessed; // TODO: Maybe make it something other than a udint
		std::vector<varTools::cacheSubscribe_typ> subscribers; // This may end up being a vector of pointers of cacheSubLink_typ
		std::vector<varTools::cacheAuth_typ> authorization;
	};
	
	
	class Cache
	{
		public:
		// For debug, maybe has other uses
		size_t size();
		size_t capacity();
		void clear(); // Does not clear variables with alias'
		void forceClear(); // Clears everything out of the cache
		
		// Interface
		Cache(void);
		~Cache(void);

		const char* getValue(char*); // TODO: We will probably need more information here
		const char* getInfo(char*, varVariable_typ&);
		void addAlias(char*, char*);
		void subscribe(char*, cacheSubscribeLink_typ&);
		void subscribe(varVariable_typ&, cacheSubscribeLink_typ&);
		void addVariable(char*); // This function will add variable if not already in the cache
		bool inCache(char*); // Returns true if variable is in cache
		
		private:
		
		cacheItem_typ* _addVariable(char*); // This function will add a new variable to the cache without checking if it already exists
		cacheItem_typ* _addVariable(char*, char*);
		cacheItem_typ* _getCacheItem(char*);
		void _updateCacheItem(cacheItem_typ*);
		cacheTime _getCurrentTime(void);
		
		std::vector<cacheItem_typ> _cache;
		bool _isSorted = false;
		cacheSortMode_enum _sortMode = CACHE_SORT_NONE;
	};
}

#endif /* VAR_CACHE_H */
