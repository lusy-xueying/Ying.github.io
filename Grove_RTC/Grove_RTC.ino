#include <Arduino.h>
#include <U8x8lib.h>

#include <U8g2lib.h>
#include <Wire.h>
#include <MsTimer2.h>
#include "DHT.h"
#include "Seeed_BMP280.h"
#include "LIS3DHTR.h"
#include <DS3231.h>
#define WIRE Wire
//20*20
const unsigned char sound_bmp[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x3e, 0x00, 0x80, 0x3f, 0x0c, 0xc0, 0x3b, 0x0c, 0xfe, 0xb8, 0x0d, 0x7f, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0x03, 0xb8, 0x0d, 0xff, 0xb8, 0x0d, 0xc0, 0x39, 0x0c, 0x80, 0x3f, 0x0c, 0x00, 0x3e, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00};
//20*30
const unsigned char temp_bmp[] U8X8_PROGMEM = {0x00, 0x06, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x00, 0x09, 0x00, 0x80, 0x19, 0x00, 0x80, 0x19, 0x00, 0xc0, 0x39, 0x00, 0xc0, 0x39, 0x00, 0xc0, 0x39, 0x00, 0xc0, 0x39, 0x00, 0xc0, 0x3f, 0x00, 0x80, 0x1f, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x06, 0x00};
//20*20
const unsigned char hum_bmp[] U8X8_PROGMEM= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0x80,0x10,0x00,0x00,0x00,0x00,0x40,0x20,0x00,0x20,0x40,0x00,0x20,0x40,0x00,0x10,0x80,0x00,0x10,0x80,0x00,0x08,0x00,0x01,0x08,0x00,0x01,0x08,0x00,0x01,0x08,0x00,0x01,0x08,0x00,0x01,0x08,0x00,0x01,0x10,0x80,0x00,0x00,0x00,0x00,0x40,0x20,0x00,0x80,0x10,0x00};
//20*20
const unsigned char pressure_bmp1[] U8X8_PROGMEM= {0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x80,0x96,0x01,0x80,0x1f,0x03,0x00,0x0f,0x06,0x18,0x06,0x04,0x1c,0x04,0x04,0x06,0x00,0x06,0xc6,0xff,0x03,0xc6,0xff,0x01,0x04,0x00,0x00,0xfc,0xff,0x03,0xf8,0xff,0x03,0x00,0x00,0x00,0xfe,0xff,0x07,0xfe,0xff,0x07,0x00,0x00,0x00};
//30*30
const unsigned char pressure_bmp[] U8X8_PROGMEM= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0xc8,0xc4,0x01,0x00,0xf8,0x87,0x07,0x00,0xf8,0x87,0x07,0x60,0xf0,0x03,0x04,0x60,0xf0,0x03,0x04,0xf0,0xc0,0x00,0x04,0xf0,0xc0,0x00,0x04,0x18,0x00,0x00,0x06,0x18,0x00,0x00,0x06,0x08,0xfc,0xff,0x03,0x08,0xfc,0xff,0x03,0x18,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0xf0,0xff,0xff,0x03,0xf0,0xff,0xff,0x03,0xe0,0xff,0xff,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0xff,0xff,0x1f,0xfe,0xff,0xff,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//30*30
const unsigned char light_tmp[] U8X8_PROGMEM = {0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0xc1, 0x60, 0x00, 0x80, 0xc3, 0x70, 0x00, 0x00, 0xc3, 0x30, 0x00, 0x00, 0xc7, 0x38, 0x00, 0x00, 0x06, 0x18, 0x00, 0x0c, 0xf0, 0x03, 0x0c, 0x3c, 0xfc, 0x0f, 0x0f, 0x78, 0x1e, 0x9e, 0x07, 0x60, 0x07, 0xb8, 0x01, 0x00, 0x03, 0x30, 0x00, 0x80, 0x03, 0x70, 0x00, 0x80, 0x01, 0x60, 0x00, 0xbf, 0x01, 0x60, 0x3f, 0xbf, 0x01, 0x60, 0x3f, 0x80, 0x01, 0x60, 0x00, 0x80, 0x03, 0x70, 0x00, 0x00, 0x03, 0x30, 0x00, 0x60, 0x07, 0xb8, 0x01, 0x78, 0x1e, 0x9e, 0x07, 0x3c, 0xfc, 0x0f, 0x0f, 0x0c, 0xf0, 0x03, 0x0c, 0x00, 0x06, 0x18, 0x00, 0x00, 0xc7, 0x38, 0x00, 0x00, 0xc3, 0x30, 0x00, 0x80, 0xc3, 0x70, 0x00, 0x80, 0xc1, 0x60, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00};

