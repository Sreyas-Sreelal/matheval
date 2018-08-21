//matheval.inc

#if defined _inc_matheval
	#undef _inc_matheval
#endif

#if defined _matheval_included
	#endinput
#endif

#define _matheval_included

#if !defined BUFFER_SIZE
    #define BUFFER_SIZE (128)
#endif

#define FloatNaN Float:0x7FFFFFFF

#define isOperator(%0) (%0=='+'||%0=='-'||%0=='*'||%0=='/'||%0=='^')
#define isNum(%0) (%0>='0'&&%0<='9')
#define isValidMEChar(%0) (isOperator(%0)||%0=='.'||%0=='('||%0==')'||%0==' '||isNum(%0))

enum ME_OPERATOR_PRIORITY{
	PLUS_AND_MINUS,
	PRODUCT_AND_DIVISION,
	EXPONENTIAL,
};

static stock 
	MEStack[BUFFER_SIZE],
	InfixExpression[BUFFER_SIZE],
	MEQueue[BUFFER_SIZE];

static stock
	TOP   = -1,
	OQFRONT = -1,
	OQREAR  = -1;

static ME_push(opr){

	if(TOP == BUFFER_SIZE-1){ 
		#if defined ME_DEBUG_MODE
			printf("[Error] MEStack overflow! Can't push %c to MEStack",opr);
		#endif
		return cellmin;
	}
	MEStack[++TOP] = opr;
	return 1;
}

static ME_insert(chr){
	if(OQREAR == -1 )
		++OQFRONT;
	else if(OQREAR == BUFFER_SIZE-1)
		return cellmin;
	MEQueue[++OQREAR] = chr;
	return 1;
}

static ME_pop(){
	if(TOP<0){
		#if defined ME_DEBUG_MODE
			printf("[Error] MEStack underflow!");
		#endif
		return cellmin;
	}
	return MEStack[TOP--];
}

static ME_delete(){
	if(OQFRONT > OQREAR)
		return cellmin;
	return MEQueue[OQFRONT++];
}

static ME_OPERATOR_PRIORITY:GetPriority(opr){
	new ME_OPERATOR_PRIORITY:priority;
	switch(opr){
		case '+','-' : priority = PLUS_AND_MINUS;
		case '*','/' : priority = PRODUCT_AND_DIVISION;
		case '^' : priority = EXPONENTIAL;
		default : return ME_OPERATOR_PRIORITY:cellmin;
	}
	return priority;
}

static bool:toPostfix(Infix[]){
	new 
		InputExpression[BUFFER_SIZE],
		chr,
		idx = -1,
		OperatorInStack,
		bool:IsPrevOperator = true;

	format(InputExpression,sizeof(InputExpression),"(%s)",Infix);
		
	while((chr = InputExpression[++idx]) != '\0'){
		#if defined ME_DEBUG_MODE
			new temp[23];
			strmid(temp, MEStack, 0, TOP);
			printf("[DEBUG] Iter %d stack : %s current chr %c top is %d",idx,temp,chr,TOP);
		#endif

		if(!isValidMEChar(chr))
			return false;
		
		if(isOperator(chr)) {
			if(IsPrevOperator)
				return false;
			IsPrevOperator = true;
			ME_insert(' ');
			while(TOP != -1 && GetPriority(MEStack[TOP]) >= GetPriority(chr)) {
				OperatorInStack = ME_pop();
				if(OperatorInStack != cellmin)
					ME_insert(OperatorInStack);
				else
					return false;
			}
			
			if(ME_push(chr) == cellmin) 
				return false;

		}else if(chr == '('){
			IsPrevOperator = false;
			if(ME_push(chr) == cellmin) 
				return false;
		}else if(chr == ')') {
			IsPrevOperator = false;
			while((OperatorInStack = ME_pop()) != '(') {
				if(OperatorInStack != cellmin)
					ME_insert(OperatorInStack);
				else 
					return false;
			}
		}else{
			IsPrevOperator = false;
			ME_insert(chr);
		}
	}

	if(TOP != -1)
		return false;
	
	return true;
}

static Float:ME_CalCulate(Float:operand1,Float:operand2,opr){
	switch(opr){
		case '+': return floatadd(operand1, operand2);
		case '-': return floatsub(operand1, operand2);
		case '*': return floatmul(operand1, operand2);
		case '/': return floatdiv(operand1, operand2);
		case '^': return floatpower(operand1,operand2);	
	}
	return FloatNaN;
}

stock ConvertToFloatArray(Float:evalStack[]){
	new 
		idx=-1,
		tempidx,
		ch;

	while(OQFRONT<=OQREAR){
		new number[11];
		tempidx = 0;
		ch = ME_delete();
		if(isNum(ch)){
			number[tempidx] = ch;
			for(;;){
				ch = ME_delete();
				if(isNum(ch) || ch == '.')
					number[++tempidx] = ch;
				else 
					break;
			} 
			evalStack[++idx] = floatstr(number);
		}
		if(isOperator(ch)){
			evalStack[++idx] = cellmin;
		}
	}
	#if defined ME_DEBUG_MODE
		printf("Operand array : ");
		for(new i;i<=idx;++i)
			printf("%f",evalStack[i]);
	#endif
	return idx;
}

stock Float:MathEval(expression[]){
	
	TOP  = OQFRONT = OQREAR  = -1;
	
	new 
		Float:OperandArray[BUFFER_SIZE],
		OperandArraySize = -1,
		OpArray[BUFFER_SIZE - 1],
		idx,
		oidx = -1,
		Float:evalStack[BUFFER_SIZE],
		evalTop = -1,
		bool:success;
	
	success = toPostfix(expression);
	
	TOP = -1;
	strdel(MEStack,0,sizeof(MEStack)); 
	
	if(!success){
		#if defined ME_DEBUG_MODE
			printf("Failed Infix to Postfix");
		#endif
		return FloatNaN;
	}

	#if defined ME_DEBUG_MODE
		new temp[BUFFER_SIZE];
		strmid(temp,MEQueue,OQFRONT,OQREAR+1);
		printf("Output queue %s \n",temp,MEStack);
	#endif

	for(idx = OQFRONT;idx <= OQREAR;++idx)
		if(isOperator(MEQueue[idx]))
			OpArray[++oidx] = MEQueue[idx];
	
	#if defined ME_DEBUG_MODE
		printf("Operator array:");
		for(idx=0;idx<=oidx;++idx)
			printf("%c",OpArray[idx]);
	#endif		
	OperandArraySize = ConvertToFloatArray(OperandArray);
	
	if(OperandArraySize == -1 )
		return FloatNaN;

	new
		Float:operand1,
		Float:operand2;

	for(idx = 0,oidx=0;idx <= OperandArraySize; ++idx){
		if(OperandArray[idx] == cellmin){
			operand2 = evalStack[evalTop--];
			operand1 = evalStack[evalTop--];
			evalStack[++evalTop] = ME_CalCulate(operand1,operand2,OpArray[oidx++]);
		}else
			evalStack[++evalTop] = OperandArray[idx];
	}
	return evalStack[evalTop];
}
