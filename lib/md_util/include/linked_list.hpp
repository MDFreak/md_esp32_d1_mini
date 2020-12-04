/*************************************************************************
|  Filename..............: linked_list.hpp
 * Project...............: part of standard utilities
 * Autor.................: Martin Dorfner (MD)
 * Date .................: 20.11.2020
 *-----------------------------------------------------------------------
 * Function:
 *   provide linked list support with small footprint
 *-----------------------------------------------------------------------
 * Dependecies:
 *   md_defines.h    (utility intern)
 *   linked_list.cpp implementation
 *-----------------------------------------------------------------------
 * Description:
 *   Primitives for handling linked lists
 *   - only void-pointers are connected with attributes
 *   - no extra memory allocation is done
 *   - derivatives with specified types have to be introduced
 *   goal is small footprint with high performance
 ************************************************************************
 * Version| Date   | Changes                                    | Autor
 *-----------------------------------------------------------------------
 * 0.1.0  |20.11.20| import from former project                 | MD
*-----------------------------------------------------------------------*/

#ifndef _LINKED_LIST_HPP_
  #define _LINKED_LIST_HPP_

  #include <stdlib.h>
  #include <Arduino.h>
  #include <md_defines.h>

  #define DICT_MAX_NAME_LEN 14

  #define MD_DEBUG          TRUE
  #define DICT_DEBUG        TRUE

  // --- base classes md_cell, md_list
    class md_cell           /* Abstrakte Basisklasse fuer Listenelemente */
      {
        protected:
          void* _pNext = NULL;
          void* _pPriv = NULL;             // Pointer auf naechstes Listenelement

        public:
          md_cell();
          ~md_cell();

          void* pNext();
          void* pPriv();
          void  setNext(void* pNext);
          void  setPriv(void* pPriv);
      };

    //
    class md_list
      {
        protected:
          md_cell* _pFirst = NULL;
          md_cell* _pLast  = NULL;
          uint16_t _count  = 0;

        public:
          md_list();  // Konstruktor
          ~md_list();
          uint16_t count (); //return count
          void*    pFirst();
          void*    pLast ();
          uint16_t add   ( void* pCell ); //return count
          uint16_t remove( bool first = FIRST );
        };
  //

#endif
