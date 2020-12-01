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

  class md_cell           /* Abstrakte Basisklasse fuer Listenelemente */
    {
      protected:
        md_cell    *_pNext;             // Pointer auf naechstes Listenelement

        md_cell();   // Konstruktor

      public:
        friend class md_list;
    };

  //
  class md_list
    {
      private:
        md_cell     *_pFirst;
        md_cell     *_pLast;

      public:
        md_list();  // Konstruktor
        ~md_list();
        void      append( md_cell *pCell );      // An Ende anhaengen
        md_cell*  getCellPointer( unsigned short index ); // Pointer auf ein Listenelement holen
        md_cell*  getNextCellPointer( md_cell *pCell ); /* Pointer auf das naechste Listenelement holen */
        md_cell*  removeFirstCell(); /* Erstes Element aus der Liste entnehmen und Pointer auf dieses Element zurueckgeben */

    };

#endif
