/*************************************************************************
|  Filename..............: ip_list.hpp
 * Project...............: part of standard utilities
 * Autor.................: Martin Dorfner (MD)
 * Date .................: 20.11.2020
 *-----------------------------------------------------------------------
 * Function:
 *   provide a list containing network login data
 *-----------------------------------------------------------------------
 * Dependecies:
 *   md_defines.h    (utility intern)
 *   linked_list.hpp (utility intern)
 *   ip_list.cpp     implementation
 ************************************************************************
 * Version| Date   | Changes                                    | Autor
 *-----------------------------------------------------------------------
 * 0.1.0  |20.11.20| import from former project                 | MD
*-----------------------------------------------------------------------*/

/* Header Digital Input */

#ifndef _IPLIST_HPP_
  #define _IPLIST_HPP_

  #include <linked_list.hpp>

  #define NET_MAX_SSID_LEN 14
  #define NET_MAX_PW_LEN   14

  class ip_cell : public md_cell
    {
      protected:
        uint32_t _locIP    = 0;
        uint32_t _gwIP     = 0;
        uint32_t _snIP     = 0;
        char     _ssid[NET_MAX_SSID_LEN] = "";
        char     _pw[NET_MAX_PW_LEN]   = "";
//        ip_cell* _me;

      public:
        ip_cell() ;
        ~ip_cell() ;

        void init(uint32_t locIP, uint32_t gwIP, uint32_t snIP,
                    const char ssid[NET_MAX_SSID_LEN], const char pw[NET_MAX_PW_LEN]);
        uint32_t locIP();
        uint32_t gwIP();
        uint32_t snIP();
        void getSSID(char ssid[NET_MAX_SSID_LEN] );
        void getPW(char pw[NET_MAX_PW_LEN]);
    };

  //
  class ip_list : public md_list
    {
      private:
        ip_cell* _pFirst;
        ip_cell* _pLast;

      public:
        ip_list();
        ~ip_list();

        void append(uint32_t locIP, uint32_t gwIP, uint32_t snIP,
                     const char ssid[NET_MAX_SSID_LEN],
                     const char pw[NET_MAX_PW_LEN]);
        ip_cell* find(const char ssid[NET_MAX_SSID_LEN]);
    };
#endif



