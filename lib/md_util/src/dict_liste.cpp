/*************************************************************************
|  Filename..............: linked_list.cpp
 * Project...............: part of standard utilities
 * Autor.................: Martin Dorfner (MD)
 * Date .................: 20.11.2020
 *-----------------------------------------------------------------------
 * Function:
 *   provide linked list support with small footprint
 *-----------------------------------------------------------------------
 * Dependecies:
 *   md_defines.h    (utility intern)
 *   linked_list.hpp
 ************************************************************************
 * Version| Date   | Changes                                    | Autor
 *-----------------------------------------------------------------------
 * 0.1.0  |20.11.20| import from former project                 | MD
*-----------------------------------------------------------------------*/

#include <dict_list.hpp>

//
// --- class dict_cell
  void dict_cell::init(int16_t idx, const char name[])
    {
      _idx = idx;
      setName(name);
    }

  //
  void dict_cell::setName(const char name[])
    {
      memcpy(_name, name, DICT_MAX_NAME_LEN);
      _name[DICT_MAX_NAME_LEN] = 0;
    }

//
// --- class dict_list
  dict_list::dict_list()
    {
      _pFirst = _pLast = NULL;
      //SOUT(millis()); SOUTLN(" ip_list new");
    }

  dict_list::~dict_list()
    {
/*
      void* pcell = NULL;
      SOUT(millis()); SOUTLN(" dict_list del ");
      while ((pcell = md_list::removeFirstCell()) != NULL)
        {
          SOUT(millis()); SOUT(" del dict_cell ");SOUTHEXLN((u_long) pcell);
          ((dict_cell*) pcell)->~dict_cell();
        }
*/
    }

  //
  void dict_list::append( int16_t idx, const char name[DICT_MAX_NAME_LEN])
    {
      dict_cell* neu = new dict_cell();
      SOUT(millis());
      SOUT(" dict_list append dict_cell "); SOUTHEX((u_long) neu);
      SOUT("  idx "); SOUTHEX(idx); SOUT("  name "); SOUTLN(name);
      neu->init(idx, name);
//      md_list::append(neu);
    }

  //
  dict_cell* dict_list::getCellPointer( unsigned short index )
    {
      void* ptmp; // = (void*) md_list::getCellPointer( index );
      SOUT(millis()); SOUT(" dict_list getCellPointer "); SOUTHEXLN((u_long) ptmp);
      return (dict_cell*) ptmp;
    }

  //
  dict_cell* dict_list::getNextCellPointer( dict_cell* pCell )
    {
      void* ptmp = (void*) pCell;
//      ptmp = (void*) md_list::getNextCellPointer( (md_cell*)(ptmp) );
      SOUT(millis()); SOUT(" dict_list getNextCellPointer "); SOUTHEXLN((u_long) ptmp);
      return (dict_cell*) ptmp;
    }

  //
  int16_t    dict_list::getIdx (const char name[])
    {
      dict_cell* pcell = _findCell(name);
      if (pcell) return pcell->getIdx();
      else       return NN;
    }

  //
  void       dict_list::getName(int16_t idx, char* pname)
    {
      dict_cell* pcell = _findCell(idx);
      if (pcell) pcell->getName(pname);
      else       pname[0] = 0;
    }

  //
  void       dict_list::setIdx (const char name[], int16_t idx)
    {
      dict_cell* pcell = _findCell(name);
      if (pcell) pcell->setIdx(idx);
    }

  //
  void       dict_list::setName(int16_t idx, const char name[])
    {
      dict_cell* pcell = _findCell(idx);
      if (pcell) pcell->setName(name);
    }

  //
  dict_cell* dict_list::_findCell(int16_t idx)
    {
      dict_cell* pcell = _pFirst;
      bool isda = false;
      while ( pcell != NULL )
        {
          if (pcell->getIdx() == idx)
            {
              isda = true;
              break;
            }
        }
      if (isda) return pcell;
      else      return NULL;
    }

  //
  dict_cell* dict_list::_findCell(const char name[])
    {
      dict_cell* pcell = _pFirst;
      char myname[DICT_MAX_NAME_LEN + 1] = "";
      bool isda = false;
      while ( pcell != NULL )
        {
          pcell->getName(myname);
          if (strcmp(myname, name) == 0)
            {
              isda = true;
              break;
            }
        }
      if (isda) return pcell;
      else      return NULL;
    }

/* EOF */

