/**************************************************************************/
/*!
  @file     FT6336U.cpp
  Author: urobot2011(https://github.com/urobot2011)
  License: MIT (see LICENSE)
*/
/**************************************************************************/

#include "FT6336U.h"

#include "touch_FT6336U.h"

TS_Point::TS_Point(int _HEIGHT, int _WIDTH, int16_t _x, int16_t _y){
    x = _x;
    y = _y;
	HEIGHT = _HEIGHT;
	WIDTH = _WIDTH;
}

void TS_Point::rotation(){
    int16_t _x = y;
    y = x;
	x = _x;
}

void TS_Point::flipX(){
    x = map(x, 0, HEIGHT, HEIGHT, 0);
}

void TS_Point::flipY(){
    y = map(y, 0, WIDTH, WIDTH, 0);
}

Touch::Touch(int _HEIGHT, int _WIDTH, int8_t sda, int8_t scl, uint8_t rst_n, uint8_t int_n){
	ft6336u = FT6336U(sda, scl, rst_n, int_n);
	HEIGHT = _HEIGHT;
	WIDTH = _WIDTH;
}

void Touch::begin(){
	ft6336u.begin();
}

bool Touch::touched(){
	return ft6336u.read_td_status();
}

TS_Point Touch::getPoint(){
	return TS_Point(HEIGHT, WIDTH, ft6336u.read_touch1_x(), ft6336u.read_touch1_y());
}

TS_Point Touch::getPoint2(){
	return TS_Point(HEIGHT, WIDTH, ft6336u.read_touch2_x(), ft6336u.read_touch2_y());
}
