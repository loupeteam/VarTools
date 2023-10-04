
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
		go1 : BOOL;
		go2 : BOOL;
		go3 : BOOL;
		go4 : BOOL;
		go5 : BOOL;
	END_STRUCT;
	task_par_typ : 	STRUCT 
		far1 : REAL;
		far2 : REAL;
		far3 : REAL;
		far4 : REAL;
		far5 : REAL;
		far : REAL;
	END_STRUCT;
	task_out_typ : 	STRUCT 
		state : task_state_typ;
		state1 : INT;
		state2 : INT;
		state3 : INT;
	END_STRUCT;
	task_state_typ : 	STRUCT 
		state1 : INT;
		state2 : INT;
		state3 : INT;
		state4 : INT;
		state : INT;
	END_STRUCT;
	io_typ : 	STRUCT 
		in : io_in_typ;
		out : io_out_typ;
	END_STRUCT;
	io_in_typ : 	STRUCT 
		top : BOOL;
		bottom : BOOL;
	END_STRUCT;
	io_out_typ : 	STRUCT 
		up : BOOL;
		down : BOOL;
	END_STRUCT;
	configuration_typ : 	STRUCT 
		enable : BOOL;
		timeout : TIME;
	END_STRUCT;
END_TYPE
