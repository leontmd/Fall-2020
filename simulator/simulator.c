/*
  Author: Daniel Kopta and Skylar Shyu (u1039726)
  Spring 2018
  CS 4400, University of Utah

  * A simple x86-like processor simulator.
  * Read in a binary file that encodes instructions to execute.
  * Simulate a processor by executing instructions one at a time and appropriately 
  * updating register and memory contents.

  * Some code and pseudo code has been provided as a starting point.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "instruction.h"

// Forward declarations for helper functions
unsigned int get_file_size(int file_descriptor);
unsigned int* load_file(int file_descriptor, unsigned int size);
instruction_t* decode_instructions(unsigned int* bytes, unsigned int num_instructions);
unsigned int execute_instruction(unsigned int program_counter, instruction_t* instructions, 
				 int* registers, unsigned char* memory);
void print_instructions(instruction_t* instructions, unsigned int num_instructions);
void error_exit(const char* message);

// 17 registers
#define NUM_REGS 17
// 1024-byte stack
#define STACK_SIZE 1024
// Define flag bits

int main(int argc, char** argv)
{
  // Make sure we have enough arguments
  if(argc < 2)
    error_exit("must provide an argument specifying a binary file to execute");

  // Open the binary file
  int file_descriptor = open(argv[1], O_RDONLY);
  if (file_descriptor == -1) 
    error_exit("unable to open input file");

  // Get the size of the file
  unsigned int file_size = get_file_size(file_descriptor);
  // Make sure the file size is a multiple of 4 bytes
  // since machine code instructions are 4 bytes each
  if(file_size % 4 != 0)
    error_exit("invalid input file");

  // Load the file into memory
  // We use an unsigned int array to represent the raw bytes
  // We could use any 4-byte integer type
  unsigned int* instruction_bytes = load_file(file_descriptor, file_size);
  close(file_descriptor);
  unsigned int num_instructions = file_size / 4;

  /****************************************/
  /**** Begin code to modify/implement ****/
  /****************************************/

  // Allocate and decode instructions (left for you to fill in)
  instruction_t* instructions = decode_instructions(instruction_bytes, num_instructions);
  //print_instructions(instructions, num_instructions);
  
  int* registers = (int*)malloc(sizeof(int) * NUM_REGS);
  int i;
  for(i = 0; i < NUM_REGS; i++){
    if (i == 6)
      registers[i] = (int32_t)1024;
    else
      registers[i] = (int32_t)0;
  }

  unsigned char* memory = (unsigned char*)malloc(sizeof(char) * STACK_SIZE);
  unsigned int j;
  for (j=0; j < STACK_SIZE; j++){
    memory[i] = 0;
  }
  // Run the simulation
  unsigned int program_counter = 0;
  // program_counter is a byte address, so we must multiply num_instructions by 4 to get the address past the last instruction
  while(program_counter != num_instructions * 4)
  {
    program_counter = execute_instruction(program_counter, instructions, registers, memory);
  }  
  return 0;
}
  


/*
 * Decodes the array of raw instruction bytes into an array of instruction_t
 * Each raw instruction is encoded as a 4-byte unsigned int
*/
instruction_t* decode_instructions(unsigned int* bytes, unsigned int num_instructions)
{
  instruction_t* retval = (instruction_t*)malloc(sizeof(instruction_t) * num_instructions);
  int i;

  for(i = 0; i < num_instructions; i++){
    unsigned int mask = 0xF8000000;
    unsigned int byte = bytes[i];

    retval[i].opcode  = (byte & mask) >> 27;
    mask >>= 5;
    retval[i].first_register = (byte & mask) >> 22;
    mask >>= 5;
    retval[i].second_register = (byte & mask) >> 17;
    mask = 0x0000FFFF;
    retval[i].immediate = (byte & mask);
  }
  return retval;
}


