#ifndef SAL_INCLUDED
#define SAL_INCLUDED
#include "Memory.h"
#include <string>

class SAL {
  public:
	std::string opCode, argType, arg;
	Memory *mem;

	virtual void execute() = 0;
	std::string to_s();
};

class DEC : public SAL {
  public:
	DEC(std::string givenSymbol, Memory &memory);
	void execute();
};
class LDX : public SAL {
  public:
	LDX(std::string instruction, std::string givenSymbol, Memory &memory);
	void execute();
};
class LDI : public SAL {
  public:
	LDI(std::string givenVal, Memory &memory);
	void execute();
};
class STR : public SAL {
  public:
	STR(std::string givenSymbol, Memory &memory);
	void execute();
};
class XCH : public SAL {
  public:
	XCH(Memory &memory);
	void execute();
};
class JMP : public SAL {
  public:
	JMP(std::string givenAddress, Memory &memory);
	void execute();
};
class JXS : public SAL {
  public:
	JXS(std::string givenAddress, std::string instruction, Memory &memory);
	void execute();
};
class ADD : public SAL {
  public:
	ADD(Memory &memory);
	void execute();
};
class HLT : public SAL {
  public:
	HLT(Memory &memory);
	void execute();
};

SAL *parseInstruction(std::string line, Memory &memory);
#endif