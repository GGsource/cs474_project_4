#ifndef MEM_INCLUDED
#define MEM_INCLUDED
#include <string>
#include <unordered_map>

class SAL;

class Memory {
  public:
	SAL **internalProgramArray;
	std::string *internalDataArray;
	int registerA, registerB, pc, zeroResultBit, overflowBit, prevhc, curhc, mc;
	std::unordered_map<std::string, int> *symbolAddresses;
	bool loopWarn;
	void executeSingle(); // Executes one line
	bool reachedEnd();	  // Check if pc is out of bounds
	std::string to_s();	  // Make memory printable
	std::string _title(std::string);
	std::string printSymbolMap(std::unordered_map<std::string, int> map);

	Memory();
};
#endif