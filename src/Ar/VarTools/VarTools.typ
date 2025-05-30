(*
 * File: VarTools.typ
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of VarTools, licensed under the MIT License.
 *
 *)

TYPE
	VAR_ERR_enum : 
		(
		VAR_ERR_PV_NOT_FOUND := 14710,
		VAR_ERR_PVITEM_ENUM := 14713,
		VAR_ERR_INVALIDINPUT := 50000,
		VAR_ERR_INVALIDVALUE,
		VAR_ERR_UNSUPPORTEDTYPE,
		VAR_ERR_INVALIDTYPE,
		VAR_ERR_TOO_MANY_ITEMS,
		VAR_ERR_
		);
	VAR_TYPE_enum : 
		(
		VAR_TYPE_STRUCT := 0, (*0*)
		VAR_TYPE_BOOL,
		VAR_TYPE_SINT,
		VAR_TYPE_INT,
		VAR_TYPE_DINT,
		VAR_TYPE_USINT, (*5*)
		VAR_TYPE_UINT,
		VAR_TYPE_UDINT,
		VAR_TYPE_REAL,
		VAR_TYPE_STRING,
		VAR_TYPE_ULINT, (*10*)
		VAR_TYPE_DATE_AND_TIME,
		VAR_TYPE_TIME,
		VAR_TYPE_DATE,
		VAR_TYPE_LREAL,
		VAR_TYPE_ARRAY_OF_STRUCT, (*15*)
		VAR_TYPE_TIME_OF_DAY,
		VAR_TYPE_BYTE,
		VAR_TYPE_WORD,
		VAR_TYPE_DWORD,
		VAR_TYPE_LWORD, (*20*)
		VAR_TYPE_WSTRING, (*21*)
		VAR_TYPE_LINT := 23, (*23*)
		VAR_TYPE_UNDEFINED := 999
		);
	varVariable_typ : 	STRUCT 
		name : STRING[VAR_STRLEN_NAME];
		value : STRING[VAR_STRLEN_VALUE];
		address : UDINT;
		dataType : UDINT;
		length : UDINT;
		dimension : UINT;
	END_STRUCT;
	varGetAllVars_internal_typ : 	STRUCT 
		iVar : UDINT := 65535;
		iDeep : UINT;
		iMember : ARRAY[0..49]OF UINT;
		Browser : variableBrowser;
		Deep : ARRAY[0..49]OF STRING[VAR_STRLEN_NAME];
		NextVariable : BOOL;
		xList : PV_xList_typ;
		moList : slMoList;
		AppMoName : STRING[32];
		MoName : STRING[12];
		checkGlobal : BOOL;
		isGlobal : BOOL;
		validVar : BOOL;
		numUniqueVars : UDINT;
		uniqueVars : ARRAY[0..1999]OF STRING[VAR_STRLEN_NAME];
	END_STRUCT;
END_TYPE
