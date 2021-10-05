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

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

	#include "VarTools.h"

#ifdef __cplusplus
	};
#endif


#include <string.h>


//*******************************************************************
// Force refresh of variable info in next getValue call				*
//*******************************************************************


unsigned short varRefresh(unsigned long pVariable)
{

// check for invalid inputs
if( pVariable == 0 ) return (UINT)VAR_ERR_INVALIDINPUT;

varVariable_typ* ipVariable = (varVariable_typ*) pVariable;

// forces varGetInfo on next getValue call for this pv
memset((void*) &ipVariable->address, 0, sizeof(ipVariable->address));

return 0;
	
} // End Fn
