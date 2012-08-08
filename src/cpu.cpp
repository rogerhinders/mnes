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
#include "cpu.h"
#include "tables.h"
CPU::CPU( MMU* mmu ) {
    this->mmu = mmu;

    A   = 0;
    X   = 0;
    Y   = 0;
    PC  = mmu->memRead16( RESET_VECTOR );
  //  PC=0xc000;
    S   = 0xFD;
    P.b = 0x24;
  //  printf("START:%x\n",PC);
}

void CPU::execInstr( u8 opcode ) {
    
    T = op_t[opcode];
    
    switch(opcode) {
        case 0x00: brk(); break;
        case 0x01: or_ind_x(); break;
        case 0x02: kil(); break;
        case 0x03: slo_ind_x(); break;
        case 0x04: nop(); break;
        case 0x05: or_zp(); break;
        case 0x06: asl_zp(); break;
        case 0x07: slo_zp(); break;
        case 0x08: php(); break;
        case 0x09: or_imm(); break;
        case 0x0a: asl(); break;
        case 0x0b: anc_imm(); break;
        case 0x0c: nop(); break;
        case 0x0d: or_abs(); break;
        case 0x0e: asl_abs(); break;
        case 0x0f: slo_abs(); break;
        case 0x10: bpl(); break;
        case 0x11: or_ind_y(); break;
        case 0x12: kil(); break;
        case 0x13: slo_ind_y(); break;
        case 0x14: nop(); break;
        case 0x15: or_zp_x(); break;
        case 0x16: asl_zp_x(); break;
        case 0x17: slo_zp_x(); break;
        case 0x18: clc(); break;
        case 0x19: or_abs_y(); break;
        case 0x1a: nop(); break;
        case 0x1b: slo_abs_y(); break;
        case 0x1c: nopX(); break;
        case 0x1d: or_abs_x(); break;
        case 0x1e: asl_abs_x(); break;
        case 0x1f: slo_abs_x(); break;
        case 0x20: jsr(); break;
        case 0x21: and_ind_x(); break;
        case 0x22: kil(); break;
        case 0x23: rla_ind_x(); break;
        case 0x24: bit_zp(); break;
        case 0x25: and_zp(); break;
        case 0x26: rol_zp(); break;
        case 0x27: rla_zp(); break;
        case 0x28: plp(); break;
        case 0x29: and_imm(); break;
        case 0x30: bmi(); break;
        case 0x32: kil(); break;
        case 0x33: rla_ind_y(); break;
        case 0x2a: rol(); break;
        case 0x2b: anc_imm2(); break;
        case 0x2c: bit_abs(); break;
        case 0x2d: and_abs(); break;
        case 0x2e: rol_abs(); break;
        case 0x2f: rla_abs(); break;
        case 0x31: and_ind_y(); break;
        case 0x34: nop(); break;
        case 0x35: and_zp_x(); break;
        case 0x36: rol_zp_x(); break;
        case 0x37: rla_zp_x(); break;
        case 0x38: sec(); break;
        case 0x39: and_abs_y(); break;
        case 0x3a: nop(); break;
        case 0x3b: rla_abs_y(); break;
        case 0x3c: nopX(); break;
        case 0x3d: and_abs_x(); break;
        case 0x3e: rol_abs_x(); break;
        case 0x3f: rla_abs_x(); break;
        case 0x40: rti(); break;
        case 0x41: xor_ind_x(); break;
        case 0x42: kil(); break;
        case 0x43: sre_ind_x(); break;
        case 0x44: nop(); break;
        case 0x45: xor_zp(); break;
        case 0x46: lsr_zp(); break;
        case 0x47: sre_zp(); break;
        case 0x48: pha(); break;
        case 0x49: xor_imm(); break;
        case 0x4a: lsr(); break;
        case 0x4b: alr_imm(); break;
        case 0x4c: jmp_abs(); break;
        case 0x4d: xor_abs(); break;
        case 0x4e: lsr_abs(); break;
        case 0x4f: sre_abs(); break;
        case 0x50: bvc(); break;
        case 0x51: xor_ind_y(); break;
        case 0x52: kil(); break;
        case 0x53: sre_ind_y(); break;
        case 0x54: nop(); break;
        case 0x55: xor_zp_x(); break;
        case 0x56: lsr_zp_x(); break;
        case 0x57: sre_zp_x(); break;
        case 0x58: cli(); break;
        case 0x59: xor_abs_y(); break;
        case 0x5a: nop(); break;
        case 0x5b: sre_abs_y(); break;
        case 0x5c: nopX(); break;
        case 0x5d: xor_abs_x(); break;
        case 0x5e: lsr_abs_x(); break;
        case 0x5f: sre_abs_x(); break;
        case 0x60: rts(); break;
        case 0x61: adc_ind_x(); break;
        case 0x62: kil(); break;
        case 0x63: rra_ind_x(); break;
        case 0x64: nop(); break;
        case 0x65: adc_zp(); break;
        case 0x66: ror_zp(); break;
        case 0x67: rra_zp(); break;
        case 0x68: pla(); break;
        case 0x69: adc_imm(); break;
        case 0x6a: ror(); break;
        case 0x6b: arr_imm(); break;
        case 0x6c: jmp_ind(); break;
        case 0x6d: adc_abs(); break;
        case 0x6e: ror_abs(); break;
        case 0x6f: rra_abs(); break;
        case 0x70: bvs(); break;
        case 0x71: adc_ind_y(); break;
        case 0x72: kil(); break;
        case 0x73: rra_ind_y(); break;
        case 0x74: nop(); break;
        case 0x75: adc_zp_x(); break;
        case 0x76: ror_zp_x(); break;
        case 0x77: rra_zp_x(); break;
        case 0x78: sei(); break;
        case 0x79: adc_abs_y(); break;
        case 0x7a: nop(); break;
        case 0x7b: rra_abs_y(); break;
        case 0x7c: nopX(); break;
        case 0x7d: adc_abs_x(); break;
        case 0x7e: ror_abs_x(); break;
        case 0x7f: rra_abs_x(); break;
        case 0x80: nop(); break;
        case 0x81: sta_ind_x(); break;
        case 0x82: nop(); break;
        case 0x83: sax_ind_x();  break;
        case 0x84: sty_zp(); break;
        case 0x85: sta_zp(); break;
        case 0x86: stx_zp(); break;
        case 0x87: sax_zp(); break;
        case 0x88: dey(); break;
        case 0x89: nop(); break;
        case 0x8a: txa(); break;
        case 0x8b: xaa_imm(); break;
        case 0x8c: sty_abs(); break;
        case 0x8d: sta_abs(); break;
        case 0x8e: stx_abs(); break;
        case 0x8f: sax_abs(); break;
        case 0x90: bcc(); break;
        case 0x91: sta_ind_y(); break;
        case 0x92: kil(); break;
        case 0x94: sty_zp_x(); break;
        case 0x95: sta_zp_x(); break;
        case 0x96: stx_zp_y(); break;
        case 0x97: sax_zp_y(); break;
        case 0x98: tya(); break;
        case 0x99: sta_abs_y(); break;
        case 0x9a: txs(); break;
        case 0x9c: shy(); break;
        case 0x9d: sta_abs_x(); break;
        case 0x9e: shx(); break;
        case 0xa0: ldy_imm(); break;
        case 0xa1: lda_ind_x(); break;
        case 0xa2: ldx_imm(); break;
        case 0xa3: lax_ind_x(); break;
        case 0xa4: ldy_zp(); break;
        case 0xa5: lda_zp(); break;
        case 0xa6: ldx_zp(); break;
        case 0xa7: lax_zp(); break;
        case 0xa8: tay(); break;
        case 0xa9: lda_imm(); break;
        case 0xaa: tax(); break;
        case 0xab: lax_imm(); break;
        case 0xac: ldy_abs(); break;
        case 0xad: lda_abs(); break;
        case 0xae: ldx_abs(); break;
        case 0xaf: lax_abs(); break;
        case 0xb0: bcs(); break;
        case 0xb1: lda_ind_y(); break;
        case 0xb2: kil(); break;
        case 0xb3: lax_ind_y(); break;
        case 0xb4: ldy_zp_x(); break;
        case 0xb5: lda_zp_x(); break;
        case 0xb6: ldx_zp_y(); break;
        case 0xb7: lax_zp_y(); break;
        case 0xb8: clv(); break;
        case 0xb9: lda_abs_y(); break;
        case 0xba: tsx(); break;
        case 0xbc: ldy_abs_x(); break;
        case 0xbd: lda_abs_x(); break;
        case 0xbe: ldx_abs_y(); break;
        case 0xbf: lax_abs_y(); break;
        case 0xc0: cpy_imm(); break;
        case 0xc1: cmp_a_ind_x(); break;
        case 0xc2: nop(); break;
        case 0xc3: dcp_ind_x(); break;
        case 0xc4: cpy_zp(); break;
        case 0xc5: cmp_a_zp(); break;
        case 0xc6: dec_zp(); break;
        case 0xc7: dcp_zp(); break;
        case 0xc8: iny(); break;
        case 0xc9: cmp_a_imm(); break;
        case 0xca: dex(); break;
        case 0xcb: axs_imm(); break;
        case 0xcc: cpy_abs(); break;
        case 0xcd: cmp_a_abs(); break;
        case 0xce: dec_abs(); break;
        case 0xcf: dcp_abs(); break;
        case 0xd0: bne(); break;
        case 0xd1: cmp_a_ind_y(); break;
        case 0xd2: kil(); break;
        case 0xd3: dcp_ind_y(); break;
        case 0xd4: nop(); break;
        case 0xd5: cmp_a_zp_x(); break;
        case 0xd6: dec_zp_x(); break;
        case 0xd7: dcp_zp_x(); break;
        case 0xd8: cld(); break;
        case 0xd9: cmp_a_abs_y(); break;
        case 0xda: nop(); break;
        case 0xdb: dcp_abs_y(); break;
        case 0xdc: nopX(); break;
        case 0xdd: cmp_a_abs_x(); break;
        case 0xde: dec_abs_x(); break;
        case 0xdf: dcp_abs_x(); break;
        case 0xe0: cpx_imm(); break;
        case 0xe1: sbc_ind_x(); break;
        case 0xe2: nop(); break;
        case 0xe3: isb_ind_x(); break;
        case 0xe4: cpx_zp(); break;
        case 0xe5: sbc_zp(); break;
        case 0xe6: inc_zp(); break;
        case 0xe7: isb_zp(); break;
        case 0xe8: inx(); break;
        case 0xe9: sbc_imm(); break;
        case 0xea: nop(); break;
        case 0xeb: sbc_imm2(); break;
        case 0xec: cpx_abs(); break;
        case 0xed: sbc_abs(); break;
        case 0xee: inc_abs(); break;
        case 0xef: isb_abs(); break;
        case 0xf0: beq(); break;
        case 0xf1: sbc_ind_y(); break;
        case 0xf2: kil(); break;
        case 0xf3: isb_ind_y(); break;
        case 0xf4: nop(); break;
        case 0xf5: sbc_zp_x(); break;
        case 0xf6: inc_zp_x(); break;
        case 0xf7: isb_zp_x(); break;
        case 0xf8: sed(); break;
        case 0xf9: sbc_abs_y(); break;
        case 0xfa: nop(); break;
        case 0xfb: isb_abs_y(); break;
        case 0xfc: nopX(); break;
        case 0xfd: sbc_abs_x(); break;
        case 0xfe: inc_abs_x(); break;
        case 0xff: isb_abs_x(); break;
    }
    // dont add to pc if it was a branch/jmp
    if(opcode==0x10 || //bpl
       opcode==0x30 || //bmi
       opcode==0x50 || //bvc
       opcode==0x70 || //bvs
       opcode==0x90 || //bcc
       opcode==0xb0 || //bcs
       opcode==0xd0 || //bne
       opcode==0xf0 || //beq
       opcode==0x4c || //jsr
       opcode==0x20 || //jmp_abs
       opcode==0x6c || //jmp_ind
       opcode==0x00 || //brk
       opcode==0x60 || //rts
       opcode==0x40    //rti
    )
        return;
    
    PC += op_l[opcode];
}

