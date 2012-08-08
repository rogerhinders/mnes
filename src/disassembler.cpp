/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <cstdio>
#include <cstring>
#include "disassembler.h"
#include "tables.h"

Disassembler::Disassembler() { }

u8 Disassembler::disassemble( u32 opcode, char *opstr, CPU* cpu ) {
    u8 op = opcode;
    u8 nn = opcode>>8;
    u16 nnnn = opcode>>8;

    switch(op) {
        case 0x00: strcpy( opstr,"brk" ); break;
        case 0x01: sprintf( opstr,"ora ($%02x,X)", nn ); break;
        case 0x02: strcpy( opstr,"kil" ); break;
        case 0x03: sprintf( opstr,"slo ($%02x,X)", nn ); break;
        case 0x04: sprintf( opstr,"nop $%02x", nn ); break;
        case 0x05: sprintf( opstr,"ora $%02x", nn ); break;
        case 0x06: sprintf( opstr,"asl $%02x", nn ); break;
        case 0x07: sprintf( opstr,"slo $%02x", nn ); break;
        case 0x08: strcpy( opstr,"php" ); break;
        case 0x09: sprintf( opstr,"ora #$%02x", nn ); break;
        case 0x0a: strcpy( opstr,"asl A" ); break;
        case 0x0b: sprintf( opstr,"anc #$%02x", nn ); break;
        case 0x0c: sprintf( opstr,"nop $%04x", nnnn ); break;
        case 0x0d: sprintf( opstr,"ora $%04x", nnnn ); break;
        case 0x0e: sprintf( opstr,"asl $%04x", nnnn ); break;
        case 0x0f: sprintf( opstr,"slo $%04x", nnnn ); break;
        case 0x10: sprintf( opstr,"bpl $%04x", cpu->PC+(s8)nn+2 ); break;
        case 0x11: sprintf( opstr,"ora ($%02x),Y", nn ); break;
        case 0x12: strcpy( opstr,"kil" ); break;
        case 0x13: sprintf( opstr,"slo ($%02x),Y", nn ); break;
        case 0x14: sprintf( opstr,"nop $%02x,X", nn ); break;
        case 0x15: sprintf( opstr,"ora $%02x,X", nn ); break;
        case 0x16: sprintf( opstr,"asl $%02x,X", nn ); break;
        case 0x17: sprintf( opstr,"slo $%02x,X", nn ); break;
        case 0x18: strcpy( opstr,"clc" ); break;
        case 0x19: sprintf( opstr,"ora $%04x,Y", nnnn ); break;
        case 0x1a: strcpy( opstr,"nop" ); break;
        case 0x1b: sprintf( opstr,"slo $%04x,Y", nnnn ); break;
        case 0x1c: sprintf( opstr,"nop $%04x,X", nnnn ); break;
        case 0x1d: sprintf( opstr,"ora $%04x,X", nnnn ); break;
        case 0x1e: sprintf( opstr,"asl $%04x,X", nnnn ); break;
        case 0x1f: sprintf( opstr,"slo $%04x,X", nnnn ); break;
        case 0x20: sprintf( opstr,"jsr $%04x", nnnn ); break;
        case 0x21: sprintf( opstr,"and ($%02x,X)", nn ); break;
        case 0x22: strcpy( opstr,"kil" ); break;
        case 0x23: sprintf( opstr,"rla ($%02x,X)", nn ); break;
        case 0x24: sprintf( opstr,"bit $%02x", nn );  break;
        case 0x25: sprintf( opstr,"and $%02x", nn ); break;
        case 0x26: sprintf( opstr,"rol $%02x", nn ); break;
        case 0x27: sprintf( opstr,"rla $%02x", nn ); break;
        case 0x28: strcpy( opstr,"plp" ); break;
        case 0x29: sprintf( opstr,"and #$%02x", nn ); break;
        case 0x2a: strcpy( opstr,"rol A" ); break;
        case 0x2b: sprintf( opstr,"anc #$%02x", nn ); break;
        case 0x2c: sprintf( opstr,"bit $%04x", nnnn ); break;
        case 0x2d: sprintf( opstr,"and $%04x", nnnn ); break;
        case 0x2e: sprintf( opstr,"rol $%04x", nnnn ); break;
        case 0x2f: sprintf( opstr,"rla $%04x", nnnn ); break;
        case 0x30: sprintf( opstr,"bmi $%04x", cpu->PC+(s8)nn+2 ); break;
        case 0x31: sprintf( opstr,"and ($%02x),Y", nn ); break;
        case 0x32: strcpy( opstr,"kil" ); break;
        case 0x33: sprintf( opstr,"rla ($%02x),Y", nn ); break;
        case 0x34: sprintf( opstr,"nop $%02x,X", nn ); break;
        case 0x35: sprintf( opstr,"and $%02x,X", nn ); break;
        case 0x36: sprintf( opstr,"rol $%02x,X", nn ); break;
        case 0x37: sprintf( opstr,"rla $%02x,X", nn ); break;
        case 0x38: strcpy( opstr,"sec" ); break;
        case 0x39: sprintf( opstr,"and $%04x,Y", nnnn ); break;
        case 0x3a: strcpy( opstr,"nop" ); break;
        case 0x3b: sprintf( opstr,"rla $%04x,Y", nnnn ); break;
        case 0x3c: sprintf( opstr,"nop $%04x,X", nnnn ); break;
        case 0x3d: sprintf( opstr,"and $%04x,X", nnnn ); break;
        case 0x3e: sprintf( opstr,"rol $%04x,X", nnnn ); break;
        case 0x3f: sprintf( opstr,"rla $%04x,X", nnnn ); break;
        case 0x40: strcpy( opstr,"rti" ); break;
        case 0x41: sprintf( opstr,"eor ($%02x,X)", nn ); break;
        case 0x42: strcpy( opstr,"kil" ); break;
        case 0x43: sprintf( opstr,"sre ($%02x,X)", nn ); break;
        case 0x44: sprintf( opstr,"nop $%02x", nn ); break;
        case 0x45: sprintf( opstr,"eor $%02x", nn ); break;
        case 0x46: sprintf( opstr,"lsr $%02x", nn ); break;
        case 0x47: sprintf( opstr,"sre $%02x", nn ); break;
        case 0x48: strcpy( opstr,"pha" ); break;
        case 0x49: sprintf( opstr,"eor #$%02x", nn ); break;
        case 0x4a:  strcpy( opstr,"lsr A" ); break;
        case 0x4b: sprintf( opstr,"alr #$%02x", nn ); break;
        case 0x4c: sprintf( opstr,"jmp $%04x", nnnn ); break;
        case 0x4d: sprintf( opstr,"eor $%04x", nnnn ); break;
        case 0x4e: sprintf( opstr,"lsr $%04x", nnnn ); break;
        case 0x4f: sprintf( opstr,"sre $%04x", nnnn ); break;
        case 0x50: sprintf( opstr,"bvc $%04x", cpu->PC+(s8)nn+2 ); break;
        case 0x51: sprintf( opstr,"eor ($%02x),Y", nn ); break;
        case 0x52: strcpy( opstr,"kil" ); break;
        case 0x53: sprintf( opstr,"sre ($%02x),Y", nn ); break;
        case 0x54: sprintf( opstr,"nop $%02x,X", nn ); break;
        case 0x55: sprintf( opstr,"eor $%02x,X", nn ); break;
        case 0x56: sprintf( opstr,"lsr $%02x,X", nn ); break;
        case 0x57: sprintf( opstr,"sre $%02x,X", nn ); break;
        case 0x58: strcpy( opstr,"cli" ); break;
        case 0x59: sprintf( opstr,"eor $%04x,Y", nnnn ); break;
        case 0x5a: strcpy( opstr,"nop" ); break;
        case 0x5b: sprintf( opstr,"sre $%04x,Y", nnnn ); break;
        case 0x5c: sprintf( opstr,"nop $%04x,X", nnnn ); break;
        case 0x5d: sprintf( opstr,"eor $%04x,X", nnnn ); break;
        case 0x5e: sprintf( opstr,"lsr $%04x,X", nnnn ); break;
        case 0x5f: sprintf( opstr,"sre $%04x,X", nnnn ); break;
        case 0x60: strcpy( opstr,"rts" ); break;
        case 0x61: sprintf( opstr,"adc ($%02x,X)", nn ); break;
        case 0x62: strcpy( opstr,"kil" ); break;
        case 0x63: sprintf( opstr,"rra ($%02x,X)", nn ); break;
        case 0x64: sprintf( opstr,"nop $%02x", nn ); break;
        case 0x65: sprintf( opstr,"adc $%02x", nn ); break;
        case 0x66: sprintf( opstr,"ror $%02x", nn ); break;
        case 0x67: sprintf( opstr,"rra $%02x", nn ); break;
        case 0x68: strcpy( opstr,"pla" ); break;
        case 0x69: sprintf( opstr,"adc #$%02x", nn ); break;
        case 0x6a: strcpy( opstr,"ror A" ); break;
        case 0x6b: sprintf( opstr,"arr #$%02x", nn ); break;
        case 0x6c: sprintf( opstr,"jmp ($%04x)", nnnn ); break;
        case 0x6d: sprintf( opstr,"adc $%04x", nnnn ); break;
        case 0x6e: sprintf( opstr,"ror $%04x", nnnn ); break;
        case 0x6f: sprintf( opstr,"rra $%04x", nnnn ); break;
        case 0x70: sprintf( opstr,"bvs $%04x", cpu->PC+(s8)nn+2 ); break;
        case 0x71: sprintf( opstr,"adc ($%02x),Y", nn ); break;
        case 0x72: strcpy( opstr,"kil" ); break;
        case 0x73: sprintf( opstr,"rra ($%02x),Y", nn ); break;
        case 0x74: sprintf( opstr,"nop $%02x,X", nn ); break;
        case 0x75: sprintf( opstr,"adc $%02x,X", nn ); break;
        case 0x76: sprintf( opstr,"ror $%02x,X", nn ); break;
        case 0x77: sprintf( opstr,"rra $%02x,X", nn ); break;
        case 0x78: strcpy( opstr,"sei" ); break;
        case 0x79: sprintf( opstr,"adc $%04x,Y", nnnn ); break;
        case 0x7a: strcpy( opstr,"nop" ); break;
        case 0x7b: sprintf( opstr,"rra $%04x,Y", nnnn ); break;
        case 0x7c: sprintf( opstr,"nop $%04x,X", nnnn ); break;
        case 0x7d: sprintf( opstr,"adc $%04x,X", nnnn ); break;
        case 0x7e: sprintf( opstr,"ror $%04x,X", nnnn ); break;
        case 0x7f: sprintf( opstr,"rra $%04x,X", nnnn ); break;
        case 0x80: sprintf( opstr,"nop #$%02x", nn ); break;
        case 0x81: sprintf( opstr,"sta ($%02x,X)", nn ); break;
        case 0x82: sprintf( opstr,"nop #$%02x", nn ); break;
        case 0x83: sprintf( opstr,"sax ($%02x,X)", nn ); break;
        case 0x84: sprintf( opstr,"sty $%02x", nn ); break;
        case 0x85: sprintf( opstr,"sta $%02x", nn ); break;
        case 0x86: sprintf( opstr,"stx $%02x", nn ); break;
        case 0x87: sprintf( opstr,"sax $%02x", nn ); break;
        case 0x88: strcpy( opstr,"dey" ); break;
        case 0x89: sprintf( opstr,"nop #$%02x", nn ); break;
        case 0x8a: strcpy( opstr,"txa" ); break;
        case 0x8b: sprintf( opstr,"xaa #$%02x", nn ); break;
        case 0x8c: sprintf( opstr,"sty $%04x", nnnn ); break;
        case 0x8d: sprintf( opstr,"sta $%04x", nnnn ); break;
        case 0x8e: sprintf( opstr,"stx $%04x", nnnn ); break;
        case 0x8f: sprintf( opstr,"sax $%04x", nnnn ); break;
        case 0x90: sprintf( opstr,"bcc $%04x", cpu->PC+(s8)nn+2 ); break;
        case 0x91: sprintf( opstr,"sta ($%02x),Y", nn ); break;
        case 0x92: strcpy( opstr,"kil" ); break;
        case 0x93: sprintf( opstr,"ahx ($%02x),Y", nn ); break;
        case 0x94: sprintf( opstr,"sty $%02x,X", nn ); break;
        case 0x95: sprintf( opstr,"sta $%02x,X", nn ); break;
        case 0x96: sprintf( opstr,"stx $%02x,Y", nn ); break;
        case 0x97: sprintf( opstr,"sax $%02x,Y", nn ); break;
        case 0x98: strcpy( opstr,"tya" ); break;
        case 0x99: sprintf( opstr,"sta $%04x,Y", nnnn ); break;
        case 0x9a: strcpy( opstr,"txs" ); break;
        case 0x9b: sprintf( opstr,"tas $%04x,Y", nnnn ); break;
        case 0x9c: sprintf( opstr,"shy $%04x,Y", nnnn ); break;
        case 0x9d: sprintf( opstr,"sta $%04x,X", nnnn ); break;
        case 0x9e: sprintf( opstr,"shx $%04x,Y", nnnn ); break;
        case 0x9f: sprintf( opstr,"ahx $%04x,Y", nnnn ); break; 
        case 0xa0: sprintf( opstr,"ldy #$%02x", nn ); break;
        case 0xa1: sprintf( opstr,"lda ($%02x,X)", nn ); break;
        case 0xa2: sprintf( opstr,"ldx #$%02x", nn ); break;
        case 0xa3: sprintf( opstr,"lax ($%02x,X)", nn ); break;
        case 0xa4: sprintf( opstr,"ldy $%02x", nn ); break;
        case 0xa5: sprintf( opstr,"lda $%02x", nn ); break;
        case 0xa6: sprintf( opstr,"ldx $%02x", nn ); break;
        case 0xa7: sprintf( opstr,"lax $%02x", nn ); break;
        case 0xa8: strcpy( opstr,"tay" ); break;
        case 0xa9: sprintf( opstr,"lda #$%02x", nn ); break;
        case 0xaa: strcpy( opstr,"tax" ); break;
        case 0xab: sprintf( opstr,"lax #$%02x", nn ); break;
        case 0xac: sprintf( opstr,"ldy $%04x", nnnn ); break;
        case 0xad: sprintf( opstr,"lda $%04x", nnnn ); break;
        case 0xae: sprintf( opstr,"ldx $%04x", nnnn ); break;
        case 0xaf: sprintf( opstr,"lax $%04x", nnnn ); break;
        case 0xb0: sprintf( opstr,"bcs $%04x", cpu->PC+(s8)nn+2 ); break;
        case 0xb1: sprintf( opstr,"lda ($%02x),Y", nn ); break;
        case 0xb2: strcpy( opstr,"kil" ); break;
        case 0xb3: sprintf( opstr,"lax ($%02x),Y", nn ); break;
        case 0xb4: sprintf( opstr,"ldy $%02x,X", nn ); break;
        case 0xb5: sprintf( opstr,"lda $%02x,X", nn ); break;
        case 0xb6: sprintf( opstr,"ldx $%02x,Y", nn ); break;
        case 0xb7: sprintf( opstr,"lax $%02x,Y", nn ); break;
        case 0xb8: strcpy( opstr,"clv" ); break;
        case 0xb9: sprintf( opstr,"lda $%04x,Y", nnnn ); break;
        case 0xba: strcpy( opstr,"tsx" ); break;
        case 0xbb: sprintf( opstr,"las $%04x,Y", nnnn ); break;
        case 0xbc: sprintf( opstr,"ldy $%04x,X", nnnn ); break;
        case 0xbd: sprintf( opstr,"lda $%04x,X", nnnn ); break;
        case 0xbe: sprintf( opstr,"ldx $%04x,Y", nnnn ); break;
        case 0xbf: sprintf( opstr,"lax $%04x,Y", nnnn ); break;
        case 0xc0: sprintf( opstr,"cpy #$%02x", nn ); break;
        case 0xc1: sprintf( opstr,"cmp ($%02x,X)", nn ); break;
        case 0xc2: sprintf( opstr,"nop #$%02x", nn ); break;
        case 0xc3: sprintf( opstr,"dcp ($%02x,X)", nn ); break;
        case 0xc4: sprintf( opstr,"cpy $%02x", nn );  break;
        case 0xc5: sprintf( opstr,"cmp $%02x", nn ); break;
        case 0xc6: sprintf( opstr,"dec $%02x", nn ); break;
        case 0xc7: sprintf( opstr,"dcp $%02x", nn ); break;
        case 0xc8: strcpy( opstr,"iny" ); break;
        case 0xc9: sprintf( opstr,"cmp #$%02x", nn ); break;
        case 0xca: strcpy( opstr,"dex" ); break;
        case 0xcb: sprintf( opstr,"axs #$%02x", nn ); break;
        case 0xcc: sprintf( opstr,"cpy $%04x", nnnn ); break;
        case 0xcd: sprintf( opstr,"cmp $%04x", nnnn ); break;
        case 0xce: sprintf( opstr,"dec $%04x", nnnn ); break;
        case 0xcf: sprintf( opstr,"dcp $%04x", nnnn ); break;
        case 0xd0: sprintf( opstr,"bne $%04x", cpu->PC+(s8)nn+2 ); break;
        case 0xd1: sprintf( opstr,"cmp ($%02x),Y", nn ); break;
        case 0xd2: strcpy( opstr,"kil" ); break;
        case 0xd3: sprintf( opstr,"dcp ($%02x),Y", nn ); break;
        case 0xd4: sprintf( opstr,"nop $%02x,X", nn ); break;
        case 0xd5: sprintf( opstr,"cmp $%02x,X", nn ); break;
        case 0xd6: sprintf( opstr,"dec $%02x,X", nn ); break;
        case 0xd7: sprintf( opstr,"dcp $%02x,X", nn ); break;
        case 0xd8: strcpy( opstr,"cld" ); break;
        case 0xd9: sprintf( opstr,"cmp $%04x,Y", nnnn ); break;
        case 0xda: strcpy( opstr,"nop" ); break;
        case 0xdb: sprintf( opstr,"dcp $%04x,Y", nnnn ); break;
        case 0xdc: sprintf( opstr,"nop $%04x,X", nnnn ); break;
        case 0xdd: sprintf( opstr,"cmp $%04x,X", nnnn ); break;
        case 0xde: sprintf( opstr,"dec $%04x,X", nnnn ); break;
        case 0xdf: sprintf( opstr,"dcp $%04x,X", nnnn ); break;
        case 0xe0: sprintf( opstr,"cpx #$%02x", nn ); break;
        case 0xe1: sprintf( opstr,"sbc ($%02x,X)", nn ); break;
        case 0xe2: sprintf( opstr,"nop #$%02x", nn ); break;
        case 0xe3: sprintf( opstr,"isb ($%02x,X)", nn ); break;
        case 0xe4: sprintf( opstr,"cpx $%02x", nn ); break;
        case 0xe5: sprintf( opstr,"sbc $%02x", nn ); break;
        case 0xe6: sprintf( opstr,"inc $%02x", nn ); break;
        case 0xe7: sprintf( opstr,"isb $%02x", nn ); break;
        case 0xe8: strcpy( opstr,"inx" ); break;
        case 0xe9: sprintf( opstr,"sbc #$%02x", nn ); break;
        case 0xea: strcpy( opstr,"nop" ); break;
        case 0xeb: sprintf( opstr,"sbc #$%02x", nn ); break;
        case 0xec: sprintf( opstr,"cpx $%04x", nnnn ); break;
        case 0xed: sprintf( opstr,"sbc $%04x", nnnn ); break;
        case 0xee: sprintf( opstr,"inc $%04x", nnnn ); break;
        case 0xef: sprintf( opstr,"isb $%04x", nnnn ); break;
        case 0xf0: sprintf( opstr,"beq $%04x", cpu->PC+(s8)nn+2 ); break;
        case 0xf1: sprintf( opstr,"sbc ($%02x),Y", nn ); break;
        case 0xf2: strcpy( opstr,"kil" ); break;
        case 0xf3: sprintf( opstr,"isb ($%02x),Y", nn ); break;
        case 0xf4: sprintf( opstr,"nop $%02x,X", nn ); break;
        case 0xf5: sprintf( opstr,"sbc $%02x,X", nn ); break;
        case 0xf6: sprintf( opstr,"inc $%02x,X", nn ); break;
        case 0xf7: sprintf( opstr,"isb $%02x,X", nn ); break;
        case 0xf8: strcpy( opstr,"sed" ); break;
        case 0xf9: sprintf( opstr,"sbc $%04x,Y", nnnn ); break;
        case 0xfa: strcpy( opstr,"nop" ); break;
        case 0xfb: sprintf( opstr,"isb $%04x,Y", nnnn ); break;
        case 0xfc: sprintf( opstr,"nop $%04x,X", nnnn ); break;
        case 0xfd: sprintf( opstr,"sbc $%04x,X", nnnn ); break;
        case 0xfe: sprintf( opstr,"inc $%04x,X", nnnn ); break;
        case 0xff: sprintf( opstr,"isb $%04x,X", nnnn ); break;
    }
    return op_l[op];
}

