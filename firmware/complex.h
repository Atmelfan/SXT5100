#ifndef COMPLEX
#define COMPLEX

typedef struct {
 	float re;
 	float im;
} complex_t;


/**
 * Add two complex numbers
 */
static inline complex_t* complex_add(complex_t* left, complex_t* right, complex_t* dest){
	dest->re = left->re + right->re;
	dest->im = left->im + right->im;
	return dest;
} 

static inline complex_t* complex_add(complex_t* left, complex_t* right){
	return complex_add(left, right, left);
}



#endif