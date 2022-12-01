#ifndef SAL_INCLUDED
#define SAL_INCLUDED
#include "Memory.h"
#include <string>

class SAL {
  public:
	Memory *mem;
	std::string opCode = "";
	std::string argType = "";
	std::string arg = "";

	SAL(Memory &memory, std::string givenOpCode, std::string givenArgType,
		std::string givenArg);
	virtual void execute() = 0;
	std::string to_s();
};

class DEC : public SAL {
  public:
	DEC(std::string givenSymbol, Memory &givenMemory);
	void execute();
};
class LDX : public SAL {
  public:
	LDX(std::string instruction, std::string givenSymbol, Memory &givenMemory);
	void execute();
};
class LDI : public SAL {
  public:
	LDI(std::string givenVal, Memory &givenMemory);
	void execute();
};
class STR : public SAL {
  public:
	STR(std::string givenSymbol, Memory &givenMemory);
	void execute();
};
class XCH : public SAL {
  public:
	XCH(Memory &givenMemory);
	void execute();
};
class JMP : public SAL {
  public:
	JMP(std::string givenAddress, Memory &givenMemory);
	void execute();
};
class JXS : public SAL {
  public:
	JXS(std::string givenAddress, std::string instruction, Memory &givenMemory);
	void execute();
};
class ADD : public SAL {
  public:
	ADD(Memory &givenMemory);
	void execute();
};
class HLT : public SAL {
  public:
	HLT(Memory &givenMemory);
	void execute();
};

SAL *parseInstruction(std::string line, Memory &memory);
#endif