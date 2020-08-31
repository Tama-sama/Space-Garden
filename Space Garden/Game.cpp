#include "Game.hpp"
#include "Texture_SpriteManager.hpp"
#include "SoundManager.hpp"
#include "Window.hpp"
#include "Menu.hpp"

#include "Buffs.hpp"
#include "Ennemies.hpp"
#include "EnnemiesShoots.hpp"
#include "Explosion.hpp"
#include "Controles.hpp"

#define SIZE_BUFFS 30
#define RADIUS_PLAYER_SHOOT 10
#define RADIUS_ENNEMIES_SHOOT 9
#define RADIUS_ENNEMIES 45


void RemoveDeadPlayerShoots()
{
	bool shootRemove = true;
	while (shootRemove)
	{
		shootRemove = false;
		for (PlayerBullet& ActualShoot : Bullets)
		{
			if (ActualShoot.getLife() <= 0)
			{
				shootRemove = true;
				Bullets.remove(ActualShoot);

				break;
			}
		}
	}
}
void RemoveDeadBuffs()
{
	bool BuffRemove = true;
	while (BuffRemove)
	{
		BuffRemove = false;
		for (Buffs& ActualBuff : BuffsList)
		{
			if (!ActualBuff.Exist())
			{
				BuffRemove = true;
				BuffsList.remove(ActualBuff);
				break;
			}
		}

	}
}

void BuffsCollisions(Player& _Player)
{
	for (Buffs& ActualBuff : BuffsList)
	{
		if (_Player.getLife() > 0)
		{
			sf::RectangleShape BuffsHitBox(sf::Vector2f(SIZE_BUFFS, SIZE_BUFFS));
			BuffsHitBox.setOrigin(SIZE_BUFFS / 2, SIZE_BUFFS / 2);
			BuffsHitBox.setPosition(ActualBuff.getpos());

			getSprite(_Player.getShip()).setPosition(_Player.getPosition());

			if (BuffsHitBox.getGlobalBounds().intersects(getSprite(_Player.getShip()).getGlobalBounds()))
			{
				if (ActualBuff.Exist())
				{
					if (ActualBuff.getType() == 1)
					{
						if (_Player.getAtkPoints() < 10)
							_Player.addAtkPoint();
					}

					if (ActualBuff.getType() == 2)
					{
						_Player.addScore(10);
					}

					if (ActualBuff.getType() == 3)
					{
						if (_Player.getLife() < 3)
							_Player.Heal();
					}

					if (ActualBuff.getType() == 4)
					{
						_Player.addPissenlitShoot();
					}

					if (ActualBuff.getType() == 5)
					{
						_Player.addSinShoot();
					}

					ActualBuff.Kill();
				}
			}
		}
	}
}
void PlayerShootsColisions()
{
	for (PlayerBullet& ActualShoot : Bullets)
	{
		ActualShoot.Update();

		for (Ennemies& ActualEnnemie : ennemies)
		{
			if (Circle_Collision(ActualShoot.Pos(), ActualEnnemie.getPos(), RADIUS_PLAYER_SHOOT, RADIUS_ENNEMIES))
			{
				if (ActualShoot.getLife() > 0 && ActualEnnemie.getLife() > 0)
				{
					ActualEnnemie.TakeDamage(ActualShoot.getDamages());
					ActualShoot.TakeDamage();

					if (ActualShoot.getOwner() == 1)
					{
						Player1.addScore(10);
					}
					else
					{
						Player2.addScore(10);
					}

					if (ActualShoot.getType() == 2)
					{
						for (int i = 0; i < 16; i++)
						{
							float Dir_Tir = (i * (pi / 8));

							Bullets.push_back(PlayerBullet(sf::Vector2f(ActualShoot.Pos().x, ActualShoot.Pos().y), 3, ActualShoot.getOwner(), 1, Dir_Tir));
						}
					}

					if (ActualEnnemie.getLife() <= 0)
					{
						Explosions.push_back(Explosion(ActualEnnemie.getPos(), ActualEnnemie.getType()));

						if (state == State::GAME)
						{
							getSound("explosions").play();
							if (rand() % 100 + 1 <= 70)
							{
								if (rand() % 100 + 1 <= 65)
								{
									BuffsList.push_back(Buffs(1, ActualEnnemie.getPos()));
								}
								else
								{
									BuffsList.push_back(Buffs(2, ActualEnnemie.getPos()));
								}
							}
						}
					}

					break;
				}
			}
		}

		if (ActualShoot.getType() == 3 && ActualShoot.getLife() > 0 && ActualShoot.getTimer() > 4.f)
		{
			ActualShoot.TakeDamage();
		}
	}
}
void EnnemiesPlayerCollision(Player& _Player)
{
	for (Ennemies& Actualennemies : ennemies)
	{
		if (Actualennemies.getLife() > 0 && _Player.getLife() > 0 && !_Player.isInvulnerable())
		{
			getSprite(_Player.getShip()).setPosition(_Player.getPosition());

			sf::Vector2f PlayerSize(getSprite(_Player.getShip()).getGlobalBounds().width , getSprite(_Player.getShip()).getGlobalBounds().height);
			sf::Vector2f PlayerPos(_Player.getPosition().x - PlayerSize.x / 2, _Player.getPosition().y - PlayerSize.y / 2);

			if (Circle_Rect_Collision(Actualennemies.getPos(), PlayerPos, RADIUS_ENNEMIES, PlayerSize))
			{
				Actualennemies.TakeDamage(Actualennemies.getLife());
				_Player.TakeDamage(1);
				getSound("player_damage").play();
			}
		}
	}
}
void EnnemiesShootPlayerCollision(Player& _Player)
{
	for (EnnemiesShoots& ActualEnnemiesShoot : EnnemiesShootsList)
	{
		if (ActualEnnemiesShoot.getLife() > 0 && _Player.getLife() > 0 && !_Player.isInvulnerable())
		{
			getSprite(_Player.getShip()).setPosition(_Player.getPosition());

			sf::Vector2f PlayerSize(getSprite(_Player.getShip()).getGlobalBounds().width, getSprite(_Player.getShip()).getGlobalBounds().height);
			sf::Vector2f PlayerPos(_Player.getPosition().x - PlayerSize.x / 2, _Player.getPosition().y - PlayerSize.y / 2);

			if (Circle_Rect_Collision(ActualEnnemiesShoot.getpos(), PlayerPos, RADIUS_ENNEMIES_SHOOT, PlayerSize))
			{
				ActualEnnemiesShoot.TakeDamage();
				_Player.TakeDamage(1);
				getSound("player_damage").play();
			}
		}
	}
}

