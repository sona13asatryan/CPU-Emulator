# CPU-Emulator
This project is an emulator of a simple 32-bit CPU designed using Turing Complete game. This CPU works only with one input and one output devices. Below you can see how to write a binary program for this architecture.

All the instructions have the same length of 32 bits. The architecture supports big-endian format.
The left byte (third byte) stands for the operation code, the second one for the first argument, the first for the second argument, and the zeroth for the destination. The meaning of each bit is described below starting from the very left bit.

## OPCODE

7\. 0 - the 1st argument is register or input, 1 - the 1st argument is an immediate value,  
6\. 0 - the 2nd argument is register or input, 1 - the 2nd argument is an immediate value,   
5\. 1 - the 1st argument is a memory address,  
4\. 1 - destination is a memory adddress,  
| 3 | 2 | 1 | 0 |   
――――――――   
| 0 | 0 | 0 | 0 | - AND  
| 0 | 0 | 0 | 1 | - OR  
| 0 | 0 | 1 | 0 | - NOT  
| 0 | 0 | 1 | 1 | - NAND  
| 0 | 1 | 0 | 0 | - NOR  
| 0 | 1 | 0 | 1 | - ADD  
| 0 | 1 | 1 | 0 | - SUB  
| 0 | 1 | 1 | 1 | - MUL  
| 1 | 0 | 0 | 0 | - ON   
| 1 | 0 | 0 | 1 | - EQ  
| 1 | 0 | 1 | 0 | - GR  
| 1 | 0 | 1 | 1 | - GREQ  
| 1 | 1 | 0 | 0 | - OF  
| 1 | 1 | 0 | 1 | - NEQ  
| 1 | 1 | 1 | 0 | - LS  
| 1 | 1 | 1 | 1 | - LSEQ  
 
 
## ARGUMENT 1,2 and DESTINATION
  
The number from 0 to 14 indicates the corresponding register, 15 stands for the counter, which cannot be read or overwritten unless you use a conditional operation, 16 indicates the input (in case of destination output). The byte can also contain a memory address (obviously from 0 to 255).
While using a conditional operation the destination is used as a number which is going to be loaded into the counter. If you mention the destination byte as a register or memory address its content is loaded into the counter.


#### You can use [this](https://hexed.it/) editor to create the binary code .


