#ifndef _M5TOUCH_H_
#define _M5TOUCH_H_

#include "utility/PointAndZone.h"
#include "utility/Config.h"

#define TOUCH_W				320
#define TOUCH_H				280
#define CST_DEVICE_ADDR		0x38
#define CST_INT 			39

// Strangely, the value 13 leads to slightly more frequent updates than 10
// (Still not every 13 ms, often more like 15 to 20)
#define DEFAULT_INTERVAL	13

class M5Touch {
  public:
	static M5Touch* instance;
    M5Touch();
    void begin();
    uint8_t ft6336(uint8_t reg);
	void ft6336(uint8_t reg, uint8_t value);
	void ft6336(uint8_t reg, uint8_t size, uint8_t* data);
	uint8_t interval(uint8_t ivl);
	uint8_t interval();
	void update();
    bool read();
    bool ispressed();
    void dump();
    Point stale();
    Point getPressPoint();
    uint8_t rotation;
    uint8_t points;
    bool changed, wasRead;
    Point point[2];
    uint8_t point0finger;
  private:
    uint8_t _interval;
	uint32_t _lastRead;
};

// For compatibility with older M5Core2 code
class HotZone : public Zone {
  public:
	HotZone(
	  int16_t x0_, int16_t y0_, int16_t x1_, int16_t y1_,
	  void (*fun_)() = nullptr
	);
	void setZone(
	  int16_t x0_, int16_t y0_, int16_t x1_, int16_t y1_,
	  void (*fun_)() = nullptr
	);
	bool inHotZone(Point &p);
	bool inHotZoneDoFun(Point &p);
    void (*fun)();
};
#define HotZone_t HotZone
#define TouchPoint Point
#define TouchPoint_t Point

#endif /* _M5TOUCH_H_ */