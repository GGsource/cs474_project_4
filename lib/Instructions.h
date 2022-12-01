#ifndef SAL_INCLUDED
#define SAL_INCLUDED
#include "Memory.h"
#include <string>

class Instruction {
  public:
	Memory *mem;
	std::string opCode = "";
	std::string argType = "";
	std::string arg = "";

	Instruction(Memory &memory, std::string givenOpCode,
				std::string givenArgType, std::string givenArg);
	virtual ~Instruction();
	virtual void execute() = 0;
	std::string to_s();
};

class DEC : public Instruction {
  public:
	DEC(std::string givenSymbol, Memory &givenMemory);
	void execute();
};
class LDX : public Instruction {
  public:
	LDX(std::string instruction, std::string givenSymbol, Memory &givenMemory);
	void execute();
};
class LDI : public Instruction {
  public:
	LDI(std::string givenVal, Memory &givenMemory);
	void execute();
};
class STR : public Instruction {
  public:
	STR(std::string givenSymbol, Memory &givenMemory);
	void execute();
};
class XCH : public Instruction {
  public:
	XCH(Memory &givenMemory);
	void execute();
};
class JMP : public Instruction {
  public:
	JMP(std::string givenAddress, Memory &givenMemory);
	void execute();
};
class JXS : public Instruction {
  public:
	JXS(std::string givenAddress, std::string instruction, Memory &givenMemory);
	void execute();
};
class ADD : public Instruction {
  public:
	ADD(Memory &givenMemory);
	void execute();
};
class HLT : public Instruction {
  public:
	HLT(Memory &givenMemory);
	void execute();
};

Instruction *parseInstruction(std::string line, Memory &memory);
#endif