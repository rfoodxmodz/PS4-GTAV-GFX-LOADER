#include "global.h"

#include "imports.h"
#include "utility.h"

int userId = -1;
int userPadHandle = -1;

signed char ClampChar(int i) {
	if (i < -128)
		return -128;

	if (i > 127)
		return 127;

	return i;
}

double deg2rad(float degrees) {
	return degrees * (MATH_PI / 180.0f);
}

float Distance(float *one, float *two) {
	double temp = sqrt(
		pow((double)(one[0] - two[0]), 2) +
		pow((double)(one[1] - two[1]), 2) +
		pow((double)(one[2] - two[2]), 2));

	return (float)temp;
}

void VectorToAngles(float forward[], float angles[]) {
	float tmp, yaw, pitch;

	if (forward[0] == 0 && forward[1] == 0) {
		yaw = 0;

		if (forward[2] > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else {
		if (forward[0])
			yaw = (atan2(forward[1], forward[0]) * 180 / MATH_PI);
		else if (forward[1] > 0)
			yaw = 90;
		else
			yaw = 270;

		if (yaw < 0)
			yaw += 360;

		tmp = sqrt((forward[0] * forward[0]) + (forward[1] * forward[1]));
		pitch = atan2(forward[2], tmp) * 180 / MATH_PI;

		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = -pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
