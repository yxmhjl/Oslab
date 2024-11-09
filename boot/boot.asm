org 07c00h  ;告诉编译器这段程序会被加载到7c00处，计算地址时要加上7c00
mov ax, cs
mov ds, ax
mov es, ax  ;调用显示字符串例程
call DispStr
jmp $

DispStr:
    mov ax, BootMessage ; ES:SI = 串地址
    mov bp,ax
    mov cx, 16           ; CX = 串长度
    mov ax, 01301h          ; AH = 13, AL = 01h
    mov bx, 000ch
    mov dl, 0            ; 页号为0 (BH = 0)
    int 10h              ; 调用10h号中断
    ret

BootMessage:    db "Hello, OS world!"

times 510-($-$$) db 0
dw 0xaa55

