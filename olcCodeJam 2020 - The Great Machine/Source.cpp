#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Object.h"

class TheGreatMachine : public olc::PixelGameEngine
{
private:
	Player* player;

	std::vector<Object> objects;

public:
	TheGreatMachine()
	{
		sAppName = "The Great Machine";
	}

public:
	bool OnUserCreate() override
	{
		player = new Player(this);
		objects.push_back(Object(20, 20, olc::DARK_GREEN));
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//clear the screen
		Clear(olc::WHITE);

		//process input
		player->processInput(this);

		//update
		player->update(this, fElapsedTime);
		for (Object obj : objects)
		{
			if (player->left() <= obj.right() && (player->top() < obj.bottom() && player->bottom() > obj.top()))
			{
				std::cout << "collide" << std::endl;
				obj.collideRight();
			}

			obj.update(this, fElapsedTime);
		}

		//draw
		player->draw(this);
		for (Object obj : objects)
		{
			obj.draw(this);
		}

		return true;
	}
};

int main()
{
	TheGreatMachine tgm;
	if (tgm.Construct(640, 480, 1, 1))
	{
		tgm.Start();
	}

	return 0;
}