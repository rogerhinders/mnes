#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "debugger.h"
#include "disassembler.h"
#include "regs.h"

using namespace std;

Debugger::Debugger( CPU* cpu, MMU* mmu ) {
    isDebuggerActive = false;
    this->cpu = cpu;
    this->mmu = mmu;
}

void Debugger::checkBreakPoints() {
    for( u32 i=0; i<breakPoints.size(); i++ ) {
        if( cpu->PC==breakPoints[i] ) {
            if( !isDebuggerActive )
                printf( "Reached address breakpoint at $%04x!\n",breakPoints[i] );
            isDebuggerActive = true;
        }
    }
}

void Debugger::getCommand() {
    checkBreakPoints();

    if( !isDebuggerActive ) return;

    //disasm PC
    printDisasmLine(cpu->PC);


    bool readingCmd = true;
    char commandStr[100];
    while( readingCmd ) {
        printf( ">> " );
        gets( commandStr );
        switch( commandStr[0] ) {
            case 'n': //run next line
                readingCmd = false;
                break;
            case 'r': //print registers
                cmdPrintRegisters();
                break;
            case 'h': //show help
            case '?':
                cmdHelp();
                break;
            case 'c': //continue execution
                isDebuggerActive = false;
                readingCmd = false;
                break;
            case 'b': //add addr breakpoint
                cmdAddBreakPoint( commandStr );
                break;
            case 'e': //kill emulator
                printf( "Good bye master!\n" );
                exit( 0 );
                break;
            case 'p': //print memory
                cmdPrintMemory( commandStr );
                break;
            case 'd': //disasm n number of lines
                cmdDisasm( commandStr );
                break;
            case 'l': //list bps
                cmdListBreakpoints();
                break;
            default:
                printf( "ERROR: Invalid command. Write 'h' to show the command help.\n" );
        }
    }
}

void Debugger::printDisasmLine( u32 addr ) {
    char disStr[50];
    char disHex[9];
    u8 opLen = Disassembler::disassemble( ( mmu->memRead8( addr+2 )<<16 )|
                                          ( mmu->memRead8( addr+1 )<<8 )|
                                          mmu->memRead8( addr ),
                                          disStr,
                                          cpu
                                        );
    switch(opLen) {
        case 1: 
            sprintf( disHex,"%02x",mmu->memRead8(addr) );
            break;
        case 2: 
            sprintf( disHex,"%02x %02x",mmu->memRead8(addr), mmu->memRead8(addr+1) );
            break;
        case 3:
            sprintf( disHex,"%02x %02x %02x",mmu->memRead8(addr), mmu->memRead8(addr+1), mmu->memRead8(addr+2) );
            break;
    }
    printf( "[%04x]: <%s> %s\n",addr,disHex,disStr );
}

void Debugger::addBreakPoint( u16 addr ) {
    breakPoints.push_back( addr );
    printf( "Added breakpoint at address $%04x\n",addr );
}

void Debugger::cmdHelp() {
    printf( "----------- HELP ------------\n" );
    printf("b <address>: add breakpoint at address.\n");
    printf("c: continue execution.\n");
    printf("d <number of lines>: disassemble n lines.\n");
    printf("e: exit emulator.\n");
    printf("h or ?: print this help.\n");
    printf("l: list breakpoints.\n");
    printf("n: run next line.\n");
    printf("p <start addr> <end addr>: print memory range.\n");
    printf("r: print registers.\n");
    printf( "-----------------------------\n" );
}


void Debugger::cmdAddBreakPoint( char* cmd ) {
    u16 addr;
    char *split;
    split = strtok( cmd," " );
    u8 cnt;
    while( split!=NULL ) {
        if( cnt==1 ) addr = strtoul( split,NULL,16 );
        split = strtok( NULL," " );
        cnt++;
    }
    if( cnt<2 ) {
        printf( "Usage: b <bp_addr>\n" );
        return;
    }
    addBreakPoint( addr );
}

void Debugger::activateDebugger() {
    isDebuggerActive = true;
    printf("Debugger activated.\n");
}

void Debugger::cmdPrintRegisters() {
    printf( "--------- REGISTERS ---------\n" );
    printf( " A:%02x\n",cpu->A );
    printf( " X:%02x\n",cpu->X );
    printf( " Y:%02x\n",cpu->Y );
    printf( " S:%02x\n",cpu->S );
    printf( " P:%02x\n",cpu->P.b );
    printf( " PC:%04x\n",cpu->PC );
    printf( "-----------------------------\n" );
}

void Debugger::cmdPrintMemory( char* cmd ) {
    u16 startAddr,endAddr;
    char *split;
    split = strtok( cmd," " );
    u8 cnt;
    while( split!=NULL ) {
        if( cnt==1 ) startAddr = strtoul( split,NULL,16 );
        if( cnt==2 ) endAddr = strtoul( split,NULL,16 );
        split = strtok( NULL," " );
        cnt++;
    }
    if( cnt<3 ) {
        printf( "Usage: p <start_addr> <end_addr>\n" );
        return;
    }
    printf( "Printing range $%x-$%x\n",startAddr,endAddr );
    printf("%04x: ",startAddr);
    for( int i=startAddr; i<endAddr; i++ ) {
        printf( "$%02x ",mmu->memRead8( i ) );
        if( ( (i-startAddr+1)%16==0 ) ) printf( "\n" );
        if(!(i==endAddr-1)&&((i-startAddr+1)%16==0 )) printf( "%04x: ",i+1 );
        if((i==endAddr-1)&&!((i-startAddr+1)%16==0 )) printf( "\n" );
    }
}

void Debugger::cmdDisasm( char* cmd ) {
    //get n of lines
    u16 numLines;
    char *split;
    split = strtok( cmd," " );
    u8 cnt;
    while( split!=NULL ) {
        if( cnt==1 ) numLines = strtoul( split,NULL,10 );
        split = strtok( NULL," " );
        cnt++;
    }
    if( cnt<2 ) {
        printf( "Usage: d <number_of_lines>\n" );
        return;
    }
    //disasm it!
    for(u16 i=0;i<numLines;i++) {
        printDisasmLine(cpu->PC+i);
    }
}

void Debugger::cmdListBreakpoints() {
    printf( "-------- BREAKPOINTS --------\n" );
    for( u32 i=0; i<breakPoints.size(); i++ ) {
        printf("$%04x\n",breakPoints[i]);
    }
    printf( "-----------------------------\n" );
}

