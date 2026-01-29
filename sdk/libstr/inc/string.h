/*
 * Copyright (c) 2026, Ian Moffett.
 * Provided under the BSD-3 clause.
 */

#ifndef _SDK_STRING_H_
#define _SDK_STRING_H_ 1

#include <sys/types.h>
#include <sys/stdarg.h>

/*
 * Returns the length of a string
 *
 * @str: String to get length of
 */
size_t strlen(const char *str);

/*
 * Copy a variable number of bytes from one memory location
 * to another.
 *
 * @dest: Destination buffer
 * @src: Source buffer
 * @count: Byte count
 *
 * Returns the base of `dest' on success
 */
void *memcpy(void *dest, const void *src, size_t count);

/*
 * Fill a memory area with a number of bytes
 *
 * @s: Target memory area
 * @c: Bytes to fill with
 * @n: Number of bytes
 *
 * Returns 's' on success
 */
void *memset(void *s, int c, size_t n);

/*
 * Compare two strings to see if they are equal.
 *
 * @s1: First string
 * @s2: Second string
 *
 * Returns the differences between the two string, zero if
 * equal.
 */
int strcmp(const char *s1, const char *s2);

/*
 * Convert a given value into a string based on a
 * specific radix/base
 *
 * @value: Value to convert
 * @buf: Buffer to copy to
 * @base: Radix
 *
 * Returns `buf' on success
 */
char *itoa(int64_t value, char *buf, int base);

/*
 * Write a formatted string to a buffer
 *
 * @s: Target buffer
 * @size: Maximum buffer size
 * @fmt: Format string
 * @<...>: Args
 */
int snprintf(char *s, size_t size, const char *fmt, ...);

/*
 * Write a formatted string to a buffer using a va_list
 *
 * @s: Target buffer
 * @size: Maximum buffer size
 * @ap: Args pointer
 */
int vsnprintf(char *s, size_t size, const char *fmt, va_list ap);


/*
 * Compare two strings of a given size
 *
 * @s1: First string
 * @s2: Second string
 * @n: Number of bytes max
 */
int memcmp(const void *s1, const void *s2, size_t n);

#endif  /* !_SDK_STRING_H_ */
