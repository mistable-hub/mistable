// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VMISTABLE_TOP_H_
#define _VMISTABLE_TOP_H_  // guard

#include "verilated.h"

//==========

class Vmistable_top__Syms;

//----------

VL_MODULE(Vmistable_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_OUT8(pix_valid,0,0);
    VL_OUT8(pix_r,7,0);
    VL_OUT8(pix_g,7,0);
    VL_OUT8(pix_b,7,0);
    VL_OUT8(frame_done,0,0);
    VL_OUT16(pix_x,15,0);
    VL_OUT16(pix_y,15,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    IData/*31:0*/ mistable_top__DOT__unnamedblk1__DOT__bar;
    IData/*31:0*/ mistable_top__DOT__unnamedblk1__DOT__unnamedblk2__DOT__grad;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vmistable_top__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vmistable_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vmistable_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vmistable_top();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vmistable_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vmistable_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vmistable_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vmistable_top__Syms* __restrict vlSymsp);
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vmistable_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vmistable_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vmistable_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__1(Vmistable_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vmistable_top__Syms* __restrict vlSymsp);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
