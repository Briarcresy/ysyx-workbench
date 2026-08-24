// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VALU.h for the primary calling header

#include "VALU__pch.h"

bool VALU___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((2U > n));
    return (0U);
}

void VALU___024root___ico_sequent__TOP__0(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___ico_sequent__TOP__0\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.debug_wb_rd = (0x0000000fU & (vlSelfRef.inst 
                                            >> 7U));
    vlSelfRef.minirvCPU__DOT__controller__DOT__addi 
        = (IData)((0x00000013U == (0x0000707fU & vlSelfRef.inst)));
    vlSelfRef.debug_wb_data = ((- (IData)((1U == (1U 
                                                  & (- (IData)((IData)(vlSelfRef.minirvCPU__DOT__controller__DOT__addi))))))) 
                               & (((IData)(vlSelfRef.minirvCPU__DOT__controller__DOT__addi)
                                    ? (((- (IData)(
                                                   ((0x13U 
                                                     == 
                                                     (0x0000007fU 
                                                      & vlSelfRef.inst)) 
                                                    | ((3U 
                                                        == 
                                                        (0x0000007fU 
                                                         & vlSelfRef.inst)) 
                                                       | (0x67U 
                                                          == 
                                                          (0x0000007fU 
                                                           & vlSelfRef.inst)))))) 
                                        & (((- (IData)(
                                                       (vlSelfRef.inst 
                                                        >> 0x0000001fU))) 
                                            << 0x0000000cU) 
                                           | (vlSelfRef.inst 
                                              >> 0x00000014U))) 
                                       | (((- (IData)(
                                                      (0x23U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.inst)))) 
                                           & (((- (IData)(
                                                          (vlSelfRef.inst 
                                                           >> 0x0000001fU))) 
                                               << 0x0000000cU) 
                                              | ((0x00000fe0U 
                                                  & (vlSelfRef.inst 
                                                     >> 0x00000014U)) 
                                                 | (0x0000001fU 
                                                    & (vlSelfRef.inst 
                                                       >> 7U))))) 
                                          | (((- (IData)(
                                                         (0x63U 
                                                          == 
                                                          (0x0000007fU 
                                                           & vlSelfRef.inst)))) 
                                              & (((- (IData)(
                                                             (vlSelfRef.inst 
                                                              >> 0x0000001fU))) 
                                                  << 0x0000000dU) 
                                                 | ((((2U 
                                                       & (vlSelfRef.inst 
                                                          >> 0x0000001eU)) 
                                                      | (1U 
                                                         & (vlSelfRef.inst 
                                                            >> 7U))) 
                                                     << 0x0000000bU) 
                                                    | ((0x000007e0U 
                                                        & (vlSelfRef.inst 
                                                           >> 0x00000014U)) 
                                                       | (0x0000001eU 
                                                          & (vlSelfRef.inst 
                                                             >> 7U)))))) 
                                             | ((0xfffff000U 
                                                 & ((- (IData)(
                                                               ((0x37U 
                                                                 == 
                                                                 (0x0000007fU 
                                                                  & vlSelfRef.inst)) 
                                                                | (0x17U 
                                                                   == 
                                                                   (0x0000007fU 
                                                                    & vlSelfRef.inst))))) 
                                                    & vlSelfRef.inst)) 
                                                | ((- (IData)(
                                                              (0x6fU 
                                                               == 
                                                               (0x0000007fU 
                                                                & vlSelfRef.inst)))) 
                                                   & ((((0x00000ffeU 
                                                         & ((- (IData)(
                                                                       (vlSelfRef.inst 
                                                                        >> 0x0000001fU))) 
                                                            << 1U)) 
                                                        | (vlSelfRef.inst 
                                                           >> 0x0000001fU)) 
                                                       << 0x00000014U) 
                                                      | ((((0x000001feU 
                                                            & (vlSelfRef.inst 
                                                               >> 0x0000000bU)) 
                                                           | (1U 
                                                              & (vlSelfRef.inst 
                                                                 >> 0x00000014U))) 
                                                          << 0x0000000bU) 
                                                         | (0x000007feU 
                                                            & (vlSelfRef.inst 
                                                               >> 0x00000014U)))))))))
                                    : ((0U == (0x0000000fU 
                                               & (vlSelfRef.inst 
                                                  >> 0x00000014U)))
                                        ? 0U : vlSelfRef.minirvCPU__DOT__reg_file__DOT__R
                                       [(0x0000000fU 
                                         & (vlSelfRef.inst 
                                            >> 0x00000014U))])) 
                                  + ((0U == (0x0000000fU 
                                             & (vlSelfRef.inst 
                                                >> 0x0000000fU)))
                                      ? 0U : vlSelfRef.minirvCPU__DOT__reg_file__DOT__R
                                     [(0x0000000fU 
                                       & (vlSelfRef.inst 
                                          >> 0x0000000fU))])));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VALU___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool VALU___024root___eval_phase__ico(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_phase__ico\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__ico
        vlSelfRef.__VicoTriggered[0U] = (QData)((IData)(
                                                        (((vlSelfRef.inst 
                                                           != vlSelfRef.__Vtrigprevexpr___TOP__inst__0) 
                                                          << 2U) 
                                                         | ((((IData)(vlSelfRef.rst) 
                                                              != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst__0)) 
                                                             << 1U) 
                                                            | ((IData)(vlSelfRef.clk) 
                                                               != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
        vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
        vlSelfRef.__Vtrigprevexpr___TOP__inst__0 = vlSelfRef.inst;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VicoDidInit)))))) {
            vlSelfRef.__VicoDidInit = 1U;
            vlSelfRef.__VicoTriggered[0U] = (1ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (2ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (4ULL | vlSelfRef.__VicoTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VALU___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = VALU___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        {
            // Inlined CFunc: _eval_ico
            if ((4ULL & vlSelfRef.__VicoTriggered[0U])) {
                VALU___024root___ico_sequent__TOP__0(vlSelf);
            }
            if ((6ULL & vlSelfRef.__VicoTriggered[0U])) {
                {
                    // Inlined CFunc: _ico_comb__TOP__0
                    vlSelfRef.debug_wb_we = ((~ ((IData)(vlSelfRef.rst) 
                                                 | (0U 
                                                    == (IData)(vlSelfRef.debug_wb_rd)))) 
                                             & (IData)(vlSelfRef.minirvCPU__DOT__controller__DOT__addi));
                }
            }
        }
    }
    return (__VicoExecute);
}

bool VALU___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void VALU___024root___nba_sequent__TOP__0(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___nba_sequent__TOP__0\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VdlyVal__minirvCPU__DOT__reg_file__DOT__R__v0;
    __VdlyVal__minirvCPU__DOT__reg_file__DOT__R__v0 = 0;
    CData/*3:0*/ __VdlyDim0__minirvCPU__DOT__reg_file__DOT__R__v0;
    __VdlyDim0__minirvCPU__DOT__reg_file__DOT__R__v0 = 0;
    CData/*0:0*/ __VdlySet__minirvCPU__DOT__reg_file__DOT__R__v0;
    __VdlySet__minirvCPU__DOT__reg_file__DOT__R__v0 = 0;
    // Body
    __VdlySet__minirvCPU__DOT__reg_file__DOT__R__v0 = 0U;
    vlSelfRef.pc = ((IData)(vlSelfRef.rst) ? 0U : ((IData)(4U) 
                                                   + vlSelfRef.pc));
    if (vlSelfRef.debug_wb_we) {
        __VdlyVal__minirvCPU__DOT__reg_file__DOT__R__v0 
            = vlSelfRef.debug_wb_data;
        __VdlyDim0__minirvCPU__DOT__reg_file__DOT__R__v0 
            = vlSelfRef.debug_wb_rd;
        __VdlySet__minirvCPU__DOT__reg_file__DOT__R__v0 = 1U;
    }
    if (__VdlySet__minirvCPU__DOT__reg_file__DOT__R__v0) {
        vlSelfRef.minirvCPU__DOT__reg_file__DOT__R[__VdlyDim0__minirvCPU__DOT__reg_file__DOT__R__v0] 
            = __VdlyVal__minirvCPU__DOT__reg_file__DOT__R__v0;
    }
    vlSelfRef.debug_wb_data = ((- (IData)((1U == (1U 
                                                  & (- (IData)((IData)(vlSelfRef.minirvCPU__DOT__controller__DOT__addi))))))) 
                               & (((IData)(vlSelfRef.minirvCPU__DOT__controller__DOT__addi)
                                    ? (((- (IData)(
                                                   ((0x13U 
                                                     == 
                                                     (0x0000007fU 
                                                      & vlSelfRef.inst)) 
                                                    | ((3U 
                                                        == 
                                                        (0x0000007fU 
                                                         & vlSelfRef.inst)) 
                                                       | (0x67U 
                                                          == 
                                                          (0x0000007fU 
                                                           & vlSelfRef.inst)))))) 
                                        & (((- (IData)(
                                                       (vlSelfRef.inst 
                                                        >> 0x0000001fU))) 
                                            << 0x0000000cU) 
                                           | (vlSelfRef.inst 
                                              >> 0x00000014U))) 
                                       | (((- (IData)(
                                                      (0x23U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.inst)))) 
                                           & (((- (IData)(
                                                          (vlSelfRef.inst 
                                                           >> 0x0000001fU))) 
                                               << 0x0000000cU) 
                                              | ((0x00000fe0U 
                                                  & (vlSelfRef.inst 
                                                     >> 0x00000014U)) 
                                                 | (0x0000001fU 
                                                    & (vlSelfRef.inst 
                                                       >> 7U))))) 
                                          | (((- (IData)(
                                                         (0x63U 
                                                          == 
                                                          (0x0000007fU 
                                                           & vlSelfRef.inst)))) 
                                              & (((- (IData)(
                                                             (vlSelfRef.inst 
                                                              >> 0x0000001fU))) 
                                                  << 0x0000000dU) 
                                                 | ((((2U 
                                                       & (vlSelfRef.inst 
                                                          >> 0x0000001eU)) 
                                                      | (1U 
                                                         & (vlSelfRef.inst 
                                                            >> 7U))) 
                                                     << 0x0000000bU) 
                                                    | ((0x000007e0U 
                                                        & (vlSelfRef.inst 
                                                           >> 0x00000014U)) 
                                                       | (0x0000001eU 
                                                          & (vlSelfRef.inst 
                                                             >> 7U)))))) 
                                             | ((0xfffff000U 
                                                 & ((- (IData)(
                                                               ((0x37U 
                                                                 == 
                                                                 (0x0000007fU 
                                                                  & vlSelfRef.inst)) 
                                                                | (0x17U 
                                                                   == 
                                                                   (0x0000007fU 
                                                                    & vlSelfRef.inst))))) 
                                                    & vlSelfRef.inst)) 
                                                | ((- (IData)(
                                                              (0x6fU 
                                                               == 
                                                               (0x0000007fU 
                                                                & vlSelfRef.inst)))) 
                                                   & ((((0x00000ffeU 
                                                         & ((- (IData)(
                                                                       (vlSelfRef.inst 
                                                                        >> 0x0000001fU))) 
                                                            << 1U)) 
                                                        | (vlSelfRef.inst 
                                                           >> 0x0000001fU)) 
                                                       << 0x00000014U) 
                                                      | ((((0x000001feU 
                                                            & (vlSelfRef.inst 
                                                               >> 0x0000000bU)) 
                                                           | (1U 
                                                              & (vlSelfRef.inst 
                                                                 >> 0x00000014U))) 
                                                          << 0x0000000bU) 
                                                         | (0x000007feU 
                                                            & (vlSelfRef.inst 
                                                               >> 0x00000014U)))))))))
                                    : ((0U == (0x0000000fU 
                                               & (vlSelfRef.inst 
                                                  >> 0x00000014U)))
                                        ? 0U : vlSelfRef.minirvCPU__DOT__reg_file__DOT__R
                                       [(0x0000000fU 
                                         & (vlSelfRef.inst 
                                            >> 0x00000014U))])) 
                                  + ((0U == (0x0000000fU 
                                             & (vlSelfRef.inst 
                                                >> 0x0000000fU)))
                                      ? 0U : vlSelfRef.minirvCPU__DOT__reg_file__DOT__R
                                     [(0x0000000fU 
                                       & (vlSelfRef.inst 
                                          >> 0x0000000fU))])));
}

void VALU___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VALU___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool VALU___024root___eval_phase__act(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_phase__act\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((IData)(vlSelfRef.clk) 
                                                         & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__1)))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VALU___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    VALU___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void VALU___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool VALU___024root___eval_phase__nba(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_phase__nba\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = VALU___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_nba
            if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
                VALU___024root___nba_sequent__TOP__0(vlSelf);
            }
        }
        VALU___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void VALU___024root___eval(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            VALU___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("vsrc/minirvCPU.v", 1, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = VALU___024root___eval_phase__ico(vlSelf);
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VALU___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("vsrc/minirvCPU.v", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VALU___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("vsrc/minirvCPU.v", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = VALU___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = VALU___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void VALU___024root___eval_debug_assertions(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_debug_assertions\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
}
#endif  // VL_DEBUG
