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
    //SOUT(millis()); SOUT(" ip_cell init _locIP "); SOUTHEX(_locIP); SOUT("  _ssid "); SOUTLN(_ssid);
  }

// class ip_list
ip_list::ip_list()
  {
    _pFirst = pLast = NULL;
    //SOUT(millis()); SOUTLN(" ip_list new");
  }

ip_list::~ip_list()
  {
    void* pcell = NULL;
    SOUT(millis()); SOUTLN(" ip_list del ");
    while (pcell = md_list::removeFirstCell())
      {
        SOUT(millis()); SOUT(" del ip_cell ");SOUTHEXLN((u_long) pcell);
        ((ip_cell*) pcell)->~ip_cell();
      }
  }

void ip_list::append(uint32_t locIP, uint32_t gwIP, uint32_t snIP,
                     const char ssid[NET_MAX_SSID_LEN],
                     const char pw[NET_MAX_PW_LEN])
  {
    ip_cell* neu = new ip_cell();
    SOUT(millis());
    SOUT(" ip_list append ip_cell "); SOUTHEX((u_long) neu);
    SOUT("  locIP "); SOUTHEX(locIP); SOUT("  ssid "); SOUTLN(ssid);
    neu->init(locIP, gwIP, snIP, ssid, pw);
    md_list::append(neu);
  }

ip_cell* ip_list::getCellPointer( unsigned short index )
  {
    void* ptmp = (void*) md_list::getCellPointer( index );
    SOUT(millis()); SOUT(" ip_list getCellPointer "); SOUTHEXLN((u_long) ptmp);
    return (ip_cell*) ptmp;
  }

ip_cell* ip_list::getNextCellPointer( ip_cell* pCell )
  {
    void* ptmp = (void*) pCell;
    ptmp = (void*) md_list::getNextCellPointer( (md_cell*)(ptmp) );
    SOUT(millis()); SOUT(" ip_list getNextCellPointer "); SOUTHEXLN((u_long) ptmp);
    return (ip_cell*) ptmp;
  }


/* EOF */