//30*30
const unsigned char sound_bmp1[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00, 0x70, 0xc0, 0x00, 0x00, 0x48, 0x80, 0x01, 0x00, 0x4c, 0x18, 0x03, 0x00, 0x46, 0x30, 0x02, 0x00, 0x43, 0x60, 0x04, 0x80, 0x41, 0x43, 0x04, 0xfc, 0x40, 0x84, 0x08, 0x46, 0x40, 0x8c, 0x08, 0x46, 0x40, 0x88, 0x08, 0x46, 0x40, 0x10, 0x09, 0x06, 0x40, 0x10, 0x09, 0x06, 0x40, 0x10, 0x19, 0x06, 0x40, 0x10, 0x09, 0x06, 0x40, 0x10, 0x09, 0x46, 0x40, 0x18, 0x09, 0x46, 0x40, 0x88, 0x08, 0x46, 0x40, 0x8c, 0x08, 0xfc, 0x40, 0x86, 0x0c, 0x80, 0x41, 0x43, 0x04, 0x00, 0x43, 0x20, 0x04, 0x00, 0x42, 0x30, 0x02, 0x00, 0x44, 0x0c, 0x03, 0x00, 0x48, 0x80, 0x01, 0x00, 0x50, 0xc0, 0x00, 0x00, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//30*30
const unsigned char acel_bmp[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x07, 0x00, 0x00, 0x07, 0x1c, 0x00, 0x80, 0x01, 0x60, 0x00, 0x60, 0x00, 0x80, 0x00, 0x30, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x02, 0x08, 0x00, 0x00, 0x04, 0x0c, 0x00, 0x00, 0x04, 0x04, 0x20, 0x01, 0x08, 0x04, 0x10, 0x02, 0x08, 0x02, 0xf8, 0x03, 0x08, 0x02, 0x0c, 0x0e, 0x10, 0x02, 0x0a, 0x10, 0x10, 0x02, 0x0a, 0x10, 0x10, 0x02, 0x02, 0x0a, 0x10, 0x02, 0x18, 0x06, 0x18, 0x06, 0x10, 0x02, 0x08, 0x04, 0x20, 0x01, 0x08, 0x04, 0xc0, 0x00, 0x0c, 0x08, 0x00, 0x00, 0x04, 0x18, 0x00, 0x00, 0x02, 0x30, 0x00, 0x00, 0x03, 0x60, 0x00, 0x80, 0x01, 0xc0, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x30, 0x00, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//30*30
const unsigned char temp_bmp1[] U8X8_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x07, 0xfe, 0xff, 0xff, 0x1f, 0x8f, 0xff, 0xff, 0x3f, 0x0f, 0x00, 0x00, 0x3e, 0x0f, 0x00, 0x00, 0x3e, 0x8f, 0xff, 0xff, 0x3f, 0xfe, 0xff, 0xff, 0x1f, 0xfe, 0xff, 0xff, 0x07, 0xfc, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//20*20
const unsigned char temp_bmps[] U8X8_PROGMEM = {
0x00,0x00,0x00,0x00,0x07,0x00,0x80,0x08,0x00,0x80,0x78,0x00,0x80,0x08,0x00,0x80,
0x78,0x00,0x80,0x0A,0x00,0x80,0x7A,0x00,0x80,0x0A,0x00,0x80,0x7A,0x00,0x80,0x0A,
0x00,0x40,0x12,0x00,0x20,0x22,0x00,0x10,0x47,0x00,0x90,0x4F,0x00,0x90,0x4F,0x00,
0x90,0x4F,0x00,0x20,0x27,0x00,0x40,0x10,0x00,0x80,0x0F,0x00,
};
//16*16 温度图片
const unsigned char temp_bmpss [] U8X8_PROGMEM = {
0x80,0x00,0x40,0x01,0x20,0x02,0xA0,0x1E,0xA0,0x02,0xA0,0x1E,0xA0,0x02,0xA0,0x02,
0xB0,0x06,0x90,0x04,0xC8,0x09,0xE8,0x0B,0xC8,0x09,0x90,0x04,0x30,0x06,0xC0,0x01,  
};

//湿度图标16*16
const unsigned char hum_hmps[] U8X8_PROGMEM = {
0x80,0x00,0x80,0x01,0x40,0x02,0x20,0x04,0x30,0x0C,0x08,0x10,0x08,0x14,0x04,0x24,
0x04,0x28,0x04,0x24,0x04,0x23,0x88,0x10,0x10,0x08,0xE0,0x07,0x00,0x00,0x00,0x00,
};
//8*16 温度单位图片
const unsigned char temp_bmpicon[] U8X8_PROGMEM = {
0x00,0x02,0x05,0x7A,0x84,0x02,0x02,0x01,0x01,0x01,0x01,0x02,0x02,0x84,0x78,0x00,  
};
//30*30
const unsigned char time_bmp1[] U8X8_PROGMEM = {
0x00,0xF8,0x07,0x00,0x00,0xFE,0x1F,0x00,0x80,0xFF,0x7F,0x00,0xE0,0x0F,0xFC,0x01,
0xF0,0x01,0xE0,0x03,0xF8,0xE0,0xC0,0x07,0x78,0xE0,0x80,0x07,0x3C,0xE0,0x00,0x0F,
0x1C,0xE0,0x00,0x1E,0x0E,0xE0,0x00,0x1C,0x0E,0xE0,0x00,0x1C,0x0F,0xE0,0x00,0x3C,
0x07,0xE0,0x00,0x38,0x07,0xE0,0x00,0x38,0x07,0xE0,0xFF,0x39,0x07,0xE0,0xFF,0x39,
0x07,0xE0,0xFF,0x39,0x07,0x00,0x00,0x38,0x0F,0x00,0x00,0x3C,0x0E,0x00,0x00,0x1C,
0x0E,0x00,0x00,0x1C,0x1C,0x00,0x00,0x1E,0x3C,0x00,0x00,0x0F,0x78,0x00,0x00,0x07,
0xF8,0x00,0xC0,0x07,0xF0,0x01,0xE0,0x03,0xE0,0x0F,0xFC,0x01,0x80,0xFF,0x7F,0x00,
0x00,0xFF,0x3F,0x00,0x00,0xF8,0x07,0x00,
};
//30*30
const unsigned char alarm_bmp1[] U8X8_PROGMEM = {
0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x03,0x00,
0x00,0xF8,0x07,0x00,0x00,0xFC,0x0F,0x00,0x00,0xFE,0x1F,0x00,0x00,0xFE,0x1F,0x00,
0x00,0xFE,0x1F,0x00,0x00,0xFE,0x1F,0x00,0x00,0xFE,0x1F,0x00,0x00,0xFE,0x1F,0x00,
0x00,0xFE,0x1F,0x00,0x00,0xFE,0x1F,0x00,0x00,0xFE,0x1F,0x00,0x00,0xFE,0x1F,0x00,
0x00,0xFF,0x3F,0x00,0x80,0xFF,0x7F,0x00,0xC0,0xFF,0xFF,0x00,0xE0,0xFF,0xFF,0x01,
0xF0,0xFF,0xFF,0x03,0x18,0xE0,0x01,0x06,0x00,0xF0,0x03,0x00,0x00,0xF0,0x03,0x00,
0x00,0xF0,0x03,0x00,0x00,0xE0,0x01,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

//20*20 小时钟图片
const unsigned char times_bmp1[] U8X8_PROGMEM = {
0x80,0x1F,0x00,0x60,0x66,0x00,0x10,0x86,0x00,0x08,0x06,0x01,0x04,0x00,0x02,0x02,
0x06,0x04,0x02,0x06,0x04,0x01,0x06,0x08,0x01,0x06,0x08,0x0F,0x7E,0x0F,0x0F,0x7E,
0x0F,0x01,0x00,0x08,0x01,0x00,0x08,0x02,0x00,0x04,0x02,0x00,0x04,0x04,0x00,0x02,
0x08,0x06,0x01,0x10,0x86,0x00,0x60,0x66,0x00,0x80,0x1F,0x00,
};

//20*20 小闹钟图片
const unsigned char alarms_bmp1[] U8X8_PROGMEM = {
0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x06,0x0F,0x00,0x0F,0x8F,0x1F,0x0F,0xE6,
0x7F,0x06,0xF0,0xF9,0x00,0xF8,0xF9,0x01,0xF8,0xF9,0x01,0xFC,0xF9,0x03,0xFC,0x01,
0x03,0xFC,0x01,0x03,0xFC,0xF9,0x03,0xF8,0xFF,0x01,0xF8,0xFF,0x01,0xF8,0xFF,0x01,
0xEC,0x7F,0x03,0x86,0x1F,0x06,0x03,0x00,0x0C,0x00,0x00,0x00,
};
/*
*Main_Menu_Index
*        Sub_
*
******/








#define BoardVersion 2//定义版本号

#if BoardVersion == 1//版本1
char led = 5;
char buzzer = 6;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);
char button = 2;
char rotary = A1;
char light = A2;
char sound = A0;
DHT dht(4,DHT11);
BMP280 bmp280; 
// LIS3DHTR<TwoWire> accelemeter(I2C_MODE);
LIS3DHTR<TwoWire> accelemeter; //IIC
#elif BoardVersion == 2//版本2
char led = 4;
char buzzer = 5;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);
char button = 6;
char rotary = A0;
char light = A6;
char sound = A2;
DHT dht(3,DHT11);
BMP280 bmp280; 
//LIS3DHTR<TwoWire> accelemeter(I2C_MODE);
LIS3DHTR<TwoWire> accelemeter; //IIC
#endif

/*下面定义了主菜单中包含的三个子菜单*/
#define DISP_TIME 0//时间显示
#define SET_TIME  1//时间设置
#define SET_ALAR  2//闹钟设置


/*下面定义了设置子菜单中包含的设置项目*/
#define YEAR_H   0//年 高
#define YEAR_L   1//年 低
#define MONTH_H  2//月
#define MONTH_L  3//月
#define DATE_H   4//日
#define DATE_L   5//日
#define HOUR_H   6//时
#define HOUR_L   7//时
#define MINUTE_H 8//分
#define MINUTE_L 9//分
#define SECOND_H 10//秒
#define SECOND_L 11//秒
#define EXIT     12//保存设置并退出
#define SENTRY   13//哨兵
#define NO_SUB   15//没有子菜单选项

/*counter*/
//#define TIME_NUMS  12//需要设置的数量

/*下面定义了按键类型*/
#define NO_PRESS    0     //无按键按下
#define SHORT_PRESS 1     //短按键按下
#define LONG_PRESS  2     //长按键按下


/*设置选项状态*/
#define NO_SET  0
#define SETTING 1

#define CLICKS 100

typedef struct Time {
  int year;
  int month;
  int date;
  int hour;
  int minute;
  int second;
  int temp;
}Time;

typedef struct Coordinate {
  char x;
  char y;
}Coordinate;

DS3231 Clock; 

Time sSetTime,sPreSetTime,sAlarTime,sTime = {20,10,19,11,17,40};//设置时间，设置前的时间，闹钟时间，当前时间

bool Century=false;
bool h12;
bool PM;

char AlarmOn = 0;
char Reexecute =0;
int MainMenuIndex = DISP_TIME;//主菜单索引
int SubMenuTimeIndex = NO_SUB;//子菜单索引
int SubMenuAlarIndex = NO_SUB;//子菜单索引
int SetOptionStatus = NO_SET;//具体的设置项索引
int Press = NO_PRESS;//按键
int SettingArray[12]={0};
int MaxVal[12]={9,9,1,9,3,9,2,9,5,9,5,9};

unsigned int DelayCnt = 0;
unsigned int AlarmCnt = 0;
unsigned int PreDelayCnt = 0;

// U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

int BuzzerFrequency = 300;
char MODE = 1;
char LongPress = false;
int x = 50, y = 13;
char PressCounter = 0;
char BlinkEnable = true;
#define BLINK 10
#define SQueueLEN 10
int SQueue[SQueueLEN] = {0};


void Checker() {  
  static char LEDBlink = 0;
  DelayCnt++;
  //Serial.println(DelayCnt); // prints a string to a serial port
  if (BlinkEnable)//使能LED闪烁
  {
    digitalWrite(led,HIGH);//输出高电平点亮LED
    LEDBlink ++;
    if (LEDBlink > BLINK)//100ms
    {
      LEDBlink = 0;//计数器清零
      BlinkEnable = false;//禁止LED亮，
      digitalWrite(led,LOW);
    }    
  }
  
  if (digitalRead(button) == HIGH)//按键读取，有按键按下了
  {
   
      PressCounter ++;//计数按下时间，计数按键按下的次数每次10ms
      if (PressCounter > CLICKS)//1s往上，
      {
        PressCounter = CLICKS + 1;
      }
  }
  else//按键未按下或者已经释放则计数器清零，短按键或长按键都要在按键释放后来判断，按键按下的状态是无法分别长短的
  {
    if((PressCounter>1)&&(PressCounter<(CLICKS + 1)))//PressCounter不为零说明有按键按下，PressCounter>1说明至少PressCounter为2或者更大，可以推断出来这是真的按键不是抖动或扰动，PressCounter<(CLICKS + 1)说明没有达到长按键的要求，所以它是短按键
    {
      Press = SHORT_PRESS;//标记此次按键为短按键，loop循环会使用本次按键标记，使用完后会将他设置为无按键状态，不影响下次按键判断。
      Serial.println("SHORT_PRESS"); // prints a string to a serial port 这是调试用的，没有实际功能。
      Reexecute = 1;
    }
    else if(PressCounter>CLICKS)//这是判断长按键用的。
    {
      Press = LONG_PRESS;
      Serial.println("LONG_PRESS"); // prints a string to a serial port
      Reexecute = 1;
    }
    else//没有按键按下
    {
      //Press = NO_PRESS;
      //Serial.println("NO_PRESS"); // prints a string to a serial port
    }
    PressCounter = 0;//按键释放，将按键计数器清零，为下一次做准备。
  } 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//串口初始化
  
  if(!bmp280.init()){//气压计初始化
    Serial.println("bmp280 init error!");
  }
  //accelemeter.begin(Wire);
  accelemeter.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); //IIC init
  delay(100);
  //accelemeter.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  accelemeter.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);

  if (!accelemeter) {
      Serial.println("LIS3DHTR didn't connect.");
  }
  
  pinMode(rotary, INPUT);//电位器管脚配置
  pinMode(button, INPUT);//按键管脚配置
  pinMode(light, INPUT);//光电传感器管教配置
  pinMode(sound, INPUT);//声音传感器配置
  for (int Index = 0 ; Index < SQueueLEN ; Index ++)
  {
    SQueue[Index] = analogRead(sound);
  }
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  u8g2.begin();
  MsTimer2::set(10, Checker); // 10ms period
  MsTimer2::start();
}

