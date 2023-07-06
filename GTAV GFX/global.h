#pragma once

#include "types.h"

#define NAMESPACE(x) namespace x {
#define END }
#define MATH_PI 3.14159265358979323846
#define AngleToShort(X) ((int)((X)*65536 / 360) & 65535)
extern int userId;
extern int userPadHandle;
signed char ClampChar(int i);
double deg2rad(float degrees);
float Distance(float *one, float *two);
void VectorToAngles(float forward[], float angles[]);
