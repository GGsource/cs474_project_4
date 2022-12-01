#ifndef SAL_INCLUDED
#define SAL_INCLUDED
#include "ALI.h"
#include <string>

class Instruction {
  public:
	ALI *mem;
	std::string printString = "";
	std::string argType = "";
	std::string argValue = "";

	Instruction(ALI &memory, std::string givenOpCode, std::string givenArgType,
				std::string givenArg);
	virtual ~Instruction();
	virtual void execute() = 0;
	std::string to_s();
};

class DEC : public Instruction {
  public:
	DEC(std::string givenSymbol, ALI &givenMemory);
	void execute();
};
class LDX : public Instruction {
  public:
	LDX(std::string instruction, std::string givenSymbol, ALI &givenMemory);
	void execute();
};
class LDI : public Instruction {
  public:
	LDI(std::string givenVal, ALI &givenMemory);
	void execute();
};
class STR : public Instruction {
  public:
	STR(std::string givenSymbol, ALI &givenMemory);
	void execute();
};
class XCH : public Instruction {
  public:
	XCH(ALI &givenMemory);
	void execute();
};
class JMP : public Instruction {
  public:
	JMP(std::string givenAddress, ALI &givenMemory);
	void execute();
};
class JXS : public Instruction {
  public:
	JXS(std::string givenAddress, std::string instruction, ALI &givenMemory);
	void execute();
};
class ADD : public Instruction {
  public:
	ADD(ALI &givenMemory);
	void execute();
};
class HLT : public Instruction {
  public:
	HLT(ALI &givenMemory);
	void execute();
};

Instruction *parseInstruction(std::string line, ALI &memory);
#endif