/*
 * Executes a single instruction and returns the next program counter
*/
unsigned int execute_instruction(unsigned int program_counter, instruction_t* instructions, int* registers, unsigned char* memory)
{
  // program_counter is a byte address, but instructions are 4 bytes each
  // divide by 4 to get the index into the instructions array
  instruction_t instr = instructions[program_counter / 4];
  int CF, OF, ZF, SF;
  long reg1 = (long)registers[instr.first_register];
  long reg2 = (long)registers[instr.second_register];
  long diff = reg2 - reg1;
  unsigned long ureg1 = (unsigned long)registers[instr.first_register];
  unsigned long ureg2 = (unsigned long)registers[instr.second_register];
  //printf("pc/4: %d pc: %d\n", &instructions[program_counter / 4], program_counter);
  //printf("OpCode: %d Reg1: %d Reg2: %d Imm: %d\n", instr.opcode, instr.first_register, instr.second_register, instr.immediate);
  switch(instr.opcode)
  {
  case subl:
    registers[instr.first_register] = registers[instr.first_register] - instr.immediate;
    break;
  case addl_reg_reg:
    registers[instr.second_register] = registers[instr.second_register] + registers[instr.first_register];
    break;
  case addl_imm_reg:
    registers[instr.first_register] = registers[instr.first_register] + instr.immediate;
    break;
  case imull:
    registers[instr.second_register] = registers[instr.first_register] * registers[instr.second_register];
    break;
  case shrl:
    registers[instr.first_register] = (uint32_t)registers[instr.first_register] >> 1;
    break;
  case movl_reg_reg:
    registers[instr.second_register] = registers[instr.first_register];
    break;
  case movl_deref_reg:
    registers[instr.second_register] = *((int*)(&memory[(registers[instr.first_register] + instr.immediate)]));
    break;
  case movl_reg_deref:
  {
    *((int*)(&memory[(registers[instr.second_register] + instr.immediate)])) = registers[instr.first_register];
    break;
  }
  case movl_imm_reg:
    registers[instr.first_register] = instr.immediate;
    break;
  case cmpl:
  {
    CF = 0;
    ZF = 0;
    SF = 0;
    OF = 0;

    if (diff == 0) 
      ZF = 64;
    if ((diff & 0x80000000) != 0)
      SF = 128;
    if (ureg1 > ureg2)
      CF = 1;
    if (diff > INT32_MAX || diff < INT32_MIN)
      OF = 2048;
    registers[16] = 0;
    registers[16] = CF + OF + SF + ZF;  
    break;
  }
  case je:
    if ((registers[16] & 0x00000040) != 0)
      return program_counter + 4 + (instr.immediate);
    break;

  case jl:
    if ( ((registers[16] & 0x00000800) != 0) ^ ((registers[16] & 0x00000080) != 0))
      return program_counter + 4 + (instr.immediate);
    break;

  case jle:
    if ( (((registers[16] & 0x00000800) != 0) ^ ((registers[16] & 0x00000080) != 0)) ||  ((registers[16] & 0x00000040) != 0) )
      return program_counter + 4 + (instr.immediate);
    break;

  case jge:
    if (!( ((registers[16] & 0x00000800) != 0) ^ ((registers[16] & 0x00000080) != 0)))
      return program_counter + 4 + (instr.immediate);
    break;

  case jbe:
    if (((registers[16] & 0x00000040) != 0) || ((registers[16] & 0x00000001) != 0))
      return program_counter + 4 + (instr.immediate);
    break;

  case jmp:
    return program_counter + 4 + (instr.immediate);
    break;

  case call:
    registers[6] = registers[6] - 4;
    *((int*)&memory[registers[6]]) = program_counter + 4;
    return program_counter + instr.immediate + 4;
    break;

  case ret:
    if(registers[6] == 1024)
      exit(0);
    else
      program_counter = *((int*)(&memory[registers[6]]));
      registers[6] = registers[6] + 4;
      return program_counter;
    break;

  case pushl:
    registers[6] = registers[6] - 4;
    *((int*)&memory[registers[6]]) = registers[instr.first_register];
    break;

  case popl:
    registers[instr.first_register] = *((int*)(&memory[registers[6]]));
    registers[6] = registers[6] + 4;
    break;

  case printr:
    printf("%d (0x%x)\n", registers[instr.first_register], registers[instr.first_register]);
    break;

  case readr:
    scanf("%d", &(registers[instr.first_register]));
    break;
  
  default:
    break;
  }
  return program_counter + 4;
}


/*********************************************/
/**** Begin helper methods. Do not modify ****/
/*********************************************/

/*
 * Returns the file size in bytes of the file referred to by the given descriptor
*/
unsigned int get_file_size(int file_descriptor)
{
  struct stat file_stat;
  fstat(file_descriptor, &file_stat);
  return file_stat.st_size;
}

/*
 * Loads the raw bytes of a file into an array of 4-byte units
*/
unsigned int* load_file(int file_descriptor, unsigned int size)
{
  unsigned int* raw_instruction_bytes = (unsigned int*)malloc(size);
  if(raw_instruction_bytes == NULL)
    error_exit("unable to allocate memory for instruction bytes (something went really wrong)");

  int num_read = read(file_descriptor, raw_instruction_bytes, size);

  if(num_read != size)
    error_exit("unable to read file (something went really wrong)");

  return raw_instruction_bytes;
}

/*
 * Prints the opcode, register IDs, and immediate of every instruction, 
 * assuming they have been decoded into the instructions array
*/
void print_instructions(instruction_t* instructions, unsigned int num_instructions)
{
  printf("instructions: \n");
  unsigned int i;
  for(i = 0; i < num_instructions; i++)
  {
    printf("op: %d, reg1: %d, reg2: %d, imm: %d\n", 
	   instructions[i].opcode,
	   instructions[i].first_register,
	   instructions[i].second_register,
	   instructions[i].immediate);
  }
  printf("--------------\n");
}


/*
 * Prints an error and then exits the program with status 1
*/
void error_exit(const char* message)
{
  printf("Error: %s\n", message);
  exit(1);
}
