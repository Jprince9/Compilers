sys_exit equ 1
sys_read equ 3
sys_write equ 4
stdin equ 4
stdout equ 1
stderr equ 3

section .data

userMsg db 'Enter an integer(less than 32,765): '
lenUserMsg equ $-userMsg
displayMsg db 'You entered: '
lenDisplayMsg equ $-displayMsg
newline db 0xA
Ten DW 10
printTempchar db 'Tempchar = : '
lenprintTempchar equ $-printTempchar
Result db 'Ans = '
ResultValue db 'aaaaa'
db	0xA
ResultEnd equ $-Result
num times 6 db 'ABCDEF'
numEnd equ $-num

section .bss


TempChar RESB 1
testchar RESB 1
ReadInt RESW 1
tempint RESW 1
negflag RESB 1


X RESW 1
Y RESW 1
Z RESW 1
ans RESW 1
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




call PrintString
call GetAnInteger
mov ax, [ReadInt]
mov [Y], ax




call PrintString
call GetAnInteger
mov ax, [ReadInt]
mov [Z], ax


mov ax, [X]
mov bx, [Y]
cmp ax, bx
JLE L5
mov ax, [Z]
mov bx, [X]
cmp ax, bx
JLE L9
mov ax, [Z]
mov [ans], ax
jmp L12
L9:
mov ax, [X]
mov [ans], ax
L12:
jmp L17
L5:
mov ax, [Y]
mov bx, [Z]
cmp ax, bx
JLE L22
mov ax, [Y]
mov [ans], ax
jmp L25
L22:
mov ax, [Z]
mov [ans], ax
L25:
L17:


mov ax, [ans]
call ConvertIntegerToString
mov eax, 4
mov ebx, 1
mov ecx, Result
mov edx, ResultEnd
int 80h



jmp fini

PrintString:
push ax
push dx
mov eax, 4
mov ebx, 1
mov ecx, userMsg
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
Next: sub bl, '0'
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

Terminate:
fini:
mov eax, sys_exit
xor ebx, ebx
int 80h
