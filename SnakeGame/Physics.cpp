#include "Physics.h"
#include <iostream>
#include <cmath>


void Physics::CalculateAAndAddToTheta(float XA, float YA, float XB, float YB)
{
	//gets the angle used for rotation.
	PivotPoint VecOfR = { XA - XB, YA - YB };
	float RY = VecOfR.Y;
	R = sqrt((VecOfR.X * VecOfR.X) + (VecOfR.Y * VecOfR.Y));
	float A = Q * (size_t)FG * RY / R;
	ThetaA = Theta + A;
}

void Physics::RotateTopPointRight(float XA, float YA, float& XB, float& YB)
{
	//rotates the ship right depending on angle.
	const float PI(3.14159265359);
	const float ChangedTheta = (ThetaA * PI) / 180;

	float CosO = cos(ChangedTheta);
	float SinO = sin(ChangedTheta);

	float XBT = XB - XA;
	float YBT = YB - YA;

	XB = (XBT * CosO) - (YBT * SinO) + XA;
	YB = (XBT * SinO) + (YBT * CosO) + YA;
}

void Physics::RotateTopPointLeft(float XA, float YA, float& XB, float& YB)
{
	//rotates the ship left depending on angle.
	const float PI(3.14159265359);
	const float ChangedTheta = -(ThetaA * PI) / 180;

	float CosO = cos(ChangedTheta);
	float SinO = sin(ChangedTheta);

	float XBT = XB - XA;
	float YBT = YB - YA;

	XB = (XBT * CosO) - (YBT * SinO) + XA;
	YB = (XBT * SinO) + (YBT * CosO) + YA;
}

void Physics::Thrust(int Rotate, float& XMovement, float& YMovement, float DT)
{
	//stores the x and y momenton of ship and adds and takes from it depending on angle.
	if (Rotate == -56)
	{
		XCheck = 1.8 * DT;

		if (XCheck < 0 || XCheck > 2.8)
		{
			XCheck = 1.8;
		}

		XMovement -= XCheck;
	}
	else if (Rotate < -49)
	{
		XCheck = 1.6 * DT;
		YCheck = 0.2 * DT;

		if (XCheck < 0 || XCheck > 2.6)
		{
			XCheck = 1.6;
		}
		if (YCheck < 0 || YCheck > 1.2)
		{
			YCheck = 0.2;
		}

		XMovement -= XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < -42)
	{
		XCheck = 1.4 * DT;
		YCheck = 0.4 * DT;

		if (XCheck < 0 || XCheck > 2.4)
		{
			XCheck = 1.4;
		}
		if (YCheck < 0 || YCheck > 1.4)
		{
			YCheck = 0.4;
		}

		XMovement -= XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < -35)
	{
		XCheck = 1.2 * DT;
		YCheck = 0.6 * DT;

		if (XCheck < 0 || XCheck > 2.2)
		{
			XCheck = 1.2;
		}
		if (YCheck < 0 || YCheck > 1.6)
		{
			YCheck = 0.6;
		}

		XMovement -= XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < -28)
	{
		XCheck = 1 * DT;
		YCheck = 0.8 * DT;

		if (XCheck < 0 || XCheck > 2)
		{
			XCheck = 1;
		}
		if (YCheck < 0 || YCheck > 1.8)
		{
			YCheck = 0.8;
		}

		XMovement -= XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < -21)
	{
		XCheck = 0.8 * DT;
		YCheck = 1 * DT;

		if (XCheck < 0 || XCheck > 1.8)
		{
			XCheck = 0.8;
		}
		if (YCheck < 0 || YCheck > 2)
		{
			YCheck = 1;
		}

		XMovement -= XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < -14)
	{
		XCheck = 0.6 * DT;
		YCheck = 1.2 * DT;

		if (XCheck < 0 || XCheck > 1.6)
		{
			XCheck = 0.6;
		}
		if (YCheck < 0 || YCheck > 2.2)
		{
			YCheck = 1.2;
		}

		XMovement -= XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < -7)
	{
		XCheck = 0.4 * DT;
		YCheck = 1.4 * DT;

		if (XCheck < 0 || XCheck > 1.4)
		{
			XCheck = 0.4;
		}
		if (YCheck < 0 || YCheck > 2.4)
		{
			YCheck = 1.4;
		}

		XMovement -= XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < 0)
	{
		XCheck = 0.2 * DT;
		YCheck = 1.6 * DT;

		if (XCheck < 0 || XCheck > 1.2)
		{
			XCheck = 0.2;
		}
		if (YCheck < 0 || YCheck > 2.6)
		{
			YCheck = 1.6;
		}

		XMovement -= XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate == 0)
	{
		YCheck = 1.8 * DT;

		if (YCheck < 0 || YCheck > 2.8)
		{
			YCheck = 1.8;
		}

		YMovement -= YCheck;
	}
	else if (Rotate < 7)
	{
		XCheck = 0.2 * DT;
		YCheck = 1.6 * DT;

		if (XCheck < 0 || XCheck > 1.2)
		{
			XCheck = 0.2;
		}
		if (YCheck < 0 || YCheck > 2.6)
		{
			YCheck = 1.6;
		}

		XMovement += XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < 14)
	{
		XCheck = 0.4 * DT;
		YCheck = 1.4 * DT;

		if (XCheck < 0 || XCheck > 1.4)
		{
			XCheck = 0.4;
		}
		if (YCheck < 0 || YCheck > 2.4)
		{
			YCheck = 1.4;
		}

		XMovement += XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < 21)
	{
		XCheck = 0.6 * DT;
		YCheck = 1.2 * DT;

		if (XCheck < 0 || XCheck > 1.6)
		{
			XCheck = 0.6;
		}
		if (YCheck < 0 || YCheck > 2.2)
		{
			YCheck = 1.2;
		}

		XMovement += XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < 28)
	{
		XCheck = 0.8 * DT;
		YCheck = 1 * DT;

		if (XCheck < 0 || XCheck > 1.8)
		{
			XCheck = 0.8;
		}
		if (YCheck < 0 || YCheck > 2)
		{
			YCheck = 1;
		}

		XMovement += XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < 35)
	{
		XCheck = 1 * DT;
		YCheck = 0.8 * DT;

		if (XCheck < 0 || XCheck > 2)
		{
			XCheck = 1;
		}
		if (YCheck < 0 || YCheck > 1.8)
		{
			YCheck = 0.8;
		}

		XMovement += XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < 42)
	{
		XCheck = 1.2 * DT;
		YCheck = 0.6 * DT;

		if (XCheck < 0 || XCheck > 2.2)
		{
			XCheck = 1.2;
		}
		if (YCheck < 0 || YCheck > 1.6)
		{
			YCheck = 0.6;
		}

		XMovement += XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < 49)
	{
		XCheck = 1.4 * DT;
		YCheck = 0.4 * DT;

		if (XCheck < 0 || XCheck > 2.4)
		{
			XCheck = 1.4;
		}
		if (YCheck < 0 || YCheck > 1.2)
		{
			YCheck = 0.4;
		}

		XMovement += XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate < 56)
	{
		XCheck = 1.6 * DT;
		YCheck = 0.2 * DT;

		if (XCheck < 0 || XCheck > 2.6)
		{
			XCheck = 1.6;
		}
		if (YCheck < 0 || YCheck > 1)
		{
			YCheck = 0.2;
		}

		XMovement += XCheck;
		YMovement -= YCheck;
	}
	else if (Rotate == 56)
	{
		XCheck = 1.8 * DT;

		if (XCheck < 0 || XCheck > 2.8)
		{
			XCheck = 1.8;
		}

		XMovement += XCheck;
	}
}


