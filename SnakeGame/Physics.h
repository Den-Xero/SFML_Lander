#ifndef PHYSICS_H
#define PHYSICS_H
#include "PivotPoint.h"
class Physics
{
	private:
		/*struct PivotPoint
		{
			float X, Y;
		};*/
		float Theta{ 1.0255 };
		float Q{ 1 };
		float FG{ 1 };
		float R{ 1 };
		float ThetaA{ 0 };
		float XCheck{ 0 };
		float YCheck{ 0 };
	public:
		void CalculateAAndAddToTheta(float XA, float YA, float XB, float YB);

		void RotateTopPointRight(float XA, float YA, float& XB, float& YB);

		void RotateTopPointLeft(float XA, float YA, float& XB, float& YB);

		void Thrust(int Rotate, float& XMovement, float& YMovement, float DT);
};
#endif

