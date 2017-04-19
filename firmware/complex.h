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

static inline complex_t* complex_sub(complex_t* left, complex_t* right, complex_t* dest){
	dest->re = left->re - right->re;
	dest->im = left->im - right->im;
	return dest;
} 

static inline complex_t* complex_mul(complex_t* left, complex_t* right, complex_t* dest){
	dest->re = (right->re*left->re) - (right->im*left->im); //Re(a+bi)(c+di) = (ac-bd)
	dest->im = (right->re*left->im) + (right->im*left->re); //Im(a+bi)(c+di) = (ad+bc)
	return dest;
} 

static inline complex_t* complex_conj(complex_t* a, complex_t* dest){
	dest->re = a->re;
	dest->im = -a->im;
	return dest;
} 

static inline complex_t* complex_div(complex_t* left, complex_t* right, complex_t* dest){
	/*
		(a+bi)/(c+di) = (a+bi)(c-di)/(c^2 + d^2)
	*/
	dest->re = (right->re*left->re) + (right->im*left->im); //Re(a+bi)(c-di) = (ac+bd)
	dest->im = (left->im*right->re) - (left->re*right->im); //Im(a+bi)(c-di) = (bc-ad)

	float d = (right->re*right->re) + (right->im*right->im);//(c^2 + d^2)
	dest->re /= d;
	dest->im /= d;
	return dest;
} 

#endif