void CPU::execNMI() {
    push( PC >> 8 );
    push( PC );
    P.f.b = 1;
    push( P.b | 0x30 );
    PC = mmu->memRead16( NMI_VECTOR );
    P.f.i = 1;
}

u16 CPU::getIndirect() {
   tmp16 = mmu->memRead16( PC+1 );
   tmp8 = mmu->memRead8( tmp16 );
   tmp16 = ( tmp16 & 0xff00 ) | ( ( tmp16 + 1 ) & 0xff  );
   return ( mmu->memRead8( tmp16 ) << 8 ) | tmp8;
}

u16 CPU::getIndirectX() {
    tmp8 = ( mmu->memRead8( PC+1 ) + X ) & 0xff;
    return ( mmu->memRead8( ( tmp8+1 ) & 0xff ) << 8 ) | mmu->memRead8( tmp8 ) ;
}

u16 CPU::getIndirectY() {
    tmp8 = mmu->memRead8( PC+1 );
    u16 addr = ( ( mmu->memRead8( ( tmp8+1 ) & 0xff ) << 8 ) | mmu->memRead8( tmp8 ) );
    
    if( ( addr & 0xff00 ) != ( ( addr + Y ) & 0xff00 ) )
        T += 1;
    
    return  addr + Y;
}

u16 CPU::getAbsoluteX() {
    addr = mmu->memRead16( PC + 1 );
    newAddr = ( addr + X ) & 0xffff;
    
    if( ( addr & 0xff00 ) != ( newAddr & 0xff00 ) )
        T += 1;
        
    return newAddr;
}

