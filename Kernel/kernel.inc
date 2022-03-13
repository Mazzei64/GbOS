bits 16

; RPN'ized expression: "512 "
; Expanded expression: "512 "
; Expression value: 512
; glb buffer : [512u] char
section .bss
	global	_buffer
_buffer:
	resb	512

; glb os_put_char : (
; prm     t : char
;     ) void
section .text
	global	_os_put_char
_os_put_char:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     t : (@4) : char
mov ah,0x0e
mov al,byte [bp+4]
int 0x10
L1:
	leave
	ret

; glb os_put_string : (
; prm     msg : * char
;     ) void
section .text
	global	_os_put_string
_os_put_string:
	push	bp
	mov	bp, sp
	 sub	sp,          4
; loc     msg : (@4) : * char
; loc     i : (@-2) : int
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(2) "
; Fused expression:    "=(170) *(@-2) 0 "
	mov	ax, 0
	mov	[bp-2], ax
; while
; RPN'ized expression: "1 "
; Expanded expression: "1 "
; Expression value: 1
L5:
; {
; loc         t : (@-4) : char
; RPN'ized expression: "t msg i + *u = "
; Expanded expression: "(@-4) (@4) *(2) (@-2) *(2) + *(-1) =(-1) "
; Fused expression:    "+ *(@4) *(@-2) =(167) *(@-4) *ax "
	mov	ax, [bp+4]
	add	ax, [bp-2]
	mov	bx, ax
	mov	al, [bx]
	cbw
	mov	[bp-4], ax
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(2) "
; Fused expression:    "++p(2) *(@-2) "
	mov	ax, [bp-2]
	inc	word [bp-2]
; if
; RPN'ized expression: "t 0 == "
; Expanded expression: "(@-4) *(-1) 0 == "
; Fused expression:    "== *(@-4) 0 IF! "
	mov	al, [bp-4]
	cbw
	cmp	ax, 0
	jne	L7
; {
; break
	jmp	L6
; }
L7:
; RPN'ized expression: "( t os_put_char ) "
; Expanded expression: " (@-4) *(-1)  os_put_char ()2 "
; Fused expression:    "( *(-1) (@-4) , os_put_char )2 "
	mov	al, [bp-4]
	cbw
	push	ax
	call	_os_put_char
	sub	sp, -2
; }
	jmp	L5
L6:
L3:
	leave
	ret

; glb os_reset_drive : (
; prm     driveno : char
;     ) char
section .text
	global	_os_reset_drive
_os_reset_drive:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     driveno : (@4) : char
mov ah,0x00
mov dl,byte [bp+4]
int 0x13
L9:
	leave
	ret

; glb os_read_sector : (
; prm     driveno : char
; prm     sector : int
;     ) char
section .text
	global	_os_read_sector
_os_read_sector:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     driveno : (@4) : char
; loc     sector : (@6) : int
mov ax,0x00
mov bx,0x00
mov cx,0x00
mov dx,0x00
mov ah,0x02
mov al,byte [bp+6]
mov dl,byte [bp+4]
mov si, _buffer
mov bx, ds
mov es, bx
mov bx, si
int 0x13
L11:
	leave
	ret

; glb os_detect_fs : (
; prm     driveno : char
;     ) char
section .text
	global	_os_detect_fs
_os_detect_fs:
	push	bp
	mov	bp, sp
	;sub	sp,          0
; loc     driveno : (@4) : char
; if
; RPN'ized expression: "( 1 , driveno os_read_sector ) 0 == "
; Expanded expression: " 1  (@4) *(-1)  os_read_sector ()4 0 == "
; Fused expression:    "( 1 , *(-1) (@4) , os_read_sector )4 == ax 0 IF! "
	push	1
	mov	al, [bp+4]
	cbw
	push	ax
	call	_os_read_sector
	sub	sp, -4
	cmp	ax, 0
	jne	L15
; {

section .rodata
L17:
	db	"sector read OK"
	times	1 db 0

section .text
; RPN'ized expression: "( L17 os_put_string ) "
; Expanded expression: " L17  os_put_string ()2 "
; Fused expression:    "( L17 , os_put_string )2 "
	push	L17
	call	_os_put_string
	sub	sp, -2
; }
	jmp	L16
L15:
; else
; {

section .rodata
L18:
	db	"sector read not OK"
	times	1 db 0

section .text
; RPN'ized expression: "( L18 os_put_string ) "
; Expanded expression: " L18  os_put_string ()2 "
; Fused expression:    "( L18 , os_put_string )2 "
	push	L18
	call	_os_put_string
	sub	sp, -2
; }
L16:
L13:
	leave
	ret