void loop() {

  if((0==(DelayCnt%100))&&(PreDelayCnt != DelayCnt))//做更新数据，判断闹钟
  {
    PreDelayCnt = DelayCnt;
    ReadDS3231(&sTime);//更新时间数据
    Reexecute = 1;
    //if(TimeCompare(sTime,sAlarTime))//比较闹钟时间与当前时间
    //  tone(buzzer,BuzzerFrequency,10000);//开启闹铃
   // /*
    if(TimeCompare(sTime,sAlarTime))//比较闹钟时间与当前时间
    {
      AlarmCnt = DelayCnt;//记录打开闹钟时的计数器，闹钟响铃10S,这是为了控制响铃时间
      //tone(buzzer,BuzzerFrequency);//开启闹铃
      analogWrite(buzzer, BuzzerFrequency);
      AlarmOn = 1;//闹钟打开状态
    }

    if(AlarmOn)//闹钟被打开后需要处理的事务
    {
      if(DiffTick(DelayCnt,AlarmCnt) > 1000)
      {
        //noTone(buzzer);//关闭闹钟
        analogWrite(buzzer, 0);
        AlarmOn = 0;//闹钟状态为关闭
      }
    }
    //*/
  }

  if(Reexecute)
  {
    Reexecute = 0;
    MenuPecess();
  }
  /*
  if (digitalRead(button) == HIGH)//按键按下
  {
    delay(5);//消抖
    if (digitalRead(button) == HIGH)//再次确认按键确实按下
    {
      BlinkEnable = true;//使能LED闪烁
      if (PressCounter > CLICKS)//按下时间超过1S
      {
        PressCounter = 0;//计数器清零
        if (digitalRead(button) == HIGH)//判断按键是否依然按下
        {
          LongPress = true;//长按键
          while (digitalRead(button))
          {
            if (LongPress)
            {
              LongPress = false;
              tone(buzzer,BuzzerFrequency);
              delay(200);
              noTone(buzzer);
            }
          }
          while (1)
          {
            int n = analogRead(rotary) / 204.8 + 1;//读取电位器的值
            digitalWrite(led, HIGH);
            digitalWrite(buzzer, LOW);
            select_mode(n);
            if (digitalRead(button) == HIGH)
            {
              delay(4);
              if (digitalRead(button) == HIGH)
              {
                MODE = analogRead(rotary) / 204.8 + 1;
                while (digitalRead(button));
                digitalWrite(led, LOW);
                digitalWrite(buzzer, LOW);
                break;
              }
            }
          }
        }
      }
    }
  }

  
  if (MODE == 1) {//
    Light_show();//显示光强度
  } else if (MODE == 2) {//
    Sound_show();//显示声音
  } else if (MODE == 3) {
    Temp_show();//显示温度值
  } else if (MODE == 4) {
    Pressure_show();//显示压力值
  } else if (MODE == 5) {
    Acele_show();//显示运动传感器值
  }
  */
}

