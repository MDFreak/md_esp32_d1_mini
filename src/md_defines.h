#ifndef _MD_DEFINES_H_
  #define _MD_DEFINES_H_

  // ------ config constants --------------------------
  #ifndef CFG_DEFS
  // --------------------------------------------------

    // --- generic
    #define NN  -1  // not used
    #define OFF  0  // not active
    #define ON   1  // active

    // boards
    #define BRD_NN                NN
    #define BRD_ESP32S_NodeMCU_AZ 1
    #define BRD_ARD_NANO_V3_AZ    2

    // assemblies
    #define ASS_NN                NN
    #define ASS_TOUCH_ESP32_AZ    1

    // switching projects
    #define CFG_PROJ_DEFTEST      0   // default Test
    #define CFG_PROJ_DETAILTEST   1   // detailed test

    // modes for serial debugging
    #define CFG_DEBUG_NONE        0   // no Serial output
    #define CFG_DEBUG_STARTUP     1   // report initialising
    #define CFG_DEBUG_ACTIONS     2   // report actions
    #define CFG_DEBUG_DETAILS     3   // report details for errors
    #define CFG_DEBUG_SPEZIAL     4   // spezial purpose
  #endif // CFG_DEFS

#endif // _MD_DEFINES_H_