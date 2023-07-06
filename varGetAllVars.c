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
#include "varGetAllVarsInternal.h"

#ifdef __cplusplus
	};
#endif


#include <string.h>


//*******************************************************************
// Get All variables on PLC				 							*
//*******************************************************************


// Fix: Seems to skip some variabels
void varGetAllVars(varGetAllVars_typ* t)
{
	// Check for invalid input
	if (t == 0) return;

	
	if(t->AcknowledgeError && isError(t)) {
		t->Status = 0;
	}
	
	if(t->Execute && isDone(t)) {
		t->Internal.iVar = 0xFFFF;
		t->Status = 65535;
		t->Internal.NextVariable = 1;
		t->Internal.numUniqueVars = 0;
	}
	
	t->Internal.validVar = 0;
	while(!t->Internal.validVar && isBusy(t)) {
		if(t->Internal.NextVariable) {
			
			getNextVariable(t);
			
			// Set rest of system bits that need to know next var
			t->Internal.moList.first = t->Internal.NextVariable; // moList needs to know to start back at begining
			setCheckGlobal(t); // Every new variable we need to check for global
			resetIsGlobal(t);
			
			t->Internal.NextVariable = 0;
			
			if(isError(t) || isDone(t)) continue;
		}
		
		if(checkGlobal(t)) {
			// Check if variable has global
			varRefresh(&t->Variable); // TODO: move thsi to getNextVariable
			strcpy(t->Variable.name, t->Internal.xList.name); // TODO: move thsi to getNextVariable
			
			t->Internal.validVar = checkValidVar(t);
			resetCheckGlobal(t);
			
			// getNextVariable returns all variables without a task perfix. So you can get duplicate variables (ex multiple Configurations)
			// So we record all varables found so we can see if we already checked this one
			// Because global variables cant exist in mulitple tasks we dont need to keep track of those
			if(isUniqueVar(t)) {
				setAsUniqueVar(t);
			} else {
				t->Internal.NextVariable = 1; // Skip this var because we already say this variable
				continue;
			}
			
			if(!t->Internal.validVar) {	
				continue;
			}
			
			setIsGlobal(t);
			
			if(variableIsStructure(t) && t->ExpandStructs || variableIsArray(t) && !t->CondenseArrays) {
				goDownALevel(t);
			}
			else if(variableIsArray(t) && t->CondenseArrays) {
				// tODO: Condense array to just [i]
				strcat(t->Variable.name, "[");
				strcat(t->Variable.name, "]");
			}
			
			if(!variableIsPrimitive(t) && t->PrimitivesOnly) {
				t->Internal.validVar = 0;
			}
			
			if(atTopLevel(t))
				t->Internal.NextVariable = 1; // Set new varaible here becuase if something is global then its in each task as well but we just want to say global
			
		}
		else if(atTopLevel(t)) {
			if(isGlobal(t)) {
				// We can get here for global structures or global array of strucutres
				t->Internal.NextVariable = 1; // Set new varaible here becuase if something is global then its in each task as well but we just want to say global
				continue;
			}
			
			getNextTask(t);
			
			if(isError(t)) continue;
			
			if(outOfTasks(t)) {
				t->Internal.NextVariable = 1;
				continue;
			}
			
			if(checkValidTask(t)) continue;
			
			t->Internal.validVar = checkValidVar(t);
			
			if(!t->Internal.validVar) continue;
			
			if(variableIsStructure(t) && t->ExpandStructs || variableIsArray(t) && !t->CondenseArrays) {
				goDownALevel(t);
			}
			else if(variableIsArray(t) && t->CondenseArrays) {
				// tODO: Condense array to just [i]
				strcat(t->Variable.name, "[");
				strcat(t->Variable.name, "]");
			}
			
			if(!variableIsPrimitive(t) && t->PrimitivesOnly) {
				t->Internal.validVar = 0;
			}
			
		}
		else {
			getMembers(t);
			
			while(outOfMemebers(t) && !atTopLevel(t)) {
				goUpALevel(t);
				getMembers(t);
			}
			
			if(atTopLevel(t)) continue;
			
			outputMember(t);
			
			incrementMember(t); // Increment member her so if we go down a level we come back to the next member
			
			if(variableIsStructure(t)) {
				goDownALevel(t); // So next pass we will be inside the current variable 
			}
			
			t->Internal.validVar = !t->PrimitivesOnly || variableIsPrimitive(t);
		}
	}
	
	if(isError(t)) {
		handleErrors(t);	
	}
	
	
	if(t->Status == 0) {
		memset(&t->Variable, 0, sizeof(t->Variable));	
	}
	
	return;
}


	
void varGetAllVars2(varGetAllVars_typ* t)
{

	// Check for invalid input
	if (t == 0) return;

	
	if(t->AcknowledgeError && t->Status && t->Status != 65535) {
		t->Status = 0;
	}
	
	if(t->Execute && t->Status == 0) {
		t->Internal.iVar = 0xFFFF;
		t->Status = 65535;
		t->Internal.NextVariable = 1;
	}
	
	if(t->Status == 65535) {
		char varName[256];
		UINT nextVarIndex;
		UINT xListStatus = 0;
		UINT moStatus = 0;
		VARIABLE_LOOP:
			if(t->Internal.iDeep == 0) {
				do {
					if(t->Internal.NextVariable) {
						nextVarIndex = t->Internal.iVar+1;
						xListStatus = PV_xlist(t->Internal.iVar, (UDINT)&nextVarIndex, &t->Internal.xList);
						t->Internal.iVar = nextVarIndex;
					}
		
					if(xListStatus == 0 || xListStatus == ERR_BUR_NOENTRY) {
						t->Internal.moList.enable = 1;
						t->Internal.moList.first = t->Internal.NextVariable;
						t->Internal.moList.pAppMoName = (UDINT)t->Internal.AppMoName;
						t->Internal.moList.pMoName = (UDINT)t->Internal.MoName;
						t->Internal.moList.sizeAppMoName = sizeof(t->Internal.AppMoName);
						t->Internal.moList.sizeMoName = sizeof(t->Internal.MoName);
			
			
			
						t->Status = xListStatus == ERR_BUR_NOENTRY ? 0 : 65535;
			
			
						t->Internal.moList.status = 0; // Set this to 0 to start the while loop
						t->Variable.dataType = VAR_TYPE_UNDEFINED; // Set this to UNDEFINED to start the while loop 
			
						if(t->Internal.NextVariable) {
							// Check if variable has global
							varRefresh(&t->Variable);
							strcpy(t->Variable.name, t->Internal.xList.name);
							varGetInfo(&t->Variable);
						}
						t->Internal.NextVariable = 0;
						while (t->Internal.moList.status == 0 && t->Variable.dataType == VAR_TYPE_UNDEFINED) {
				
							slMoList(&t->Internal.moList);
							t->Internal.moList.first = 0;
							if(t->Internal.moList.status != 0) break; // Break if error
				
							// 0x11 = Object of a cyclic resource 
							// MoName will be empty if its a cyclic not added by User
							if(t->Internal.moList.moType != 0x11 || t->Internal.MoName[0] == '\0') continue; 
							varRefresh(&t->Variable);
							strcpy(t->Variable.name, t->Internal.MoName);
							strcat(t->Variable.name, ":");
							strcat(t->Variable.name, t->Internal.xList.name);
							varGetInfo(&t->Variable);
							varGetValue(&t->Variable);
					
						}
			
						if(t->Internal.moList.status == ERR_BUR_NOENTRY) {
							t->Internal.NextVariable = 1;
						}
						else if(t->Internal.moList.status && moStatus != 65535 && moStatus != ERR_BUR_NOENTRY) {
							t->Status = moStatus;	
						}
			
						//			if(t->Internal.xList.dimension > 0) {
						//				strcat(varName, "[0]");
						//			}
						//			else if(t->Internal.xList.data_typ == PB_DT_ARRAY) {
						//				strcat(varName, "[1]");
						//			}
			
		
					}
					else {
						t->Status = xListStatus;
					}
				} while(t->Internal.moList.status == ERR_BUR_NOENTRY && xListStatus == 0);
			}
			else {
				variableBrowser(&t->Internal.Browser);
				while(t->Internal.iMember[t->Internal.iDeep] > t->Internal.Browser.NumberMembers){
					t->Internal.Browser.Back = 1;
					t->Internal.iDeep--;
					strcpy(t->Internal.Deep[t->Internal.iDeep], "");
					t->Internal.iMember[t->Internal.iDeep] = 0;
					variableBrowser(&t->Internal.Browser);
					if(t->Internal.iDeep == 0) {
						t->Internal.iDeep = 0;
						goto VARIABLE_LOOP;
						// break;
						// We need to jump back to task loop here
					}
				}
				variableBrowser(&t->Internal.Browser);
				memcpy(&t->Variable, &t->Internal.Browser.MemberInfo[t->Internal.iMember[t->Internal.iDeep]], sizeof(t->Variable));
			
				t->Internal.iMember[t->Internal.iDeep]++;
				if(t->Variable.dataType == VAR_TYPE_STRUCT) {
					t->Internal.Browser.MemberIndex = t->Internal.iMember[t->Internal.iDeep]-1;
				}
			
			}
		
		if(t->Variable.dataType == VAR_TYPE_STRUCT) {
			strcpy(t->Internal.Deep[t->Internal.iDeep], t->Variable.name);
			if(t->Internal.iDeep == 0) // Name browser will update its own name if we are digging deeper on an existing variable
				strcpy(t->Internal.Browser.VariableName, t->Variable.name);
			t->Internal.iDeep++;
		}
	}

	return;


} // End Fn //