/*
void select_mode(int n)
{
  switch (n)
  {
    case 1:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 16, 30, 30, light_tmp);
        u8g2.setCursor(44, 46);
        u8g2.print(F("Light")); // write something to the internal memory
      } while (u8g2.nextPage());
      break;
    case 2:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 8, 30, 30, sound_bmp1);
        u8g2.setCursor(44, 48);
        u8g2.print(F("Sound")); // write something to the internal memory
      } while (u8g2.nextPage());
      break;
    case 3:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_12b_mr);//
        u8g2.drawXBMP(49, 0, 30, 30, temp_bmp1);
        u8g2.setCursor(31, 35);
        u8g2.print(F("Temperature")); // write something to the internal memory
        u8g2.setCursor(43, 49);
        u8g2.print(F("Humidity"));    // write something to the internal memory
      } while (u8g2.nextPage());
      break;
    case 4:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 8, 30, 30, pressure_bmp);
        u8g2.setCursor(16, 48);
        u8g2.print(F("Air Pressure")); // write something to the internal memory
      } while (u8g2.nextPage());

      break;
    case 5:
      u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 8, 30, 30, acel_bmp);
        u8g2.setCursor(16, 48);
        u8g2.print(F("Acceleration")); // write something to the internal memory
      } while (u8g2.nextPage());
      break;
  }
}
*/


/*
void Light_show()
{
  int l = analogRead(light);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.drawCircle(8, 8, 8, U8G2_DRAW_ALL);
    if (l >= 50 && l < 100) {
      u8g2.drawDisc(8, 8, 8, U8G2_DRAW_UPPER_LEFT);
    }
    if (l >= 100 & l < 200) {
      u8g2.drawDisc(8, 8, 8,  U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
    }
    if (l >= 200 && l < 350) {
      u8g2.drawDisc(8, 8, 8,  U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT);
    }
    if (l >= 350) {
      u8g2.drawDisc(8, 8, 8,  U8G2_DRAW_ALL);
    }
    u8g2.setCursor(26, 32);
    u8g2.print(F("Light:"));
    u8g2.setCursor(80, 32);
    u8g2.print(l);
    u8g2.drawHLine(0, 48, 128);
  } while (u8g2.nextPage());
}
//*/

/*
int filter1(int NEW_DATA,int QUEUE[],char n)
{
    int max;
    int min;
    int sum;
    char i;
    QUEUE[0]=NEW_DATA;
    if (QUEUE[0] < 0)
    QUEUE[0] = 0;
    max=QUEUE[0];
    min=QUEUE[0];
    sum=QUEUE[0];
    for(i=n-1;i!=0;i--){
        if(QUEUE[i]>max)max=QUEUE[i];                  
        else if (QUEUE[i]<min)min=QUEUE[i];             
        sum=sum+QUEUE[i];                              
        QUEUE[i]=QUEUE[i-1];                            
    }

    i=n-2;
    sum=sum-max-min+i/2;
    sum=sum/i;                                     
                                                    
    return ((int)sum);
}    
//*/
 
/*  
void Sound_show()
{
  int s = analogRead(sound);
  s = filter1(s,SQueue,SQueueLEN);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.setCursor(28, 32);
    u8g2.print(F("Sound:"));
    u8g2.setCursor(76, 32);
    u8g2.drawXBMP(0, 0, 20, 20, sound_bmp);
    u8g2.print(s);
  } while (u8g2.nextPage());
}
//*/

/*
void Temp_show()
{
  int temp = 0, humid = 0;
  humid = dht.readHumidity();
  temp = dht.readTemperature();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.setCursor(32, 16);
    u8g2.print(F("temp:"));
    u8g2.setCursor(72, 16);
    u8g2.print(temp);
    u8g2.setCursor(88, 16);
    u8g2.print("C");
    u8g2.setCursor(32, 48);
    u8g2.print(F("humid:"));
    u8g2.setCursor(80, 48);
    u8g2.print(humid);
    u8g2.drawLine(25, 0, 25, 64);
    u8g2.drawLine(103, 0, 103, 64);
    u8g2.drawXBMP(0, 0, 20, 30, temp_bmp);
    u8g2.drawXBMP(0, 35, 20, 20, hum_bmp);
  } while (u8g2.nextPage());
}
//*/

/*
void Pressure_show()
{
  float pressure = bmp280.getPressure();
  Serial.println(pressure);
  u8g2.setFont(u8g2_font_t0_16b_mr);
  u8g2.firstPage();
  do {
      u8g2.setCursor(76, 32);
      u8g2.drawXBMP(0, 0, 20, 20, pressure_bmp1);
      u8g2.setCursor(30, 37);
      u8g2.print("Pressure:"); 
      u8g2.setCursor(25, 51);
      u8g2.print(pressure);
      u8g2.print("Pa");
  } while (u8g2.nextPage());
}
*/

/*
void Acele_show()
{
  float ax, ay, az;
  ax = accelemeter.getAccelerationX();
  ay = -accelemeter.getAccelerationY();
  az = accelemeter.getAccelerationZ();
  if (y >= 15) {
    if (ay > 0.2 && ay < 0.5) {
      y = y - 1;
    } else if (ay >= 0.5 && ay < 0.8) {
      y = y - 2;
    } else if (ay >= 0.8) {
      y = y - 3;
    }
  }
  if (y < 57) {
    if (ay < -0.2 && ay > -0.5) {
      y = y + 1;
    } else if (ay <= -0.5 && ay > -0.8) {
      y = y + 2;
    } else if (ay <= -0.8) {
      y = y + 3;
    }
  }
  if (x <= 108) {
    if (ax > 0.2 && ax < 0.5) {
      x = x + 1;
    } else if (ax >= 0.5 && ax < 0.8) {
      x = x + 2;
    } else if (ax >= 0.8) {
      x = x + 3;
    }
  }
  if (x >= 52) {
    if (ax < -0.2 && ax > -0.5) {
      x = x - 1;
    } else if (ax <= -0.5 && ax > -0.8) {
      x= x - 2;
    } else if (ax <= -0.8) {
      x = x - 3;
    }
  }
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_12b_mr);
    u8g2.setCursor(0, 16);
    u8g2.print(F("X:"));
    u8g2.setCursor(16, 16);
    u8g2.print(ax);
    u8g2.setCursor(0, 32);
    u8g2.print(F("Y:"));
    u8g2.setCursor(16, 32);
    u8g2.print(ay);
    u8g2.setCursor(0, 48);
    u8g2.print(F("Z:"));
    u8g2.setCursor(16, 48);
    u8g2.print(az);
    u8g2.drawLine(50, 60, 50, 10);
    u8g2.drawLine(110, 10, 50, 10);
    u8g2.drawLine(110, 60, 50, 60);
    u8g2.drawLine(110, 60, 110, 10);
    u8g2.drawDisc(x, y, 3, U8G2_DRAW_ALL);
  } while (u8g2.nextPage());
}
*/
void SetDS3231(Time tim)
{
  Clock.setSecond(tim.second);//Set the second 
  Clock.setMinute(tim.minute);//Set the minute 
  Clock.setHour(tim.hour);  //Set the hour 
  //Clock.setDoW(4);    //Set the day of the week 1-7
  Clock.setDate(tim.date);  //Set the date of the month
  Clock.setMonth(tim.month);  //Set the month of the year
  Clock.setYear(tim.year);  //Set the year (Last two digits of the year)
}
void ReadDS3231(Time *tim)
{
  int second,minute,hour,date,month,year,temperature; 
  second=Clock.getSecond();
  minute=Clock.getMinute();
  hour=Clock.getHour(h12, PM);
  date=Clock.getDate();
  month=Clock.getMonth(Century);
  year=Clock.getYear();

  tim->year  = year;
  tim->month = month;
  tim->date = date;
  tim->hour = hour;
  tim->minute = minute;
  tim->second = second;
  
  temperature=Clock.getTemperature();
  tim->temp=temperature;
  
  Serial.print("20");
  Serial.print(year,DEC);
  Serial.print('-');
  Serial.print(month,DEC);
  Serial.print('-');
  Serial.print(date,DEC);
  Serial.print(' ');
  Serial.print(hour,DEC);
  Serial.print(':');
  Serial.print(minute,DEC);
  Serial.print(':');
  Serial.print(second,DEC);
  Serial.print('\n');
  Serial.print("Temperature=");
  Serial.print(temperature); 
  Serial.print('\n');
}

