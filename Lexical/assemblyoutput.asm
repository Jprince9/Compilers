sys_exit equ 1
sys_read equ 3
sys_write equ 4
stdin equ 4
stdout equ 1
stderr equ 3

;&&copy the section.data replace the message with correct message&&


M DW 13
N DW 56
Lit18 DW 18
Lit10 DW 10
Lit2 DW 2
Lit4 DW 4
Lit1 DW 1
Lit2 DW 2
Lit5 DW 5
Lit3 DW 3
Lit4 DW 4
Lit16 DW 16
Lit11 DW 11
Lit12 DW 12
Lit15 DW 15
Lit16 DW 16
Lit17 DW 17
Lit18 DW 18
Lit19 DW 19
Lit20 DW 20
Lit21 DW 21
Lit22 DW 22
Lit1 DW 1
Lit10 DW 10
Lit1 DW 1
Lit2 DW 2


TempChar RESB 1
testchar RESB 1
ReadInt RESW 1
tempint RESW 1
negflag RESB 1


section .bss
X RESW 1
Z RESW 1
Y RESW 1
ans RESW 1
a RESW 1
Bob RESW 1
Jane RESW 1
b RESW 1
c RESW 1
t1 RESW 1
t2 RESW 1
t3 RESW 1
t4 RESW 1
t5 RESW 1
t6 RESW 1
t7 RESW 1
t8 RESW 1
t9 RESW 1
t10 RESW 1
t11 RESW 1
t12 RESW 1
t13 RESW 1
t14 RESW 1
t15 RESW 1


section .text
_start: nop
Again: 


call PrintString
call GetAnInteger
mov ax, [ReadInt]
mov [X], ax


mov eax, [M]
mul [N]
mov [t1], eax
mov ax, [t1]
add ax, 18
mov [t2], ax
mov ax, [t2]
sub ax, [Y]
mov [t3], ax
mov ax, [t3]
mov [X], ax
mov ax, [Bob]
add ax, [Jane]
mov [t1], ax
mov ax, [t1]
sub ax, 10
mov [t2], ax
mov edx, 0
mov eax, [t2]
div 2
mov [t3], eax
mov eax, [t3]
mul 4
mov [t4], eax
mov eax, [a]
mul [t4]
mov [t5], eax
mov ax, [b]
add ax, [c]
mov [t6], ax
mov edx, 0
mov eax, [t5]
div [t6]
mov [t7], eax
mov ax, [t7]
mov [ans], ax
mov ax, 3
add ax, 4
mov [t1], ax
mov ax, [t1]
mov [Y], ax
mov ax, 16
mov [Bob], ax
mov ax, 16
mov [Y], ax
mov ax, 17
mov [X], ax
mov ax, 21
mov [Y], ax
mov ax, 22
mov [X], ax
mov ax, 1
mov [X], ax
mov ax, [X]
add ax, 1
mov [t1], ax
mov ax, [t1]
mov [X], ax
mov eax, [X]
mul 2
mov [t1], eax
mov ax, [t1]
mov [Y], ax


mov ax, [X], ax
call ConvertIntegerToString
mov eax, 4
mov ebx, 1
mov ecx, Result
mov edx, ResultEnd
int 80h


fini:
mov eax,sys_exit
xor ebx,ebx
int80h

PrintString:
push ax
push dx
mov eax, 4
mov ebx, 1
 mov exc, userMsg
mov edx, lenUserMsg
int 80h
pop dx
pop ax
ret

GetAnInteger:
mov eax, 3
mov ebx, 2
mov ecx, num
mov edx,6
int 0x80
mov edx, eax
mov eax, 4
mov ebx, 1
mov ecx, num
int 80h
ConvertStringToInteger:
mov ax, 0
mov [ReadInt], ax
mov ecx, num
mov bx, 0
mov bl, byte [ecx]
sub bl, '0'
mov ax, [ReadInt]
mov dx, 10
mul dx
add ax, bx
mov [ReadInt], ax
mov bx, 0
add ecx, 1
mov bl, byte[ecx]
cmp bl, 0xA
jne Next
ret
ConvertIntegerToString:
mov ebx, ResultValue + 4
ConvertLoop:
sub dx, dx
mov cx, 10
div cx
add dl, '0'
mov [ebx], dl
dec ebx
cmp ebx, ResultValue
jge ConvertLoop
ret
Conversion Algorithms: Burris Compiler 2 page 77
Get:
call PrintString
call GetAnInteger
mov ax, [ReadInt]
mov [Y], ax
Put:
mov ax, [X]
call ConvertIntegerToString
mov eax, 4
mov ebx, 1
mov ecx, Result
mov edx, ResultEnd
int 80h
Terminate:
fini:
mov eax, sys_exit
xor ebx, ebx
int 80h
