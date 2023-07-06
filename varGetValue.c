/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: VarInfo
 * File: varGetValue.c
 * Author: davidblackburn
 * Created: June 02, 2014
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


//*******************************************************************
// Get the value of a variable as a string 							*
//*******************************************************************


// Check for null pointers		DONE and TESTED DFB 20140625

// Check for variable info		DONE and TESTED DFB 20140625

// Get Value					DONE and TESTED DFB 20141103
	
	// BOOL						DONE and TESTED DFB 20141103
			
	// SINT						DONE and TESTED DFB 20140625
	// INT						DONE and TESTED DFB 20140625
	// DINT						DONE and TESTED DFB 20140625
	// TIME						DONE and TESTED DFB 20140625
	// USINT					DONE and TESTED DFB 20140625
	// UINT						DONE and TESTED DFB 20140625
	// UDINT					DONE and TESTED DFB 20140625
	// DATE_AND_TIME			DONE and TESTED DFB 20140625

	// REAL						DONE and TESTED DFB 20140625

	// STRING					DONE and TESTED DFB 20140925
	
	// Unsupported type			DONE and TESTED DFB 20140625
	// Invalid type				DONE and TESTED DFB 20140625

	
unsigned short varGetValue(unsigned long pVariable)
{

	// Check for invalid input
	if (pVariable == 0) return (UINT)VAR_ERR_INVALIDINPUT;

	// Check address
	varVariable_typ	*ipVariable = (varVariable_typ*)pVariable;
	UINT status = 0;

	if (ipVariable->address == 0) {
		// Get info if necessary
		status = varGetInfo(pVariable);
		if (status != 0) return status;
	}


	//*******************************************************
	// Get value of variable and copy to Variable.value		*
	//*******************************************************

	DINT	valueDint;
	UDINT	valueUdint;
	REAL	valueReal;
	STRING 	valueString[VAR_STRLEN_NAME+1];
	UDINT	valueStringLen = 0;


	// Lazy Clear the Value string. It will be overwritten below
	valueString[0] = '\0';
	
	// Reset changed status
	ipVariable->changed = 0;


	switch( ipVariable->dataType ){
	
	
		//*******************************************************************************
		// BOOL																			*
		//*******************************************************************************
	
		case VAR_TYPE_BOOL:
		
			if( *(BOOL*)(ipVariable->address) == 0 ){
			
				strcpy( valueString, "false" );
			
			}
			else if( *(BOOL*)(ipVariable->address) == 1 ){
			
				strcpy( valueString, "true" );
			
			}
			else{
			
				// Invalid BOOL value.
				// Use convention of non-zero == TRUE for now
				strcpy( valueString, "true" );
			
			}
			
			valueStringLen = strlen( valueString );
		
			break;
	
	
		//*******************************************************************************
		// Integer types																*
		//*******************************************************************************
					
		case VAR_TYPE_SINT:
		
			valueDint=	*(SINT*)(ipVariable->address);
		
			brsitoa( valueDint, (UDINT)valueString );
			
			valueStringLen = strlen( valueString );
		
			break;
	
	
		case VAR_TYPE_INT:
		
			valueDint=	*(INT*)(ipVariable->address);
		
			brsitoa( valueDint, (UDINT)valueString );
		
			valueStringLen = strlen( valueString );
			
			break;
	
	
		case VAR_TYPE_DINT:
		case VAR_TYPE_TIME:
		
			valueDint=	*(DINT*)(ipVariable->address);
		
			brsitoa( valueDint, (UDINT)valueString );
		
			valueStringLen = strlen( valueString );
			
			break;
	
		case VAR_TYPE_BYTE:
		case VAR_TYPE_USINT:
		
			valueDint=	*(USINT*)(ipVariable->address);
		
			brsitoa( valueDint, (UDINT)valueString );
		
			valueStringLen = strlen( valueString );
			
			break;

		case VAR_TYPE_WORD:
		case VAR_TYPE_UINT:
		
			valueDint=	*(UINT*)(ipVariable->address);
		
			brsitoa( valueDint, (UDINT)valueString );
		
			valueStringLen = strlen( valueString );
			
			break;
	
		case VAR_TYPE_DWORD:
		case VAR_TYPE_UDINT:
		case VAR_TYPE_DATE_AND_TIME:
		
			valueUdint=	*(UDINT*)(ipVariable->address);
		
			uitoa( valueUdint, (UDINT)valueString );
		
			valueStringLen = strlen( valueString );
			
			break;
	
	
		//*******************************************************************************
		// REAL																			*
		//*******************************************************************************
	
		case VAR_TYPE_REAL:
		
			valueReal=	*(REAL*)(ipVariable->address);
		
			brsftoa( valueReal, (UDINT)valueString );
			
			valueStringLen = strlen( valueString );
		
			break;
	
		//*******************************************************************************
		// LREAL																			*
		//*******************************************************************************
	
		case VAR_TYPE_LREAL:
		
			valueReal=	(REAL)*(LREAL*)(ipVariable->address);
		
			brsftoa( valueReal, (UDINT)valueString );
			
			valueStringLen = strlen( valueString );
		
			break;
	
		//*******************************************************************************
		// STRING types																	*
		//*******************************************************************************
	
		case VAR_TYPE_STRING:
		
			valueStringLen = stringlcpy( (UDINT)valueString, ipVariable->address, sizeof(valueString) );
		
			break;
		
		case VAR_TYPE_WSTRING:
			
			valueStringLen = wstring2string( (UDINT)valueString, ipVariable->address, sizeof(valueString) );
			
			break;
		
	
		//*******************************************************************************
		// Unsupported and Invalid types												*
		//*******************************************************************************
	
		case VAR_TYPE_STRUCT:
		case VAR_TYPE_ULINT:
		case VAR_TYPE_DATE:
		case VAR_TYPE_ARRAY_OF_STRUCT:
		case VAR_TYPE_TIME_OF_DAY:
		case VAR_TYPE_LWORD:
		case VAR_TYPE_LINT: 
			status = VAR_ERR_UNSUPPORTEDTYPE; 
			break;
		
		case VAR_TYPE_UNDEFINED:  
			valueStringLen = stringlcpy( (UDINT)valueString, (UDINT)"undefined", sizeof(valueStringLen) ); 
			status = VAR_ERR_PV_NOT_FOUND;
			break;

		default: 
			status = VAR_ERR_INVALIDTYPE; 
			break;	
	
	
	} // switch(DataType) //

	// Check for value changed
	if( valueStringLen != strlen(ipVariable->value)
	|| strcmp( valueString, ipVariable->value )) {
		
		ipVariable->changed = 1;
		// Note: valueStringLen may be greater than sizeof(ipVariable->value)
		strcpy(ipVariable->value, valueString);
		
	}

	return status;


} // End Fn //
