#pragma once
class Player
{
public:
	Player(olc::PixelGameEngine* pge)
	{
		pos = { float(pge->ScreenWidth() / 2), float(pge->ScreenHeight() / 2) };
		updateLandmarkLocations();
	}

	void processInput(olc::PixelGameEngine* pge)
	{
		delta = { 0, 0 };

		//move left
		if (pge->GetKey(olc::Key::A).bHeld)
		{
			delta.x = -moveSpeed;
		}
		//move right
		if (pge->GetKey(olc::Key::D).bHeld)
		{
			delta.x = moveSpeed;
		}
		//move up
		if (pge->GetKey(olc::Key::W).bHeld)
		{
			delta.y = -moveSpeed;
		}
		//moveDown
		if (pge->GetKey(olc::Key::S).bHeld)
		{
			delta.y = moveSpeed;
		}

		//normalize the delta vector if there is diagonal movement
		if (delta.x != 0 || delta.y != 0)
		{
			//std::cout << "Normalizing" << std::endl;
			float mag = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));
			//std::cout << mag << std::endl;
			delta /= mag;
		}
		//std::cout << delta << std::endl;

	}

	void update(olc::PixelGameEngine* pge, float fElapsedTime)
	{

		//move the player
		pos += delta * moveSpeed * fElapsedTime;

		//update the landmark locations of the player
		updateLandmarkLocations();

		//prevent the player from moving offscreen
		if (fLeft < 0) { pos.x = 0; } //left
		if (fRight >= pge->ScreenWidth()) { pos.x = pge->ScreenWidth() - nSize; } //right
		if (fTop < 0) { pos.y = 0; } //top
		if (fBottom >= pge->ScreenHeight()) { pos.y = pge->ScreenHeight() - nSize; } //bottom

	}

	void draw(olc::PixelGameEngine* pge)
	{
		pge->DrawRect(pos, { nSize, nSize }, olc::BLUE);
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

	float centerX()
	{
		return center.x;
	}

	float centerY()
	{
		return center.y;
	}

private:
	void updateLandmarkLocations()
	{
		fLeft = pos.x;
		fRight = pos.x + nSize;
		fTop = pos.y;
		fBottom = pos.y + nSize;
		center = { pos.x + nSize / 2, pos.y + nSize / 2 };
	}

private:
	//floating-point position vector of the top-left of the player
	olc::vf2d pos;

	//floating-point position vector of the center of the player
	olc::vf2d center;

	//floating-point delta movement vector
	olc::vf2d delta;

	//the x-coordinate of the left edge of the player
	float fLeft;

	//the x-coordinate of the right edge of the player
	float fRight;

	//the y-coorinate of the top of the player
	float fTop;

	//the y-coordinate of the bottom of the player
	float fBottom;

	//constant move speed of the player
	const float moveSpeed = 200;

	//the width and height of the player
	const int nSize = 50;
};

