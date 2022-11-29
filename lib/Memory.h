#include <string>
#include <unordered_map>

class Memory {
  private:
	std::string internalArray[256];

  public:
	int registerA, registerB, pc, zeroResultBit, overflowBit, prevhc, curhc, mc;
	std::unordered_map<std::string, std::string> symbolAddresses;

	std::string operator[](int ndx) const; // For index access
	std::string &operator[](int ndx);	   // for assignment at an index
	void executeSingle();				   // Executes one line
	bool reachedEnd();					   // Check if pc is out of bounds
	std::string to_s();					   // Make memory printable
	std::string _title();				   // makes headers stand out

	Memory();
};