#pragma once
#include <SFML/Graphics.hpp>
int viewX, viewY;
sf::View view;

void getplayercoordinateforview(float x, float y) { //функция для считывания координат игрока
	viewX = int(x); viewY = int(y);//считываем коорд игрока и проверяем их, чтобы убрать края
	view.setCenter(viewX, viewY); //следим за игроком, передавая его координаты камере. +100 - сместили камеру по иксу вправо. эксперементируйте
}
void setposview(float x, float y)
{
	viewX = int(x); viewY = int(y);
	view.setCenter(viewX, viewY);
}
int getviewx() { return(viewX); }
int getviewy() { return(viewY); }
