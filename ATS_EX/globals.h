#pragma once

const uint8_t g_app_id = 45;
const int g_eeprom_address = 0;
long g_storeTime = millis();

bool g_voltagePinConnnected = false;
bool g_ssbLoaded = false;
bool g_fmStereo = true;

bool g_cmdVolume = false;
bool g_cmdStep = false;
bool g_cmdBw = false;
bool g_cmdBand = false;
bool g_settingsActive = false;
bool g_sMeterOn = false;
bool g_displayOn = true;

uint8_t g_muteVolume = 0;
int g_currentBFO = 0;

// Encoder buttons
SimpleButton  btn_Bandwidth(BANDWIDTH_BUTTON);
SimpleButton  btn_BandUp(BAND_BUTTON);
SimpleButton  btn_BandDn(SOFTMUTE_BUTTON);
SimpleButton  btn_VolumeUp(VOLUME_BUTTON);
SimpleButton  btn_VolumeDn(AVC_BUTTON);
SimpleButton  btn_Encoder(ENCODER_BUTTON);
SimpleButton  btn_AGC(AGC_BUTTON);
SimpleButton  btn_Step(STEP_BUTTON);
SimpleButton  btn_Mode(MODE_SWITCH);

volatile int g_encoderCount = 0;

//Frequency tracking
uint16_t g_currentFrequency;
uint16_t g_previousFrequency;

enum SettingType
{
    ZeroAuto,
    Num,
    Switch,
    SwitchAuto
};

struct SettingsItem
{
    char name[5];
    int8_t param;
    uint8_t type;
    void (*manipulateCallback)(int8_t);
};

void doAttenuation(int8_t v);
void doSoftMute(int8_t v);
void doBrightness(int8_t v);
void doSSBAVC(int8_t v = 0);
void doAvc(int8_t v);
void doSync(int8_t v = 0);
void doDeEmp(int8_t v = 0);
void doSWUnits(int8_t v = 0);
void doSSBSoftMuteMode(int8_t v = 0);
void doCutoffFilter(int8_t v);
void doCPUSpeed(int8_t v = 0);

SettingsItem g_Settings[] =
{
    { "ATT", 0,  SettingType::ZeroAuto,     doAttenuation     },  //Attenuation
    { "SM ", 0,  SettingType::Num,          doSoftMute        },  //Soft Mute
    { "SVC", 1,  SettingType::Switch,       doSSBAVC          },  //SSB AVC Switch
    { "Syn", 0,  SettingType::Switch,       doSync            },  //SSB Sync
    { "DeE", 1,  SettingType::Switch,       doDeEmp           },  //FM DeEmphasis (0 - 50, 1 - 75)
    { "AVC", 46, SettingType::Num,          doAvc             },  //Automatic Volume Control
    { "Scr", 80, SettingType::Num,          doBrightness      },  //Screen Brightness
    { "SW ", 0,  SettingType::Switch,       doSWUnits         },  //SW Units
    { "SSM", 1,  SettingType::Switch,       doSSBSoftMuteMode },  //SSB Soft Mute Mode
    { "COF", 1,  SettingType::SwitchAuto,   doCutoffFilter    },  //SSB Cutoff Filter
    { "CPU", 1,  SettingType::Switch,       doCPUSpeed        },  //CPU Frequency
};

enum SettingsIndex
{
    ATT,
    SoftMute,
    SVC,
    Sync,
    DeEmp,
    AutoVolControl,
    Brightness,
    SWUnits,
    SSM,
    CutoffFilter,
    CPUSpeed,
    SETTINGS_MAX
};

const uint8_t g_SettingsMaxPages = 2;
uint8_t g_SettingSelected = 0;
uint8_t g_SettingsPage = 1;
bool g_SettingEditing = false;

//For managing BW
struct Bandwidth
{
    uint8_t idx;      //Internal SI473X index
    const char* desc;
};

int8_t g_bwIndexSSB = 4;
Bandwidth g_bandwidthSSB[] =
{
    {4, "0.5k"},
    {5, "1.0k"},
    {0, "1.2k"},
    {1, "2.2k"},
    {2, "3.0k"},
    {3, "4.0k"}
};

int8_t g_bwIndexAM = 4;
const int g_maxFilterAM = 6;
Bandwidth g_bandwidthAM[] =
{
    {4, "1.0k"}, // 0
    {5, "1.8k"}, // 1
    {3, "2.0k"}, // 2
    {6, "2.5k"}, // 3
    {2, "3.0k"}, // 4 - Default
    {1, "4.0k"}, // 5
    {0, "6.0k"}  // 6
};

