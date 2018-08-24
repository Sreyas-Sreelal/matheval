#include<a_samp>

#define RUN_TESTS
#include <YSI\y_testing>

//#define ME_DEBUG_MODE
#include "matheval"

Test:NormalExpression(){
	new expression[] = "((2^3)+1)/3*4-2";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f",expression,result);
	ASSERT(floatcmp(result,10.0) == 0));
}

Test:IrrationalResult(){
	new expression[] = "(((2^3)+1)/3*4-2)/3";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f",expression,result);
	ASSERT(floatcmp(result,3.33) == 1));
}

Test:ExpressionParanthesisError(){
	new expression[] = "(56-12)(";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(result != result);
}

Test:OperatorAtBeginningError(){
	new expression[] = "+12+(12-12)";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(result != result);
}

Test:OperatorAtEndError(){
	new expression[] = "1+3+";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(result != result);
}

Test:InvalidInfixExpression(){
	new expression[] = "12 13 +";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(result != result);
}

Test:DivisionByZeroError(){
	new expression[] = "(2^6)/(5-5)";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(result != result);
}

Test:AdjacentOperatorError(){
	new expression[] = "12*^6+3";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(result != result);
}

Test:ExpressionWithSpaces(){
	new expression[] = "((5 * (5 * (5 * (5 * (5 - 1))))))";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(floatcmp(result,2500.0) == 0));
}

Test:BracketAfterOperandError(){
	new expression[] = "(1+7)(2*8)";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(result != result);
}

Test:EmptyExpressionError(){
	new expression[] = "()";
	new Float:result = MathEval(expression);
	printf("Expression %s result : %f ",expression,result);
	ASSERT(result != result);
}