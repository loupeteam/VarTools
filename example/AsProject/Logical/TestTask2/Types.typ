
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
		go6 : BOOL;
		go7 : BOOL;
		go8 : BOOL;
		go9 : BOOL;
		go10 : BOOL;
		go11 : BOOL;
		go12 : BOOL;
	END_STRUCT;
	task_par_typ : 	STRUCT 
		far1 : REAL;
		far4 : REAL;
		far5 : REAL;
		far : REAL;
	END_STRUCT;
	task_out_typ : 	STRUCT 
		state4 : task_state_typ;
		state : task_state_typ;
		state3 : INT;
	END_STRUCT;
	task_state_typ : 	STRUCT 
		state4 : INT;
		state : INT;
	END_STRUCT;
	io_typ : 	STRUCT 
		in : io_in_typ;
		out : io_out_typ;
	END_STRUCT;
	io_in_typ : 	STRUCT 
		bottom : BOOL;
	END_STRUCT;
	io_out_typ : 	STRUCT 
		down : BOOL;
	END_STRUCT;
	configuration_typ : 	STRUCT 
		enable : BOOL;
		timeout : TIME;
	END_STRUCT;
END_TYPE