/*
* 当前时间与闹钟时间比较，如果相等返回1，如果不等返回0
*/
char TimeCompare(Time tim1,Time tim2)
{
  if((tim1.year == tim2.year) && (tim1.month == tim2.month) &&(tim1.date == tim2.date))
    if((tim1.hour == tim2.hour) && (tim1.minute == tim2.minute) &&(tim1.second == tim2.second))
      return 1;
  
  return 0;
}

unsigned int CurrTick(void)
{
  return DelayCnt;  
}


/*计算时间差*/
unsigned int DiffTick(unsigned int curr,unsigned int pre)
{
  if(curr >= pre)  
    return (curr-pre);
  else
    return (~((unsigned int)0) - pre + curr);
}



/*显示当前时间*/
void DispCurrTime(void)
{
  int tmp = 0;
  int temp = 0, humid = 0;
  static int humidPre = 100;
  humid = dht.readHumidity();
  temp = dht.readTemperature();
  //Serial.println(second);
  u8g2.setFont(u8g2_font_t0_16b_mr);
  u8g2.firstPage();
  do {
      u8g2.setCursor(0, 0);
      u8g2.drawXBMP(0, 48, 16, 16, temp_bmpss);
      u8g2.setCursor(20, 63);
      //if(0 != temp)
      u8g2.print(sTime.temp);//显示温度
      //u8g2.print("/");
      u8g2.setCursor(36, 63);
      u8g2.print("C");
      u8g2.drawXBMP(80, 48, 16, 16, hum_hmps);
      u8g2.setCursor(96, 63);
      if(0 != humid)
      {
        u8g2.print(humid);//显示湿度
        humidPre = humid;
      }
      else
      {
        u8g2.print(humidPre);//显示湿度
      }
      u8g2.setCursor(120, 63);
      u8g2.print("%");
      u8g2.setCursor(32, 24);
      tmp = sTime.year/10;
      u8g2.print(tmp);
      //u8g2.print(sTime.year); 
      u8g2.setCursor(40, 24);
      tmp = sTime.year%10;
      u8g2.print(tmp);
       
      u8g2.setCursor(48, 24);
      u8g2.print("/");

      u8g2.setCursor(56, 24);
      tmp = sTime.month/10;
      u8g2.print(tmp);
      u8g2.setCursor(64, 24);
      tmp = sTime.month%10;
      u8g2.print(tmp);
      
      
      u8g2.setCursor(72, 24);
      u8g2.print("/");
      
      u8g2.setCursor(80, 24);
      tmp = sTime.date/10;
      u8g2.print(tmp);
      u8g2.setCursor(88, 24);
      tmp = sTime.date%10;
      u8g2.print(tmp);
    
      u8g2.setCursor(32, 40);
      tmp = sTime.hour/10;
      u8g2.print(tmp);
      u8g2.setCursor(40, 40);
      tmp = sTime.hour%10;
      u8g2.print(tmp);
     
      u8g2.setCursor(48, 40);
      u8g2.print(":");
      
      u8g2.setCursor(56, 40);
      tmp = sTime.minute/10;
      u8g2.print(tmp);
      u8g2.setCursor(64, 40);
      tmp = sTime.minute%10;
      u8g2.print(tmp);
      
      u8g2.setCursor(72, 40);
      u8g2.print(":");
  
      u8g2.setCursor(80, 40);
      tmp = sTime.second/10;
      u8g2.print(tmp);
      u8g2.setCursor(88, 40);
      tmp = sTime.second%10;
      u8g2.print(tmp);
  } while (u8g2.nextPage());
}

/*显示设置时间菜单界面*/
void DispSetTimeMenu(void)
{
     /*
     u8g2.firstPage();
     do {
     } while (u8g2.nextPage());

     这是U8G2提供的一种显示模式，firstPage会清屏，do while之间的东西是我们要显示的东西，nextPage会发送一个刷新命令给OLED 屏幕，从绘图像。
     */
     u8g2.firstPage();
      do {
        u8g2.setFont(u8g2_font_t0_16b_mr);//这个是设置要使用的字库文件，我们用的是宽为8个像素点，高位16个像素点的字体
        u8g2.drawXBMP(49, 4, 30, 30, time_bmp1);//显示一张图片
        u8g2.setCursor(32, 48);//设置要显示的位置
        u8g2.print(F("Set Time")); // write something to the internal memory 显示字体
      } while (u8g2.nextPage());
}
/*显示设置闹钟菜单界面*/
void DispSetAlarmMenu(void)
{
   u8g2.firstPage();
      do {
        //u8g2.setFont(u8g2_font_t0_12b_mr);//
        //u8g2.setFont(u8g2_font_t0_16b_mr);
        u8g2.drawXBMP(49, 8, 30, 30, alarm_bmp1);
        u8g2.setCursor(32, 48);
        u8g2.print(F("Set Alarm")); // write something to the internal memory
        //u8g2.setCursor(43, 49);
        //u8g2.print(F("Humidity"));    // write something to the internal memory
      } while (u8g2.nextPage());
}

/*计算选择光标移动的位置*/
void CalculationsShowPosition(char option,Coordinate * coord)
{
  switch(option)    
  {
  case YEAR_H://0
  coord->x = 32;
  coord->y = 24;
  break;
  
  case YEAR_L://1
  coord->x = 40;
  coord->y = 24;
  break;
  
  case MONTH_H://2
  coord->x = 56;
  coord->y = 24;
  break;
  
  case MONTH_L://3
  coord->x = 64;
  coord->y = 24;
  break;
  
  case DATE_H://4
  coord->x = 80;
  coord->y = 24;
  break;
  
  case DATE_L://5
  coord->x = 88;
  coord->y = 24;
  break;
  
  case HOUR_H://6
  coord->x = 32;
  coord->y = 40;
  break;
  case HOUR_L://7
  coord->x = 40;
  coord->y = 40;
  break;
  case MINUTE_H://8
  coord->x = 56;
  coord->y = 40;
  break;
  case MINUTE_L://9
  coord->x = 64;
  coord->y = 40;
  break;
  case SECOND_H://10
  coord->x = 80;
  coord->y = 40;
  break;
  
  case SECOND_L://11
  coord->x = 88;
  coord->y = 40;
  break;

  case EXIT://12
  coord->x = 56;
  coord->y = 56;
  break;
  
  default:
  break;
  }
}

