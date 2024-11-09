#include <geekos/bootinfo.h>
#include <geekos/string.h>
#include <geekos/screen.h>
#include <geekos/mem.h>
#include <geekos/crc32.h>
#include <geekos/tss.h>
#include <geekos/int.h>
#include <geekos/kthread.h>
#include <geekos/trap.h>
#include <geekos/timer.h>
#include <geekos/keyboard.h>

static void print_A(ulong_t arg) {
    Print("This is the sub thread_A");
    
    Exit(0); // 退出线程
}

static void print_B(ulong_t arg) {
    Print("This is the sub thread_B");
    Exit(0); // 退出线程
}
// 全局退出标志
volatile bool exitFlag = false;

void print_key(ulong_t arg) {
    bool keyDown = false; // 用于跟踪键是否按下
    while (1) {
        int key = Wait_For_Key();
        char keyChar = (char)(key & 0xFF);

        if (key & KEY_RELEASE_FLAG) {
        // 释放键的扫描码，设置keyDown为false
            keyDown = false;
        } else {
            if (!keyDown) {
                Print("%c", keyChar);
                keyDown = true;
            }
        }

        if ((key & KEY_CTRL_FLAG) && keyChar == 'd') {
	    exitFlag = true; // 设置退出标志
            break;
        }
        if ((key & KEY_CTRL_FLAG) && keyChar == 'a') {
            
	    Start_Kernel_Thread(print_A, 0, PRIORITY_NORMAL, true);
        }
        if ((key & KEY_CTRL_FLAG) && keyChar == 'b') {
            
	    Start_Kernel_Thread(print_B, 0, PRIORITY_NORMAL, true);
        }
    }
    Exit(0);
}


void Main(struct Boot_Info* bootInfo) {
    Init_BSS();
    Init_Screen();
    Init_Mem(bootInfo);
    Init_CRC32();
    Init_TSS();
    Init_Interrupts();
    Init_Scheduler();
    Init_Traps();
    Init_Timer();
    Init_Keyboard();

    Set_Current_Attr(ATTRIB(BLACK, GREEN | BRIGHT));
    Print("Welcome to GeekOS!\n");
    Set_Current_Attr(ATTRIB(BLACK, GRAY));

    Start_Kernel_Thread(print_key, 0, PRIORITY_NORMAL, true);
    //Start_Kernel_Thread(print_A, 0, PRIORITY_NORMAL, true);
    Start_Kernel_Thread(print_B, 0, PRIORITY_NORMAL, true);

    /* Now this thread is done. */
    Exit(0);
}
