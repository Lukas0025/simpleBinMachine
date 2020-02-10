/** Simple CPU emulator with own inscruction set writed in C
 * @file simpleBinMachine.c
 * @author Lukáš PLevač <lukasplevac@gmail.com>
 * @date 10.02.2020
 * date in dd.mm.rrrr
 */

#include <stdio.h>

//assembler definition
#define NOP  0b000 // empty op
#define LOAD 0b001 // load <adr> - load from memory to register
#define ADD  0b010 // add  <adr> - add number from memory on adr to number in register
#define SAVE 0b011 // save <adr> - save data in register to memory on adr
#define NEG  0b100 // neg        - do * (-1) with number in register 
#define JMP  0b101 // jmp  <adr> - jump to adr (next command on adr)
#define JN   0b110 // jm   <adr> - jump to adr if number in register < 0
#define HALT 0b111 // halt       - end of program


//CPU commands part begin

/** Function for virtual CPU
 * load (rewrite) data from memory to register
 * @param mem char array (memory with 8bits cells) with size 32
 * @param reg pointer to char - register
 * @param adr char with address
 */
void load_f(char mem[], char *reg, char adr) {
    *reg = mem[adr];
}

/** Function for virtual CPU
 * add (+) data from memory to register
 * @param mem char array (memory with 8bits cells) with size 32
 * @param reg pointer to char - register
 * @param adr char with address
 */
void add_f(char mem[], char *reg, char adr) {
    *reg += mem[adr];
}

/** Function for virtual CPU
 * save data from register to memory on address
 * @param mem char array (memory with 8bits cells) with size 32
 * @param reg pointer to char - register
 * @param adr char with address
 */
void save_f(char mem[], char *reg, char adr) {
    mem[adr] = *reg;
}

/** Function for virtual CPU
 * do * (-1) with number in register
 * @param reg pointer to char - register
 */
void neg_f(char *reg) {
    *reg *= -1;
}

/** Function for virtual CPU
 * jump to next command
 * @param ip pointer to char with instruction pointer
 * @param adr char with address
 */
void jmp_f(char *ip, char adr) {
    *ip = adr - 1; //after complete CPU do ip++
}

/** Function for virtual CPU
 * jump to next command if number in register < 0
 * @param reg pointer to char - register
 * @param ip pointer to char with instruction pointer
 * @param adr char with address
 */
void jn_f(char *reg, char *ip, char adr) {
    if (*reg < 0) {
        *ip = adr - 1; //after complete CPU do ip++
    }
}

//CPU commands part end

/* from https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format */
/**
 * Print data as bits
 * @param size size of data type
 * @param prt pointer to varaible
 * @return void
 */
void printBits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

/**
 * Print memory data
 * @param mem char array (memory with 8bits cells) with size 32
 * @return void
 */
void print_mem(char mem[]) {
    printf("ADR\n");
    for (int i = 0; i < 32; i++) {
        printf("%3X         HEX %8X     DEC %3d     BIN ", i, mem[i], mem[i]);
        printBits(1, &mem[i]);
    }
}

/** 
 * virtual cpu with 1B register
 * start reading on byte with address 0
 * @param mem char array (memory with 8bits cells) with size 32
 * @return void
 */
void cpu(char mem[]) {
    unsigned char ip = 0b00000; //PC / IP pointer to command
    char reg;                   //register for CPU
    char operation;

    do {
        char command   = mem[ip];
        operation      = (command >> 5) & 0b00000111; //shift 5bit with addres and get last 3 bits to get operation
        char adr       = command & 0b00011111;        // get adr using bin AND

        switch (operation) {
            case LOAD:
                load_f(mem, &reg, adr);
                break;
            case ADD:
                add_f(mem, &reg, adr);
                break;
            case SAVE:
                save_f(mem, &reg, adr);
                break;
            case NEG:
                neg_f(&reg);
                break;
            case JMP:
                jmp_f(&ip, adr);
                break;
            case JN:
                jn_f(&reg, &ip, adr);
                break;
        }

        ip++;

    } while (operation != HALT);
}

int main() {
    char mem[32] = {
        0b00111111, //LOAD 11111
        0b01011110, //ADD  11110
        0b01011110, //ADD  11110
        0b01111101, //SAVE 11101
        0b11111111  //HALT
    };

    //add vars
    mem[0b11111] = 56;
    mem[0b11110] = 10;

    print_mem(mem);
    cpu(mem);
    print_mem(mem);

    return 0;
}