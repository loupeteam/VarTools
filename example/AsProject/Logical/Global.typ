
TYPE
	task_typ : 	STRUCT 
		in : task_in_typ;
		out : task_out_typ;
	END_STRUCT;
	task_in_typ : 	STRUCT 
		cmd : task_cmd_typ;
		par : task_par_typ;
	END_STRUCT;
	task_cmd_typ : 	STRUCT 
		go : BOOL;
	END_STRUCT;
	task_par_typ : 	STRUCT 
		far : REAL;
	END_STRUCT;
	task_out_typ : 	STRUCT 
		state : REAL;
	END_STRUCT;
END_TYPE
