#include "Map.h"
#include <fstream>
#include "doodle/doodle.hpp"
#include "Guard.h"


void Guard::setup()
{
	guards.clear();


	//guards.push_back(guard_info{ math::ivec2(4, 3) , Direction::UP });
	guards.push_back(guard_info{ math::ivec2(8, 2), Direction::LEFT });
	//guards.push_back(guard_info{ math::ivec2(15, 4), Direction::UP });
	//guards.push_back(guard_info{ math::ivec2(6, 8), Direction::DOWN });
	//guards.push_back(guard_info{ math::ivec2(11,8), Direction::UP });
	//guards.push_back(guard_info{ math::ivec2(14, 8), Direction::RIGHT });
	//guards.push_back(guard_info{ math::ivec2(4, 15), Direction::DOWN });
	//guards.push_back(guard_info{ math::ivec2(7, 16), Direction::UP });
	//guards.push_back(guard_info{ math::ivec2(15, 17), Direction::UP });
	//guards.push_back(guard_info{ math::ivec2(21, 9), Direction::DOWN });
	//guards.push_back(guard_info{ math::ivec2(25, 9), Direction::UP });
	//guards.push_back(guard_info{ math::ivec2(27, 11), Direction::UP });

	set_sight();

}

void Guard::Draw_guard(Camera& camera)
{
	doodle::set_fill_color(255, 0, 0);
	for (auto &p : guards)
	{
		if (p.is_okay == true)
		{
			switch (p.direction)
			{
			case Direction::UP:
				doodle::draw_image(GuardUP_image, (p.position.x + camera.GetPosition().x) * block_size, (p.position.y + camera.GetPosition().y) * block_size, block_size + 10.0, block_size + 10.0);
				break;
			case Direction::DOWN:
				doodle::draw_image(GuardDown_image, (p.position.x + camera.GetPosition().x) * block_size, (p.position.y + camera.GetPosition().y) * block_size, block_size + 10.0, block_size + 10.0);
				break;
			case Direction::RIGHT:
				doodle::draw_image(GuardRight_image, (p.position.x + camera.GetPosition().x) * block_size, (p.position.y + camera.GetPosition().y) * block_size, block_size + 10.0, block_size + 10.0);
				break;
			case Direction::LEFT:
				doodle::draw_image(GuardLeft_image, (p.position.x + camera.GetPosition().x) * block_size, (p.position.y + camera.GetPosition().y) * block_size, block_size + 10.0, block_size + 10.0);
				break;

			}
		}
		else if(p.is_okay == false)
		{
			doodle::draw_image(Guard_CHEW_image, (p.position.x + camera.GetPosition().x) * block_size, (p.position.y + camera.GetPosition().y) * block_size, block_size + 10.0, block_size + 10.0);
		}
		if (p.is_trace == true)
		{
			doodle::draw_image(Guard_tracing_image, (p.position.x + camera.GetPosition().x) * block_size, (p.position.y + camera.GetPosition().y) * block_size, block_size + 10.0, block_size + 10.0);
		}
	}
}

void Guard::Draw_Sight(Camera& camera,Map MAP)
{

	for (auto& guard : guards)
	{
		for (int i = 0; i < sight_size; i++)
		{
			for (auto& m : MAP.map)
			{		
				if (guard.sight_position[i].position.x == m.position.x && guard.sight_position[i].position.y == m.position.y && guard.sight_position[i].is_valid == true )
				{
					if (m.type == Type::road)
					{
						doodle::draw_ellipse((guard.sight_position[i].position.x + camera.GetPosition().x) * block_size + block_size / 2, (guard.sight_position[i].position.y + camera.GetPosition().y) * block_size + block_size / 2, block_size);
					}

					if (m.type != Type::road)
					{
						while (i < sight_size)
						{
							guard.sight_position[i++].is_valid = false;
						}
					}
				}
			}
		}
	}


}
	

