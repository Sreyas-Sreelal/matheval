#include<a_samp>

//#define ME_DEBUG_MODE

#include "matheval"

test(expression[]){
	new Float:result = MathEval(expression);
	printf("[%s] %s = %f ",(result != result)?("Failed"):("Success"),expression,result); 
}
main(){
	test("+12+(12-12)");
	test("1+3+");
	test("1-3)");
	test("(56-12)(");

	test("(2^3)+1");
	test("(5 * 5) - 1");
	test("(5 - 1) * (5 - 1)");
	test("(5 * (5 * (5 * (5 * (5 - 1)))))");
	
}


