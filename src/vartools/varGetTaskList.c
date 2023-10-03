/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: VarTools
 * File: varGetVariableList.c
 * Author: Josh
 * Created: May 29, 2015
 ********************************************************************
 * Implementation of library VarTools
 ********************************************************************/

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


#include <string.h>
#include <stdlib.h>


//*******************************************************************
// Get a list of all local and global variables with a given name 	*
//*******************************************************************

// DONE passes first tests

unsigned short varGetTaskListJson(plcstring* List, unsigned long size)
{
	
	//structure to look through data objects
	MO_List_typ item;

	//Keep track of the objects that we've gone through
	//unsigned int objectIndex = 0;
	UINT objectIndex = 0;

	UINT index=0;
	BOOL duplicate=0;
		
	//Number of variables that have been found
	UINT numberVariables =0;
	UINT maxVariables = size/81;
	
	char list[maxVariables][81];	
	//Check for valid inputs
	if( List == 0 ) return (UINT)VAR_ERR_INVALIDINPUT;
	
	//Clear out any bad data
	memset((void*)List,0,size);		
	memset((void*)list,0,size);		
	
	//Look through all the objects
	while( MO_list(objectIndex, &objectIndex, &item) == 0 && numberVariables < maxVariables ){
		//If it is a cyclic object check if it has the variable
		if( item.type == 0x11){			
			duplicate=0;				
			for(index=0;index<numberVariables;index++){
				if(strcmp(item.name, list[index] )==0){
					duplicate=1;
					break;
				}
			}
			if(!duplicate){
				strcpy( list[numberVariables],item.name);
				numberVariables++;				
			}
		}
	}
		
	//Sort the list that we found to ensure the order doesn't change arbitrarily.
	qsort(list,numberVariables,sizeof(list[0]),(int(*)(const void*,const void*))strcmp);
		
	//Copy list out for the user
	memcpy((void*)List,list,sizeof(list));	

	//Return the number of found variables to make it easy to add to the list outside the function.
	return numberVariables;
	
}
