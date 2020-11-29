/*************************************************************************
|  Filename..............: ip_list.cpp
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
 *   ip_list.hpp
 ************************************************************************
 * Version| Date   | Changes                                    | Autor
 *-----------------------------------------------------------------------
 * 0.1.0  |20.11.20| import from former project                 | MD
*-----------------------------------------------------------------------*/

#include <ip_list.hpp>

// class ip_cell
void ip_cell::init(uint32_t locIP, uint32_t gwIP, uint32_t snIP,
                     const char ssid[NET_MAX_SSID_LEN],
                     const char pw[NET_MAX_PW_LEN])
  {
    _locIP = locIP;
    _gwIP  = gwIP;
    _snIP  = snIP;
    strncpy(_ssid, ssid, NET_MAX_SSID_LEN);
    strncpy(_pw, pw, NET_MAX_PW_LEN);
  }

// class ip_list

ip_list::~ip_list()
  {
    ip_cell *pcell = NULL;
    while (md_list::removeFirstCell())
      {
        delete pcell;
      }
  }

void ip_list::append(uint32_t locIP, uint32_t gwIP, uint32_t snIP,
                     const char ssid[NET_MAX_SSID_LEN],
                     const char pw[NET_MAX_PW_LEN])
  {
    ip_cell *neu = new ip_cell();
    neu->init(locIP, gwIP, snIP, ssid, pw);
    md_list::append(neu);
  }



/* EOF */

