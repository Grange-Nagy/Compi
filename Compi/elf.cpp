#include <stdio.h>
#include <limits>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "elf_debug.h"
#include "elf64.h"
#include "elf_create.h"


//Usage, input 3 filenames representing .text and .data and name of elf executable
int main(int argc, char *argv[])
{
	if (argc != 4){
		std::cout << "Requires 2 filename inputs, .text then .data then an output file name\n";
		return 0;
	}
	
	//TODO make this prettier, or at least consistant
	
	Elf64_Half fileType = ET_EXEC; //should be an input
	Elf64_Addr entryAddress = 0x401000; //should be an input
	Elf64_Off programHeaderTableOffset = 0x00000040; //should NOT need to be an input
	Elf64_Off sectionHeaderTableOffset = 0; //should be an input
	Elf64_Half numberOfProgramHeaders = 3; //should be an input
	Elf64_Half numberOfSectionHeaders = 0; //should be an input
	Elf64_Half sectionHeaderStringTableIndex = SHN_UNDEF; //should be an input
	
	
	int textSize = findSizeOfFile(argv[1]); //get size of .text
	int dataSize = findSizeOfFile(argv[2]); //get size of .data
	
	//null header can be hardcoded
	Elf64_Phdr nullProgramHeader = createProgramHeader(PT_LOAD,PF_R,0x0000,0x400000,0x400000,0x0000e8,0x0000e8,0x1000); 
	Elf64_Phdr * nullProgramHeaderPointer = &nullProgramHeader;
	
	//size of text file needed to create header
	Elf64_Phdr textProgramHeader = createProgramHeader(PT_LOAD,(PF_R + PF_X),0x1000,0x401000,0x401000,textSize,textSize,0x1000);
	Elf64_Phdr * textProgramHeaderPointer = &textProgramHeader;
	
	//size of data is needed
	Elf64_Phdr dataProgramHeader = createProgramHeader(PT_LOAD,(PF_W + PF_R),0x2000,0x402000,0x402000,dataSize,dataSize,0x1000);
	Elf64_Phdr * dataProgramHeaderPointer = &dataProgramHeader;
	
	
	
	Elf64_Ehdr testHeader = createHeader	(fileType,
											entryAddress,
											programHeaderTableOffset,
											sectionHeaderTableOffset,
											numberOfProgramHeaders,
											numberOfSectionHeaders,
											sectionHeaderStringTableIndex);
	Elf64_Ehdr * headerPointer = &testHeader;
	
	//array of pointers to structs allows arbitarary dumping of data into binary, NEEDS TO BE IN ORDER
	const void* structPointerArray[4] = {	headerPointer,
											nullProgramHeaderPointer,
											textProgramHeaderPointer,
											dataProgramHeaderPointer};
	
	
	//hexDump("header dump", headerPointer, 64);
	createELF(argv [1], argv[2], argv[3], structPointerArray);
	//printHeader(testHeader);
	
	return 0;
}