; glb os_detect_drives : () void
section .text
	global	_os_detect_drives
_os_detect_drives:
	push	bp
	mov	bp, sp
	 sub	sp,          4
; for
; loc     i : (@-2) : char
; RPN'ized expression: "i 0 = "
; Expanded expression: "(@-2) 0 =(-1) "
; Fused expression:    "=(170) *(@-2) 0 "
	mov	ax, 0
	mov	[bp-2], ax
L21:
; RPN'ized expression: "i 5 < "
; Expanded expression: "(@-2) *(-1) 5 < "
; Fused expression:    "< *(@-2) 5 IF! "
	mov	al, [bp-2]
	cbw
	cmp	ax, 5
	jge	L24
; RPN'ized expression: "i ++p "
; Expanded expression: "(@-2) ++p(-1) "
; {
; loc         t : (@-4) : char
; RPN'ized expression: "t ( i os_reset_drive ) = "
; Expanded expression: "(@-4)  (@-2) *(-1)  os_reset_drive ()2 =(-1) "
; Fused expression:    "( *(-1) (@-2) , os_reset_drive )2 =(170) *(@-4) ax "
	mov	al, [bp-2]
	cbw
	push	ax
	call	_os_reset_drive
	sub	sp, -2
	mov	[bp-4], ax
; if
; RPN'ized expression: "t 0 == "
; Expanded expression: "(@-4) *(-1) 0 == "
; Fused expression:    "== *(@-4) 0 IF! "
	mov	al, [bp-4]
	cbw
	cmp	ax, 0
	jne	L25
; {

section .rodata
L27:
	db	"Drive present",13,10
	times	1 db 0

section .text
; RPN'ized expression: "( L27 os_put_string ) "
; Expanded expression: " L27  os_put_string ()2 "
; Fused expression:    "( L27 , os_put_string )2 "
	push	L27
	call	_os_put_string
	sub	sp, -2
; RPN'ized expression: "( i os_detect_fs ) "
; Expanded expression: " (@-2) *(-1)  os_detect_fs ()2 "
; Fused expression:    "( *(-1) (@-2) , os_detect_fs )2 "
	mov	al, [bp-2]
	cbw
	push	ax
	call	_os_detect_fs
	sub	sp, -2
; }
L25:
; }
L22:
; Fused expression:    "++p(-1) *(@-2) "
	mov	al, [bp-2]
	cbw
	inc	byte [bp-2]
	jmp	L21
L24:
L19:
	leave
	ret

; glb main : () void
section .text
	global	_main
_main:
	push	bp
	mov	bp, sp
	;sub	sp,          0

section .rodata
L30:
	db	"Welcome to GBOS!",13,10
	times	1 db 0

section .text
; RPN'ized expression: "( L30 os_put_string ) "
; Expanded expression: " L30  os_put_string ()2 "
; Fused expression:    "( L30 , os_put_string )2 "
	push	L30
	call	_os_put_string
	sub	sp, -2
; RPN'ized expression: "( os_detect_drives ) "
; Expanded expression: " os_detect_drives ()0 "
; Fused expression:    "( os_detect_drives )0 "
	call	_os_detect_drives
; Fused expression:    "0  "
	mov	ax, 0
L28:
	leave
	ret



; Syntax/declaration table/stack:
; Bytes used: 285/15360


; Macro table:
; Macro __SMALLER_C__ = `0x0100`
; Macro __SMALLER_C_16__ = ``
; Macro __SMALLER_C_SCHAR__ = ``
; Macro __SMALLER_C_UWCHAR__ = ``
; Macro __SMALLER_C_WCHAR16__ = ``
; Bytes used: 110/5120


; Identifier table:
; Ident 
; Ident __floatsisf
; Ident __floatunsisf
; Ident __fixsfsi
; Ident __fixunssfsi
; Ident __addsf3
; Ident __subsf3
; Ident __negsf2
; Ident __mulsf3
; Ident __divsf3
; Ident __lesf2
; Ident __gesf2
; Ident buffer
; Ident os_put_char
; Ident t
; Ident os_put_string
; Ident msg
; Ident os_reset_drive
; Ident driveno
; Ident os_read_sector
; Ident sector
; Ident os_detect_fs
; Ident os_detect_drives
; Ident main
; Bytes used: 254/5632

; Next label number: 31
; Compilation succeeded.
