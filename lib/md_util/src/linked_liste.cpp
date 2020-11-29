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

// --- public methods
void md_list::append (md_cell *pCell)   /* ein Listenelement am Ende anhaengen */
  {
    if (_pLast == NULL)            /* wenn noch kein Listenelement eingetragen */
        {
            _pFirst = _pLast = pCell;
        }
      else
        {
            _pLast->_pNext = pCell;
            _pLast = pCell;
        }
  }

//
md_cell *md_list::getCellPointer( unsigned short index ) /* Pointer auf ein Listenelement holen */
  {
    /* index beginnt ab 0 */
    md_cell *pCell;
    unsigned short i;

    pCell = _pFirst;
    for ( i=0; i<index; i++ )
      {
        if ( pCell != NULL )  /* wenn Element eingetragen */
          {
            pCell = pCell->_pNext; /* Pointer auf naechstes Listenelement */
          }
        else
          {
            i = index;        /* Liste ist nicht so lang (ende for-Schleife) */
          }
      }

    return( pCell );
  }

//
md_cell *md_list::getNextCellPointer( md_cell *pCell ) /* Pointer auf das naechste Listenelement holen */
  {

    if ( pCell != NULL )  /* wenn Element eingetragen */
      {
        pCell = pCell->_pNext; /* Pointer auf naechstes Listenelement */
      }
    else
      {
        ;/* bereits letztes Listenelement erreicht */
      }

    return( pCell );
  }

//
md_cell *md_list::removeFirstCell( ) /* Erstes Element aus der Liste entnehmen und Pointer auf dieses Element zurueckgeben */
  {
    md_cell *pCell = NULL;

    if ( _pFirst != NULL )   /* wenn noch mind. ein Element in der Liste */
      {
        pCell = _pFirst;
        if ( _pFirst != _pLast )  /* wenn noch nicht letztes Element */
          {
            _pFirst = _pFirst->_pNext;
          }
        else
          {
            _pFirst = _pLast = NULL;
          }
      }
    return( pCell );
  }

/* EOF */