/*显示设置菜单中的具体项目
*参数1：选择光标应该停留的项目
*参数2：0 显示设置时间项目 1 显示设置闹钟项目
*/
void DispSubMenu(int suboption, int *dispp, char select)
{
  //int tmp=0;
  Coordinate sDispCoordinate;
  
  CalculationsShowPosition(suboption,&sDispCoordinate);
  
  u8g2.setFont(u8g2_font_t0_16b_mr);
  u8g2.firstPage();
  do {
      u8g2.setCursor(0, 0);
      if(!select)
      u8g2.drawXBMP(0, 0, 20, 20, times_bmp1);//时间设置
      else
      u8g2.drawXBMP(0, 0, 20, 20, alarms_bmp1);//闹钟设置

      u8g2.setCursor(32, 24);
      //tmp = sTime.year/10;
      //u8g2.print(tmp);
      u8g2.print(dispp[YEAR_H]);

      u8g2.setCursor(40, 24);
      //tmp = sTime.year%10;
      //u8g2.print(tmp);
      u8g2.print(dispp[YEAR_L]);
      
      u8g2.setCursor(48, 24);
      u8g2.print("/");
      
      u8g2.setCursor(56, 24);
      //tmp = sTime.month/10;
      //u8g2.print(tmp);
      u8g2.print(dispp[MONTH_H]);

      u8g2.setCursor(64, 24);
      //tmp = sTime.month%10;
      //u8g2.print(tmp);
      u8g2.print(dispp[MONTH_L]);
      
      u8g2.setCursor(72, 24);
      u8g2.print("/");
      
      u8g2.setCursor(80, 24);
      //tmp = sTime.date/10;
      //u8g2.print(tmp);
      u8g2.print(dispp[DATE_H]);

      u8g2.setCursor(88, 24);
      //tmp = sTime.date%10;
      //u8g2.print(tmp);
      u8g2.print(dispp[DATE_L]);

      u8g2.setCursor(32, 40);
      //tmp = sTime.hour/10;
      //u8g2.print(tmp);
      u8g2.print(dispp[HOUR_H]);

      u8g2.setCursor(40, 40);
      //tmp = sTime.hour%10;
      //u8g2.print(tmp);
      u8g2.print(dispp[HOUR_L]);
      
      u8g2.setCursor(48, 40);
      u8g2.print(":");
      
      u8g2.setCursor(56, 40);
      //tmp = sTime.minute/10;
      //u8g2.print(tmp);
      u8g2.print(dispp[MINUTE_H]);

      u8g2.setCursor(64, 40);
      //tmp = sTime.minute%10;
      //u8g2.print(tmp);
      u8g2.print(dispp[MINUTE_L]);
      
      u8g2.setCursor(72, 40);
      u8g2.print(":");
      
      u8g2.setCursor(80, 40);
      //tmp = sTime.second/10;
      //u8g2.print(tmp);
      u8g2.print(dispp[SECOND_H]);

      u8g2.setCursor(88, 40);
      //tmp = sTime.second%10;
      //u8g2.print(tmp);
      u8g2.print(dispp[SECOND_L]);

      u8g2.setCursor(48, 56);
      u8g2.print("Exit");

      u8g2.drawLine(sDispCoordinate.x, (sDispCoordinate.y+1), (sDispCoordinate.x+8), (sDispCoordinate.y+1)); 
  } while (u8g2.nextPage());
  
}
/*显示设置的具体项目的过程*/
void DispSetOptions(int suboption,int *dispp,char select)
{
  int tmp=0;
  u8g2.setFont(u8g2_font_t0_16b_mr);
  u8g2.firstPage();
  do {
      u8g2.setCursor(0, 0);
      //u8g2.drawXBMP(0, 0, 20, 20, times_bmp1);
      if(!select)
      u8g2.drawXBMP(0, 0, 20, 20, times_bmp1);//时间设置
      else
      u8g2.drawXBMP(0, 0, 20, 20, alarms_bmp1);//闹钟设置
      
      u8g2.setCursor(32, 24);
      //tmp = sTime.year/10;
      if(YEAR_H==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[YEAR_H]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[YEAR_H]);

      u8g2.setCursor(40, 24);
      //tmp = sTime.year%10;
      if(YEAR_L==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[YEAR_L]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[YEAR_L]);
      
      u8g2.setCursor(48, 24);
      u8g2.print("/");
      
      u8g2.setCursor(56, 24);
      //tmp = sTime.month/10;
      if(MONTH_H==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[MONTH_H]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[MONTH_H]);

      u8g2.setCursor(64, 24);
      //tmp = sTime.month%10;
      if(MONTH_L==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[MONTH_L]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[MONTH_L]);
      
      u8g2.setCursor(72, 24);
      u8g2.print("/");
      
      u8g2.setCursor(80, 24);
      //tmp = sTime.date/10;
      if(DATE_H==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[DATE_H]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[DATE_H]);

      u8g2.setCursor(88, 24);
      //tmp = sTime.date%10;
      if(DATE_L==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[DATE_L]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[DATE_L]);

      u8g2.setCursor(32, 40);
      //tmp = sTime.hour/10;
      if(HOUR_H==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[HOUR_H]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[HOUR_H]);

      u8g2.setCursor(40, 40);
      //tmp = sTime.hour%10;
      if(HOUR_L==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[HOUR_L]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[HOUR_L]);
      
      u8g2.setCursor(48, 40);
      u8g2.print(":");
      
      u8g2.setCursor(56, 40);
      //tmp = sTime.minute/10;
      if(MINUTE_H==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[MINUTE_H]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[MINUTE_H]);

      u8g2.setCursor(64, 40);
      //tmp = sTime.minute%10;
      if(MINUTE_L==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[MINUTE_L]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[MINUTE_L]);
      
      u8g2.setCursor(72, 40);
      u8g2.print(":");
      
      u8g2.setCursor(80, 40);
      //tmp = sTime.second/10;
      if(SECOND_H==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[SECOND_H]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[SECOND_H]);

      u8g2.setCursor(88, 40);
      //tmp = sTime.second%10;
      if(SECOND_L==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print(dispp[SECOND_L]);
        u8g2.setDrawColor(1);
      }
      else
        u8g2.print(dispp[SECOND_L]);

      u8g2.setCursor(48, 56);
      if(EXIT==suboption)
      {
        u8g2.setDrawColor(0);
        u8g2.print("Exit");
        u8g2.setDrawColor(1);
      }
      else
      u8g2.print("Exit");

  } while (u8g2.nextPage());
}



