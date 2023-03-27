#pragma once

struct SCamera{
	float x , y , z;
	float Xrot, Zrot;
};

void Camera_Apply();

void Camera_Rotation(float xAngle, float zAngle);

void Camera_AutoMoveByMouse(int centerX, int centerY, float speed);

void Camera_MoveDirection(int forwardMove, int rightMove, float speed);