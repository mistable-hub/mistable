// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmistable_top.h for the primary calling header

#include "Vmistable_top.h"
#include "Vmistable_top__Syms.h"

//==========

VL_CTOR_IMP(Vmistable_top) {
    Vmistable_top__Syms* __restrict vlSymsp = __VlSymsp = new Vmistable_top__Syms(this, name());
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vmistable_top::__Vconfigure(Vmistable_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vmistable_top::~Vmistable_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vmistable_top::_eval_initial(Vmistable_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_eval_initial\n"); );
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vmistable_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::final\n"); );
    // Variables
    Vmistable_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vmistable_top::_eval_settle(Vmistable_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_eval_settle\n"); );
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void Vmistable_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    pix_valid = VL_RAND_RESET_I(1);
    pix_r = VL_RAND_RESET_I(8);
    pix_g = VL_RAND_RESET_I(8);
    pix_b = VL_RAND_RESET_I(8);
    pix_x = VL_RAND_RESET_I(16);
    pix_y = VL_RAND_RESET_I(16);
    frame_done = VL_RAND_RESET_I(1);
    mistable_top__DOT__unnamedblk1__DOT__bar = 0;
    mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad = 0;
}
