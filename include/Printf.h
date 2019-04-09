#ifndef Printf_h
#define Printf_h
#include <stdarg.h>

int Printf(char *, const void *, const char *, va_list);

/**********************************************************************
 * Writes a character into the buffer unless the buffer is full. Is
 * called by all other functions
 * returns: true if sucessfull
 **********************************************************************/
bool writeCharToBuffer(char **, int, const void *);

/**********************************************************************
 * Writes a string char by char into the buffer
 * returns: true if sucessfull
 **********************************************************************/
bool writeStringToBuffer(char **, char *, const void *);

/**********************************************************************
 * Writes a signed int in the buffer and adds a '-' character
 * if necessary
 * returns: true if sucessfull
 **********************************************************************/
bool writeSignedToBuffer(char **, signed int, const void *);

/**********************************************************************
 * Writes a binary number into the buffer and adds "0b"
 * returns: true if sucessfull
 **********************************************************************/
bool writeBinToBuffer(char **, int, const void *);

/**********************************************************************
 * Writes a hex number into the buffer and adds "0x"
 * returns: true if sucessfull
 **********************************************************************/
bool writeHexToBuffer(char **, int, const void *);

/**********************************************************************
 * takes any number and a base system and writes it into the buffer
 * is called by writeSignedToBuffer, writeBinToBuffer
 * and writeHexToBuffer
 * returns: true if sucessfull
 **********************************************************************/
bool writeConvertedToBuffer(char **, int, int, const void *);

#endif /* Printf_h */
