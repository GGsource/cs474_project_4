#ifndef ALI_INCLUDED
#define ALI_INCLUDED
#include <string>
#include <unordered_map>

class Instruction;

class ALI {
  public:
	Instruction **internalProgramArray;
	std::string *internalDataArray;
	int registerA, registerB, pc, zeroResultBit, overflowBit, prevhc, curhc, mc;
	std::unordered_map<std::string, int> *symbolAddresses;
	bool loopWarn;
	void executeSingle(); // Executes one line
	bool reachedEnd();	  // Check if pc is out of bounds
	std::string to_s();	  // Make ALI printable
	std::string _title(std::string title, char delimiter);
	std::string printSymbolMap(std::unordered_map<std::string, int> map);

	ALI();
	~ALI();
};
#endif