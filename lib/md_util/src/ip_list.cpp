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
    SOUT(millis()); SOUT(" ip_cell init _locIP "); SOUTHEX(_locIP); SOUT("  _ssid "); SOUTLN(_ssid);
  }

ip_list::~ip_list()
  {
//    void* pcell = NULL;
    SOUT(millis()); SOUTLN(" ip_list del ");
/*
    while ((pcell = md_list::removeFirstCell()) != NULL)
      {
        SOUT(millis()); SOUT(" del ip_cell ");SOUTHEXLN((u_long) pcell);
        ((ip_cell*) pcell)->~ip_cell();
      }
*/
  }

//
void ip_list::append(uint32_t locIP, uint32_t gwIP, uint32_t snIP,
                     const char ssid[NET_MAX_SSID_LEN],
                     const char pw[NET_MAX_PW_LEN])
  {
    ip_cell* neu = new ip_cell();
    this->add((void*) neu);
    neu->init(locIP, gwIP, snIP, ssid, pw);
    char stmp[NET_MAX_SSID_LEN];
    neu->getSSID(stmp);
    SOUT(millis());
    SOUT(" ip_list append ip_cell "); SOUTHEX((u_long) neu);
    SOUT("  locIP "); SOUTHEX(neu->locIP()); SOUT("  ssid "); SOUTLN(stmp);
  }

ip_cell* ip_list::find(const char ssid[NET_MAX_SSID_LEN])
  {
    void* ptmp = _pFirst;
    char myname[NET_MAX_SSID_LEN + 1] = "";
    SOUT(" ip_list::find search for ssid "); SOUTLN(ssid);
    SOUT(" ptmp "); SOUTHEX((u_long) ptmp);
    while ( ptmp != NULL )
      {
        ((ip_cell*) ptmp)->getSSID(myname);
        SOUT(" ptmp "); SOUTHEX((u_long) ptmp); SOUT(" found ssid "); SOUTLN(myname);
        if (strcmp(myname, ssid) == 0)
          {
            break;
          }
        ptmp = (ip_cell*) ptmp->pNext();
      }
    return ptmp;
  }

/* EOF */

