// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmistable_top.h for the primary calling header

#include "Vmistable_top.h"
#include "Vmistable_top__Syms.h"

//==========

void Vmistable_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmistable_top::eval\n"); );
    Vmistable_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("rtl/mistable_top.sv", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vmistable_top::_eval_initial_loop(Vmistable_top__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("rtl/mistable_top.sv", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vmistable_top::_sequent__TOP__1(Vmistable_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_sequent__TOP__1\n"); );
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    SData/*15:0*/ __Vdly__pix_x;
    SData/*15:0*/ __Vdly__pix_y;
    // Body
    __Vdly__pix_y = vlTOPp->pix_y;
    __Vdly__pix_x = vlTOPp->pix_x;
    if (vlTOPp->rst) {
        __Vdly__pix_x = 0U;
        __Vdly__pix_y = 0U;
        vlTOPp->frame_done = 0U;
    } else {
        vlTOPp->frame_done = 0U;
        if ((0xffU == (IData)(vlTOPp->pix_x))) {
            __Vdly__pix_x = 0U;
            if ((0xefU == (IData)(vlTOPp->pix_y))) {
                __Vdly__pix_y = 0U;
                vlTOPp->frame_done = 1U;
            } else {
                __Vdly__pix_y = (0xffffU & ((IData)(1U) 
                                            + (IData)(vlTOPp->pix_y)));
            }
        } else {
            __Vdly__pix_x = (0xffffU & ((IData)(1U) 
                                        + (IData)(vlTOPp->pix_x)));
        }
    }
    vlTOPp->pix_y = __Vdly__pix_y;
    vlTOPp->pix_x = __Vdly__pix_x;
}

VL_INLINE_OPT void Vmistable_top::_settle__TOP__2(Vmistable_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_settle__TOP__2\n"); );
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->pix_valid = (1U & (~ (IData)(vlTOPp->rst)));
    vlTOPp->pix_r = 0U;
    vlTOPp->pix_g = 0U;
    vlTOPp->pix_b = 0U;
    if (vlTOPp->pix_valid) {
        vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar 
            = (0xffffffU & ((IData)(vlTOPp->pix_x) 
                            >> 5U));
        if (VL_GTS_III(1,32,32, 0U, vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
            vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar = 0U;
        }
        if (VL_LTS_III(1,32,32, 7U, vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
            vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar = 7U;
        }
        if ((7U == vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
            vlTOPp->mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad 
                = VL_DIVS_III(32, VL_MULS_III(32,32,32, (IData)(0xffU), 
                                              ((IData)(vlTOPp->pix_x) 
                                               - (IData)(0xe0U))), (IData)(0x1fU));
            if (VL_GTS_III(1,32,32, 0U, vlTOPp->mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad)) {
                vlTOPp->mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad = 0U;
            }
            if (VL_LTS_III(1,32,32, 0xffU, vlTOPp->mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad)) {
                vlTOPp->mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad = 0xffU;
            }
            vlTOPp->pix_r = (0xffU & vlTOPp->mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad);
            vlTOPp->pix_g = (0xffU & vlTOPp->mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad);
            vlTOPp->pix_b = (0xffU & vlTOPp->mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad);
        } else {
            if ((0U == vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
                vlTOPp->pix_r = 0xffU;
                vlTOPp->pix_g = 0U;
                vlTOPp->pix_b = 0U;
            } else {
                if ((1U == vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
                    vlTOPp->pix_r = 0xffU;
                    vlTOPp->pix_g = 0x80U;
                    vlTOPp->pix_b = 0U;
                } else {
                    if ((2U == vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
                        vlTOPp->pix_r = 0xffU;
                        vlTOPp->pix_g = 0xffU;
                        vlTOPp->pix_b = 0U;
                    } else {
                        if ((3U == vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
                            vlTOPp->pix_r = 0U;
                            vlTOPp->pix_g = 0xffU;
                            vlTOPp->pix_b = 0U;
                        } else {
                            if ((4U == vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
                                vlTOPp->pix_r = 0U;
                                vlTOPp->pix_g = 0xffU;
                                vlTOPp->pix_b = 0xffU;
                            } else {
                                if ((5U == vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
                                    vlTOPp->pix_r = 0U;
                                    vlTOPp->pix_g = 0U;
                                    vlTOPp->pix_b = 0xffU;
                                } else {
                                    if ((6U == vlTOPp->mistable_top__DOT__unnamedblk1__DOT__bar)) {
                                        vlTOPp->pix_r = 0x80U;
                                        vlTOPp->pix_g = 0U;
                                        vlTOPp->pix_b = 0xffU;
                                    } else {
                                        vlTOPp->pix_r = 0xffU;
                                        vlTOPp->pix_g = 0xffU;
                                        vlTOPp->pix_b = 0xffU;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Vmistable_top::_eval(Vmistable_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_eval\n"); );
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    vlTOPp->_settle__TOP__2(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

VL_INLINE_OPT QData Vmistable_top::_change_request(Vmistable_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_change_request\n"); );
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vmistable_top::_change_request_1(Vmistable_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_change_request_1\n"); );
    Vmistable_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vmistable_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmistable_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
