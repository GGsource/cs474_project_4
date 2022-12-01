#include "Instructions.h"
#include <cmath>
#include <iostream>
#include <string>

// DONE SAL Constructor
Instruction::Instruction(ALI &memory, std::string givenOpCode,
						 std::string givenArgType, std::string givenArg)
	: mem(&memory), printString(givenOpCode), argType(givenArgType),
	  argValue(givenArg) {}

// DONE: Implement printing SAL
std::string Instruction::to_s() {
	std::string s;

	if (!printString.empty()) {
		s += printString;
	};

	if (!argValue.empty()) {
		s += " with " + argType + " argument of " + argValue;
	}
	return s;
}
// DONE SAL Virtual Destructor
Instruction::~Instruction() {}

// DONE: DEC - Declares a symbolic variable & stores in memory
DEC::DEC(std::string givenSymbol, ALI &givenMemory)
	: Instruction(givenMemory, "DEC", "STRING", givenSymbol) {}
void DEC::execute() {
	mem->internalDataArray[mem->mc] = " ";
	mem->symbolAddresses->insert({argValue, mem->mc});
	mem->mc += 1;
	mem->pc += 1;
}
// DONE: LDX - LDA and LDB take given symbol value and store it in the register
LDX::LDX(std::string instruction, std::string givenSymbol, ALI &givenMemory)
	: Instruction(givenMemory, instruction, "STRING", givenSymbol) {}
void LDX::execute() {
	if (printString == "LDA") {
		mem->registerA = std::stoi(
			mem->internalDataArray[mem->symbolAddresses->at(argValue)]);
	} else {
		mem->registerB = std::stoi(
			mem->internalDataArray[mem->symbolAddresses->at(argValue)]);
	}
	mem->pc += 1;
}

// DONE: LDI - Loads the integer value into the accumulator register. The value
// could be negative
LDI::LDI(std::string givenVal, ALI &givenMemory)
	: Instruction(givenMemory, "LDI", "NUMBER", givenVal) {}
void LDI::execute() {
	mem->registerA = std::stoi(argValue);
	mem->pc += 1;
}

// DONE: STR - Stores content of accumulator into data memory at address of
// symbol.
STR::STR(std::string givenSymbol, ALI &givenMemory)
	: Instruction(givenMemory, "STR", "STRING", givenSymbol) {}
void STR::execute() {
	mem->internalDataArray[mem->symbolAddresses->at(argValue)] =
		std::to_string(mem->registerA);
	mem->pc += 1;
}

// DONE: XCH - Exchanges the content registers A and B.
XCH::XCH(ALI &givenMemory) : Instruction(givenMemory, "XCH", "NONE", "") {}
void XCH::execute() {
	int temp = mem->registerA;
	mem->registerA = mem->registerB;
	mem->registerB = temp;
	mem->pc += 1;
}

// DONE: JMP - Transfers control to instruction at address number in program
// memory.
JMP::JMP(std::string givenAddress, ALI &givenMemory)
	: Instruction(givenMemory, "JMP", "NUMBER", givenAddress) {}
void JMP::execute() { mem->pc = std::stoi(argValue); }

// DONE: JXS - JZS & JVS Transfer control to instruction at address number if
// the zero-result bit or overlfow bit is set respectively.
JXS::JXS(std::string givenAddress, std::string instruction, ALI &givenMemory)
	: Instruction(givenMemory, instruction, "NUMBER", givenAddress) {}
void JXS::execute() {
	if ((printString == "JZS" && mem->zeroResultBit == 1) ||
		(printString == "JVS" && mem->overflowBit == 1)) {
		mem->pc = std::stoi(argValue);
	} else {
		mem->pc += 1;
	}
}

// DONE: ADD - Adds registers A and B. Sum is stored in A. The overflow and
// zero-result bits are set or cleared
ADD::ADD(ALI &givenMemory) : Instruction(givenMemory, "ADD", "NONE", "") {}
void ADD::execute() {
	if (mem->registerA < 0 && mem->registerB < 0 &&
			(mem->registerA + mem->registerB) > 0 ||
		mem->registerA > 0 && mem->registerB > 0 &&
			(mem->registerA + mem->registerB) < 0) {
		mem->overflowBit = 1;
	} else {
		mem->overflowBit = 0;
		mem->registerA += mem->registerB;
	}
	if (mem->registerA == 0) {
		mem->zeroResultBit = 1;
	} else {
		mem->zeroResultBit = 0;
	}
	mem->pc += 1;
}
// DONE: HLT - Terminates program execution.
HLT::HLT(ALI &givenMemory) : Instruction(givenMemory, "HLT", "NONE", "") {}
void HLT::execute() { mem->pc = -1; }

Instruction *parseInstruction(std::string line, ALI &memory) {
	std::string instruction = line.substr(0, 3);
	std::string arg = "";
	if (line.length() > 3) {
		arg = line.substr(4);
	}

	if (instruction == "DEC") {
		return new DEC(arg, memory);
	} else if (instruction == "LDA" || instruction == "LDB") {
		return new LDX(instruction, arg, memory);
	} else if (instruction == "LDI") {
		return new LDI(arg, memory);

	} else if (instruction == "STR") {
		return new STR(arg, memory);

	} else if (instruction == "XCH") {
		return new XCH(memory);

	} else if (instruction == "JMP") {
		return new JMP(arg, memory);

	} else if (instruction == "JZS" || instruction == "JVS") {
		return new JXS(arg, instruction, memory);

	} else if (instruction == "ADD") {
		return new ADD(memory);
	} else if (instruction == "HLT") {
		return new HLT(memory);
	}
	return nullptr;
}