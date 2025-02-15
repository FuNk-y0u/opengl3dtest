#pragma once

#include "../includes.h"

#define glc(x)\
        (\
                gl_clear_error(), \
                x\
        );\
        gl_get_error(#x, __FILE__, __LINE__);\

void gl_clear_error();
int gl_get_error(const char* function, const char* file, int line);