void Guard::move(int index)
{
	switch (guards[index].direction)
	{
	case Direction::UP:
		//move up
		if (guards[index].is_okay == true)
		{
			guards[index].position.y--;
		}
		break;

	case Direction::DOWN:   //move down
		if (guards[index].is_okay == true)
		{
			guards[index].position.y++;
		}
		break;

	case Direction::RIGHT:  //move right
		if (guards[index].is_okay == true)
		{
			guards[index].position.x++;
		}
		break;

	case Direction::LEFT:   //move left
		if (guards[index].is_okay == true)
		{
			guards[index].position.x--;
		}
		break;
	}

}

void Guard::change_sight(Map m, int index)
{
	Direction dir;
	bool is_change = false;
	if (guards[index].is_okay == true)
	{
		while (is_change == false)
		{
			dir = static_cast<Direction>(doodle::random(0, 4));
			while (dir == guards[index].direction)
			{
				dir = static_cast<Direction>(doodle::random(0, 4));
			}
			switch (dir)
			{
			case Direction::UP:
			{
				for (auto& j : m.map)
				{
					if (guards[index].position.x == j.position.x && guards[index].position.y - 1 == j.position.y && (j.type != Type::wall))
					{
						guards[index].direction = Direction::UP;
						is_change = true;
					}
				}
			}
			break;
			case Direction::DOWN:
			{
				for (auto& j : m.map)
				{
					if (guards[index].position.x == j.position.x && guards[index].position.y + 1 == j.position.y && (j.type != Type::wall))
					{
						guards[index].direction = Direction::DOWN;
						is_change = true;
					}
				}
			}
			break;
			case Direction::RIGHT:
			{
				for (auto& j : m.map)
				{
					if (guards[index].position.x + 1 == j.position.x && guards[index].position.y == j.position.y && (j.type != Type::wall))
					{
						guards[index].direction = Direction::RIGHT;
						is_change = true;
					}
				}
			}
			break;
			case Direction::LEFT:
			{
				for (auto& j : m.map)
				{
					if (guards[index].position.x - 1 == j.position.x && guards[index].position.y == j.position.y && (j.type != Type::wall))
					{
						guards[index].direction = Direction::LEFT;
						is_change = true;
					}
				}
			}
			break;

			}
		}
	}

}

void Guard::get_dogchew(Map& m, int movement) //개껌먹었을때, 트레이스 트루일때 움직임 계산후 리셋
{
	for (auto& i : guards)
	{
		for (auto& j : m.map)
		{
			if (i.position == j.position && j.type == Type::dog_chew)
			{
				i.is_okay = false;
				i.movement = movement;
				j.type = Type::road;
			}
		}
	}

	for (auto& i : guards)
	{

		if (i.is_okay == false)
		{
			if (movement - i.movement == 3)
			{
				i.is_okay = true;
			}
		}
		if (i.trace_movement == 3)
		{
			i.is_trace = false;
		}
	}

}

void Guard::set_sight()
{
	for (auto& guard : guards)
	{
		for (int i = 0; i < sight_size; i++)
		{
			guard.sight_position[i].is_valid = true;
		}
		switch (guard.direction)
		{
		case Direction::UP:
		{
			for (int i = 0; i < sight_size; i++)
			{
				guard.sight_position[i].position = { guard.position.x,guard.position.y - (i + 1) };
			}
		}
		break;
		case Direction::DOWN:
		{
			for (int i = 0; i < sight_size; i++)
			{
				guard.sight_position[i].position = { guard.position.x,guard.position.y + (i + 1) };
			}
		}
		break;
		case Direction::RIGHT:
		{
			for (int i = 0; i < sight_size; i++)
			{
				guard.sight_position[i].position = { guard.position.x + (i + 1),guard.position.y };
			}
		}
		break;
		case Direction::LEFT:
		{
			for (int i = 0; i < sight_size; i++)
			{
				guard.sight_position[i].position = { guard.position.x - (i + 1),guard.position.y };
			}
		}
		break;
		}
	}
}

int Guard::in_guard_sight(Minsoo minsoo)
{
	for (int i=0; i<static_cast<int>(guards.size()); i++)
	{
		for (int j = 0; j < sight_size; j++)
		{
			if (minsoo.GetPosition() == guards[i].sight_position[j].position)
			{
				return i;
			}
		}
	}
	return -1;
}

