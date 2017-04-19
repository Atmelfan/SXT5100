// #include "apl.h"

// typedef enum
// {
// 	NOUN,
// 	VERB
// }exp_type;

// static struct{
// 	char o;
// 	apl_object* (func*)(apl_object, apl_object);
// } apl_operators[] = {
// 	{''}
// };

// static struct {
// 	exp_type match[4];
// 	void (*handler)();
// }cases[] = {

// };


// uint8_t apl_is_char_operator(char o){
// 	return o != 0 && o < 32;
// }

// //push-char
// //push-complex
// apl_object* parse_string(char* s){

// }

// apl_object* parse_vector(char* s){

// }

// apl_object* parse_lambda(char* s){

// }
// //Names can't contain numbers, too lazy to fix.
// //Use roman numbers instead or whatever non-alphanumeric
// //system you prefer (or fix the code).

// apl_object* apl_parse(char* s, apl_object* a, apl_object* w){
// 	apl_object* c[4];
// 	uint8_t indx = 0;
// 	while(*s){
// 		char c = *s;
// 		if(c == '\''){
// 			c[indx] = parse_string(s);
// 			indx++;
// 		}else if(c == '\''){
// 			c[indx] = parse_string(s);
// 			indx++;
// 		}else if(c == '\''){
// 			c[indx] = parse_string(s);
// 			indx++;
// 		}else if(c == '}'){
// 			c[indx] = parse_lambda(s);
// 			indx++;
// 		}else if(c == ')'{
			
// 		}else 
// 		s++;
// 	}
// }



