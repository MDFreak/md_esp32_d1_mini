/*************************************************************************
|  Filename..............: dict_list.hpp
 * Project...............: part of standard utilities
 * Autor.................: Martin Dorfner (MD)
 * Date .................: 20.11.2020
 *-----------------------------------------------------------------------
 * Function:
 *   provide dictionary
 *-----------------------------------------------------------------------
 * Dependecies:
 *   md_defines.h    (utility intern)
 *   linked_list.hpp base class
 ************************************************************************
 * Version| Date   | Changes                                    | Autor
 *-----------------------------------------------------------------------
 * 0.1.0  |20.11.20| import from former project                 | MD
*-----------------------------------------------------------------------*/

#ifndef _DICT_LIST_HPP_
  #define _DICT_LIST_HPP_

  #include <stdlib.h>
  #include <Arduino.h>
  #include <md_defines.h>
  #include <linked_list.hpp>

  //
  // --- dictionary classes dict_cell, dict_list
    class dict_cell : public md_cell
      {
        private:
          int16_t  _idx = (int16_t) NN;
          char     _name[DICT_MAX_NAME_LEN+1] = "";

        public:
          dict_cell() {}
          ~dict_cell() {}

          void    init   (int16_t idx, const char name[DICT_MAX_NAME_LEN]);
          int16_t getIdx ()             { return _idx; }
          void    getName(char* pname)  { strcpy( pname, _name); }
          void    setIdx (int16_t idx)  { _idx = idx; }
          void    setName(const char name[DICT_MAX_NAME_LEN]);
      };

    //
    class dict_list : public md_list
      {
        private:
          dict_cell* _pFirst;
          dict_cell* _pLast;

        public:
          dict_list();
          ~dict_list();

          void    append( int16_t idx, const char name[DICT_MAX_NAME_LEN]);
          int16_t getIdx (const char name[DICT_MAX_NAME_LEN]);
          void    getName(int16_t idx, char* pname);
          void    setIdx (const char name[DICT_MAX_NAME_LEN], int16_t idx);
          void    setName(int16_t idx, const char name[DICT_MAX_NAME_LEN]);
          dict_cell* getCellPointer( unsigned short index);
          dict_cell* getNextCellPointer( dict_cell* pCell );

        protected:
          dict_cell* _findCell(int16_t idx);
          dict_cell* _findCell(const char name[]);

      };

#endif
