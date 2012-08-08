#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <vector>
#include "types.h"
#include "cpu.h"
#include "mmu.h"

class Debugger {

public:
    Debugger( CPU* cpu, MMU* mmu );
    void getCommand();
    void addBreakPoint( u16 addr );
    void activateDebugger();
private:
    std::vector<u32> breakPoints;
    bool isDebuggerActive;
    CPU* cpu;
    MMU* mmu;
    void printDisasmLine( u32 addr );
    void checkBreakPoints();
    void cmdHelp();
    void cmdAddBreakPoint( char* cmd );
    void cmdPrintRegisters();
    void cmdPrintMemory( char* cmd );
    void cmdDisasm( char* cmd );
    void cmdListBreakpoints();
};

#endif // DEBUGGER_H
