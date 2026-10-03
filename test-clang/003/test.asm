	.build_version macos, 26, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_add_max                        ; -- Begin function add_max
	.p2align	2
_add_max:                               ; @add_max
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #8]
	ldr	w0, [sp, #12]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
