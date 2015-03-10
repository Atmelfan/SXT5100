#ifndef KEYBOARD_H_
#define KEYBOARD_H_

typedef uint8_t mkey;

#define XKEYS 9
#define YKEYS 3
#define TOKEY(x, y) ((y)*XKEYS + (x))

typedef keyboard_mode{
	KEYBOARD_NORMAL,//
	KEYBOARD_QWERTY,
	KEYBOARD_ALTERN
};

/**
 * Returns '1' if key is pressed, 0 otherwise.
 */
char keyboard_ispressed(mkey k);
/**
 * Returns the character of key if it exists, NULL (\x00) otherwise
 */
char keyboard_tochar(mkey k);


#endif