void SubMenuPecess(int *sbumenuption,char select)
{
  int Year = 0;
  int SetMonth = 0;
  int LeapYear = 0;
  int PreValue = 0;
  int CheckDate = 0;
  int ChechMonth = 0;
  int MaxDateNums = 0;
  if(NO_SET == SetOptionStatus)//没有进入下一级设置选项
  {
    if(SHORT_PRESS == Press)//在子菜单中有短按键按下。  
    {
      Press = NO_PRESS;
      (*sbumenuption)++;//滑向同级选项的下一个
      Serial.println(*sbumenuption); // prints a string to a serial port
      if(SENTRY == *sbumenuption)//判断是否本级菜单已经轮回完成，如果完成重新开始SENTRY
      {
        *sbumenuption = YEAR_H;
      }
    }
    else if(LONG_PRESS == Press)//在子菜单中有长按键按下。
    {
      Press = NO_PRESS;
      if(EXIT == *sbumenuption)//如果是本级菜单的EXIT项目上按下的长按键，则退出本级菜单返回到上一级。
      {
        *sbumenuption = NO_SUB;
        if(!select)//设置当前时间
        {
          sSetTime.year = SettingArray[YEAR_H]*10+SettingArray[YEAR_L];
          sSetTime.month = SettingArray[MONTH_H]*10+SettingArray[MONTH_L];
          sSetTime.date = SettingArray[DATE_H]*10+SettingArray[DATE_L];
          sSetTime.hour = SettingArray[HOUR_H]*10+SettingArray[HOUR_L];
          sSetTime.minute = SettingArray[MINUTE_H]*10+SettingArray[MINUTE_L];
          sSetTime.second = SettingArray[SECOND_H]*10+SettingArray[SECOND_L]; 
          if(!TimeCompare(sSetTime,sPreSetTime))//时间不相等则将设置的时间写入时钟模块
          {
            SetDS3231(sSetTime);
          }
        }
        else//设置闹钟时间
        {
          sAlarTime.year = SettingArray[YEAR_H]*10+SettingArray[YEAR_L];
          sAlarTime.month = SettingArray[MONTH_H]*10+SettingArray[MONTH_L];
          sAlarTime.date = SettingArray[DATE_H]*10+SettingArray[DATE_L];
          sAlarTime.hour = SettingArray[HOUR_H]*10+SettingArray[HOUR_L];
          sAlarTime.minute = SettingArray[MINUTE_H]*10+SettingArray[MINUTE_L];
          sAlarTime.second = SettingArray[SECOND_H]*10+SettingArray[SECOND_L];  
        }
        
        return;
      }
      if(NO_SET == SetOptionStatus)//如果是在当前设置项的状态为未设置的情况下，按下长按键则进入设置状态。
      {
        SetOptionStatus = SETTING;
        return;
      }
    }
    //Serial.println("DispSubMenu(SubMenuTimeIndex);"); // prints a string to a serial port
    DispSubMenu(*sbumenuption,SettingArray,select);
  }
  else
  {
    //Serial.println("SETTING == SetOptionStatus"); // prints a string to a serial port
    if(SHORT_PRESS == Press)//进入设置项，进行设置参数
    {
      Press = NO_PRESS;
      PreValue = SettingArray[*sbumenuption];
      SettingArray[*sbumenuption]++;
      switch(*sbumenuption)
      {
      case YEAR_H:
      case YEAR_L:
      if(SettingArray[*sbumenuption]>9)//如果是年怎高低位可以去0-9之间的任何数字。
        SettingArray[*sbumenuption] = 0;
      break;

      case MONTH_H:
      if(1==SettingArray[MONTH_H])//月份的十位
      {
        if(SettingArray[MONTH_L]>2)//月份的十位为1时，个位只能是0,1,2
        {
          SettingArray[MONTH_L] = 0;//我们直接取零
        }
      }
      if(SettingArray[*sbumenuption]>1)//月份的十位不会大于1，
      {
        SettingArray[*sbumenuption] = 0;
      }
      break;

      case MONTH_L:
      if(!SettingArray[MONTH_H])
      {
        if(SettingArray[*sbumenuption]>9)
        SettingArray[*sbumenuption] = 1;
      }
      else
      {
        if(SettingArray[*sbumenuption]>2)
        SettingArray[*sbumenuption] = 0;
      }

      
      break;

      case DATE_H:
      SetMonth = SettingArray[MONTH_H]*10 + SettingArray[MONTH_L];
      Year = SettingArray[YEAR_H]*10 + SettingArray[YEAR_L] + 2000;
      LeapYear = (0==Year%400)? 1:((0==Year%4)&&(0!=Year%100)?1:0);
      if(2==SetMonth)//只有2月师日期的十位与其他月份不一样
      {
        if(2==SettingArray[*sbumenuption])
        {
          if(!LeapYear)
          {
            if(SettingArray[DATE_L]>8)
            SettingArray[DATE_L] = 0;
          }
        }
        else if(SettingArray[*sbumenuption]>2)
        {
          SettingArray[*sbumenuption] = 0;
        }  
        else
          ;
      }
      else
      {
        if(3==SettingArray[*sbumenuption])
        {
          if((4==SetMonth)||(6==SetMonth)||(9==SetMonth)||(11==SetMonth))
          {
            if(SettingArray[DATE_L]>0)
              SettingArray[DATE_L] = 0;
          }
          else
          {
            if(SettingArray[DATE_L]>1)
              SettingArray[DATE_L] = 0;
          }
        }
        else if(SettingArray[*sbumenuption]>3)
        {SettingArray[*sbumenuption] = 0;}
        else
        {;}
      }  
      break;

      case DATE_L:
      SetMonth = SettingArray[MONTH_H]*10 + SettingArray[MONTH_L];
      Year = SettingArray[YEAR_H]*10 + SettingArray[YEAR_L] + 2000;
      LeapYear = (0==Year%400)? 1:((0==Year%4)&&(0!=Year%100)?1:0);
      
      if(0==SettingArray[DATE_H])
      {
          if(SettingArray[*sbumenuption]>9)//十位为零，日期从1开始
            SettingArray[*sbumenuption] = 1;
      }
      else if(3==SettingArray[DATE_H])
      {
        if((4==SetMonth)||(6==SetMonth)||(9==SetMonth)||(11==SetMonth))
        {
          SettingArray[*sbumenuption] = 0;
        }//十位为3，个位只能是0
        else
        {
          if(SettingArray[*sbumenuption]>1)//十位为3，个位只能是0或1
            SettingArray[*sbumenuption] = 0;
        }
      }
      else//1,2
      {
        if((2==SetMonth)&&(!LeapYear))
        {
          if(SettingArray[*sbumenuption]>8)
            SettingArray[*sbumenuption] = 0;
        }
        else
        {
          if(SettingArray[*sbumenuption]>9)//十位为1或2，个位取0-9
            SettingArray[*sbumenuption] = 0;
        }   
      }
      break;
      
      case HOUR_H:
      if(2 == SettingArray[*sbumenuption])
      {
        if(SettingArray[HOUR_L]>3)
          SettingArray[HOUR_L] = 0;
      }
      else if(SettingArray[*sbumenuption]>2)//十位为0,1或2，
        SettingArray[*sbumenuption] = 0;
      else
       ;
      break;

      case HOUR_L:
      if(2==SettingArray[HOUR_H])//
      {
        if(SettingArray[*sbumenuption]>3)
          SettingArray[*sbumenuption] = 0;
      }
      else
      {
        if(SettingArray[*sbumenuption]>9)
          SettingArray[*sbumenuption] = 0; 
      }
      break;

      default:
      if(SettingArray[*sbumenuption]>MaxVal[*sbumenuption])//设置的值大于这个值实际中所允许的最大值
      {
        SettingArray[*sbumenuption] = 0;
      }
      break;
      }
      
      /*
      if(MONTH_L==*sbumenuption)
      {
        if(1==SettingArray[MONTH_H])//月份的十位数为1，就是说最小都是10月份
        {
          if(SettingArray[*sbumenuption]>2)//个位最大只能是2
          {
            SettingArray[*sbumenuption]=1;//从1重新开始
          }
        }
      }
      else if(MONTH_H==*sbumenuption)
      {
        if(SettingArray[MONTH_L]>2)//月份个位大于2
        {
          if(1==SettingArray[*sbumenuption])//月份的十位只能取0
          {SettingArray[*sbumenuption]=0;}
        }
      }
      else if(DATE_L==*sbumenuption)
      {
        if(3==SettingArray[DATE_H])//日期的十位数为3，就是说最小都是30日
        {
          if(SettingArray[*sbumenuption]>1)//个位最大只能是1
          {
            SettingArray[*sbumenuption]=0;//从1重新开始
          }
        } 
      }
      else if(DATE_H==*sbumenuption)
      {
        if(SettingArray[DATE_L]>1)//日期个位大于1
        {
          if(3==SettingArray[*sbumenuption])//日期的十位只能取0,1,2
          {SettingArray[*sbumenuption]=0;}
        }
      }
      else if(HOUR_L==*sbumenuption)
      {
        if(2==SettingArray[HOUR_H])//小时的十位数为2，就是说最小都是20时
        {
          if(SettingArray[*sbumenuption]>3)//个位只能取0,1,2,3
          {
            SettingArray[*sbumenuption]=0;//从1重新开始
          }
        } 
      }
      else if(HOUR_H==*sbumenuption)
      {
        if(SettingArray[HOUR_L]>3)//小时的个位大于3
        {
          if(2==SettingArray[*sbumenuption])//小时的十位只能取0和1
          {SettingArray[*sbumenuption]=0;}
        }
      }
      else
      {;}
      
      if(SettingArray[*sbumenuption]>MaxVal[*sbumenuption])//设置的值大于这个值实际中所允许的最大值
      {
        if((MONTH_L == *sbumenuption)&&(0 == SettingArray[MONTH_H]))//月份是从1开始的不是从0开始时的，跳过0月
          SettingArray[*sbumenuption] = 1;
        else if((DATE_L == *sbumenuption)&&(0 == SettingArray[DATE_H]))//
          SettingArray[*sbumenuption] = 1;
        else
          SettingArray[*sbumenuption] = 0;
      }*/
    }
    else if(LONG_PRESS == Press)//退出设置状态
    {
      SetOptionStatus = NO_SET;
      Press = NO_PRESS;
      if(0 == sTime.month)//月份从1开始
         sTime.month = 1;
      if(0 == sTime.date)//日期从1开始
        sTime.date = 1;
      ChechMonth =  SettingArray[MONTH_H]*10 + SettingArray[MONTH_L];
      CheckDate = SettingArray[DATE_H]*10 + SettingArray[DATE_L];
      if(2==ChechMonth)
      {
        if(!LeapYear)
          if(CheckDate>28) 
          {
            SettingArray[DATE_H] = 0;
            SettingArray[DATE_L] = 1;
          }
      }
      else if((4==ChechMonth)||(6==ChechMonth)||(9==ChechMonth)||(11==ChechMonth))
      {
        if(CheckDate>30)  
        {
          SettingArray[DATE_H] = 0;
          SettingArray[DATE_L] = 1;
        }
      }
      else
      {;}
      return;
    }  
    else
    {;}
    DispSetOptions(*sbumenuption,SettingArray,select);
    //显示更新后的选项 
  }
}

