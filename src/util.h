#ifndef __UTIL_H__
#define __UTIL_H__

void swap (int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

#endif // __UTIL_H__