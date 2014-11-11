#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define VERT_POSITION  0
#define VERT_TEXCOORD  1
#define VERT_NORMAL    2

#define FRAG_OUTPUT0   0

#define TEXTURE_COLOR  0
#define TEXTURE_DEPTH  1

typedef float float2[2];
typedef float float3[3];
typedef float float4[4];

#if defined(_MSC_VER)
typedef __int8           int8_t;
typedef unsigned __int8  uint8_t;
typedef __int16          int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32          int32_t;
typedef unsigned __int32 uint32_t;

// ������� MSVC �� ����� ��� snprintf, �� ��� ���� _snprintf
#define snprintf _snprintf

#elif defined(__MINGW32__)
#include <stdint.h>

#else
#error You must compile this code with MSVC or MinGW!
#endif

// �������� ����� ������� � ������
bool LoadFile(const char *fileName, bool binary, uint8_t **buffer, uint32_t *size);

#endif /* COMMON_H */
