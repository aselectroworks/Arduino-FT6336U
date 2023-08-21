/**************************************************************************/
/*!
  @file     FT6336U.h
  Author: urobot2011(https://github.com/urobot2011)
  License: MIT (see LICENSE)
*/
/**************************************************************************/

#ifndef __FT6336U_h__
#define __FT6336U_h__

#include "touch_FT6336U.h"

class TS_Point {
    public:
    TS_Point(int HEIGHT, int WIDTH, int16_t _x, int16_t _y);
	void rotation();
	void flipX();
	void flipY();
	int HEIGHT, WIDTH;
    int16_t x = 0;
    int16_t y = 0;
};

class Touch {
	public:
	Touch(int HEIGHT, int WIDTH, int8_t sda, int8_t scl, uint8_t rst_n, uint8_t int_n);
	void begin();
	FT6336U ft6336u = FT6336U(-1, -1, -1, -1);
	int HEIGHT, WIDTH;
	bool touched();
	TS_Point getPoint();
	TS_Point getPoint2();
};

#endif
