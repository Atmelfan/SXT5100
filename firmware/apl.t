#ifndef APL_H_
#define APL_H_



typedef enum apl_types
{
	APL_VECTOR,
	APL_MATRIX,
	APL_STRING
} apl_types;

typedef struct apl_scalar
{
	float real, imag;
} apl_scalar;

typedef struct apl_object
{
	apl_types type;
	unsigned char x,y;
	void* ptr;
} apl_object;

#define OBJ_ZERO {.type=APL_VECTOR, .x=0, .y=0, .ptr = NULL}

void apl_eval(char*, apl_object*);
void apl_error(char* msg);
void apl_print_object(apl_object*);

#endif

