#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <time.h>
#include <string>
#include "view.h"
#include <math.h>

using namespace sf;
using namespace std;

float evenly(float shit, int shit1)
{
	shit *= shit1;
	shit = nearbyint(shit);
	shit /= shit1;
	return shit;
}

float distantion(float x[2], float y[2])
{
	return sqrt(pow(x[0] - y[0], 2) + pow(x[1] - y[1], 2));
}

int whatisangle(float sx, float sy)
{
	float gippo = sqrt(sx * sx + sy * sy);
	float cosshit = abs(sx / gippo);
	float sinshit = abs(sy / gippo);
	int angle = 0;
	int fourth = 0;
	if (sx >= 0 && sy >= 0) fourth = 0;
	if (sx <= 0 && sy >= 0) fourth = 1;
	if (sx <= 0 && sy <= 0) fourth = 2;
	if (sx >= 0 && sy <= 0) fourth = 3;
	angle = asin(sinshit) * 57.29577951308232;
	angle = angle + 90 * fourth;

	if (sx == 0 && sy > 0) angle = 90;
	if (sx == 0 && sy < 0) angle = 270;
	if (sy == 0 && sx > 0) angle = 0;
	if (sy == 0 && sx < 0) angle = 180;

	if (sx == 0 && sy == 0) return 0; else return angle;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	float stuffy = -126;
	float culldown = 5;
	const int qoflens = 8;

	int refraction[qoflens];
	int lightershit[3] = {100, int(sh / 2), 0};
	int lensshit[qoflens][4] = { int(sw / 2), int(sh / 2), 0, 1};

	int folowing = 0;
	int mousechange[2];

	for (int i = 0; i < qoflens; i++)
	{
		lensshit[i][0] = int(sw / 2) + i * 30;
		lensshit[i][1] = int(sh / 2);
		lensshit[i][2] = 0;
		refraction[i] = 15;
	}

	Font font;
	font.loadFromFile("font.ttf");
	Text text("", font, 24);
	text.setFillColor(Color(120, 120, 120));
	text.setStyle(sf::Text::Bold);

	Image exit_image;
	exit_image.loadFromFile("images/exitimage.png");
	exit_image.createMaskFromColor(Color(255, 255, 255));
	Texture exit_t;
	exit_t.loadFromImage(exit_image);
	Sprite s_exit;
	s_exit.setTexture(exit_t);

	Image lighter_image;
	lighter_image.loadFromFile("images/stuff.png");
	lighter_image.createMaskFromColor(Color(255, 255, 255));
	Texture lighter_t;
	lighter_t.loadFromImage(lighter_image);
	Sprite s_lighter;
	s_lighter.setTexture(lighter_t);
	s_lighter.setTextureRect(IntRect(0, 64, 128, 56));
	s_lighter.setPosition(lightershit[0], lightershit[1]);
	s_lighter.setRotation(lightershit[2]);
	

	Image bg_image;
	bg_image.loadFromFile("images/bg.png");
	bg_image.createMaskFromColor(Color(255, 255, 255));
	Texture bg_t;
	bg_t.loadFromImage(bg_image);
	Sprite s_bg;
	s_bg.setTexture(bg_t);
	s_bg.setScale((float(sw) / float(1366)), (float(sh) / float(768)));
	s_bg.setPosition(0, 0);

	Image smallbg_image;
	smallbg_image.loadFromFile("images/stuff.png");
	smallbg_image.createMaskFromColor(Color(255, 255, 255));
	Texture smallbg_t;
	smallbg_t.loadFromImage(smallbg_image);
	Sprite smalls_bg;
	smalls_bg.setTexture(smallbg_t);
	smalls_bg.setTextureRect(IntRect(8, 8, 42, 14));
	smalls_bg.setScale(3, 3);

	Image point_image;
	point_image.loadFromFile("images/stuff.png");
	point_image.createMaskFromColor(Color(255, 255, 255));
	Texture point_t;
	point_t.loadFromImage(point_image);
	Sprite point_s[2];
	point_s[0].setTexture(point_t);
	point_s[1].setTexture(point_t);
	point_s[0].setTextureRect(IntRect(128, 0, 1, 1));
	point_s[1].setTextureRect(IntRect(134, 0, 2, 2));
	point_s[0].setPosition(0, 0);
	point_s[1].setPosition(0, 0);
	point_s[0].setColor(Color(255, 255, 255, 140));
	point_s[1].setColor(Color(255, 255, 255, 180));

	Image stuff_image;
	stuff_image.loadFromFile("images/stuff.png");
	stuff_image.createMaskFromColor(Color(255, 255, 255));
	Texture stuff_t;
	stuff_t.loadFromImage(stuff_image);
	const int qofstuff = 4;
	Sprite s_stuff[4];
	for (int i = 0; i < qofstuff; i++)
	{
		s_stuff[i].setTexture(stuff_t);
		if (i % 2 == 0) s_stuff[i].setTextureRect(IntRect(0, 0, 64, 64));
		else s_stuff[i].setTextureRect(IntRect(64, 0, 64, 64));
	}

	//Координаты кнопок
	if (true)
	{
		s_stuff[0].setPosition(sw - 128, sh - 64);
		s_stuff[1].setPosition(sw - 64, sh - 64);
		s_stuff[2].setPosition(sw - 256, sh - 64);
		s_stuff[3].setPosition(sw - 192, sh - 64);
	}

	RenderWindow window(sf::VideoMode(sw, sh), "Optics", Style::Fullscreen);
	view.reset(sf::FloatRect(0, 0, sw, sh));
	window.setPosition(Vector2i(0, 0));
	Clock clock;
	getplayercoordinateforview(int(sw / 2), int(sh / 2));

	float mouseshit[2] = {0, 0};
	float optimiz = 8;

	int choosenlens = -1;

	int choosenlight = 0;
	bool shiiiiiiiiiit = false;

	Image len_image;
	len_image.create(500, 200, Color(255, 255, 255));
	len_image.createMaskFromColor(Color(255, 255, 255));
	Texture len_t[qoflens];
	Sprite s_len[qoflens];
	for (int i = 0; i < qoflens; i++)
	{
		len_t[i].loadFromImage(len_image);
		s_len[i].setTexture(len_t[i]);
		s_len[i].setRotation(lensshit[i][2]);
		s_len[i].setPosition(lensshit[i][0], lensshit[i][1]);
		s_len[i].setOrigin(250, 100);
		lensshit[i][3] = 1;
	}

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		if (culldown < 5) culldown += time * 0.05;
		if (culldown >= 5)
		{
			for (int i = 0; i < qofstuff; i++)
				s_stuff[i].setColor(Color(255, 255, 255));
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			s_exit.setColor(Color(200, 200, 200));
			window.draw(s_exit);
			window.display();
			Sleep(300);
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Q) && shiiiiiiiiiit)
		{
			choosenlight--; Sleep(100);
		}
		if (Keyboard::isKeyPressed(Keyboard::W) && shiiiiiiiiiit)
		{
			choosenlight++; Sleep(100);
		}

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left) {//а именно левая
					if (s_exit.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
					{
						s_exit.setColor(Color::Green);
						window.draw(s_exit);
						window.display();
						Sleep(300);
						window.close();
					}
					if (s_lighter.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
					{
						folowing = 1; choosenlens = -1;
						s_lighter.setColor(Color(220, 220, 220));
					}
					int shitfuck = 30;
					for (int i = 0; i < qoflens; i++)
						if (pos.x > lensshit[i][0] - shitfuck && pos.x < lensshit[i][0] + shitfuck && pos.y > lensshit[i][1] - shitfuck && pos.y < lensshit[i][1] + shitfuck)//и при этом координата курсора попадает в спрайт
						{
							folowing = 2 + i;
							choosenlens = i;
						}
					if (true)
					{
						int pressedbut = -1;
						for (int i = 0; i < qofstuff; i++)
							if (s_stuff[i].getGlobalBounds().contains(pos.x, pos.y))
								pressedbut = i;

						if (pressedbut == 0 && choosenlens != -1)
						{
							int secondrefr = refraction[choosenlens];
							if (Keyboard::isKeyPressed(Keyboard::LControl)) refraction[choosenlens] -= 6;
							else if (Keyboard::isKeyPressed(Keyboard::LShift)) refraction[choosenlens] -= 24;
							else refraction[choosenlens] -= 12;

							float refr = ((refraction[choosenlens] / 8) + 9 * refraction[choosenlens] / abs(refraction[choosenlens]));
							int shit = int(sqrt(abs(pow(refr, 2))) / 10000);

							if (abs(int(((shit * (1 - 0.05)) - refr * 0.05))) > 250)
								refraction[choosenlens] = secondrefr;
							else
								lensshit[choosenlens][3] = 1;
						}
						if (pressedbut == 1 && choosenlens != -1)
						{
							int secondrefr = refraction[choosenlens];
							if (Keyboard::isKeyPressed(Keyboard::LControl)) refraction[choosenlens] += 6;
							else if (Keyboard::isKeyPressed(Keyboard::LShift)) refraction[choosenlens] += 24;
							else refraction[choosenlens] += 12;
							float refr = ((refraction[choosenlens] / 8) + 9 * refraction[choosenlens] / abs(refraction[choosenlens]));
							int shit = int(sqrt(abs(pow(refr, 2))) / 10000);
							if (abs(int(((shit * (1 - 0.05)) - refr * 0.05))) > 250)
								refraction[choosenlens] = secondrefr;
							else
								lensshit[choosenlens][3] = 1;
						}
						if (pressedbut == 2) optimiz = optimiz * 2;
						if (pressedbut == 3 && optimiz > 0) optimiz = optimiz / 2;

						if (pressedbut != -1)
						{
							culldown = 0;
							s_stuff[pressedbut].setColor(Color(200, 200, 200));
						}
					}
				}
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					folowing = 0;

			if (event.type == Event::MouseWheelMoved)
			{
				if (folowing == 1)
				{
					lightershit[2] += event.key.code * 5;
					while (lightershit[2] > 360) lightershit[2] -= 360;
					while (lightershit[2] < 0) lightershit[2] += 360;
					s_lighter.setRotation(lightershit[2]);
				}
				if (folowing > 1)
				{
					lensshit[folowing - 2][2] += event.key.code * 5;
					while (lensshit[folowing - 2][2] > 360) lensshit[folowing - 2][2] -= 360;
					while (lensshit[folowing - 2][2] < 0) lensshit[folowing - 2][2] += 360;
					s_len[folowing - 2].setRotation(lensshit[folowing - 2][2]);
				}
			}
		}

		if (folowing != 0)
		{
			if (folowing == 1)
			{
				lightershit[0] += pos.x - mouseshit[0];
				lightershit[1] += pos.y - mouseshit[1];
				s_lighter.setPosition(lightershit[0], lightershit[1]);
			}
			else
			{
				lensshit[choosenlens][0] += pos.x - mouseshit[0];
				lensshit[choosenlens][1] += pos.y - mouseshit[1];
				s_len[choosenlens].setPosition(lensshit[choosenlens][0], lensshit[choosenlens][1]);
			}
		}
		else
		{
			s_lighter.setColor(Color(255, 255, 255));
			point_s[0].setColor(Color(255, 255, 255, 150));
		}

		mouseshit[0] = pos.x;
		mouseshit[1] = pos.y;

		if (pos.y > 128)
		{
			if (stuffy > -126) stuffy -= 0.5 * time;
		}
		else
			if (stuffy < 0) stuffy += 0.5 * time;
		if (stuffy > 0) stuffy = 0;
		if (stuffy < -126) stuffy = -126;

		window.setView(view);
		window.clear();
		window.getSystemHandle();

		window.draw(s_bg);

		if (true)
		{
			int light = -1;
			//128 / 56
			for (int i = 1; i < (54 / optimiz); i++)
			{
				light++;
				bool show = false;
				float cosin = cos(lightershit[2] * 0.0175);
				float sinus = sin(lightershit[2] * 0.0175);
				float lightcords[2] = { int(lightershit[0] + int(((124 * cosin) - ((((i) * optimiz)) * sinus)))), int(lightershit[1] + int((128 * sinus) + ((((i)*optimiz)) * cosin))) };
				point_s[1].setPosition(lightcords[0], lightcords[1]);
				float move[2];
				move[0] = cos(lightershit[2] * 0.0175);
				move[1] = sin(lightershit[2] * 0.0175);
				if (light == choosenlight && shiiiiiiiiiit)
				{
					show = true;
					point_s[1].setColor(Color(255, 255, 255, 180));
				}
				else
					if (shiiiiiiiiiit) point_s[1].setColor(Color(255, 0, 0, 180));

				while (lightcords[0] > 0 && lightcords[0] < sw && lightcords[1] > 0 && lightcords[1] < sh)
				{
					bool lensishere = false;
					int whichlens = 0;
					for (int g = 0; g < qoflens; g++)
					{
							float shit[2];
							shit[0] = lensshit[g][0] - lightcords[0];
							shit[1] = lensshit[g][1] - lightcords[1];
							cosin = cos((360 - lensshit[g][2]) * 0.0175);
							sinus = sin((360 - lensshit[g][2]) * 0.0175);
							float shhhit[2];
							shhhit[0] = shit[0] * cosin - shit[1] * sinus;
							shhhit[1] = shit[0] * sinus + shit[1] * cosin;
							if (abs(shhhit[0]) <= 1 && abs(shhhit[1]) <= 100)
							{
								if (abs(shhhit[0]) <= 1 && abs(shhhit[1]) > 90)
								{
									lightcords[0] = -100;
									lightcords[1] = -100;
									g = qoflens + 1;
								}
								else
								{
									bool vpered = true;
									if (true)
									{
										float shiiiit[2];
										shiiiit[0] = lightcords[0];
										shiiiit[1] = lightcords[1];
										shiiiit[0] += move[0] * 200;
										shiiiit[1] += move[1] * 200;
										float fosucshit[2];
										float fosucshit1[2];
										cosin = cos((lensshit[g][2]) * 0.0175);
										sinus = sin((lensshit[g][2]) * 0.0175);
										fosucshit[0] = lensshit[g][0] + refraction[g] * cosin;
										fosucshit[1] = lensshit[g][1] + refraction[g] * sinus;
										fosucshit1[0] = lensshit[g][0] - refraction[g] * cosin;
										fosucshit1[1] = lensshit[g][1] - refraction[g] * sinus;
										if (distantion(shiiiit, fosucshit1) < distantion(shiiiit, fosucshit))
											vpered = false;
									}
									
									
									float newmove[2];
									float heremove[2];
									float fuckingshit[2];
									float herelensshit[3];
									herelensshit[0] = 100;
									herelensshit[1] = 200;
									herelensshit[2] = 0;
									cosin = cos(-lensshit[g][2] * 0.0175);
									sinus = sin(-lensshit[g][2] * 0.0175);
									heremove[0] = move[0] * cosin - move[1] * sinus;
									heremove[1] = move[0] * sinus + move[1] * cosin;
									if (heremove[0] < 0)
									{
										heremove[0] = -heremove[0];
										heremove[1] = -heremove[1];
										shhhit[0] = -shhhit[0];
										shhhit[1] = -shhhit[1];
									}
									fuckingshit[0] = refraction[g];
									fuckingshit[1] = (refraction[g] / heremove[0]) * heremove[1];

									if (true)
									{
										float fuckit[2];
										float fuckit2[2];
										fuckit[0] = herelensshit[0] - shhhit[0];
										fuckit[1] = herelensshit[1] - shhhit[1];
										fuckit2[0] = herelensshit[0] + fuckingshit[0];
										fuckit2[1] = herelensshit[1] + fuckingshit[1];
										float dist = distantion(fuckit, fuckit2);
										newmove[0] = -(fuckit[0] - fuckit2[0]) / dist;
										newmove[1] = -(fuckit[1] - fuckit2[1]) / dist;
									}

									if (refraction[g] < 0)
									{
										newmove[0] = -newmove[0];
										newmove[1] = -newmove[1];
									}

									
									cosin = cos(lensshit[g][2] * 0.0175);
									sinus = sin(lensshit[g][2] * 0.0175);
									move[0] = newmove[0] * cosin - newmove[1] * sinus;
									move[1] = newmove[0] * sinus + newmove[1] * cosin;

									if (!vpered)
									{
										move[0] = -move[0];
										move[1] = -move[1];
									}

									if (refraction[g] < 0)
									{
										move[0] = -move[0];
										move[1] = -move[1];
									}

									if (true)
									{
										bool shit = true;
										while (shit)
										{
											if (true)
											{
												float cosin1;
												float sinus1;
												float shit1[2];
												shit1[0] = lensshit[g][0] - lightcords[0];
												shit1[1] = lensshit[g][1] - lightcords[1];
												cosin1 = cos((360 - lensshit[g][2]) * 0.0175);
												sinus1 = sin((360 - lensshit[g][2]) * 0.0175);
												float shhhit1[2];
												shhhit1[0] = shit1[0] * cosin1 - shit1[1] * sinus1;
												shhhit1[1] = shit1[0] * sinus1 + shit1[1] * cosin1;
												if (abs(shhhit1[0]) <= 1 && abs(shhhit1[1]) <= 100)
													shit = true;
												else
													shit = false;
											}
											lightcords[0] += move[0];
											lightcords[1] += move[1];
											point_s[1].setPosition(int(lightcords[0]), int(lightcords[1]));
											window.draw(point_s[1]);
										}
									}

									if (show)
									{
										if (g == choosenlens)
											point_s[0].setColor(Color(220, 220, 220, 100));
										else
											point_s[0].setColor(Color(255, 255, 255, 100));
										float fuck = 0.05;
										float refr = ((refraction[g] / 8) + 9 * refraction[g] / abs(refraction[g]));
										float cosin = cos(herelensshit[2] * 0.0175);
										float sinus = sin(herelensshit[2] * 0.0175);
										if (refraction[g] > 0)
											for (int i = -100; i < 101; i += 2)
											{
												int shit = int(sqrt(abs(pow(refr, 2)) - (i * i * abs(pow(refr, 2))) / 10000));
												if (shit >= refr) shit = refr - 1;
												for (int u = -(shit * (1 - fuck)) - refr * fuck; u < (shit * (1 - fuck)) + refr * fuck; u++)
												{
													point_s[0].setPosition(herelensshit[0] + u, herelensshit[1] + i);
													window.draw(point_s[0]);
												}
											}
										else
										{
											refr = abs(refr);
											for (int i = -100; i < 101; i += 2)
											{
												int shit = int(sqrt(abs(pow(refr, 2)) - (i * i * abs(pow(refr, 2))) / 10000));
												shit -= refr;
												shit = abs(shit);
												if (shit >= refr - 2) shit = refr - 2;
												if (shit <= 1) shit = 1;
												for (int u = (-(shit * (1 - fuck)) - refr * fuck); u < ((shit * (1 - fuck)) + refr * fuck); u++)
												{
													point_s[0].setPosition(herelensshit[0] + u, herelensshit[1] + i);
													window.draw(point_s[0]);
												}
											}
										}
										point_s[1].setColor(Color(255, 0, 0));
										point_s[1].setScale(5, 5);
										point_s[1].setPosition(int(herelensshit[0] - shhhit[0]), int(herelensshit[1] - shhhit[1]));
										window.draw(point_s[1]);
										point_s[1].setScale(1, 1);
										point_s[1].setColor(Color(255, 255, 255));
										for (int i = 0; i < 25; i++)
										{
											point_s[1].setPosition(int(herelensshit[0] - shhhit[0] + heremove[0] * i), int(herelensshit[1] - shhhit[1] + heremove[1] * i));
											window.draw(point_s[1]);
										}

										point_s[1].setColor(Color(0, 255, 255));
										for (int i = 0; i < refraction[g] / heremove[0]; i++)
										{
											point_s[1].setPosition(int(herelensshit[0] + heremove[0] * i), int(herelensshit[1] + heremove[1] * i));
											window.draw(point_s[1]);
										}
										point_s[1].setColor(Color(255, 255, 255));
										for (int i = 0; abs(i) < abs(fuckingshit[1]); i++)
										{
											point_s[1].setPosition(int(herelensshit[0] + refraction[g]), int(herelensshit[1] + i * fuckingshit[1] / abs(fuckingshit[1])));
											window.draw(point_s[1]);
										}
										for (int i = 0; i < fuckingshit[0]; i++)
										{
											point_s[1].setPosition(int(herelensshit[0] + i), int(herelensshit[1]));
											window.draw(point_s[1]);
										}
										point_s[1].setColor(Color(0, 0, 255));
										for (int i = 0; i < 90; i++)
										{
											point_s[1].setPosition(int(herelensshit[0] - shhhit[0] + newmove[0] * i), int(herelensshit[1] - shhhit[1] + newmove[1] * i));
											window.draw(point_s[1]);
										}
										point_s[1].setColor(Color(255, 255, 255));
									}
								}
							}
					}

					float pastlightcords[2];
					pastlightcords[0] = lightcords[0];
					pastlightcords[1] = lightcords[1];
					float shitt = 1000;
					for (int g = 0; g < qoflens; g++)
					{
						float sshitt = sqrt(pow(lightcords[0] - lensshit[g][0], 2) + pow(lightcords[1] - lensshit[g][1], 2));
						if (shitt > sshitt) shitt = sshitt;
					}
					if (shitt > 250)
					{
						for (int g = 0; g < 65; g++)
						{
							lightcords[0] += move[0] * 2;
							lightcords[1] += move[1] * 2;
							point_s[1].setPosition(int(lightcords[0]), int(lightcords[1]));
							window.draw(point_s[1]);
						}
						lightcords[0] += move[0] * 2;
						lightcords[1] += move[1] * 2;
					}
					else
					{
						lightcords[0] += move[0] * 2;
						lightcords[1] += move[1] * 2;
					}
					point_s[1].setPosition(int(lightcords[0]), int(lightcords[1]));
					window.draw(point_s[1]);
				}
			}
		}

		window.draw(s_lighter);

		if (true)
		{
			for (int g = 0; g < qoflens; g++)
			{
				if (g == choosenlens)
					s_len[g].setColor(Color(220, 220, 220, 180));
				else
					s_len[g].setColor(Color(255, 255, 255, 180));

				if (lensshit[g][3] == 1)
				{
					for (int i = 0; i < 200; i++)
						for (int u = 0; u < 500; u++)
							len_image.setPixel(u, i, Color(255, 255, 255));
					len_image.createMaskFromColor(Color(255, 255, 255));
					int shiiit = 0;
					float fuck = 0.05;
					float refr = ((refraction[g] / 8) + 9 * refraction[g] / abs(refraction[g]));
					if (refraction[g] > 0)
						for (int i = -100; i < 100; i += 1)
						{
							if (abs(i) > 90)
									shiiit = 1;
							else
									shiiit = 3;
							int shit = int(sqrt(abs(pow(refr, 2)) - (i * i * abs(pow(refr, 2))) / 10000));
							if (shit >= refr) shit = refr - 1;
							int w = int(((shit * (1 - fuck)) - refr * fuck) * 2);

							for (int u = (-(shit * (1 - fuck)) - refr * fuck) + 250; u < 250 + ((shit * (1 - fuck)) + refr * fuck); u++)
							{
								if (shiiit == 1) len_image.setPixel(u, i + 100, Color(85, 150, 170));
								if (shiiit == 3) len_image.setPixel(u, i + 100, Color(150, 215, 235));
							}
							len_t[g].loadFromImage(len_image);
							s_len[g].setTexture(len_t[g]);
							s_len[g].setColor(Color(255, 255, 255, 180));
							window.draw(s_len[g]);
						}
					else
					{
						refr = abs(refr);

						for (int i = -100; i < 100; i += 1)
						{
							if (abs(i) > 90)
									shiiit = 1;
							else
									shiiit = 3;
							int shit = int(sqrt(abs(pow(refr, 2)) - (i * i * abs(pow(refr, 2))) / 10000));
							shit -= refr;
							shit = abs(shit);
							if (shit >= refr - 2) shit = refr - 2;
							if (shit <= 1) shit = 1;
							for (int u = (-(shit * (1 - fuck)) - refr * fuck) + 250; u < ((shit * (1 - fuck)) + refr * fuck) + 250; u++)
							{
								if (shiiit == 1) len_image.setPixel(u, i + 100, Color(85, 150, 170));
								if (shiiit == 3) len_image.setPixel(u, i + 100, Color(150, 215, 235));
							}
							len_t[g].loadFromImage(len_image);
							s_len[g].setTexture(len_t[g]);
							s_len[g].setColor(Color(255, 255, 255, 180));
							window.draw(s_len[g]);
						}
					}
					lensshit[g][3] = 0;
				}
			}
		}
			
		for (int g = 0; g < qoflens; g++)
			window.draw(s_len[g]);

		for (int i = 0; i < qofstuff; i++) window.draw(s_stuff[i]);

		smalls_bg.setPosition(getviewx() - int(sw / 2) + int(sw / 455), getviewy() - int(sh / 2));
		window.draw(smalls_bg);

		std::ostringstream thing;
		thing << int((2000 / time) / 2);
		thing << " fps";
		text.setString(thing.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(getviewx() - int(sw / 2) + 21, getviewy() - int(sh / 2) + 6);//задаем позицию текста, отступая от центра камеры
		window.draw(text);

		s_exit.setPosition(getviewx() + int(sw / 2) - 126, getviewy() - int(sh / 2) + stuffy);
		window.draw(s_exit);
		window.display();
		// 1 к 9
	}
	return 0;
}