/*
    Copyright (c) 2013  Steven Mead,
                        School of Computing,
                        University of Teesside,
                        Middlesbrough,
                        UK TS1 3BA
                        email: steven.j.mead@tees.ac.uk

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/

// Check for C++11 compliance using the standard library header.
#include <bits/c++0x_warning.h>

#pragma once


#if !defined    TYPES_HPP
#   define      TYPES_HPP

namespace prg {

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef unsigned long   ulong;

typedef uchar			byte;
typedef ushort			word;
typedef uint			dword;

struct Point2D final {    //primitive 2D coodinate type
    int x_ = 0,
        y_ = 0;

    Point2D() : Point2D( 0, 0 ) {}
    Point2D( int x, int y ) : x_( x ), y_( y ) {}
    Point2D( const Point2D& copy )  : x_( copy.x_ ), y_( copy.y_ ) {}
    Point2D& operator=( const Point2D& copy ) { x_ = copy.x_; y_ = copy.y_; return *this; }
};

template<class T>
T& clamp( T& val, const T& min, const T& max )
{
    if(val < min) val = min;
    else if(val > max) val = max;

    return val;
}

}//namespace prg



#endif // TYPES_HPP