void RemoveDeadEnnemies()
{
	bool EnnemiesRemove = true;
	while (EnnemiesRemove)
	{
		EnnemiesRemove = false;
		for (Ennemies& ActualEnnemie : ennemies)
		{
			if (ActualEnnemie.getLife() <= 0)
			{
				ennemies.remove(ActualEnnemie);
				EnnemiesRemove = true;
				break;
			}
		}
	}
}
void RemoveDeadEnnemiesShoots()
{
	bool EnnemiesShootsRemove = true;
	while (EnnemiesShootsRemove)
	{
		EnnemiesShootsRemove = false;
		for (EnnemiesShoots& ActualEnnemieShoot : EnnemiesShootsList)
		{
			if (ActualEnnemieShoot.getLife() <= 0)
			{
				EnnemiesShootsList.remove(ActualEnnemieShoot);
				EnnemiesShootsRemove = true;
				break;
			}
		}
	}
}
void RemoveDeadExplosions()
{
	bool ExplosionRemove = true;
	while (ExplosionRemove)
	{
		ExplosionRemove = false;
		for (Explosion& ActualExplosion : Explosions)
		{
			if (ActualExplosion.getLife() <= 0)
			{
				Explosions.remove(ActualExplosion);
				ExplosionRemove = true;
				break;
			}
		}
	}
}


Player Player1(sf::Vector2f(1920 / 2, 900), 1, 1);
Player Player2(sf::Vector2f(1920 / 1.3f, 900), 1, 2);
bool SoloGame = true;
bool isPause = false;
int IgMenu_Choice = 0;
bool IgMenu_Options = false;

