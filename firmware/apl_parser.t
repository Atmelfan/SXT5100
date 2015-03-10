#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "apl.h"


#define AS_VECTOR(object)	((apl_scalar*)(object)->ptr)
#define AS_STRING(object)	((char*)(object)->ptr)

char* skip_space(char* s){
	while(isspace(*s)){
		s++;
	}	
	return s;
}

void* apl_malloc_vector(void* ptr, char length){
	return realloc(ptr, length * sizeof(float));
}

void apl_free_object(apl_object* obj){
	free(obj->ptr);
}

char* apl_read_scalar(char* s, apl_scalar* scalar){
	char* c;
	scalar->real = strtof(s, &c);
	if(*c == 'j'){
		s = c+1;
		scalar->imag = strtof(s, &c);
	}
	return c;
}

char apl_len_until(char* s, char end){
	char len = 0;
	while(*s && *s != end && len < 0xFF) {
		s++;
		len++;
	}
	return len;
}

char* apl_read_value(char* s, apl_object* value){
	if(*s == ')'||*s == ']'||*s == '}'||*s == ';'){
		return skip_space(s+1);
	}
	else if(*s == '\'')
	{
		value->x = apl_len_until(s, '\'')
		value->ptr = apl_malloc_vector(value->ptr, value->x);
		if (value->ptr == NULL)
		{
			return NULL;
		}
		strncpy(AS_STRING(value), s, len);
		s += value->x;
	}
	else if(isdigit(*s) || *s == '-')
	{
		value->type = APL_VECTOR;
		value->x = 1;
		value->y = 1;
		while(*s == ' '){
			s = skip_space(s);
			if(!isdigit(*s) && *s != '-')
				break;
			value->x++;
			value->ptr = apl_malloc_vector(value->ptr, value->x);
			if (value->ptr == NULL)
			{
				return NULL;
			}
			s = apl_read_scalar(s, &AS_VECTOR(value)[value->x-1]);
		}
	}
	else if(*s == '(')
	{
		s = apl_read_value(s+1, value);
	}
	else
	{
		switch(*s){
			case '+':
				
				break;
		}
	}
	return skip_space(s);
}


void apl_op_add(apl_object* left, apl_object* right, apl_object* dest){
	dest->type = right->type;
	dest->x = right->x;
	dest->y = right->y;
	
}


void apl_eval(char* s, apl_object* o){
	
}
