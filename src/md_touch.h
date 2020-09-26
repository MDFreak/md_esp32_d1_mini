#ifndef _MD_TOUCH_H_
  #define _MD_TOUCH_H_

  #include "FS.h"
  #include <SPI.h>
  #include <TFT_eSPI.h>      // Hardware-specific library
  #include "config.h"

  #ifdef USE_TOUCHSCREEN
    #ifdef USE_DEFTOUCH
      bool md_start_deftouch();
      void md_run_deftouch();
    #elif USE_MD_TOUCH1
      bool md_start_md1touch();
      bool md_run_md1touch();
    #elif USE_MD_TOUCH2
      bool md_start_md2touch();
      bool md_run_md2touch();
    #elif USE_MD_TOUCH3
      bool md_start_md3touch();
      bool md_run_md3touch();
    #elif USE_MD_TOUCH4
      bool md_start_md4touch();
      bool md_run_md4touch();
    #endif
  #endif

#endif
