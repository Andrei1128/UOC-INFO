JUMPS
.model small
 .stack 100h
 .data
 a db 10
 _cx dw 0
 _dx dw 0
 ccx dw 0
 cdx dw 0
 aux dw 0
 .code
 sterg:
mov ax,@data
mov ds,ax
mov ah,0h
mov al,12h
int 10h

bucla:
push ax
mov ax,3
int 33h
pop ax
mov bh,bl

cmp bl,1
jnz desenez
mov al,a
mov ah,0ch
mov bh,0
int 10h
;--------------------------------------------------------------
mov ccx,cx
mov cdx,dx

mov _cx,320
mov _dx,240
sub _cx,cx
sub _dx,dx
mov cx,_cx
mov dx,_dx

add cx,320
add dx,240
mov al,a
mov ah,0ch
mov bh,0
int 10h
;--------------------------------------------------------------
mov cx,ccx
mov dx,cdx

mov _dx,320
sub _dx,dx
mov dx,_dx

mov aux,cx
mov cx,dx
mov dx,aux

add cx,240
sub dx,80

mov al,a
mov ah,0ch
mov bh,0
int 10h
;--------------------------------------------------------------
mov cx,ccx
mov dx,cdx

mov _cx,240
sub _cx,cx
mov cx,_cx

mov aux,cx
mov cx,dx
mov dx,aux

add dx,320
add cx,80

mov al,a
mov ah,0ch
mov bh,0
int 10h
;--------------------------------------------------------------
desenez:
mov bl,bh

mov ah,6h
mov dl,255
int 21h
cmp al,20h
jz sterg

mov ah,6h
mov dl,255
int 21h
cmp al,31h
jnz culoare1
mov a,1
culoare1:

mov ah,6h
mov dl,255
int 21h
cmp al,32h
jnz culoare2
mov a,4
culoare2:

mov ah,6h
mov dl,255
int 21h
cmp al,33h
jnz culoare3
mov a,10
culoare3:

mov ah,6h
mov dl,255
int 21h
cmp al,34h
jnz culoare4
mov a,14
culoare4:

mov ah,6h
mov dl,255
int 21h
cmp al,35h
jnz culoare5
mov a,5
culoare5:

mov ah,6h
mov dl,255
int 21h
cmp al,36h
jnz culoare6
mov a,15
culoare6:

mov ah,6h
mov dl,255
int 21h
cmp al,37h
jnz culoare7
mov a,0
culoare7:

mov ah,6h
mov dl,255
int 21h
cmp al,1Bh
je sfarsit

jmp bucla

sfarsit:
mov ah,0h
mov al,3h
int 10h
mov ah,4ch
int 21h
end