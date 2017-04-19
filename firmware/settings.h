#define F_CPU 32000000
#define HW_REVISION 2
#define THE_ANSWER 42

#if HW_REVISION == 2
	#define EXT_RAM_SIZE	0x8000
	#define EXT_RAM_START 	0x4000
#endif