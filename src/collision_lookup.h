#ifndef _COLLISION_LOOKUP_H_
#define _COLLISION_LOOKUP_H_

#include <stdio.h>
#include <collision_lookup.c>

#if __cplusplus
extern "C" {
#endif

void hello(void);

int bottom_collision_1(float x, float y);

int upper_collision_1(float x, float y);

int left_collision_1(float x, float y);

int right_collision_1(float x, float y);

int bottom_collision_2(float x, float y);

int upper_collision_2(float x, float y);

int left_collision_2(float x, float y);

int right_collision_2(float x, float y);

#if __cplusplus
};
#endif

#endif