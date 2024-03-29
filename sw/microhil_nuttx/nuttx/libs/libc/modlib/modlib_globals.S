#ifdef __CYGWIN__
#  define SYMBOL(s) s
#  define WEAK .weak
#  define GLOBAL .global
#  define SECTION .data
	.macro GLOBAL ep
	.global SYMBOL(\ep)
	.type 	SYMBOL(\ep), "object"
	.endm
	.macro SIZE ep
	.endm
#elif defined(__ELF__)
#  define SYMBOL(s) s
#  define WEAK .weak
#  define SECTION .data
	.macro GLOBAL ep
	.global SYMBOL(\ep)
	.type 	SYMBOL(\ep), "object"
	.endm
	.macro SIZE ep
 	.size 	SYMBOL(\ep), . - SYMBOL(\ep)
	.endm
#else
#  define SYMBOL(s) _##s
#  define WEAK .weak_definition
#  define SECTION .section __DATA,__data
	.macro GLOBAL ep
	.private_extern SYMBOL(\ep)
	.globl 	SYMBOL(\ep)
	.endm
	.macro SIZE ep
	.endm
#endif

#if __SIZEOF_POINTER__ == 8
	.macro globalEntry index, ep
	WEAK	SYMBOL(\ep)
	.quad	.l\index
	.quad	\ep
	.endm
# define ALIGN 8
#else
	.macro globalEntry index, ep
	WEAK	SYMBOL(\ep)		
	.long	.l\index
	.long	\ep
	.endm
# define ALIGN 4
#endif
#ifdef __ARM_ARCH_ISA_THUMB2
#ifdef __ARM_ASM_SYNTAX_UNIFIED__
	.syntax unified
#endif
	.thumb
#endif
	.data
	.align	ALIGN
	GLOBAL	globalNames

SYMBOL(globalNames):
	SIZE globalNames

	.align	ALIGN
	GLOBAL	nglobals
SYMBOL(nglobals):
	.word	0
	SIZE	nglobals

	.align	ALIGN
	GLOBAL	global_table
SYMBOL(global_table):
	SIZE	global_table