void MenuPecess(void)
{
     switch(MainMenuIndex)  
    {
    case DISP_TIME:
        DispCurrTime();//显示当前时间
        //Sound_show();
        if(SHORT_PRESS == Press)
        {
            MainMenuIndex = SET_TIME;
            //Serial.println("MainMenuIndex = SET_TIME"); // prints a string to a serial port
        } 
        Press = NO_PRESS;
        //Serial.println("DISP_TIME"); // prints a string to a serial port
        //delay(1000); //delay of 1 second
       
    break;

    case SET_TIME:
        if(NO_SUB == SubMenuTimeIndex)
        {
            if(SHORT_PRESS == Press)//跳入同级菜单的下一项
            {
                MainMenuIndex = SET_ALAR;
                Press = NO_PRESS;
                break;
            }
            else if(LONG_PRESS == Press)//进入子菜单
            {
              SubMenuTimeIndex = YEAR_H;
              Press = NO_PRESS;
              SettingArray[YEAR_H] = sTime.year/10;
              SettingArray[YEAR_L] = sTime.year%10;
              SettingArray[MONTH_H] = sTime.month/10;
              SettingArray[MONTH_L] = sTime.month%10;       
              SettingArray[DATE_H] = sTime.date/10;
              SettingArray[DATE_L] = sTime.date%10;       
              SettingArray[HOUR_H] = sTime.hour/10;
              SettingArray[HOUR_L] = sTime.hour%10;        
              SettingArray[MINUTE_H] = sTime.minute/10;
              SettingArray[MINUTE_L] = sTime.minute%10; 
              SettingArray[SECOND_H] = sTime.second/10;
              SettingArray[SECOND_L] = sTime.second%10;
              sPreSetTime = sTime;//即将进行时间设置，记录设置前的时间
              //Serial.println("SubMenuTimeIndex = YEAR_H"); // prints a string to a serial port
              break;
            }
            else
            {;}
            Press = NO_PRESS;
        }
        else//子菜单中
        {
            //Serial.println("SubMenuPecess"); // prints a string to a serial port
            SubMenuPecess(&SubMenuTimeIndex,0);
            break;
        }
        DispSetTimeMenu();
        //Light_show();
        //Serial.println("SET_TIME"); // prints a string to a serial port
        //delay(1000); //delay of 1 second
    break;

    case SET_ALAR: 
        if(NO_SUB == SubMenuAlarIndex)
        {
            if(SHORT_PRESS == Press)//跳入同级菜单的下一项
            {
                MainMenuIndex = DISP_TIME;
                Press = NO_PRESS;
                break;  
            }
            else if(LONG_PRESS == Press)//进入子菜单
            {
              SubMenuAlarIndex = YEAR_H;
              Press = NO_PRESS;
              SettingArray[YEAR_H] = sTime.year/10;
              SettingArray[YEAR_L] = sTime.year%10;
              SettingArray[MONTH_H] = sTime.month/10;
              SettingArray[MONTH_L] = sTime.month%10;       
              SettingArray[DATE_H] = sTime.date/10;
              SettingArray[DATE_L] = sTime.date%10;       
              SettingArray[HOUR_H] = sTime.hour/10;
              SettingArray[HOUR_L] = sTime.hour%10;        
              SettingArray[MINUTE_H] = sTime.minute/10;
              SettingArray[MINUTE_L] = sTime.minute%10; 
              SettingArray[SECOND_H] = sTime.second/10;
              SettingArray[SECOND_L] = sTime.second%10;
              //Serial.println("SubMenuAlarIndex = YEAR_H"); // prints a string to a serial port
              break;
            }
            else
            {;}
            Press = NO_PRESS;
        }
        else
        {
          //Serial.println("SubMenuPecess"); // prints a string to a serial port
          SubMenuPecess(&SubMenuAlarIndex,1);
          break;
        }
        DispSetAlarmMenu();
        //Temp_show();
        //Serial.println("SET_ALAR"); // prints a string to a serial port
        //delay(1000); //delay of 1 second
    break;

    default:
    break;
    }
}
