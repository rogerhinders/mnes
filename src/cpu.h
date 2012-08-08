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


#ifndef CPU_H
#define CPU_H
#include "types.h"
#include "mmu.h"

#define NMI_VECTOR 0xfffa
#define RESET_VECTOR 0xfffc
#define IRQ_VECTOR 0xfffe

class MMU;
class CPU {

public:
    typedef union {
        u8 b;
        struct {
            u8 c :1;
            u8 z :1;
            u8 i :1;
            u8 d :1;
            u8 b  :1;
            u8 _u  :1;
            u8 v  :1;
            u8 n  :1;
        } f;

    } StatusReg;
    
    //regs
    u8 A;
    u8 X;
    u8 Y;
    u16 PC;
    u8 S;
    StatusReg P;
    
    //instruction time
    u8 T;
    
    //methods
    CPU( MMU* mmu );
    void execInstr(u8 opcode);
    void execNMI();
private:
    MMU* mmu;
    u8 tmp8, prev;
    u16 tmp16,addr,newAddr;
    s16 tmp16s;

    u16 getIndirect();
    u16 getIndirectX();
    u16 getIndirectY();
    
    u16 getAbsoluteX();
    u16 getAbsoluteY();

    void push(u8 val);
    u8 pop();

    void txa();
    void tya();
    void txs();
    void tay();
    void tax();
    void tsx();
    
    void lda_imm();
    void lda_zp();
    void lda_zp_x();
    void lda_abs();
    void lda_abs_x();
    void lda_abs_y();
    void lda_ind_x();
    void lda_ind_y();
    void ldx_imm();
    void ldx_zp();
    void ldx_zp_y();
    void ldx_abs();
    void ldx_abs_y();
    void ldy_imm();
    void ldy_zp();
    void ldy_zp_x();
    void ldy_abs();
    void ldy_abs_x();
    
    void sta_zp();
    void sta_zp_x();
    void sta_abs();
    void sta_abs_x();
    void sta_abs_y();
    void sta_ind_x();
    void sta_ind_y();
    void stx_zp();
    void stx_zp_y();
    void stx_abs();
    void sty_zp();
    void sty_zp_x();
    void sty_abs();
    
    void pha();
    void php();
    void pla();
    void plp();
    
    void adc_imm();
    void adc_zp();
    void adc_zp_x();
    void adc_abs();
    void adc_abs_x();
    void adc_abs_y();
    void adc_ind_x();
    void adc_ind_y();

    void sbc_imm();
    void sbc_zp();
    void sbc_zp_x();
    void sbc_abs();
    void sbc_abs_x();
    void sbc_abs_y();
    void sbc_ind_x();
    void sbc_ind_y();
    
    void and_imm();
    void and_zp();
    void and_zp_x();
    void and_abs();
    void and_abs_x();
    void and_abs_y();
    void and_ind_x();
    void and_ind_y();
    
    void xor_imm();
    void xor_zp();
    void xor_zp_x();
    void xor_abs();
    void xor_abs_x();
    void xor_abs_y();
    void xor_ind_x();
    void xor_ind_y();
    
    void or_imm();
    void or_zp();
    void or_zp_x();
    void or_abs();
    void or_abs_x();
    void or_abs_y();
    void or_ind_x();
    void or_ind_y();
    
    void cmp_a_imm();
    void cmp_a_zp();
    void cmp_a_zp_x();
    void cmp_a_abs();
    void cmp_a_abs_x();
    void cmp_a_abs_y();
    void cmp_a_ind_x();
    void cmp_a_ind_y();
    void cpx_imm();
    void cpx_zp();
    void cpx_abs();
    void cpy_imm();
    void cpy_zp();
    void cpy_abs();
    
    void bit_zp();
    void bit_abs();
    
    void inc_zp();
    void inc_zp_x();
    void inc_abs();
    void inc_abs_x();
    void inc_abs_y();
    void inx();
    void iny();
    void inc_ind_x();
    void inc_ind_y();
    
    void dec_zp();
    void dec_zp_x();
    void dec_abs();
    void dec_abs_x();
    void dec_abs_y();
    void dex();
    void dey();
    void dec_ind_x();
    void dec_ind_y();
    
    void asl();
    void asl_zp();
    void asl_zp_x();
    void asl_abs();
    void asl_abs_x();
    void asl_abs_y();
    void asl_ind_x();
    void asl_ind_y();
    
    void lsr();
    void lsr_zp();
    void lsr_zp_x();
    void lsr_abs();
    void lsr_abs_x();
    void lsr_abs_y();
    void lsr_ind_y();
    void lsr_ind_x();
    
    void rol();
    void rol_zp();
    void rol_zp_x();
    void rol_abs();
    void rol_abs_x();
    void rol_abs_y();
    void rol_ind_x();
    void rol_ind_y();
    
    void ror();
    void ror_zp();
    void ror_zp_x();
    void ror_abs();
    void ror_abs_x();
    void ror_abs_y();
    void ror_ind_y();
    void ror_ind_x();
    
    void jmp_abs();
    void jmp_ind();
    void jsr();
    void rti();
    void rts();
    
    void bpl();
    void bmi();
    void bvc();
    void bvs();
    void bcc();
    void bcs();
    void bne();
    void beq();
    
    void brk();
    
    void clc();
    void cli();
    void cld();
    void clv();
    void sec();
    void sei();
    void sed();
    
    void nop();
    void nopX();
    void kil();
    
    void sax_zp();
    void sax_zp_y();
    void sax_abs();
    void sax_ind_x();
    void lax_zp();
    void lax_zp_y();
    void lax_abs();
    void lax_abs_y();
    void lax_ind_x();
    void lax_ind_y();
    
    void slo_zp();
    void slo_zp_x();
    void slo_ind_x();
    void slo_ind_y();
    void slo_abs();
    void slo_abs_x();
    void slo_abs_y();

    void rla_zp();
    void rla_zp_x();
    void rla_ind_x();
    void rla_ind_y();
    void rla_abs();
    void rla_abs_x();
    void rla_abs_y();
    
    void sre_zp();
    void sre_zp_x();
    void sre_ind_x();
    void sre_ind_y();
    void sre_abs();
    void sre_abs_x();
    void sre_abs_y();
    
    void rra_zp();
    void rra_zp_x();
    void rra_ind_x();
    void rra_ind_y();
    void rra_abs();
    void rra_abs_x();
    void rra_abs_y();
    
    void dcp_zp();
    void dcp_zp_x();
    void dcp_ind_x();
    void dcp_ind_y();
    void dcp_abs();
    void dcp_abs_x();
    void dcp_abs_y();
    
    void isb_zp();
    void isb_zp_x();
    void isb_ind_x();
    void isb_ind_y();
    void isb_abs();
    void isb_abs_x();
    void isb_abs_y();
    
    void anc_imm();
    void anc_imm2();
    void alr_imm();
    void arr_imm();
    void xaa_imm();
    void lax_imm();
    void axs_imm();
    void sbc_imm2();
    
    void shy();
    void shx();
};

#endif // CPU_H
