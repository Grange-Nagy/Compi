#include <stdio.h>
#include <limits>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "elf_debug.h"
#include "elf64.h"
#include "elf_create.h"



int main()
{
	
	Elf64_Phdr nullProgramHeader = createProgramHeader(PT_LOAD,PF_W,0,0x400000,0x400000,0x0000e8,0x0000e8,0x1000);
	Elf64_Phdr textProgramHeader = createProgramHeader(PT_LOAD,(PF_R + PF_X),0,0x401000,0x401000,0x000027,0x000027,0x1000);
	Elf64_Phdr dataProgramHeader = createProgramHeader(PT_LOAD,(PF_W + PF_R),0,0x402000,0x402000,0x00000d,0x00000d,0x1000);
	
	Elf64_Phdr * nullProgramHeaderPointer = &nullProgramHeader;
	Elf64_Phdr * textProgramHeaderPointer = &textProgramHeader;
	Elf64_Phdr * dataProgramHeaderPointer = &dataProgramHeader;
	
	
	Elf64_Half fileType = ET_EXEC; //should be an input
	Elf64_Addr entryAddress = 0x401000; //should be an input
	Elf64_Off programHeaderTableOffset = 0x00000040; //should NOT be an input
	Elf64_Off sectionHeaderTableOffset = 0; //should be an input
	Elf64_Half numberOfProgramHeaders = 3; //should be an input
	Elf64_Half numberOfSectionHeaders = 0; //should be an input
	Elf64_Half sectionHeaderStringTableIndex = 0; //should be an input
	
	Elf64_Ehdr testHeader = createHeader	(fileType,
											entryAddress,
											programHeaderTableOffset,
											sectionHeaderTableOffset,
											numberOfProgramHeaders,
											numberOfSectionHeaders,
											sectionHeaderStringTableIndex);
	Elf64_Ehdr * headerPointer = &testHeader;
	
	const void* structPointerArray[4];
	structPointerArray[0] = headerPointer;
	structPointerArray[1] = nullProgramHeaderPointer;
	structPointerArray[2] = textProgramHeaderPointer;
	structPointerArray[3] = dataProgramHeaderPointer;
	
	
	hexDump("header dump", headerPointer, 64);
	writeStructPointerArrayToFileAsBinary("test.dat", structPointerArray, 64);
	printHeader(testHeader);
	
	return 0;
}