u16 CPU::getAbsoluteY() {
    addr = mmu->memRead16( PC + 1 );
    newAddr = ( addr + Y ) & 0xffff;
    
    if( ( addr & 0xff00 ) != ( newAddr & 0xff00 ) )
        T += 1;
    
    return newAddr;
}


void CPU::push(u8 val) {
    //printf("PUSH: %x\n",val);
    mmu->memWrite8( 0x100 | S, val );
    S--;
}
u8 CPU::pop() {
    S++;
    //printf("POP: %x(%x) SP:%x\n",mmu->memRead8( 0x100 & S ),0x100&S,S);
    return mmu->memRead8( 0x100 | S );
}

void CPU::txa() {
    A = X;
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::tya() {
    A = Y;
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::txs() {
    S = X;
}

void CPU::tay() {
    Y = A;
    P.f.n = Y>>7;
    P.f.z = Y==0;
}

void CPU::tax() {
    X = A;
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::tsx() {
    X = S;
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::lda_imm() {
    A = mmu->memRead8( PC+1 );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::lda_zp() {
    A = mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::lda_zp_x() {
    A = mmu->memRead8( ( mmu->memRead8( PC+1 ) + X ) & 0xff );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::lda_abs() {
    A = mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::lda_abs_x() {
    A = mmu->memRead8( getAbsoluteX() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::lda_abs_y() {
    A = mmu->memRead8( getAbsoluteY() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::lda_ind_x() {
    A = mmu->memRead8( getIndirectX() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::lda_ind_y() {
    A = mmu->memRead8( getIndirectY() );
   // if(PC==0xd959) printf("%x\n",A);
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::ldx_imm() {
    X = mmu->memRead8( PC+1 );
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::ldx_zp() {
    X = mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::ldx_zp_y() {
    X = mmu->memRead8( ( mmu->memRead8( PC+1 ) + Y ) & 0xff );
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::ldx_abs() {
    X = mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::ldx_abs_y() {
    X = mmu->memRead8( getAbsoluteY() );
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::ldy_imm() {
    Y = mmu->memRead8( PC+1 );
    P.f.n = Y>>7;
    P.f.z = Y==0;
}

void CPU::ldy_zp() {
    Y = mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = Y>>7;
    P.f.z = Y==0;
}

void CPU::ldy_zp_x() {
    Y = mmu->memRead8( ( mmu->memRead8( PC+1 ) + X ) & 0xff );
    P.f.n = Y>>7;
    P.f.z = Y==0;
}

void CPU::ldy_abs() {
    Y = mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = Y>>7;
    P.f.z = Y==0;
}

void CPU::ldy_abs_x() {
    Y = mmu->memRead8( getAbsoluteX() );
    P.f.n = Y>>7;
    P.f.z = Y==0;
}

void CPU::sta_zp() {
    mmu->memWrite8( mmu->memRead8( PC+1 ), A );
}

void CPU::sta_zp_x() {
    mmu->memWrite8( ( mmu->memRead8( PC+1 ) + X ) & 0xff, A );
}

void CPU::sta_abs() {
    mmu->memWrite8( mmu->memRead16( PC+1 ), A );
}

void CPU::sta_abs_x() {
    mmu->memWrite8( ( mmu->memRead16( PC+1 ) + X ) & 0xffff, A );
}

void CPU::sta_abs_y() {
    mmu->memWrite8( ( mmu->memRead16( PC+1 ) + Y ) & 0xffff, A );
}

void CPU::sta_ind_x() {
    mmu->memWrite8( getIndirectX(), A );
}

void CPU::sta_ind_y() {
    mmu->memWrite8( getIndirectY(), A );
}

void CPU::stx_zp() {
    mmu->memWrite8( mmu->memRead8( PC+1 ), X );
}

void CPU::stx_zp_y() {
    mmu->memWrite8( ( mmu->memRead8( PC+1 ) + Y ) & 0xff, X );
}

void CPU::stx_abs() {
    mmu->memWrite8( mmu->memRead16( PC+1 ), X );
}

void CPU::sty_zp() {
    mmu->memWrite8( mmu->memRead8( PC+1 ), Y );
}

void CPU::sty_zp_x() {
    mmu->memWrite8( ( mmu->memRead8( PC+1 ) + X ) & 0xff, Y );
}

void CPU::sty_abs() {
    mmu->memWrite8( mmu->memRead16( PC+1 ), Y );
}

void CPU::pha() {
    push(A);
}

void CPU::php() {
    push( P.b | 0x30 );
}

void CPU::pla() {
   // for(int i=0x17a;i<0x18a;i++) {
    //    printf("S: %x: %x\n",i, mmu->memRead8(i));
   // }
    A = pop();
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::plp() {
    P.b = ( pop() | 0x20 ) & 0xef;
}

void CPU::adc_imm() {
    prev = A;
    tmp8 = mmu->memRead8( PC+1 );
    tmp16 = A + P.f.c + tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16>0xff;
    P.f.v = !((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::adc_zp() {
    prev = A;
    tmp8 = mmu->memRead8( mmu->memRead8( PC+1 ) );
    tmp16 = A + P.f.c + tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16>0xff;
    P.f.v = !((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::adc_zp_x() {
    prev = A;
    tmp8 = mmu->memRead8( ( mmu->memRead8( PC+1 ) + X ) & 0xFF );
    tmp16 = A + P.f.c + tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16>0xff;
    P.f.v = !((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::adc_abs() {
    prev = A;
    tmp8 = mmu->memRead8( mmu->memRead16( PC+1 ) );
    tmp16 = A + P.f.c + tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16>0xff;
    P.f.v = !((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::adc_abs_x() {
    prev = A;
    tmp8 = mmu->memRead8( getAbsoluteX() );
    tmp16 = A + P.f.c + tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16>0xff;
    P.f.v = !((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::adc_abs_y() {
    prev = A;
    tmp8 = mmu->memRead8( getAbsoluteY() );
    tmp16 = A + P.f.c + tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16>0xff;
    P.f.v = !((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::adc_ind_x() {
    prev = A;
    tmp8 = mmu->memRead8( getIndirectX() );
    tmp16 = A + P.f.c + tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16>0xff;
    P.f.v = !((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::adc_ind_y() {
    prev = A;
    tmp8 = mmu->memRead8( getIndirectY() );
    tmp16 = A + P.f.c + tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16>0xff;
    P.f.v = !((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}
/*
void CPU::sbc_imm() {
    prev = A;
    tmp8 = mmu->memRead8( PC+1 );
    A = A + P.f.c - 1 - tmp8;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = A<=prev;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}*/
void CPU::sbc_imm() {
    prev = A;
    tmp8 = mmu->memRead8( PC+1 );
    tmp16 = A + P.f.c - 1 - tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16<0x100;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::sbc_zp() {
    prev = A;
    tmp8 = mmu->memRead8( mmu->memRead8( PC+1 ) );
    tmp16 = A + P.f.c - 1 - tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16<0x100;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::sbc_zp_x() {
    prev = A;
    tmp8 = mmu->memRead8( ( mmu->memRead8( PC+1 ) + X ) & 0xFF );
    tmp16 = A + P.f.c - 1 - tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16<0x100;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::sbc_abs() {
    prev = A;
    tmp8 = mmu->memRead8( mmu->memRead16( PC+1 ) );
    tmp16 = A + P.f.c - 1 - tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16<0x100;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::sbc_abs_x() {
    prev = A;
    tmp8 = mmu->memRead8( getAbsoluteX() );
    tmp16 = A + P.f.c - 1 - tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16<0x100;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::sbc_abs_y() {
    prev = A;
    tmp8 = mmu->memRead8( getAbsoluteY() );
    tmp16 = A + P.f.c - 1 - tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16<0x100;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::sbc_ind_x() {
    prev = A;
    tmp8 = mmu->memRead8( getIndirectX() );
    tmp16 = A + P.f.c - 1- tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16<0x100;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::sbc_ind_y() {
    prev = A;
    tmp8 = mmu->memRead8( getIndirectY() );
    tmp16 = A + P.f.c - 1 - tmp8;
    A = tmp16;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = tmp16<0x100;
    P.f.v = ((prev ^ tmp8) & 0x80) && ((prev ^ A) & 0x80);
}

void CPU::and_imm() {
    A &= mmu->memRead8( PC+1 );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::and_zp() {
    A &= mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::and_zp_x() {
    A &= mmu->memRead8( ( mmu->memRead8( PC+1 ) + X ) & 0xFF );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::and_abs() {
    A &= mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::and_abs_x() {
    A &= mmu->memRead8( getAbsoluteX() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::and_abs_y() {
    A &= mmu->memRead8( getAbsoluteY() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::and_ind_x() {
    A &= mmu->memRead8( getIndirectX() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::and_ind_y() {
    A &= mmu->memRead8( getIndirectY() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::xor_imm() {
    A ^= mmu->memRead8( PC+1 );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::xor_zp() {
    A ^= mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::xor_zp_x() {
    A ^= mmu->memRead8( ( mmu->memRead8( PC+1 ) + X ) & 0xFF );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::xor_abs() {
    A ^= mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::xor_abs_x() {
    A ^= mmu->memRead8( getAbsoluteX() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::xor_abs_y() {
    A ^= mmu->memRead8( getAbsoluteY() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::xor_ind_x() {
    A ^= mmu->memRead8( getIndirectX() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::xor_ind_y() {
    A ^= mmu->memRead8( getIndirectY() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::or_imm() {
    A |= mmu->memRead8( PC+1 );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::or_zp() {
    A |= mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::or_zp_x() {
    A |= mmu->memRead8( ( mmu->memRead8( PC+1 ) + X ) & 0xFF );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::or_abs() {
    A |= mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::or_abs_x() {
    A |= mmu->memRead8( getAbsoluteX() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::or_abs_y() {
    A |= mmu->memRead8( getAbsoluteY() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::or_ind_x() {
    A |= mmu->memRead8( getIndirectX() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::or_ind_y() {
    A |= mmu->memRead8( getIndirectY() );
    P.f.n = A>>7;
    P.f.z = A==0;
}

void CPU::cmp_a_imm() {
    tmp8 = A - mmu->memRead8( PC+1 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=A;
}

void CPU::cmp_a_zp() {
    tmp8 = A -mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=A;
}

void CPU::cmp_a_zp_x() {
    tmp8 = A - mmu->memRead8( ( mmu->memRead8( PC+1 ) + X ) & 0xFF );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=A;
}

void CPU::cmp_a_abs() {
    tmp8 = A - mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=A;
}

void CPU::cmp_a_abs_x() {
    tmp8 = A - mmu->memRead8( getAbsoluteX() );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=A;
}

void CPU::cmp_a_abs_y() {
    tmp8 = A - mmu->memRead8( getAbsoluteY() );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=A;
}

void CPU::cmp_a_ind_x() {
    tmp8 = A - mmu->memRead8( getIndirectX() );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=A;
}

void CPU::cmp_a_ind_y() {
    tmp8 = A - mmu->memRead8( getIndirectY() );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=A;
}

void CPU::cpx_imm() {

    tmp8 = X - mmu->memRead8( PC+1 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=X;
}

void CPU::cpx_zp() {
    tmp8 = X - mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=X;
}

void CPU::cpx_abs() {
    tmp8 = X - mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=X;
}

void CPU::cpy_imm() {
    tmp8 = Y - mmu->memRead8( PC+1 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=Y;
}

void CPU::cpy_zp() {
    tmp8 = Y - mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=Y;
}

void CPU::cpy_abs() {
    tmp8 = Y - mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = tmp8<=Y;
}

void CPU::bit_zp() {
    tmp8 = mmu->memRead8( mmu->memRead8( PC+1 ) );
    P.f.z = (A & tmp8)==0;
    P.f.v = tmp8 >> 6;
    P.f.n = tmp8 >> 7;
}

void CPU::bit_abs() {
    tmp8 = mmu->memRead8( mmu->memRead16( PC+1 ) );
    P.f.z = (A & tmp8)==0;
    P.f.v = tmp8 >> 6;
    P.f.n = tmp8 >> 7;
}

void CPU::inc_ind_x() {
    addr = getIndirectX();
    tmp8 = mmu->memRead8( addr ) + 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::inc_ind_y() {
    addr = getIndirectY();
    tmp8 = mmu->memRead8( addr ) + 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::inc_zp() {
    addr = mmu->memRead8( PC+1 );
    tmp8 = mmu->memRead8( addr ) + 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::inc_zp_x() {
    addr = ( mmu->memRead8( PC+1 ) + X ) & 0xff;
    tmp8 = mmu->memRead8( addr ) + 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::inc_abs() {
    addr = mmu->memRead16( PC+1 );
    tmp8 = mmu->memRead8( addr ) + 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::inc_abs_x() {
    addr = mmu->memRead16( PC+1 ) + X;
    tmp8 = mmu->memRead8( addr ) + 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::inc_abs_y() {
    addr = mmu->memRead16( PC+1 ) + Y;
    tmp8 = mmu->memRead8( addr ) + 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::inx() {
    X++;
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::iny() {
    Y++;
    P.f.n = Y>>7;
    P.f.z = Y==0;
}

void CPU::dec_ind_x() {
    addr = getIndirectX();
    tmp8 = mmu->memRead8( addr ) - 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::dec_ind_y() {
    addr = getIndirectY();
    tmp8 = mmu->memRead8( addr ) - 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::dec_zp() {
    addr = mmu->memRead8( PC+1 );
    tmp8 = mmu->memRead8( addr ) - 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::dec_zp_x() {
    addr = ( mmu->memRead8( PC+1 ) + X ) & 0xff;
    tmp8 = mmu->memRead8( addr ) - 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::dec_abs() {
    addr = mmu->memRead16( PC+1 );
    tmp8 = mmu->memRead8( addr ) - 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::dec_abs_x() {
    addr = mmu->memRead16( PC+1 ) + X;
    tmp8 = mmu->memRead8( addr ) - 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::dec_abs_y() {
    addr = mmu->memRead16( PC+1 ) + Y;
    tmp8 = mmu->memRead8( addr ) - 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
}

void CPU::dex() {
    X--;
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::dey() {
    Y--;
    P.f.n = Y>>7;
    P.f.z = Y==0;
}

void CPU::asl() {
    prev = A;
    A <<= 1;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = prev>>7;
}

void CPU::asl_zp() {
    addr = mmu->memRead8( PC+1 );
    prev = mmu->memRead8( addr );
    tmp8 = prev << 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::asl_ind_x() {
    addr = getIndirectX();
    prev = mmu->memRead8( addr );
    tmp8 = prev << 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::asl_ind_y() {
    addr = getIndirectY();
    prev = mmu->memRead8( addr );
    tmp8 = prev << 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::asl_zp_x() {
    addr = ( mmu->memRead8( PC+1 ) + X ) & 0xff;
    prev = mmu->memRead8( addr );
    tmp8 = prev << 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::asl_abs() {
    addr = mmu->memRead16( PC+1 );
    prev = mmu->memRead8( addr );
    tmp8 = prev << 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::asl_abs_x() {
    addr = mmu->memRead16( PC+1 ) + X;
    prev = mmu->memRead8( addr );
    tmp8 = prev << 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::asl_abs_y() {
    addr = mmu->memRead16( PC+1 ) + Y;
    prev = mmu->memRead8( addr );
    tmp8 = prev << 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::lsr() {
    prev = A;
    A >>= 1;
    P.f.n = 0;
    P.f.z = A==0;
    P.f.c = prev&1;
}

void CPU::lsr_ind_x() {
    addr = getIndirectX();
    prev = mmu->memRead8( addr );
    tmp8 = prev >> 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = 0;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::lsr_ind_y() {
    addr = getIndirectY();
    prev = mmu->memRead8( addr );
    tmp8 = prev >> 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = 0;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::lsr_zp() {
    addr = mmu->memRead8( PC+1 );
    prev = mmu->memRead8( addr );
    tmp8 = prev >> 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = 0;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::lsr_zp_x() {
    addr = ( mmu->memRead8( PC+1 ) + X ) & 0xff;
    prev = mmu->memRead8( addr );
    tmp8 = prev >> 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = 0;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::lsr_abs() {
    addr = mmu->memRead16( PC+1 );
    prev = mmu->memRead8( addr );
    tmp8 = prev >> 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = 0;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::lsr_abs_x() {
    addr = mmu->memRead16( PC+1 ) + X;
    prev = mmu->memRead8( addr );
    tmp8 = prev >> 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = 0;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::lsr_abs_y() {
    addr = mmu->memRead16( PC+1 ) + Y;
    prev = mmu->memRead8( addr );
    tmp8 = prev >> 1;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = 0;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::rol() {
    prev = A;
    A = ( ( A << 1 ) & 0xfe ) | P.f.c;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = prev>>7;
}

void CPU::rol_ind_x() {
    addr = getIndirectX();
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev << 1) & 0xfe ) | P.f.c;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::rol_ind_y() {
    addr = getIndirectY();
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev << 1) & 0xfe ) | P.f.c;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::rol_zp() {
    addr = mmu->memRead8( PC+1 );
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev << 1) & 0xfe ) | P.f.c;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::rol_zp_x() {
    addr = ( mmu->memRead8( PC+1 ) + X ) & 0xff;
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev << 1) & 0xfe ) | P.f.c;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::rol_abs() {
    addr = mmu->memRead16( PC+1 );
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev << 1) & 0xfe ) | P.f.c;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::rol_abs_x() {
    addr = mmu->memRead16( PC+1 ) + X;
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev << 1) & 0xfe ) | P.f.c;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::rol_abs_y() {
    addr = mmu->memRead16( PC+1 ) + Y;
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev << 1) & 0xfe ) | P.f.c;
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev>>7;
}

void CPU::ror() {
    prev = A;
    A = ( ( A >> 1 ) & 0x7f ) | ( P.f.c << 7 );
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = prev&1;
}

void CPU::ror_ind_x() {
    addr = getIndirectX();
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev >> 1) & 0x7f ) | ( P.f.c << 7 );
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::ror_ind_y() {
    addr = getIndirectY();
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev >> 1) & 0x7f ) | ( P.f.c << 7 );
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::ror_zp() {
    addr = mmu->memRead8( PC+1 );
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev >> 1) & 0x7f ) | ( P.f.c << 7 );
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::ror_zp_x() {
    addr = ( mmu->memRead8( PC+1 ) + X ) & 0xff;
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev >> 1) & 0x7f ) | ( P.f.c << 7 );
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::ror_abs() {
    addr = mmu->memRead16( PC+1 );
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev >> 1) & 0x7f ) | ( P.f.c << 7 );
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::ror_abs_x() {
    addr = mmu->memRead16( PC+1 ) + X;
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev >> 1) & 0x7f ) | ( P.f.c << 7 );
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

void CPU::ror_abs_y() {
    addr = mmu->memRead16( PC+1 ) + Y;
    prev = mmu->memRead8( addr );
    tmp8 = ( ( prev >> 1) & 0x7f ) | ( P.f.c << 7 );
    mmu->memWrite8( addr, tmp8 );
    P.f.n = tmp8>>7;
    P.f.z = tmp8==0;
    P.f.c = prev&1;
}

/*
 * 
 * NOTE TO SELF: DO NOT UPDATE PC IN MAIN LOOP!
 * 
 */
void CPU::jmp_abs() {
    PC = mmu->memRead16( PC+1 );
}

void CPU::jmp_ind() {
    PC = getIndirect();
}

void CPU::jsr() {
    push( ( PC+2 ) >> 8 );
    push( ( PC+2 ) & 0xff );
   // printf("derpaherr %x\n",PC);
    PC = mmu->memRead16( PC+1 );
}

void CPU::rti() {
    P.b = pop() | 0x20;
    PC = pop();
    PC = PC | ( pop() << 8 );
}

void CPU::rts() {

    PC = ( pop() | ( pop() << 8 ) ) + 1;
}

void CPU::bpl() {
    u8 tmp8 = mmu->memRead8( PC+1 );
    PC += 2;
    if(!P.f.n) {
        addr = (s16)PC + (s8)tmp8;
        if( ( addr & 0xff00 ) != ( ( PC ) & 0xFF00 ) )
            T += 2;
        else 
            T += 1;
        PC = addr;
    }
}

void CPU::bmi() {
    u8 tmp8 = mmu->memRead8( PC+1 );
    PC += 2;
    if(P.f.n) {
        addr = (s16)PC + (s8)tmp8;
        if( ( addr & 0xff00 ) != ( ( PC ) & 0xFF00 ) )
            T += 2;
        else 
            T += 1;
        PC = addr;
    }
}

void CPU::bvc() {
    u8 tmp8 = mmu->memRead8( PC+1 );
    PC += 2;
    if(!P.f.v) {
        addr = (s16)PC + (s8)tmp8;
        if( ( addr & 0xff00 ) != ( ( PC ) & 0xFF00 ) )
            T += 2;
        else 
            T += 1;
        PC = addr;
    }
}

void CPU::bvs() {
    u8 tmp8 = mmu->memRead8( PC+1 );
    PC += 2;
    if(P.f.v) {
        addr = (s16)PC + (s8)tmp8;
        if( ( addr & 0xff00 ) != ( ( PC ) & 0xFF00 ) )
            T += 2;
        else 
            T += 1;
        PC = addr;
    }
}

void CPU::bcc() {
    u8 tmp8 = mmu->memRead8( PC+1 );
    PC += 2;
    if(!P.f.c) {
        addr = (s16)PC + (s8)tmp8;
        if( ( addr & 0xff00 ) != ( ( PC ) & 0xFF00 ) )
            T += 2;
        else 
            T += 1;
        PC = addr;
    }
}

void CPU::bcs() {
    u8 tmp8 = mmu->memRead8( PC+1 );
    PC += 2;
    if(P.f.c) {
        addr = (s16)PC + (s8)tmp8;
        if( ( addr & 0xff00 ) != ( ( PC ) & 0xFF00 ) )
            T += 2;
        else 
            T += 1;
        PC = addr;
    }
}

void CPU::bne() {
    u8 tmp8 = mmu->memRead8( PC+1 );
    PC += 2;
    if(!P.f.z) {
        addr = (s16)PC + (s8)tmp8;
        if( ( addr & 0xff00 ) != ( ( PC ) & 0xFF00 ) )
            T += 2;
        else 
            T += 1;
        PC = addr;
    }
}

void CPU::beq() {
    u8 tmp8 = mmu->memRead8( PC+1 );
    PC += 2;
    if(P.f.z) {
        addr = (s16)PC + (s8)tmp8;
        if( ( addr & 0xff00 ) != ( ( PC ) & 0xFF00 ) )
            T += 2;
        else 
            T += 1;
        PC = addr;
    }
}

void CPU::brk() {
    PC+=2;
    push( PC >> 8 );
    push( PC );
    P.f.b = 1;
    push( P.b | 0x30 );
    PC = mmu->memRead16(IRQ_VECTOR);
    P.f.i = 1;
}

void CPU::clc() {
    P.f.c = 0;
}

void CPU::cli() {
    P.f.i = 0;
}

void CPU::cld() {
    P.f.d = 0;
}

void CPU::clv() {
    P.f.v = 0;
}

void CPU::sec() {
    P.f.c = 1;
}

void CPU::sei() {
    P.f.i = 1;
}

void CPU::sed() {
    P.f.d = 1;
}

void CPU::nop() {
    
}

void CPU::nopX() {
    getAbsoluteX();
}

void CPU::kil() {
    PC--; //negate pc inc to halt cpu
}

void CPU::sax_zp() {
    mmu->memWrite8( mmu->memRead8( PC+1 ), A & X);
}

void CPU::sax_zp_y() {
    mmu->memWrite8( ( mmu->memRead8( PC+1 ) + Y ) & 0xff, A & X);
}

void CPU::sax_abs() {
    mmu->memWrite8( mmu->memRead16( PC+1 ), A & X);
}

void CPU::sax_ind_x() {
    mmu->memWrite8( getIndirectX(), A & X);
}

void CPU::lax_zp() {
    lda_zp();
    ldx_zp();
}

void CPU::lax_zp_y() {
    A = mmu->memRead8( ( mmu->memRead8( PC+1 ) + Y ) & 0xff );
    ldx_zp_y();
}

void CPU::lax_abs() {
    lda_abs();
    ldx_abs();
}

void CPU::lax_abs_y() {
    //lda_abs_x();
    A = mmu->memRead8( ( mmu->memRead16( PC+1 ) + Y ) & 0xffff );
    X = mmu->memRead8( ( mmu->memRead16( PC+1 ) + Y ) & 0xffff );
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::lax_ind_x() {
    lda_ind_x();
    X = mmu->memRead8( getIndirectX() );
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::lax_ind_y() {
    lda_ind_y();
    T = 5;
    X = mmu->memRead8( getIndirectY() );
    P.f.n = X>>7;
    P.f.z = X==0;
}

void CPU::slo_zp() {
   /* prev 
    A = ( mmu->memRead8( PC+1 ) << 1;
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = prev>>7;*/
   asl_zp();
   or_zp();
}

void CPU::slo_zp_x() {
    asl_zp_x();
    or_zp_x();
}

void CPU::slo_ind_x() {
   asl_ind_x();
   or_ind_x();
}

void CPU::slo_ind_y() {
    asl_ind_y();
    or_ind_y();
    T = 8;
}

void CPU::slo_abs() {
    asl_abs();
    or_abs();
}

void CPU::slo_abs_x() {
    asl_abs_x();
    or_abs_x();
    T = 7;
}

void CPU::slo_abs_y() {
    asl_abs_y();
    or_abs_y();
    T = 7;
}

void CPU::rla_zp() {
    rol_zp();
    and_zp();
}

void CPU::rla_zp_x() {
    rol_zp_x();
    and_zp_x();
}

void CPU::rla_ind_x() {
    rol_ind_x();
    and_ind_x();
}

void CPU::rla_ind_y() {
    rol_ind_y();
    and_ind_y();
    T = 8;
}

void CPU::rla_abs() {
    rol_abs();
    and_abs();
}

void CPU::rla_abs_x() {
    rol_abs_x();
    and_abs_x();
    T = 7;
}

void CPU::rla_abs_y() {
    rol_abs_y();
    and_abs_y();
    T = 7;
}

void CPU::sre_zp() {
    lsr_zp();
    xor_zp();
}

void CPU::sre_zp_x() {
    lsr_zp_x();
    xor_zp_x();
}

void CPU::sre_ind_x() {
    lsr_ind_x();
    xor_ind_x();
}

void CPU::sre_ind_y() {
    lsr_ind_y();
    xor_ind_y();
    T = 8 ;
}

void CPU::sre_abs() {
    lsr_abs();
    xor_abs();
}

void CPU::sre_abs_x() {
    lsr_abs_x();
    xor_abs_x();
    T = 7;
}

void CPU::sre_abs_y() {
    lsr_abs_y();
    xor_abs_y();
    T = 7;
}

void CPU::rra_zp() {
    ror_zp();
    adc_zp();
}

void CPU::rra_zp_x() {
    ror_zp_x();
    adc_zp_x();
}

void CPU::rra_ind_x() {
    ror_ind_x();
    adc_ind_x();
}

void CPU::rra_ind_y() {
    ror_ind_y();
    adc_ind_y();
    T = 8;
}

void CPU::rra_abs() {
    ror_abs();
    adc_abs();
}

void CPU::rra_abs_x() {
    ror_abs_x();
    adc_abs_x();
    T = 7;
}

void CPU::rra_abs_y() {
    ror_abs_y();
    adc_abs_y();
    T = 7;
}

void CPU::dcp_zp() {
    dec_zp();
    cmp_a_zp();
}

void CPU::dcp_zp_x() {
    dec_zp_x();
    cmp_a_zp_x();
}

void CPU::dcp_ind_x() {
    dec_ind_x();
    cmp_a_ind_x();
}

void CPU::dcp_ind_y() {
    dec_ind_y();
    cmp_a_ind_y();
    T = 8;
}

void CPU::dcp_abs() {
    dec_abs();
    cmp_a_abs();
}

void CPU::dcp_abs_x() {
    dec_abs_x();
    cmp_a_abs_x();
    T = 7;
}

void CPU::dcp_abs_y() {
    dec_abs_y();
    cmp_a_abs_y();
    T = 7;
}

void CPU::isb_zp() {
    inc_zp();
    sbc_zp();
}

void CPU::isb_zp_x() {
    inc_zp_x();
    sbc_zp_x();
}

void CPU::isb_ind_x() {
    inc_ind_x();
    sbc_ind_x();
}

void CPU::isb_ind_y() {
    inc_ind_y();
    sbc_ind_y();
    T = 8;
}

void CPU::isb_abs() {
    inc_abs();
    sbc_abs();
}

void CPU::isb_abs_x() {
    inc_abs_x();
    sbc_abs_x();
    T = 7;
}

void CPU::isb_abs_y() {
    inc_abs_y();
    sbc_abs_y();
    T = 7;
}

void CPU::anc_imm() {
    and_imm();
    P.f.c = P.f.n;
}

void CPU::anc_imm2() {
    and_imm();
    P.f.c = P.f.n;
}

void CPU::alr_imm() {
    and_imm();
    lsr();
}

void CPU::arr_imm() {
    A &= mmu->memRead8( PC+1 );
    A = (A>>1) | (P.f.c<<7);
    P.f.n = A>>7;
    P.f.z = A==0;
    P.f.c = (A & 0x40)>>6;
    P.f.v = P.f.c ^ ((A >> 5) & 1);
}

void CPU::xaa_imm() {

}

void CPU::lax_imm() {
    lda_imm();
    tax();
}

void CPU::axs_imm() {
    tmp16 = ( A & X ) - mmu->memRead8( PC+1 );
    P.f.n = tmp16>>7;
    P.f.z = tmp16==0;
    P.f.c = tmp16<0x100;
    X = tmp16;
}

void CPU::sbc_imm2() {
    sbc_imm();
    nop();
}

void CPU::shy() {
    addr = mmu->memRead16( PC+1 );
    tmp16 = ( Y & ( ( addr >> 8 ) +1) ) & 0xff;
    if((X+(addr&0xff))<=0xff)mmu->memWrite8(addr+X,tmp16);
}

void CPU::shx() {
    addr = mmu->memRead16( PC+1 );
    tmp16 = ( X & ( ( addr >> 8 ) +1) ) & 0xff;
    if((Y+(addr&0xff))<=0xff)mmu->memWrite8(addr+Y,tmp16);
}
