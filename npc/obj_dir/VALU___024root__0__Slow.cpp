// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VALU.h for the primary calling header

#include "VALU__pch.h"

VL_ATTR_COLD void VALU___024root___eval_static(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_static\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst__0 = vlSelfRef.rst;
    vlSelfRef.__Vtrigprevexpr___TOP__inst__0 = vlSelfRef.inst;
    vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
}

VL_ATTR_COLD void VALU___024root___eval_initial(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_initial\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VALU___024root___eval_final(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_final\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VALU___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VALU___024root___eval_phase__stl(VALU___024root* vlSelf);

VL_ATTR_COLD void VALU___024root___eval_settle(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_settle\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            VALU___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("vsrc/minirvCPU.v", 1, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = VALU___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD bool VALU___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VALU___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(VALU___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool VALU___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void VALU___024root___stl_sequent__TOP__0(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___stl_sequent__TOP__0\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.debug_wb_rd = (0x0000000fU & (vlSelfRef.inst 
                                            >> 7U));
    vlSelfRef.minirvCPU__DOT__controller__DOT__addi 
        = (IData)((0x00000013U == (0x0000707fU & vlSelfRef.inst)));
    vlSelfRef.debug_wb_we = ((~ ((IData)(vlSelfRef.rst) 
                                 | (0U == (IData)(vlSelfRef.debug_wb_rd)))) 
                             & (IData)(vlSelfRef.minirvCPU__DOT__controller__DOT__addi));
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

VL_ATTR_COLD bool VALU___024root___eval_phase__stl(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___eval_phase__stl\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__stl
        vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                          & vlSelfRef.__VstlTriggered[0U]) 
                                         | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VALU___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = VALU___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_stl
            if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
                VALU___024root___stl_sequent__TOP__0(vlSelf);
            }
        }
    }
    return (__VstlExecute);
}

bool VALU___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VALU___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(VALU___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @( clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @( inst)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool VALU___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VALU___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(VALU___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VALU___024root___ctor_var_reset(VALU___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VALU___024root___ctor_var_reset\n"); );
    VALU__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->inst = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9812503827101699671ull);
    vlSelf->pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4211327832146562899ull);
    vlSelf->debug_wb_we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 412486034681393186ull);
    vlSelf->debug_wb_rd = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10831591772840186980ull);
    vlSelf->debug_wb_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17627782879201798645ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->minirvCPU__DOT__reg_file__DOT__R[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16068533449004814149ull);
    }
    vlSelf->minirvCPU__DOT__controller__DOT__addi = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7645463189223728298ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__inst__0 = 0;
    vlSelf->__VicoDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__1 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