int8_t g_bwIndexFM = 0;
Bandwidth g_bandwidthFM[] =
{
    {0, "AUTO"},
    {1, "110k"},
    {2, " 84k"},
    {3, " 60k"},
    {4, " 40k"}
};

int g_tabStep[] =
{
    // AM steps in KHz
    1,
    5,
    9,
    10,
    // Large AM steps in KHz
    50,
    100,
    1000,
    // SSB steps in Hz
    10,
    25,
    50,
    100,
    500
};
int g_amTotalSteps = 7;
int g_amTotalStepsSSB = 4; //Prevent large AM steps appear in SSB mode
int g_ssbTotalSteps = 5;
volatile int g_stepIndex = 3;

int g_tabStepFM[] =
{
    5,  // 50 KHz
    10, // 100 KHz
    100 // 1 MHz
};
uint16_t g_FMStepIndex = 1;
const int g_lastStepFM = (sizeof(g_tabStepFM) / sizeof(int)) - 1;

//Band table structure
struct Band
{
    uint8_t bandType;
    uint16_t minimumFreq;
    uint16_t maximumFreq;
    uint16_t currentFreq;
    uint16_t currentStepIdx;
    int8_t bandwidthIdx;     // Bandwidth table index (internal table in Si473x controller)
    char* tag;
};

const char _literal_SW[3] = "SW"; //To reduce binary image size
const char _literal_EmptyLine[14] = "             ";

Band g_bandList[] =
{
    {LW_BAND_TYPE, 153, 520, 300, 0, 4, "LW"},
    {MW_BAND_TYPE, 520, 1710, 1476, 3, 4, "MW"},
    {SW_BAND_TYPE, SW_LIMIT_LOW, 3500, 1900, 0, 4, _literal_SW},     // 160 Meter
    {SW_BAND_TYPE, 3500, 4500, 3700, 0, 5, _literal_SW},     // 80 Meter
    {SW_BAND_TYPE, 4500, 5600, 4850, 1, 4, _literal_SW},
    {SW_BAND_TYPE, 5600, 6800, 6000, 1, 4, _literal_SW},
    {SW_BAND_TYPE, 6800, 7300, 7100, 0, 4, _literal_SW},     // 40 Meter
    {SW_BAND_TYPE, 7200, 8500, 7200, 1, 4, _literal_SW},     // 41 Meter
    {SW_BAND_TYPE, 8500, 10000, 9604, 1, 4, _literal_SW},
    {SW_BAND_TYPE, 10000, 11200, 10100, 0, 4, _literal_SW},  // 30 Meter
    {SW_BAND_TYPE, 11200, 12500, 11940, 1, 4, _literal_SW},
    {SW_BAND_TYPE, 13400, 13900, 13600, 1, 4, _literal_SW},
    {SW_BAND_TYPE, 14000, 14500, 14200, 0, 4, _literal_SW},  // 20 Meter
    {SW_BAND_TYPE, 15000, 15900, 15300, 1, 4, _literal_SW},
    {SW_BAND_TYPE, 17200, 17900, 17600, 1, 4, _literal_SW},
    {SW_BAND_TYPE, 18000, 18300, 18100, 0, 4, _literal_SW},  // 17 Meter
    {SW_BAND_TYPE, 21000, 21400, 21200, 0, 4, _literal_SW},  // 15 Meter
    {SW_BAND_TYPE, 21400, 21900, 21500, 1, 4, _literal_SW},  // 13 Meter
    {SW_BAND_TYPE, 24890, 26200, 24940, 0, 4, _literal_SW},  // 12 Meter
    {SW_BAND_TYPE, 26200, 28000, 27500, 0, 4, "CB"},  // CB Band (11 Meter)
    {SW_BAND_TYPE, 28000, SW_LIMIT_HIGH, 28400, 0, 4, _literal_SW},  // 10 Meter
    {FM_BAND_TYPE, 6400, 10800, 7000, 1, 0, "  "},
    {FM_BAND_TYPE, 8400, 10800, 10570, 1, 0, "  "},
};

const int g_lastBand = (sizeof(g_bandList) / sizeof(Band)) - 1;
int g_bandIndex = 1;

// Modulation
volatile uint8_t g_currentMode = FM;
const char* g_bandModeDesc[] = { "FM ", "LSB", "USB", "AM ", "CW " };
volatile uint8_t g_prevMode = FM;
uint8_t g_seekDirection = 1;

//Special logic for fast and responsive frequency surfing
uint32_t g_lastFreqChange = 0;
bool g_processFreqChange = 0;
uint8_t g_volume = DEFAULT_VOLUME;

Rotary g_encoder = Rotary(ENCODER_PIN_A, ENCODER_PIN_B);
SI4735 g_si4735;