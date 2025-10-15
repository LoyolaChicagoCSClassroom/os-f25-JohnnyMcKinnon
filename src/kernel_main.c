
#include <stdint.h>

#define MULTIBOOT2_HEADER_MAGIC         0xe85250d6

const unsigned int multiboot_header[]  __attribute__((section(".multiboot"))) = {MULTIBOOT2_HEADER_MAGIC, 0, 16, -(16+MULTIBOOT2_HEADER_MAGIC), 0, 12};

uint8_t inb (uint16_t _port) {
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
int x=0;
int y=0;

unsigned char keyboard_map[128] =
{
   0,  27, '1', '2', '3', '4', '5', '6', '7', '8',     /* 9 */
 '9', '0', '-', '=', '\b',     /* Backspace */
 '\t',                 /* Tab */
 'q', 'w', 'e', 'r',   /* 19 */
 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
   0,                  /* 29   - Control */
 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',     /* 39 */
'\'', '`',   0,                /* Left shift */
'\\', 'z', 'x', 'c', 'v', 'b', 'n',                    /* 49 */
 'm', ',', '.', '/',   0,                              /* Right shift */
 '*',
   0,  /* Alt */
 ' ',  /* Space bar */
   0,  /* Caps lock */
   0,  /* 59 - F1 key ... > */
   0,   0,   0,   0,   0,   0,   0,   0,
   0,  /* < ... F10 */
   0,  /* 69 - Num lock*/
   0,  /* Scroll Lock */
   0,  /* Home key */
   0,  /* Up Arrow */
   0,  /* Page Up */
 '-',
   0,  /* Left Arrow */
   0,
   0,  /* Right Arrow */
 '+',
   0,  /* 79 - End key*/
   0,  /* Down Arrow */
   0,  /* Page Down */
   0,  /* Insert Key */
   0,  /* Delete Key */
   0,   0,   0,
   0,  /* F11 Key */
   0,  /* F12 Key */
   0,  /* All other keys are undefined */
};

void print_char(char c){
char *vram=(char*)0xb8000;
vram[x*2]=c;
vram[x*2+1]=7;
x++;
}//print_char

void print_str(char arr[]){
char *ptr=arr;
while(*ptr!='\0'){
print_char(*ptr);
ptr++;
}
}//print_str

void main() {
//unsigned char *vram = (unsigned char*)0xb8000; // Base address of video mem
//const unsigned char color = 7; // gray text on black background
print_char('J');
print_char('o');
print_char('h');
print_char('n');
print_char('n');
print_char('y');
print_str("Johnny");

    while(1) {
        uint8_t status = inb(0x64);

        if(status & 1) {
            uint8_t scancode = inb(0x60);
char ascii=keyboard_map[scancode];
print_char(ascii);
        }
    }
}
