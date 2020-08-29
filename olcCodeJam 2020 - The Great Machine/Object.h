#pragma once
class Object
{
public:

	Object(float x, float y, olc::Pixel color)
	{
		pos = { x, y };
		objColor = color;
		updateLandmarkLocations();
	}

	void update(olc::PixelGameEngine* pge, float fElapsedTime)
	{
		if (bLeft)
		{
			pos.x += (1.0f);
			bLeft = false;
		}
		if (bRight)
		{
			pos.x -= (1.0f);
			bRight = false;
		}
		if (bTop)
		{
			pos.y += (1.0f);
			bTop = false;
		}
		if (bBottom)
		{
			pos.y -= (1.0f);
			bBottom = false;
		}
	}

	void draw(olc::PixelGameEngine* pge)
	{
		pge->DrawRect(pos, { nSize, nSize }, objColor);
	}

public:

	float left()
	{
		return fLeft;
	}

	float right()
	{
		return fRight;
	}

	float top()
	{
		return fTop;
	}

	float bottom()
	{
		return fBottom;
	}

	void collideLeft()
	{
		bLeft = true;
	}

	void collideRight()
	{
		bRight = true;
	}

	void collideTop()
	{
		bTop = true;
	}

	void collideBottom()
	{
		bBottom = true;
	}

private:
	void updateLandmarkLocations()
	{
		fLeft = pos.x;
		fRight = pos.x + nSize;
		fTop = pos.y;
		fBottom = pos.y + nSize;
	}

private:
	//color of the object
	olc::Pixel objColor;

	//floating-point position vector of the top-left of the object
	olc::vf2d pos;

	//floating-point delta movement vector
	olc::vf2d delta;

	//the x-coordinate of the left edge of the object
	float fLeft;

	//the x-coordinate of the right edge of the object
	float fRight;

	//the y-coorinate of the top of the object
	float fTop;

	//the y-coordinate of the bottom of the object
	float fBottom;

	//the width and height of the player
	const int nSize = 50;

	//boolean flags representing which edge of the object has been collided with
	bool bLeft, bRight, bTop, bBottom;

};

