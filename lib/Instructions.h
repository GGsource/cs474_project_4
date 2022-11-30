#ifndef SAL_INCLUDED
#define SAL_INCLUDED
#include "Memory.h"
#include <string>

class SAL {
  public:
	std::string opCode, argType, arg;
	Memory *mem;

	virtual void execute();
	std::string to_s();
};

class DEC : private SAL {
  public:
	std::string symbol;

	DEC(std::string givenSymbol, Memory &memory);
	void execute() = 0;
};

#endif