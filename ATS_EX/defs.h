#pragma once

//#define MINIMAL_BUILD
#define INCLUDE_SERIAL_CONTROL
#define SERIAL_BAUD_RATE          57600     // 115200

// If you remark out USE_RDS, project will be compiled without RDS 
// and everything related to RDS will be excluded from build
// Since RDS isn't necessary for operation, removing it from
// the build allows you to implement Serial control. With it
// there is no way to get serial to fit...
#ifdef INCLUDE_SERIAL_CONTROL
enum eSerialCtlCmds
{
  eFMFreqBand,
  eAMFreqBand,
  eSBFreqBand,
  eScanUp,
  eScanDown,
  eVolume,
  eMute,
  eTotSerialCtlCmds
};
#else // !INCLUDE_SERIAL_CONTROL
#define USE_RDS
#endif // !INCLUDE_SERIAL_CONTROL

#define EEPROM_APP_ID				        235
#define EEPROM_DATA_START_ADDRESS   1
#define EEPROM_VERSION_ADDRESS      1000
#define EEPROM_APP_ID_ADDRESS       0

// EEPROM Settings
#define STORE_TIME 10000 // Inactive time to save our settings

// OLED Const values
#define DEFAULT_FONT    FONT8X16POB
#define RST_PIN         -1
#define RESET_PIN       12

// Battery charge monitoring analog pin (Voltage divider 10-10 KOhm directly from battery)
#ifndef INCLUDE_SERIAL_CONTROL         // As long as we code in feedback information (like local volume or scanning changes), there is no room for battery voltage display
                                       // NOTE: IF you remark (or delete out) the INCLUDE_SERIAL_CONTROL condition, the feedback information will automatically be removed!!
#define BATTERY_VOLTAGE_DISPLAY        // If unremarked, removes the code that checks and displays (if found) the voltage divider for reading the battery
#endif // !INCLUDE_SERIAL_CONTROL
#define BATTERY_VOLTAGE_PIN   A1       // This originally showed A2, but in the online schematic they show using the A1 pin (and the A0 pin being used for the encoder)
                                       // So if you wire up your battery voltage divider and notice the display still shows 0, double check which analog pin you wired it too

// Encoder
#define ENCODER_PIN_A 2
#define ENCODER_PIN_B 3

// Buttons
#define MODE_SWITCH       4 
#define BANDWIDTH_BUTTON  5
#define VOLUME_BUTTON     6
#define AVC_BUTTON        7
#define BAND_BUTTON       8 
#define SOFTMUTE_BUTTON   9
#define AGC_BUTTON       11
#define STEP_BUTTON      10

#define ENCODER_BUTTON   14

// Default values
#define MIN_ELAPSED_TIME 100
#define MIN_ELAPSED_RSSI_TIME 150
#define DEFAULT_VOLUME 25
#define ADJUSTMENT_ACTIVE_TIMEOUT 3000

// Band settings
#define SW_LIMIT_LOW		1710
#define SW_LIMIT_HIGH		30000
#define LW_LIMIT_LOW		153
#define CB_LIMIT_LOW		26200
#define CB_LIMIT_HIGH		28000

#define BAND_DELAY                 2
#define VOLUME_DELAY               1 

#define buttonEvent                NULL
