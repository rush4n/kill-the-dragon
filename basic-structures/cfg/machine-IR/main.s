	.build_version macos, 26, 0
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_foo                            ; -- Begin function foo
	.p2align	2
_foo:                                   ; @foo
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	w0, [x29, #-4]
	str	w1, [sp, #8]
	ldur	w8, [x29, #-4]
	ldr	w9, [sp, #8]
	add	w8, w8, w9
	str	w8, [sp, #4]
	ldr	w8, [sp, #4]
	subs	w8, w8, #255
	b.eq	LBB0_1
	b	LBB0_2
LBB0_1:
	ldr	w0, [sp, #4]
	bl	_bar
	bl	_baz
	str	w0, [sp, #4]
	b	LBB0_2
LBB0_2:
	ldr	w0, [sp, #4]
	bl	_bar
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
