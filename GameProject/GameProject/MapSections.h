#ifndef MAPSECTIONS_H
#define MAPSECTIONS_H

//these are full map structures that will have sections placed inside
#define SECTST_CELLS 2
#define SECTST_SIZE 3
#define SECT_START "1,1"

#define SECT1_CELLS 3
#define SECT1_SIZE 24
#define SECT1_A "1,1n\
                 1,1"
#define SECT1_B "1,1n\
                 1,0"
#define SECT1_C "1,0n\
                 1,1"
#define SECT1_D "0,1n\
                 1,1"
#define SECT1_E "1,1n\
                 0,1"

#define SECT2_CELLS 4
#define SECT2_SIZE 28
#define SECT2_A "1,1,1n\
                 0,1,0"
#define SECT2_B "0,1,0n\
                 1,1,1"
#define SECT2_C "1,0,1n\
                 1,1,1"
#define SECT2_D "0,0,1n\
                 1,1,1"
#define SECT2_E "1,0,0n\
                 1,1,1"

#define SECT3_CELLS 7
#define SECT3_SIZE 45
#define SECT3_A "0,1,1,0n\
                 1,1,1,1n\
				 0,1,1,0"
#define SECT3_B "1,1,1,0n\
                 0,1,1,1n\
				 0,1,0,0"
#define SECT3_C "0,1,1,1n\
                 1,1,1,0n\
				 0,0,1,0"
#define SECT3_D "1,1,1,1n\
                 1,1,1,1n\
				 0,0,0,0"

#define SECT3_E "1,1,1,0n\
                 0,1,1,1n\
				 1,1,1,0"

#endif // !MAPSECTIONS_H