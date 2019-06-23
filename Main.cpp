#include<iostream>
#include"CoreSystems/Math/Vector3.h"
#include"CoreSystems/Math/Vector4.h"
#include"CoreSystems/Math/Math.h"
#include"CoreSystems/Math/Matrix3.h"
#include"CoreSystems/Math/AABB.h"

int main()
{
	AABB aabb(Vector3(-1.0f, -10.0f, -0.5f), Vector3(1.0f, 10.0f, 0.5f));
	Vector3 vector(-1.0f, -10.0f, -0.5f);
	Matrix3 rotation = Matrix3::CreateRotation(PI/4.0f, Vector3(0.0f, 1.0f, 0.0f));
	AABB newAABB = aabb.Transform(rotation, Vector3(0.0f));
	newAABB.min.Print();
	std::cout << "\n";
	newAABB.max.Print();
	std::cout << "\n";
	system("pause");
}