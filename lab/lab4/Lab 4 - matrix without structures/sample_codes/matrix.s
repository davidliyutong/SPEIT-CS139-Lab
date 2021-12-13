
matrix.o:	file format mach-o arm64


Disassembly of section __TEXT,__text:

0000000000000000 <ltmp0>:
; err_t matrix_assign(double* mat, size_t n_row, size_t n_col) {
       0: ff c3 00 d1  	sub	sp, sp, #48
       4: fd 7b 02 a9  	stp	x29, x30, [sp, #32]
       8: fd 83 00 91  	add	x29, sp, #32
       c: a0 83 1f f8  	stur	x0, [x29, #-8]
      10: e1 0b 00 f9  	str	x1, [sp, #16]
      14: e2 07 00 f9  	str	x2, [sp, #8]
;     for (size_t idx = 0; idx < n_row * n_col; ++idx) {
      18: ff 03 00 f9  	str	xzr, [sp]
      1c: e8 03 40 f9  	ldr	x8, [sp]
      20: e9 0b 40 f9  	ldr	x9, [sp, #16]
      24: ea 07 40 f9  	ldr	x10, [sp, #8]
      28: 29 7d 0a 9b  	mul	x9, x9, x10
      2c: 08 01 09 eb  	subs	x8, x8, x9
      30: c2 01 00 54  	b.hs	0x68 <ltmp0+0x68>
;         mat[idx] = RANDINT(VALUE_MAX);
      34: 00 00 00 94  	bl	0x34 <ltmp0+0x34>
      38: 09 01 80 52  	mov	w9, #8
      3c: 08 0c c9 1a  	sdiv	w8, w0, w9
      40: 08 7d 09 1b  	mul	w8, w8, w9
      44: 08 00 08 6b  	subs	w8, w0, w8
      48: 00 01 62 1e  	scvtf	d0, w8
      4c: a8 83 5f f8  	ldur	x8, [x29, #-8]
      50: e9 03 40 f9  	ldr	x9, [sp]
      54: 00 79 29 fc  	str	d0, [x8, x9, lsl #3]
;     for (size_t idx = 0; idx < n_row * n_col; ++idx) {
      58: e8 03 40 f9  	ldr	x8, [sp]
      5c: 08 05 00 91  	add	x8, x8, #1
      60: e8 03 00 f9  	str	x8, [sp]
      64: ee ff ff 17  	b	0x1c <ltmp0+0x1c>
      68: 00 00 80 52  	mov	w0, #0
;     return MATRIX_OK;
      6c: fd 7b 42 a9  	ldp	x29, x30, [sp, #32]
      70: ff c3 00 91  	add	sp, sp, #48
      74: c0 03 5f d6  	ret

0000000000000078 <_matrix_repr>:
; err_t matrix_repr(double* mat, size_t n_row, size_t n_col) {
      78: ff 03 01 d1  	sub	sp, sp, #64
      7c: fd 7b 03 a9  	stp	x29, x30, [sp, #48]
      80: fd c3 00 91  	add	x29, sp, #48
      84: a0 83 1f f8  	stur	x0, [x29, #-8]
      88: a1 03 1f f8  	stur	x1, [x29, #-16]
      8c: e2 0f 00 f9  	str	x2, [sp, #24]
      90: 00 00 00 90  	adrp	x0, 0x0 <_matrix_repr+0x18>
      94: 00 00 00 91  	add	x0, x0, #0
;     printf("array([");
      98: 00 00 00 94  	bl	0x98 <_matrix_repr+0x20>
;     size_t row = 0, col = 0;
      9c: ff 0b 00 f9  	str	xzr, [sp, #16]
      a0: ff 07 00 f9  	str	xzr, [sp, #8]
;     for (row = 0; row < n_row; ++row) {
      a4: ff 0b 00 f9  	str	xzr, [sp, #16]
      a8: e8 0b 40 f9  	ldr	x8, [sp, #16]
      ac: a9 03 5f f8  	ldur	x9, [x29, #-16]
      b0: 08 01 09 eb  	subs	x8, x8, x9
      b4: 22 05 00 54  	b.hs	0x158 <_matrix_repr+0xe0>
      b8: 00 00 00 90  	adrp	x0, 0x0 <_matrix_repr+0x40>
      bc: 00 00 00 91  	add	x0, x0, #0
;         printf("[");
      c0: 00 00 00 94  	bl	0xc0 <_matrix_repr+0x48>
;         for (col = 0; col < n_col; ++col) {
      c4: ff 07 00 f9  	str	xzr, [sp, #8]
      c8: e8 07 40 f9  	ldr	x8, [sp, #8]
      cc: e9 0f 40 f9  	ldr	x9, [sp, #24]
      d0: 08 01 09 eb  	subs	x8, x8, x9
      d4: 22 02 00 54  	b.hs	0x118 <_matrix_repr+0xa0>
;             printf("%.3f, ", mat[row * n_col + col]);
      d8: a8 83 5f f8  	ldur	x8, [x29, #-8]
      dc: e9 0b 40 f9  	ldr	x9, [sp, #16]
      e0: ea 0f 40 f9  	ldr	x10, [sp, #24]
      e4: 29 7d 0a 9b  	mul	x9, x9, x10
      e8: ea 07 40 f9  	ldr	x10, [sp, #8]
      ec: 29 01 0a 8b  	add	x9, x9, x10
      f0: 00 79 69 fc  	ldr	d0, [x8, x9, lsl #3]
      f4: 00 00 00 90  	adrp	x0, 0x0 <_matrix_repr+0x7c>
      f8: 00 00 00 91  	add	x0, x0, #0
;             printf("%.3f, ", mat[row * n_col + col]);
      fc: e8 03 00 91  	mov	x8, sp
     100: 00 01 00 fd  	str	d0, [x8]
     104: 00 00 00 94  	bl	0x104 <_matrix_repr+0x8c>
;         for (col = 0; col < n_col; ++col) {
     108: e8 07 40 f9  	ldr	x8, [sp, #8]
     10c: 08 05 00 91  	add	x8, x8, #1
     110: e8 07 00 f9  	str	x8, [sp, #8]
     114: ed ff ff 17  	b	0xc8 <_matrix_repr+0x50>
;         if (row < n_row - 1) {
     118: e8 0b 40 f9  	ldr	x8, [sp, #16]
     11c: a9 03 5f f8  	ldur	x9, [x29, #-16]
     120: 29 05 00 f1  	subs	x9, x9, #1
     124: 08 01 09 eb  	subs	x8, x8, x9
     128: a2 00 00 54  	b.hs	0x13c <_matrix_repr+0xc4>
     12c: 00 00 00 90  	adrp	x0, 0x0 <_matrix_repr+0xb4>
     130: 00 00 00 91  	add	x0, x0, #0
;             printf("\b\b],\n       ");
     134: 00 00 00 94  	bl	0x134 <_matrix_repr+0xbc>
;         } else {
     138: 04 00 00 14  	b	0x148 <_matrix_repr+0xd0>
     13c: 00 00 00 90  	adrp	x0, 0x0 <_matrix_repr+0xc4>
     140: 00 00 00 91  	add	x0, x0, #0
;             printf("\b\b]])\n\n");
     144: 00 00 00 94  	bl	0x144 <_matrix_repr+0xcc>
;     for (row = 0; row < n_row; ++row) {
     148: e8 0b 40 f9  	ldr	x8, [sp, #16]
     14c: 08 05 00 91  	add	x8, x8, #1
     150: e8 0b 00 f9  	str	x8, [sp, #16]
     154: d5 ff ff 17  	b	0xa8 <_matrix_repr+0x30>
     158: 00 00 80 52  	mov	w0, #0
;     return MATRIX_OK;
     15c: fd 7b 43 a9  	ldp	x29, x30, [sp, #48]
     160: ff 03 01 91  	add	sp, sp, #64
     164: c0 03 5f d6  	ret

0000000000000168 <_matrix_add>:
;                  size_t n_row, size_t n_col) {
     168: ff 43 01 d1  	sub	sp, sp, #80
     16c: e0 27 00 f9  	str	x0, [sp, #72]
     170: e1 23 00 f9  	str	x1, [sp, #64]
     174: e2 1f 00 f9  	str	x2, [sp, #56]
     178: e0 1b 00 fd  	str	d0, [sp, #48]
     17c: e1 17 00 fd  	str	d1, [sp, #40]
     180: e2 13 00 fd  	str	d2, [sp, #32]
     184: e3 0f 00 f9  	str	x3, [sp, #24]
     188: e4 0b 00 f9  	str	x4, [sp, #16]
;     for (size_t idx = 0; idx < n_row * n_col; ++idx) {
     18c: ff 07 00 f9  	str	xzr, [sp, #8]
     190: e8 07 40 f9  	ldr	x8, [sp, #8]
     194: e9 0f 40 f9  	ldr	x9, [sp, #24]
     198: ea 0b 40 f9  	ldr	x10, [sp, #16]
     19c: 29 7d 0a 9b  	mul	x9, x9, x10
     1a0: 08 01 09 eb  	subs	x8, x8, x9
     1a4: a2 02 00 54  	b.hs	0x1f8 <_matrix_add+0x90>
;         res[idx] = mat1[idx] * lmd1 + mat2[idx] * lmd2 + k;
     1a8: e8 27 40 f9  	ldr	x8, [sp, #72]
     1ac: e9 07 40 f9  	ldr	x9, [sp, #8]
     1b0: 00 79 69 fc  	ldr	d0, [x8, x9, lsl #3]
     1b4: e1 1b 40 fd  	ldr	d1, [sp, #48]
     1b8: 00 08 61 1e  	fmul	d0, d0, d1
     1bc: e8 23 40 f9  	ldr	x8, [sp, #64]
     1c0: e9 07 40 f9  	ldr	x9, [sp, #8]
     1c4: 01 79 69 fc  	ldr	d1, [x8, x9, lsl #3]
     1c8: e2 17 40 fd  	ldr	d2, [sp, #40]
     1cc: 21 08 62 1e  	fmul	d1, d1, d2
     1d0: 00 28 61 1e  	fadd	d0, d0, d1
     1d4: e1 13 40 fd  	ldr	d1, [sp, #32]
     1d8: 00 28 61 1e  	fadd	d0, d0, d1
     1dc: e8 1f 40 f9  	ldr	x8, [sp, #56]
     1e0: e9 07 40 f9  	ldr	x9, [sp, #8]
     1e4: 00 79 29 fc  	str	d0, [x8, x9, lsl #3]
;     for (size_t idx = 0; idx < n_row * n_col; ++idx) {
     1e8: e8 07 40 f9  	ldr	x8, [sp, #8]
     1ec: 08 05 00 91  	add	x8, x8, #1
     1f0: e8 07 00 f9  	str	x8, [sp, #8]
     1f4: e7 ff ff 17  	b	0x190 <_matrix_add+0x28>
     1f8: 00 00 80 52  	mov	w0, #0
;     return MATRIX_OK;
     1fc: ff 43 01 91  	add	sp, sp, #80
     200: c0 03 5f d6  	ret

0000000000000204 <_matrix_matmul>:
;                     size_t n_row2, size_t n_col2) {
     204: ff 83 01 d1  	sub	sp, sp, #96
     208: e0 2b 00 f9  	str	x0, [sp, #80]
     20c: e1 27 00 f9  	str	x1, [sp, #72]
     210: e2 23 00 f9  	str	x2, [sp, #64]
     214: e3 1f 00 f9  	str	x3, [sp, #56]
     218: e4 1b 00 f9  	str	x4, [sp, #48]
     21c: e5 17 00 f9  	str	x5, [sp, #40]
     220: e6 13 00 f9  	str	x6, [sp, #32]
;     if (n_col1 != n_row2) {
     224: e8 1b 40 f9  	ldr	x8, [sp, #48]
     228: e9 17 40 f9  	ldr	x9, [sp, #40]
     22c: 08 01 09 eb  	subs	x8, x8, x9
     230: 80 00 00 54  	b.eq	0x240 <_matrix_matmul+0x3c>
     234: 28 00 80 52  	mov	w8, #1
;         return MATRIX_FAIL;
     238: e8 5f 00 b9  	str	w8, [sp, #92]
     23c: 3a 00 00 14  	b	0x324 <_matrix_matmul+0x120>
;     size_t row = 0, col = 0;
     240: ff 0f 00 f9  	str	xzr, [sp, #24]
     244: ff 0b 00 f9  	str	xzr, [sp, #16]
;     for (row = 0; row < n_row1; ++row) {
     248: ff 0f 00 f9  	str	xzr, [sp, #24]
     24c: e8 0f 40 f9  	ldr	x8, [sp, #24]
     250: e9 1f 40 f9  	ldr	x9, [sp, #56]
     254: 08 01 09 eb  	subs	x8, x8, x9
     258: 42 06 00 54  	b.hs	0x320 <_matrix_matmul+0x11c>
;         for (col = 0; col < n_col2; ++col) {
     25c: ff 0b 00 f9  	str	xzr, [sp, #16]
     260: e8 0b 40 f9  	ldr	x8, [sp, #16]
     264: e9 13 40 f9  	ldr	x9, [sp, #32]
     268: 08 01 09 eb  	subs	x8, x8, x9
     26c: 22 05 00 54  	b.hs	0x310 <_matrix_matmul+0x10c>
;             double sum = 0.;
     270: ff 07 00 f9  	str	xzr, [sp, #8]
;             for (size_t idx = 0; idx < n_col1; ++idx) {
     274: ff 03 00 f9  	str	xzr, [sp]
     278: e8 03 40 f9  	ldr	x8, [sp]
     27c: e9 1b 40 f9  	ldr	x9, [sp, #48]
     280: 08 01 09 eb  	subs	x8, x8, x9
     284: e2 02 00 54  	b.hs	0x2e0 <_matrix_matmul+0xdc>
;                 sum += mat1[row * n_col1 + idx] * mat2[idx * n_col2 + col];
     288: e8 2b 40 f9  	ldr	x8, [sp, #80]
     28c: e9 0f 40 f9  	ldr	x9, [sp, #24]
     290: ea 1b 40 f9  	ldr	x10, [sp, #48]
     294: 29 7d 0a 9b  	mul	x9, x9, x10
     298: ea 03 40 f9  	ldr	x10, [sp]
     29c: 29 01 0a 8b  	add	x9, x9, x10
     2a0: 00 79 69 fc  	ldr	d0, [x8, x9, lsl #3]
     2a4: e8 27 40 f9  	ldr	x8, [sp, #72]
     2a8: e9 03 40 f9  	ldr	x9, [sp]
     2ac: ea 13 40 f9  	ldr	x10, [sp, #32]
     2b0: 29 7d 0a 9b  	mul	x9, x9, x10
     2b4: ea 0b 40 f9  	ldr	x10, [sp, #16]
     2b8: 29 01 0a 8b  	add	x9, x9, x10
     2bc: 01 79 69 fc  	ldr	d1, [x8, x9, lsl #3]
     2c0: 01 08 61 1e  	fmul	d1, d0, d1
     2c4: e0 07 40 fd  	ldr	d0, [sp, #8]
     2c8: 00 28 61 1e  	fadd	d0, d0, d1
     2cc: e0 07 00 fd  	str	d0, [sp, #8]
;             for (size_t idx = 0; idx < n_col1; ++idx) {
     2d0: e8 03 40 f9  	ldr	x8, [sp]
     2d4: 08 05 00 91  	add	x8, x8, #1
     2d8: e8 03 00 f9  	str	x8, [sp]
     2dc: e7 ff ff 17  	b	0x278 <_matrix_matmul+0x74>
;             res[row * n_col2 + col] = sum;
     2e0: e0 07 40 fd  	ldr	d0, [sp, #8]
     2e4: e8 23 40 f9  	ldr	x8, [sp, #64]
     2e8: e9 0f 40 f9  	ldr	x9, [sp, #24]
     2ec: ea 13 40 f9  	ldr	x10, [sp, #32]
     2f0: 29 7d 0a 9b  	mul	x9, x9, x10
     2f4: ea 0b 40 f9  	ldr	x10, [sp, #16]
     2f8: 29 01 0a 8b  	add	x9, x9, x10
     2fc: 00 79 29 fc  	str	d0, [x8, x9, lsl #3]
;         for (col = 0; col < n_col2; ++col) {
     300: e8 0b 40 f9  	ldr	x8, [sp, #16]
     304: 08 05 00 91  	add	x8, x8, #1
     308: e8 0b 00 f9  	str	x8, [sp, #16]
     30c: d5 ff ff 17  	b	0x260 <_matrix_matmul+0x5c>
;     for (row = 0; row < n_row1; ++row) {
     310: e8 0f 40 f9  	ldr	x8, [sp, #24]
     314: 08 05 00 91  	add	x8, x8, #1
     318: e8 0f 00 f9  	str	x8, [sp, #24]
     31c: cc ff ff 17  	b	0x24c <_matrix_matmul+0x48>
;     return MATRIX_OK;
     320: ff 5f 00 b9  	str	wzr, [sp, #92]
; }
     324: e0 5f 40 b9  	ldr	w0, [sp, #92]
     328: ff 83 01 91  	add	sp, sp, #96
     32c: c0 03 5f d6  	ret
