#pragma once

struct Vector3f
{
	float x, y, z;
	Vector3f(float inx, float iny, float inz): x(inx), y(iny) , z(inz)
	{
	}

	Vector3f operator+(Vector3f& v){
		//this->x + v.x;
	}
};



class Planets3D
{
	//cameraMatrix
};

