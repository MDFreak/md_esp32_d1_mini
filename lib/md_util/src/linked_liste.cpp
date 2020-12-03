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

#include "linked_list.hpp"

//
// --- class md_cell
  md_cell::md_cell()
  {
    SOUT(millis()); SOUTLN(" md_cell new");
    _pNext = NULL;
    _pPriv = NULL;
  }

  void* md_cell::pNext()
    {
      SOUT(millis()); SOUT(" md_list pNext "); SOUTHEXLN((u_long) _pNext);
      return (void*) _pNext;
    }

  void* md_cell::pPriv()
    {
      SOUT(millis()); SOUT(" md_list pPriv "); SOUTHEXLN((u_long) _pPriv);
      return (void*) _pPriv;
    }

  void  md_cell::setNext(void* pNext)
    {
      SOUT(millis()); SOUT(" md_list setNext "); SOUTHEXLN((u_long) pNext);
      _pNext = pNext;
    }

  void  md_cell::setPriv(void* pPriv)
    {
      SOUT(millis()); SOUT(" md_list setPriv "); SOUTHEXLN((u_long) pPriv);
      _pPriv = pPriv;
    }


//
// --- class md_list
  md_list::md_list()
    {
      SOUT(millis()); SOUTLN(" md_list new");
      _pFirst = _pLast = NULL;
      _count  = 0;
    }

  md_list::~md_list()
    {
      //md_cell* pcell = NULL;
      SOUT(millis()); SOUTLN(" md_list del ");
/*
      while ((pcell = md_list::removeFirstCell()) != NULL)
        {
          SOUTHEXLN((u_long) pcell);
        }
*/
    }

  uint16_t md_list::count ()
    {
      return _count;
    }

  void*    md_list::pFirst()
    {
      return (void*) _pFirst;
    }

  void*    md_list::pLast ()
    {
      return (void*) _pLast;
    }

  //
  uint16_t md_list::add (void* pCell)   /* ein Listenelement am Ende anhaengen */
    {
      SOUT(millis()); SOUT(" md_list before add: count ");
      SOUT(_count);SOUT(" pFirst "); SOUTHEX((u_long) _pFirst); SOUT(" plast "); SOUTHEXLN((u_long) _pLast);
      if (_pLast == NULL)            /* wenn noch kein Listenelement eingetragen */
          {
            _pFirst = _pLast = (md_cell*) pCell;
            _count++;
          }
        else
          {
            _pLast->setNext(pCell);
            md_cell* ptmp = (md_cell*) pCell;
            ptmp->setPriv((void*) _pLast);
            ptmp->setNext(NULL);
            _pLast = ptmp;
            _count++;
          }
      SOUT(millis()); SOUT(" md_list after add: count ");
      SOUT(_count);SOUT(" pFirst "); SOUTHEX((u_long) _pFirst); SOUT(" plast "); SOUTHEXLN((u_long) _pLast);
      return count();
    }

  //
/*
  md_cell* md_list::removeFirstCell( ) // Erstes Element aus der Liste entnehmen und Pointer auf dieses Element zurueckgeben
    {
      md_cell *pCell = NULL;
      if ( _pFirst != NULL )   // wenn noch mind. ein Element in der Liste
        {
          pCell = _pFirst;
          if ( _pFirst != _pLast )  // wenn noch nicht letztes Element
            {
              _pFirst = _pFirst->pNext();
            }
          else
            {
              _pFirst = _pLast = NULL;
            }
        }
      //SOUT(millis()); SOUT(" md_list removeFirstCell "); SOUTHEXLN((u_long) pCell);
      return( pCell );
    }
*/

/* EOF */

