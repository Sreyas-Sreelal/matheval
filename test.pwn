#include<a_samp>

#define ME_DEBUG_MODE
#include<matheval>

main(){
	printf("result : %f ",MathEval("(2^3)+1"));
	printf("result : %f ",MathEval("(5 * 5) - 1"));
	printf("result : %f ",MathEval("(5 - 1) * (5 - 1)"));
	printf("result : %f ",MathEval("(5 * (5 * (5 * (5 * (5 - 1)))))"));
}