int _game_phase = 0;
float Game_timer = 0;
///////////////////////////////////////////
// Boucle scripter de jeux jusqu'au boss //
///////////////////////////////////////////
void ennemies_Loop_1P()
{
	Game_timer += MainTime.GetTimeDeltaF();

	/*if (*_game_phase == -1)
	{
		if (sfMusic_getStatus(Game_music.music) == sfStopped)
		{
			sfMusic_stop(Menu_music.music);
			sfMusic_stop(Boss_music.music);
			sfMusic_play(Game_music.music);
			sfMusic_setLoop(Game_music.music, sfTrue);
		}
		*_game_phase += 1;
		Game_timer = 0;
	}*/
	if (_game_phase == 0)
	{
		if (Game_timer >= 2)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 50), 1));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 50), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 1)
	{
		if (Game_timer >= 1)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 50), 1));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 50), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 2)
	{
		if (Game_timer >= 6)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 350), 3));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 350), 4));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 3)
	{
		 _game_phase += 1;
		Game_timer = 0;

	}
	else if ( _game_phase == 4)
	{
		if (Game_timer >= 5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(660, 0), 5));
			ennemies.push_back(Ennemies(sf::Vector2f(1260, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 5)
	{
		if (Game_timer >= 2.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(780, 0), 5));
			ennemies.push_back(Ennemies(sf::Vector2f(1140, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 6)
	{
		if (Game_timer >= 4.25)
		{
			BuffsList.push_back(Buffs(3, sf::Vector2f(970, -25)));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 7)
	{
		if (Game_timer >= 5.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 0), 1));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 0), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 8)
	{
		if (Game_timer >= 2.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 0), 1));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 0), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 9)
	{

		 _game_phase += 1;
		Game_timer = 0;

	}
	else if ( _game_phase == 10)
	{
		if (Game_timer >= 6)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(190, 250), 3));
			ennemies.push_back(Ennemies(sf::Vector2f(1732, 250), 4));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 11)
	{
		if (Game_timer >= 5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(630, -25), 6));
			ennemies.push_back(Ennemies(sf::Vector2f(1310, -25), 7));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 12)
	{
		if (Game_timer >= 6)
		{
			//ennemies.push_back(Ennemies(sf::Vector2f(780, -30), 4)); // it is not where it need to be
			//ennemies.push_back(Ennemies(sf::Vector2f(1140, -30), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 13)
	{
		if (Game_timer >= 8)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, -50), 1));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, -50), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 14)
	{
		if (Game_timer >= 5.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 400), 3));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 400), 4));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 15)
	{
		if (Game_timer >= 5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(640, 0), 5));
			ennemies.push_back(Ennemies(sf::Vector2f(1280, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 16)
	{
		if (Game_timer >= 4)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(840, 0), 5));
			ennemies.push_back(Ennemies(sf::Vector2f(1080, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 17)
	{
		if (Game_timer >= 2.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 350), 3));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 350), 4));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 18)
	{
		if (Game_timer >= 2.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(630, 0), 6));
			ennemies.push_back(Ennemies(sf::Vector2f(1310, 0), 7));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 19)
	{
		if (Game_timer >= 5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, -50), 1));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, -50), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 20)
	{
		if (Game_timer >= 3.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(640, -25), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 21)
	{
		if (Game_timer >= 0.75)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(1280, -25), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 22)
	{
		if (Game_timer >= 5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(110, 350), 3));
			ennemies.push_back(Ennemies(sf::Vector2f(1782, 350), 4));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 23)
	{
		if (Game_timer >= 4)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 250), 3));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 250), 4));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 24)
	{
		if (Game_timer >= 7)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, -50), 1));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, -50), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 25)
	{
		if (Game_timer >= 1.25)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(190, -25), 1));
			ennemies.push_back(Ennemies(sf::Vector2f(1732, -25), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 26)
	{
		if (Game_timer >= 5.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 300), 3));
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 300), 4));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 27)
	{
		if (Game_timer >= 6.5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(760, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 28)
	{
		if (Game_timer >= 1)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(1160, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 29)
	{
		if (Game_timer >= 2)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(890, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 30)
	{
		if (Game_timer >= 1)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(1030, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 31)
	{
		if (Game_timer >= 5)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(630, -25), 6));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 32)
	{
		if (Game_timer >= 3)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(1310, -25), 7));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 33)
	{
		if (Game_timer >= 3)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 25), 1));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 34)
	{
		if (Game_timer >= 2)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 25), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 35)
	{
		if (Game_timer >= 2)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(340, 0), 1));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 36)
	{
		if (Game_timer >= 2)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(1582, 0), 2));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 37)
	{
		if (Game_timer >= 4)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(290, 400), 3));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 38)
	{
		if (Game_timer >= 1)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(1632, 400), 4));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 39)
	{
		if (Game_timer >= 6)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(790, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 40)
	{
		if (Game_timer >= 1)
		{
			ennemies.push_back(Ennemies(sf::Vector2f(1130, 0), 5));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	else if ( _game_phase == 41)
	{
		if (Game_timer >= 3)
		{
			//ennemies.push_back(Ennemies(sf::Vector2f(960, -30), 3));
			 _game_phase += 1;
			Game_timer = 0;
		}
	}
	//else if ( _game_phase == 42)
	//{
	//	if (sfMusic_getStatus(Boss_music.music) == sfStopped)
	//	{
	//		sfMusic_stop(Menu_music.music);
	//		sfMusic_stop(Game_music.music);
	//		sfMusic_play(Boss_music.music);
	//		sfMusic_setLoop(Boss_music.music, sfTrue);
	//	}


	//	static sfBool boss_spawn = sfFalse;
	//	if (Game_timer >= 7 && !boss_spawn)
	//	{
	//		PrepareBOSS();
	//		boss_spawn = sfTrue;
	//	}
	//	if (Game_timer >= 10 && boss_spawn)
	//	{
	//		int boss_is_alive = 0;
	//		BOSS  tempboss;
	//		tempboss = BOSSDepart;
	//		while (tempboss)
	//		{
	//			boss_is_alive++;
	//			tempboss = tempboss->Suivant;
	//		}

	//		if (boss_is_alive == 0)
	//		{
	//			sfMusic_stop(Boss_music.music);
	//			sfMusic_play(Game_music.music);
	//			sfMusic_setLoop(Game_music.music, sfTrue);
	//			boss_spawn = sfFalse;
	//			 _game_phase += 1;
	//			Game_timer = 0;
	//		}
	//	}
	//}
	//else if ( _game_phase == 43)
	//{
	//	static int type_2 = 0;
	//	static int type_3 = 0;
	//	static int type_4 = 0;
	//	static int type_5 = 0;
	//	static float Last_spawxX = 0;
	//	static float Last_spawxX2 = 0;
	//	static float spawn_speed = 2;
	//	if (Game_timer >= spawn_speed)
	//	{
	//		float randX = rand() % 1300 + 300; // 300 - 1600
	//		while (randX > Last_spawxX - 100 && randX < Last_spawxX + 100 && randX > Last_spawxX2 - 100 && randX < Last_spawxX2 + 100)
	//			randX = rand() % 1300 + 300; // 300 - 1600

	//		PrepareMonstre1((sfVector2f) { randX, 0 }, 5);
	//		Last_spawxX2 = Last_spawxX;
	//		Last_spawxX = randX;

	//		type_2++;
	//		type_3++;
	//		type_4++;
	//		type_5++;

	//		if (spawn_speed > 1.25)
	//			spawn_speed -= 0.05;

	//		if (type_2 == 4)
	//		{
	//			if (rand() % 2 + 1 == 1)
	//				PrepareMonstre1((sfVector2f) { 290, 425 }, 3);
	//			else
	//				PrepareMonstre1((sfVector2f) { 1632, 425 }, 4);
	//			type_2 = 0;
	//		}
	//		if (type_3 == 6)
	//		{
	//			if (rand() % 2 + 1 == 1)
	//				PrepareMonstre1((sfVector2f) { 290, 25 }, 1);
	//			else
	//				PrepareMonstre1((sfVector2f) { 1632, 25 }, 2);
	//			type_3 = 0;
	//		}
	//		if (type_4 == 8)
	//		{
	//			if (rand() % 2 + 1 == 1)
	//				PrepareMonstre1((sfVector2f) { 630, -25 }, 6);
	//			else
	//				PrepareMonstre1((sfVector2f) { 1310, -25 }, 7);
	//			type_4 = 0;
	//		}
	//		if (type_5 >= 15)
	//		{
	//			int temprand = rand() % 100 + 1;
	//			if (temprand >= 75)
	//				prepareBuff((sfVector2f) { 960, -20 }, 3);
	//			else if (temprand >= 55 && temprand < 75)
	//				prepareBuff((sfVector2f) { 960, -20 }, 4);
	//			else if (temprand >= 35 && temprand < 55)
	//				prepareBuff((sfVector2f) { 960, -20 }, 5);
	//			type_5 = 0;
	//		}


	//		Game_timer = 0;
	//	}
	//}
}

void ennemies_patern()
{
	for (Ennemies& ActualEnnemie : ennemies)
	{
		ActualEnnemie.addTimer(MainTime.GetTimeDeltaF());

		if (ActualEnnemie.getType() == 1)
		{
			if (ActualEnnemie.getPhase() == 0)
			{
				ActualEnnemie.getSprite().setRotation(135);
				ActualEnnemie.setDelta(225, 150);
				if (ActualEnnemie.getTimer() > 2)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 2, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 2);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setPhase(1);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 1)
			{
				if (ActualEnnemie.getSprite().getRotation() < 180 && ActualEnnemie.getTimer() > 0.2)
					ActualEnnemie.getSprite().rotate(140 * MainTime.GetTimeDeltaF());

				if (ActualEnnemie.getTimer() > 0.5)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 0.5, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 0.5);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.getSprite().setRotation(180);
					ActualEnnemie.setDelta(0, 0);
					ActualEnnemie.setPhase(2);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 2)
			{
				if (ActualEnnemie.getTimer() > 0.2)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(3);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 3)
			{
				if (ActualEnnemie.getTimer() > 0.3)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(4);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 4)
			{
				if (ActualEnnemie.getTimer() > 1.2)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(5);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 5)
			{
				if (ActualEnnemie.getTimer() > 0.8)
				{
					if (ActualEnnemie.getSprite().getRotation() < 210)
						ActualEnnemie.getSprite().rotate(140 * MainTime.GetTimeDeltaF());
					else
						ActualEnnemie.getSprite().setRotation(210);

					ActualEnnemie.setDelta(75, -100);
				}
			}
		}
		else if (ActualEnnemie.getType() == 2)
		{
			if (ActualEnnemie.getPhase() == 0)
			{
				ActualEnnemie.getSprite().setRotation(225);
				ActualEnnemie.setDelta(-225, 150);
				if (ActualEnnemie.getTimer() > 2)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 2, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 2);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setPhase(1);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 1)
			{
				if (ActualEnnemie.getSprite().getRotation() > 180 && ActualEnnemie.getTimer() > 0.2)
					ActualEnnemie.getSprite().rotate(-140 * MainTime.GetTimeDeltaF());

				if (ActualEnnemie.getTimer() > 0.5)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 0.5, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 0.5);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.getSprite().setRotation(180);
					ActualEnnemie.setDelta(0, 0);
					ActualEnnemie.setPhase(2);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 2)
			{
				if (ActualEnnemie.getTimer() > 0.2)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(3);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 3)
			{
				if (ActualEnnemie.getTimer() > 0.3)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(4);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 4)
			{
				if (ActualEnnemie.getTimer() > 1.2)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(5);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 5)
			{
				if (ActualEnnemie.getTimer() > 0.8)
				{
					if (ActualEnnemie.getSprite().getRotation() > 150)
						ActualEnnemie.getSprite().rotate(-25 * MainTime.GetTimeDeltaF());
					else
						ActualEnnemie.getSprite().setRotation(150);

					ActualEnnemie.setDelta(-75, -100);
				}
			}
		}
		else if (ActualEnnemie.getType() == 3)
		{
			if (ActualEnnemie.getPhase() == 0)
			{
				ActualEnnemie.getSprite().setRotation(90);
				ActualEnnemie.setDelta(300, 0);
				if (ActualEnnemie.getTimer() > 1.75)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 1.75, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 1.75);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setPhase(1);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 1)
			{
				if (ActualEnnemie.getSprite().getRotation() < 180)
					ActualEnnemie.getSprite().rotate(125 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.getSprite().setRotation(180);

				if (ActualEnnemie.getTimer() > 0.25)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 0.25, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 0.25);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setDelta(0, 0);
				}

				if (ActualEnnemie.getTimer() > 0.75)
				{
					ActualEnnemie.setPhase(2);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 2)
			{
				if (ActualEnnemie.getTimer() > 0.5)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(3);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 3)
			{
				if (ActualEnnemie.getTimer() > 1.5)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(4);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 4)
			{
				if (ActualEnnemie.getTimer() > 1)
				{
					ActualEnnemie.setDelta(0, -150);
					ActualEnnemie.setPhase(5);
					ActualEnnemie.resetTimer();
				}
			}
		}
		else if (ActualEnnemie.getType() == 4)
		{
			if (ActualEnnemie.getPhase() == 0)
			{
				ActualEnnemie.getSprite().setRotation(270);
				ActualEnnemie.setDelta(-300, 0);
				if (ActualEnnemie.getTimer() > 1.75)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 1.75, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 1.75);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setPhase(1);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 1)
			{
				if (ActualEnnemie.getSprite().getRotation() > 180)
					ActualEnnemie.getSprite().rotate(-125 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.getSprite().setRotation(180);

				if (ActualEnnemie.getTimer() > 0.25)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 0.25, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 0.25);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setDelta(0, 0);
				}

				if (ActualEnnemie.getTimer() > 1.75)
				{
					ActualEnnemie.setPhase(2);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 2)
			{
				if (ActualEnnemie.getTimer() > 0.5)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(3);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 3)
			{
				if (ActualEnnemie.getTimer() > 1.5)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(4);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 4)
			{
				if (ActualEnnemie.getTimer() > 1)
				{
					ActualEnnemie.setDelta(0, -150);
					ActualEnnemie.setPhase(5);
					ActualEnnemie.resetTimer();
				}
			}
		}
		else if (ActualEnnemie.getType() == 5)
		{
			if (ActualEnnemie.getPhase() == 0)
			{
				ActualEnnemie.getSprite().setRotation(180);
				ActualEnnemie.setDelta(0, 300);
				if (ActualEnnemie.getTimer() > 1)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 1, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 1);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setPhase(1);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 1)
			{
				ActualEnnemie.setDelta(0, 0);

				if (ActualEnnemie.getTimer() > 1)
				{
					ActualEnnemie.setPhase(2);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 2)
			{
				if (ActualEnnemie.getTimer() > 0.25)
				{
					ActualEnnemie.Fire();
					ActualEnnemie.setPhase(3);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 3)
			{
				if (ActualEnnemie.getTimer() > 1.25)
				{
					ActualEnnemie.setDelta(0, -100);
					ActualEnnemie.setPhase(4);
					ActualEnnemie.resetTimer();
				}
			}
		}
		else if (ActualEnnemie.getType() == 6)
		{
			if (ActualEnnemie.getPhase() == 0)
			{
				ActualEnnemie.getSprite().setRotation(180);
				ActualEnnemie.setDelta(0, 400);
				if (ActualEnnemie.getTimer() > 1.5)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 1.5, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 1.5);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setPhase(1);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 1)
			{
				if (ActualEnnemie.getDelta().x < 400)
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x + 375 * MainTime.GetTimeDeltaF(), ActualEnnemie.getDelta().y);
				else
					ActualEnnemie.setDelta(400, ActualEnnemie.getDelta().y);

				if (ActualEnnemie.getDelta().y > 0)
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x, ActualEnnemie.getDelta().y - 375 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x, 0);

				if (ActualEnnemie.getSprite().getRotation() > 90)
					ActualEnnemie.getSprite().rotate(-85 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.getSprite().setRotation(90);

				if (ActualEnnemie.getTimer() > 2)
				{
					ActualEnnemie.setPhase(2);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 2)
			{
				if (ActualEnnemie.getDelta().x > 0)
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x - 375 * MainTime.GetTimeDeltaF(), ActualEnnemie.getDelta().y);
				else
					ActualEnnemie.setDelta(0, ActualEnnemie.getDelta().y);

				if (ActualEnnemie.getDelta().y > -250)
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x, ActualEnnemie.getDelta().y - 375 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x, -250);

				if (ActualEnnemie.getSprite().getRotation() > 0 && ActualEnnemie.getSprite().getRotation() < 340)
					ActualEnnemie.getSprite().rotate(-85 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.getSprite().setRotation(0);

			}
		}
		else if (ActualEnnemie.getType() == 7)
		{
			if (ActualEnnemie.getPhase() == 0)
			{
				ActualEnnemie.getSprite().setRotation(180);
				ActualEnnemie.setDelta(0, 400);
				if (ActualEnnemie.getTimer() > 1.5)
				{
					ActualEnnemie.NewLastSwitch(ActualEnnemie.getLastSwitch().x + ActualEnnemie.getDelta().x * 1.5, ActualEnnemie.getLastSwitch().y + ActualEnnemie.getDelta().y * 1.5);
					ActualEnnemie.setPosition(ActualEnnemie.getLastSwitch());
					ActualEnnemie.setPhase(1);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 1)
			{
				if (ActualEnnemie.getDelta().x > -400)
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x + -375 * MainTime.GetTimeDeltaF(), ActualEnnemie.getDelta().y);
				else
					ActualEnnemie.setDelta(-400, ActualEnnemie.getDelta().y);

				if (ActualEnnemie.getDelta().y > 0)
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x, ActualEnnemie.getDelta().y - 375 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x, 0);

				if (ActualEnnemie.getSprite().getRotation() < 270)
					ActualEnnemie.getSprite().rotate(85 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.getSprite().setRotation(270);

				if (ActualEnnemie.getTimer() > 2)
				{
					ActualEnnemie.setPhase(2);
					ActualEnnemie.resetTimer();
				}
			}
			else if (ActualEnnemie.getPhase() == 2)
			{
				if (ActualEnnemie.getDelta().x < 0)
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x + 375 * MainTime.GetTimeDeltaF(), ActualEnnemie.getDelta().y);
				else
					ActualEnnemie.setDelta(0, ActualEnnemie.getDelta().y);

				if (ActualEnnemie.getDelta().y > -250)
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x, ActualEnnemie.getDelta().y - 375 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.setDelta(ActualEnnemie.getDelta().x, -250);

				if (ActualEnnemie.getSprite().getRotation() < 360 && ActualEnnemie.getSprite().getRotation() > 20)
					ActualEnnemie.getSprite().rotate(85 * MainTime.GetTimeDeltaF());
				else
					ActualEnnemie.getSprite().setRotation(0);

			}
		}

		ActualEnnemie.Update();
	}
}


