#include "memory/dram.h"
#include "memory/instruction.h"
#include "cpu/register.h"
#include "cpu/mmu.h"
#include "disk/elf.h"
#include <stdio.h>

int main(){
    init_handler_table();

    reg.rax = 0x12340000;
    reg.rbx = 0x0;
    reg.rcx = 0x8000660;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7ffffffeddd8;
    reg.rdi = 0x1;
    reg.rbp = 0x7ffffffedfa0;
    reg.rsp = 0x7ffffffedf80;
    reg.rip = (uint64_t)&program[11];

    write64bits_dram(va2pa(0x7ffffffedfa0), 0x08000660);
    write64bits_dram(va2pa(0x7ffffffedf98), 0x0);
    write64bits_dram(va2pa(0x7ffffffedf90), 0x0000abcd);
    write64bits_dram(va2pa(0x7ffffffedf88), 0x12340000);
    write64bits_dram(va2pa(0x7ffffffedf80), 0x08000660);

    print_register();
    print_stack();

    for(int i=0; i<15;i++){
        instruction_cycle();
        print_register();
        print_stack();
    }

    int match = 1;
    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x0);
    match = match && (reg.rcx == 0x8000660);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7ffffffedfa0);
    match = match && (reg.rsp == 0x7ffffffedf80);

    if (match == 1)
    {
        printf("register match\n");
    }
    else
    {
        printf("register not match\n");
    }

    match = match && (read64bits_dram(va2pa(0x7ffffffedfa0)) == 0x08000660);     // rbp
    match = match && (read64bits_dram(va2pa(0x7ffffffedf98)) == 0x1234abcd);
    match = match && (read64bits_dram(va2pa(0x7ffffffedf90)) == 0xabcd);
    match = match && (read64bits_dram(va2pa(0x7ffffffedf88)) == 0x12340000);
    match = match && (read64bits_dram(va2pa(0x7ffffffedf80)) == 0x08000660);
    
    if (match == 1)
    {
        printf("memory match\n");
    }
    else
    {
        printf("memory not match\n");
    }
    
    return 0;
}