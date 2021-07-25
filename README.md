# simpleBinMachine

Simple CPU emulator with own inscructions set writed in C for educational purposes.

#### Schema of block in memory
```
 ---------------------------------------
 | BIT | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 ---------------------------------------
 |     | OP CODE   | Address (adr)     |
 ---------------------------------------
 ```
 
#### inscructions
```c
//      AS   OP.CODE
#define NOP  0b000 // empty op
#define LOAD 0b001 // load <adr> - load from memory to register
#define ADD  0b010 // add  <adr> - add number from memory on adr to number in register
#define SAVE 0b011 // save <adr> - save data in register to memory on adr
#define NEG  0b100 // neg        - do * (-1) with number in register 
#define JMP  0b101 // jmp  <adr> - jump to adr (next command on adr)
#define JN   0b110 // jm   <adr> - jump to adr if number in register < 0
#define HALT 0b111 // halt       - end of program
 ```
 
 #### Example code
 ```c
00111111  //LOAD data from 11111 to register
01011110  //ADD  data from 11110 to register
01011110  //ADD  data from 11110 to register
01111101  //SAVE data from register to 11101
11100000  //HALT (program end)
 ```
 
 #### full memory example
  ```c
ADR
  0         HEX       3F     DEC  63     BIN 00111111 //start of program (first command) - LOAD data from 11111 (1F) to register
  1         HEX       5E     DEC  94     BIN 01011110 //ADD  data from 11110 (1E) to register
  2         HEX       5E     DEC  94     BIN 01011110 //ADD  data from 11110 (1E) to register
  3         HEX       7D     DEC 125     BIN 01111101 //SAVE data from register to 11101 (1D)
  4         HEX FFFFFFFF     DEC  -1     BIN 11111111 //HALT
  5         HEX        0     DEC   0     BIN 00000000
  6         HEX        0     DEC   0     BIN 00000000
  7         HEX        0     DEC   0     BIN 00000000
  8         HEX        0     DEC   0     BIN 00000000
  9         HEX        0     DEC   0     BIN 00000000
  A         HEX        0     DEC   0     BIN 00000000
  B         HEX        0     DEC   0     BIN 00000000
  C         HEX        0     DEC   0     BIN 00000000
  D         HEX        0     DEC   0     BIN 00000000
  E         HEX        0     DEC   0     BIN 00000000
  F         HEX        0     DEC   0     BIN 00000000
 10         HEX        0     DEC   0     BIN 00000000
 11         HEX        0     DEC   0     BIN 00000000
 12         HEX        0     DEC   0     BIN 00000000
 13         HEX        0     DEC   0     BIN 00000000
 14         HEX        0     DEC   0     BIN 00000000
 15         HEX        0     DEC   0     BIN 00000000
 16         HEX        0     DEC   0     BIN 00000000
 17         HEX        0     DEC   0     BIN 00000000
 18         HEX        0     DEC   0     BIN 00000000
 19         HEX        0     DEC   0     BIN 00000000
 1A         HEX        0     DEC   0     BIN 00000000
 1B         HEX        0     DEC   0     BIN 00000000
 1C         HEX        0     DEC   0     BIN 00000000
 1D         HEX        0     DEC   0     BIN 00000000 //here will be the result
 1E         HEX        A     DEC  10     BIN 00001010
 1F         HEX       14     DEC  20     BIN 00010100

 ```