void GameInit()
{
	_game_phase = 0;
	Game_timer = 0;
	isPause = false;

	RemoveAllBuffs();
	RemoveAllEnnemies();
	RemoveAllEnnemiesShoots();
	RemoveAllExplosions();
	RemoveAllPlayerShoots();
	
	Player1.Reset();
	Player2.Reset();

	Player1.setPosition(1920 / 2, 900);
	Player2.setPosition(1920 / 1.3f, 900);

	if (SoloGame)
	{
		Player2.TakeDamage(Player2.getLife());
	}
}

void UpdateGame()
{
	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();
	
	Player* ptPlayer = 0;
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
			ptPlayer = &Player1;
		else if (!SoloGame)
			ptPlayer = &Player2;		
		else
			break;


		ptPlayer->setLRectFrame(0);

		if (isButtonPressed(Action::Up, ptPlayer->getController()))
		{
			if (ptPlayer->getPosition().y >= 55)
				ptPlayer->addPositionY(-325 * MainTime.GetTimeDeltaF());
			ptPlayer->setLRectFrame(1);
		}

		if (isButtonPressed(Action::Down, ptPlayer->getController()))
		{
			if (ptPlayer->getPosition().y <= 1025)
				ptPlayer->addPositionY(325 * MainTime.GetTimeDeltaF());
			ptPlayer->setLRectFrame(0);
		}

		if (isButtonPressed(Action::Left, ptPlayer->getController()))
		{
			if (ptPlayer->getPosition().x >= 275)
				ptPlayer->addPositionX(-325 * MainTime.GetTimeDeltaF());
			ptPlayer->setLRectFrame(3);
		}

		if (isButtonPressed(Action::Right, ptPlayer->getController()))
		{
			if (ptPlayer->getPosition().x <= 1645)
				ptPlayer->addPositionX(325 * MainTime.GetTimeDeltaF());
			ptPlayer->setLRectFrame(2);
		}

		ptPlayer->TimersUpdate(MainTime.GetTimeDeltaF());
		if (isButtonPressed(Action::Fire, ptPlayer->getController()))
		{
			ptPlayer->Fire();
		}

		if (isButtonPressed(Action::Fire_Spe1, ptPlayer->getController()))
		{
			ptPlayer->FirePissenlit();
		}

		if (isButtonPressed(Action::Fire_Spe2, ptPlayer->getController()))
		{
			ptPlayer->SetFireSin();
		}
		ptPlayer->FireSin();

		if (isButtonPressed(Action::Start, ptPlayer->getController()) && ActionTiming >= 0.3)
		{
			ActionTiming = 0.f;
			isPause = true;
		}
	}

	ennemies_Loop_1P();
	ennemies_patern();

	for (EnnemiesShoots& ActualEnnemieBullet : EnnemiesShootsList)
	{
		ActualEnnemieBullet.update();
	}

	for (PlayerBullet& ActualPlayerBullet : Bullets)
	{
		ActualPlayerBullet.Update();
	}

	for (Buffs& ActualBuff : BuffsList)
		ActualBuff.Update();

	BuffsCollisions(Player1); 
	BuffsCollisions(Player2); 
	RemoveDeadBuffs();

	PlayerShootsColisions();
	RemoveDeadPlayerShoots();

	RemoveDeadEnnemies();
	RemoveDeadEnnemiesShoots();

	for (Explosion& ActualExplosion : Explosions)
	{
		ActualExplosion.update();
	}

	RemoveDeadExplosions();

	EnnemiesPlayerCollision(Player1);
	EnnemiesShootPlayerCollision(Player1);
	Player1.Update();

	EnnemiesPlayerCollision(Player2);
	EnnemiesShootPlayerCollision(Player2);
	Player2.Update();


	if (Player1.getLife() <= 0 && Player2.getLife() <= 0)
	{
		RemoveAllBuffs();
		RemoveAllEnnemies();
		RemoveAllEnnemiesShoots();
		RemoveAllExplosions();
		RemoveAllPlayerShoots();

		ChangeState(State::SAVE);
	}
}
void UpdateGamePause()
{
	extern bool OptionChangeKeys;

	static float ActionTiming = 0.f;
	ActionTiming += MainTime.GetTimeDeltaF();

	if (IgMenu_Options)
	{
		UpdateOptionMenu();

		if (isButtonPressed(Action::Return) && ActionTiming >= 0.3)
		{
			ActionTiming = 0;
			if (!OptionChangeKeys)
			{
				IgMenu_Options = false;
			}
		}
	}
	else
	{
		Player* ptPlayer = 0;
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
				ptPlayer = &Player1;
			else if (!SoloGame)
				ptPlayer = &Player2;
			else
				break;


			ptPlayer->setLRectFrame(0);

			if (isButtonPressed(Action::Up, ptPlayer->getController()) && ActionTiming >= 0.3)
			{
				if (IgMenu_Choice > 0)
				{
					IgMenu_Choice--;
					ActionTiming = 0;
				}
			}

			if (isButtonPressed(Action::Down, ptPlayer->getController()) && ActionTiming >= 0.3)
			{
				if (IgMenu_Choice < 3)
				{
					IgMenu_Choice++;
					ActionTiming = 0;
				}
			}

			if (isButtonPressed(Action::Interact, ptPlayer->getController()) && ActionTiming >= 0.3)
			{
				ActionTiming = 0;

				switch (IgMenu_Choice)
				{
				case 0: // resume
					isPause = false;
					IgMenu_Choice = 0;
					break;
				case 1: // options
					IgMenu_Options = true;
					break;
				case 2:	// restart
					GameInit();
					IgMenu_Choice = 0;
					break;
				case 3: // Menu
					RemoveAllBuffs();
					RemoveAllEnnemies();
					RemoveAllEnnemiesShoots();
					RemoveAllExplosions();
					RemoveAllPlayerShoots();
					IgMenu_Choice = 0;
					ChangeState(State::MAIN_MENU);
					break;

				default:
					break;
				}

			}

			if (isButtonPressed(Action::Start, ptPlayer->getController()) && ActionTiming >= 0.3)
			{
				ActionTiming = 0;
				isPause = false;
				IgMenu_Choice = 0;
			}
		}
	}
}

