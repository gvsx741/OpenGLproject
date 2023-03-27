#include <windows.h>
#include <gl/gl.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "camera.h"

 SCamera camera = { 0.0f, 0.0f, 1.7f, 0.0f, 0.0f };

void Camera_Apply() {
	glRotatef(-camera.Xrot, 1, 0, 0);
	glRotatef(-camera.Zrot, 0, 0, 1);
	glTranslatef(-camera.x, -camera.y, -camera.z);
}

void Camera_Rotation(float xAngle, float zAngle) {
	camera.Zrot += zAngle;
	if (camera.Zrot < 0) camera.Zrot += 360;
	if (camera.Zrot > 360) camera.Zrot -= 360;
	camera.Xrot += xAngle;
	if (camera.Xrot < 0) camera.Xrot = 0;
	if (camera.Xrot > 180) camera.Xrot = 180;
}

void Camera_AutoMoveByMouse(int centerX, int centerY, float speed) {
	POINT cur;
	POINT base = { centerX, centerY };
	GetCursorPos(&cur);
	Camera_Rotation((base.y - cur.y) * speed, (base.x - cur.x) * speed);
	SetCursorPos(base.x, base.y);
}

void Camera_MoveDirection(int forwardMove, int rightMove, float speed) {
	float ugol = -camera.Zrot / 180 * M_PI;

	if (forwardMove > 0)
		ugol += rightMove > 0 ? M_PI_4 : (rightMove < 0 ? -M_PI_4 : 0);
	if (forwardMove < 0)
		ugol += M_PI + (rightMove > 0 ? -M_PI_4 : (rightMove < 0 ? M_PI_4 : 0));
	if (forwardMove == 0){
		ugol += rightMove > 0 ? M_PI_2 : -M_PI_2;
		if (rightMove == 0) speed = 0;
	}

	if (speed != 0) {
		camera.x += sin(ugol) * speed;
		camera.y += cos(ugol) * speed;
	}
}