void DisplayGame()
{
	static float posY = -4320;
	static float posY2 = -9720;
	static float posYBulle = -4320;
	static float posY2Bulle = -9720;

	static int background_sup = 0;

	posY += 85 * MainTime.GetTimeDeltaF();
	posY2 += 85 * MainTime.GetTimeDeltaF();

	posYBulle += 125 * MainTime.GetTimeDeltaF();
	posY2Bulle += 125 * MainTime.GetTimeDeltaF();

	if (background_sup == 0)
	{
		posY2 = posY - 5399;
		if (posY >= 5400)
			background_sup = 1;
	}
	if (background_sup == 1)
	{
		posY = posY2 - 5399;
		if (posY2 >= 5400)
			background_sup = 0;
	}


	if (posYBulle >= 5400)
		posYBulle = posY2Bulle - 5400;

	if (posY2Bulle >= 5400)
		posY2Bulle = posYBulle - 5400;



	getSprite("Fond").setPosition(240, posY);
	win.Window().draw(getSprite("Fond"));
	getSprite("Fond").setPosition(240, posY2);
	win.Window().draw(getSprite("Fond"));

	getSprite("Bubulles").setPosition(240, posYBulle);
	win.Window().draw(getSprite("Bubulles"));
	getSprite("Bubulles").setPosition(240, posY2Bulle);
	win.Window().draw(getSprite("Bubulles"));


	for (Buffs& ActualBuff : BuffsList)
	{
		if (ActualBuff.getType() == 1)
		{
			getSprite("Power_Up").setOrigin(getSprite("Power_Up").getGlobalBounds().width / 2, getSprite("Power_Up").getGlobalBounds().height / 2);
			getSprite("Power_Up").setPosition(ActualBuff.getpos());
			win.Window().draw(getSprite("Power_Up"));
		}
		else if (ActualBuff.getType() == 2)
		{
			getSprite("Score_Up").setOrigin(getSprite("Score_Up").getGlobalBounds().width / 2, getSprite("Score_Up").getGlobalBounds().height / 2);
			getSprite("Score_Up").setPosition(ActualBuff.getpos());
			win.Window().draw(getSprite("Score_Up"));
		}
		else if (ActualBuff.getType() == 3)
		{
			getSprite("HP_Up").setOrigin(getSprite("HP_Up").getGlobalBounds().width / 2, getSprite("HP_Up").getGlobalBounds().height / 2);
			getSprite("HP_Up").setPosition(ActualBuff.getpos());
			win.Window().draw(getSprite("HP_Up"));
		}
		else if (ActualBuff.getType() == 4)
		{
			getSprite("Pissenlit_Up").setOrigin(getSprite("Pissenlit_Up").getGlobalBounds().width / 2, getSprite("Pissenlit_Up").getGlobalBounds().height / 2);
			getSprite("Pissenlit_Up").setPosition(ActualBuff.getpos());
			win.Window().draw(getSprite("Pissenlit_Up"));
		}
		else if (ActualBuff.getType() == 5)
		{
			getSprite("Sin_Up").setOrigin(getSprite("Sin_Up").getGlobalBounds().width / 2, getSprite("Sin_Up").getGlobalBounds().height / 2);
			getSprite("Sin_Up").setPosition(ActualBuff.getpos());
			win.Window().draw(getSprite("Sin_Up"));
		}
	}

	for (PlayerBullet& ActualPlayerBullet : Bullets)
	{
		win.Window().draw(ActualPlayerBullet.Sprite());
	}

	for (EnnemiesShoots& ActualEnnemieBullet : EnnemiesShootsList)
	{
		win.Window().draw(ActualEnnemieBullet.getSprite());
	}

	for (Ennemies& ActualEnnemie : ennemies)
	{
		win.Window().draw(ActualEnnemie.getSprite());
	}

	for (Explosion& ActualExplosion : Explosions)
	{
		win.Window().draw(ActualExplosion.getSprite());
	}


	// Player 1
	getSprite(Player1.getShip()).setPosition(Player1.getPosition());
	getSprite(Player1.getShip()).setColor(sf::Color::White);

	if (Player1.isInvulnerable())
		getSprite(Player1.getShip()).setColor(sf::Color::Color(255, 255, 255, 100));

	win.Window().draw(getSprite(Player1.getShip()));

	// Player 2
	getSprite(Player2.getShip()).setPosition(Player2.getPosition());
	getSprite(Player2.getShip()).setColor(sf::Color::White);

	if (Player2.isInvulnerable())
		getSprite(Player2.getShip()).setColor(sf::Color::Color(255, 255, 255, 100));

	win.Window().draw(getSprite(Player2.getShip()));

	// Hud Background
	win.Window().draw(getSprite("HUD_J1"));
	getSprite("HUD_J2").setPosition(1680, 0);
	win.Window().draw(getSprite("HUD_J2"));


	win.Window().draw(getSprite("HUDJ1"));
	if (!SoloGame)
	{
		getSprite("HUDJ2").setPosition(1680,0);
		win.Window().draw(getSprite("HUDJ2"));
	}

	// Info Hud
	for (int i = 0; i < Player1.getLife(); i++)
	{
		getSprite("Coeur").setPosition(60, 100 + (100 * i));
		win.Window().draw(getSprite("Coeur"));
	}


	sf::IntRect XpRect(0, 0, 210, 88);
	XpRect.width = 52 + (210 - 52) * ((float)Player1.getAtkPoints() / 10);
	getSprite("XP").setTextureRect(XpRect);
	getSprite("XP").setPosition(17, 593);
	win.Window().draw(getSprite("XP"));
	getSprite("XpBar").setPosition(17, 593);
	win.Window().draw(getSprite("XpBar"));




	sf::Text Scores("", Font, 65);
	std::string strScores;
	strScores = "  " + std::to_string(Player1.getScore()) + "\n\n\n\n\t * " + std::to_string(Player1.getPissenlitShoot()) + "\n\n\t * " + std::to_string(Player1.getSinShoot());
	Scores.setString(strScores);
	Scores.setPosition(60, 433);
	Scores.setFillColor(sf::Color::Black);
	win.Window().draw(Scores);

	if (!SoloGame)
	{
		for (int i = 0; i < Player2.getLife(); i++)
		{
			getSprite("Coeur").setPosition(1740, 100 + (100 * i));
			win.Window().draw(getSprite("Coeur"));
		}

		XpRect.width = 52 + (210 - 52) * ((float)Player2.getAtkPoints() / 10);
		getSprite("XP").setTextureRect(XpRect);
		getSprite("XP").setPosition(1700, 593);
		win.Window().draw(getSprite("XP"));
		getSprite("XpBar").setPosition(1700, 593);
		win.Window().draw(getSprite("XpBar"));
				

		strScores = "  " + std::to_string(Player2.getScore()) + "\n\n\n\n\t * " + std::to_string(Player2.getPissenlitShoot()) + "\n\n\t * " + std::to_string(Player2.getSinShoot());
		Scores.setString(strScores);
		Scores.setPosition(1740, 433);
		Scores.setFillColor(sf::Color::Black);
		win.Window().draw(Scores);
	}

	if (true) // future HitBox Show 
	{
		sf::RectangleShape RectHitBox;
		sf::CircleShape CircleHitBox;

		RectHitBox.setFillColor(sf::Color::Transparent);
		RectHitBox.setOutlineColor(sf::Color::Blue);
		RectHitBox.setOutlineThickness(1);

		CircleHitBox.setFillColor(sf::Color::Transparent);
		CircleHitBox.setOutlineColor(sf::Color::Blue);
		CircleHitBox.setOutlineThickness(1);
		
		for (Buffs& ActualBuff : BuffsList)
		{
			RectHitBox.setSize(sf::Vector2f(SIZE_BUFFS, SIZE_BUFFS));
			RectHitBox.setOrigin(SIZE_BUFFS / 2, SIZE_BUFFS / 2);
			RectHitBox.setPosition(ActualBuff.getpos());
			win.Window().draw(RectHitBox);
		}

		for (PlayerBullet& ActualPlayerBullet : Bullets)
		{
			CircleHitBox.setRadius(RADIUS_PLAYER_SHOOT);
			CircleHitBox.setOrigin(sf::Vector2f(CircleHitBox.getRadius(), CircleHitBox.getRadius()));
			CircleHitBox.setPosition(ActualPlayerBullet.Pos());
			win.Window().draw(CircleHitBox);
		}

		for (EnnemiesShoots& ActualEnnemieBullet : EnnemiesShootsList)
		{
			CircleHitBox.setRadius(RADIUS_ENNEMIES_SHOOT);
			CircleHitBox.setOrigin(sf::Vector2f(CircleHitBox.getRadius(), CircleHitBox.getRadius()));
			CircleHitBox.setPosition(ActualEnnemieBullet.getpos());
			win.Window().draw(CircleHitBox);
		}

		for (Ennemies& ActualEnnemie : ennemies)
		{
			CircleHitBox.setRadius(RADIUS_ENNEMIES);
			CircleHitBox.setOrigin(sf::Vector2f(CircleHitBox.getRadius(), CircleHitBox.getRadius()));
			CircleHitBox.setPosition(ActualEnnemie.getPos());
			win.Window().draw(CircleHitBox);
		}

		RectHitBox.setSize(sf::Vector2f(getSprite(Player1.getShip()).getGlobalBounds().width, getSprite(Player1.getShip()).getGlobalBounds().height));
		RectHitBox.setOrigin(RectHitBox.getSize().x / 2, RectHitBox.getSize().y / 2);
		RectHitBox.setPosition(Player1.getPosition());
		win.Window().draw(RectHitBox);

		RectHitBox.setSize(sf::Vector2f(getSprite(Player2.getShip()).getGlobalBounds().width, getSprite(Player2.getShip()).getGlobalBounds().height));
		RectHitBox.setOrigin(RectHitBox.getSize().x / 2, RectHitBox.getSize().y / 2);
		RectHitBox.setPosition(Player2.getPosition());
		win.Window().draw(RectHitBox);
	}
}
void DisplayGamePause()
{
	if (IgMenu_Options)
	{
		DisplayOptionMenu();
	}
	else
	{
		sf::RectangleShape Shady(sf::Vector2f(1920, 1080));
		Shady.setFillColor(sf::Color::Color(0, 0, 0, 50));
		win.Window().draw(Shady);

		win.Window().draw(getSprite("Bande_L"));
		getSprite("Bande_R").setPosition(1680, 0);
		win.Window().draw(getSprite("Bande_R"));

		sf::Text buttons_text("", Font, 70);
		std::string Textyes[4]{ "Return","Options","Restart","Menu" };
		sf::Vector2f TextPos[4]{ sf::Vector2f(850,175),sf::Vector2f(990,375), sf::Vector2f(800,580), sf::Vector2f(990,775) };

		for (int i = 0; i < 4; i++)
		{
			if (i == IgMenu_Choice)
			{
				getSprite("Button").setTextureRect(sf::IntRect(477, 0, 477, 217));
				buttons_text.setFillColor(sf::Color::Color(180, 50, 0));
			}
			else
			{
				getSprite("Button").setTextureRect(sf::IntRect(0, 0, 477, 217));
				buttons_text.setFillColor(sf::Color::Black);
			}


			if (i % 2 == 0)
			{
				getSprite("Button").setRotation(180);
				getSprite("Button").setPosition(sf::Vector2f(600 + getSprite("Button").getGlobalBounds().width, 125 + (200 * i + getSprite("Button").getGlobalBounds().height)));
			}
			else
			{
				getSprite("Button").setRotation(0);
				getSprite("Button").setPosition(sf::Vector2f(600 + 250, 125 + (200 * i)));
			}

			buttons_text.setString(Textyes[i]);
			buttons_text.setPosition(TextPos[i]);

			win.Window().draw(getSprite("Button"));
			win.Window().draw(buttons_text);
		}
	}
}