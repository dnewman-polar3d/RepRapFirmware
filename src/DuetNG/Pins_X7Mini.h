#ifndef PINS_DUETNG_H__
#define PINS_DUETNG_H__

#if defined(DUET_WIFI)

# define FIRMWARE_NAME "RepRapFirmware for Duet WiFi"
# define DEFAULT_BOARD_TYPE BoardType::AzteegX7Mini_10
const size_t NumFirmwareUpdateModules = 4;		// 3 modules, plus one for manual upload to WiFi module
# define IAP_FIRMWARE_FILE	"AzteegX7MiniFirmware.bin"
# define WIFI_FIRMWARE_FILE	"DuetWiFiServer.bin"
# define WIFI_WEB_FILE		"DuetWebControl.bin"
#else
# error Firmware name not defined
#endif

#define IAP_UPDATE_FILE		"iap4e.bin"			// hoping eventually to use the same IAP file for both Duet WiFi and Duet Ethernet

#define SUPPORT_INKJET		0					// set nonzero to support inkjet control
#define SUPPORT_ROLAND		0					// set nonzero to support Roland mill
#define SUPPORT_SCANNER		1					// set zero to disable support for FreeLSS scanners

// The physical capabilities of the machine

const size_t DRIVES = 4;						// The number of drives in the machine, including X, Y, and Z plus extruder drives
#define DRIVES_(a,b,c,d,e,f,g,h,i,j) { a,b,c,d }

const int8_t HEATERS = 2;						// The number of heaters in the machine; 0 is the heated bed even if there isn't one
#define HEATERS_(a,b,c,d,e,f,g,h) { a,b }
const size_t MaxDriversPerAxis = 4;				// The maximum number of stepper drivers assigned to one axis

const size_t MAX_AXES = 3;						// The maximum number of movement axes in the machine, usually just X, Y and Z, <= DRIVES
const size_t MIN_AXES = 3;						// The minimum and default number of axes
const size_t MaxExtruders = DRIVES - MIN_AXES;	// The maximum number of extruders
#define MOTION_DRIVES_(a,b,c,d,e,f) { a,b,c }


const size_t NUM_SERIAL_CHANNELS = 2;			// The number of serial IO channels (USB and one auxiliary UART)
#define SERIAL_MAIN_DEVICE SerialUSB
#define SERIAL_AUX_DEVICE Serial

// The numbers of entries in each array must correspond with the values of DRIVES, AXES, or HEATERS. Set values to NoPin to flag unavailability.

// DRIVES

const Pin ENABLE_PINS[DRIVES] = { 46, 47, 48, 49 };
const Pin STEP_PINS[DRIVES] = { 38, 39, 40, 36 };
const Pin DIRECTION_PINS[DRIVES] = { 53, 52, 51, 50 };

// Endstops
// RepRapFirmware only has a single endstop per axis.
// Gcode defines if it is a max ("high end") or min ("low end") endstop and sets if it is active HIGH or LOW.
const Pin END_STOP_PINS[DRIVES] = { 21, 7, 8, 22 };

// Indices for motor current digipots (if any): first 4 are for digipot 1 (on duet)
const uint8_t POT_WIPES[4] = { 1, 3, 2, 0 };
const float SENSE_RESISTOR = 0.1;										// Stepper motor current sense resistor
const float MAX_STEPPER_DIGIPOT_VOLTAGE = (3.3 * 2.5 / (2.7 + 2.5));	// Stepper motor current reference voltage
const float STEPPER_DAC_VOLTAGE_RANGE = 2.02;							// Stepper motor current reference voltage for E1 if using a DAC
const float STEPPER_DAC_VOLTAGE_OFFSET = -0.025;						// Stepper motor current offset voltage for E1 if using a DAC

// HEATERS

const bool HEAT_ON = false;												// false for inverted heater (e.g. Duet v0.6), true for not (e.g. Duet v0.4)
const Pin TEMP_SENSE_PINS[HEATERS] = { 17, 18 };						// Thermistor pin numbers
const Pin HEAT_ON_PINS[HEATERS] = { 19, 20 };							// Heater pin numbers (heater 7 pin TBC)

// Default thermistor parameters
const float BED_R25 = 100000.0;
const float BED_BETA = 3988.0;
const float BED_SHC = 0.0;
const float EXT_R25 = 100000.0;
const float EXT_BETA = 4388.0;
const float EXT_SHC = 0.0;

// Thermistor series resistor value in Ohms
const float THERMISTOR_SERIES_RS = 4700.0;

// Number of SPI temperature sensors to support

const size_t MaxSpiTempSensors = 0;

// Arduino Due pin number that controls the ATX power on/off
const Pin ATX_POWER_PIN = -1;											// Arduino Due pin number that controls the ATX power on/off

// Analogue pin numbers
const Pin Z_PROBE_PIN = 29;												// AFE1_AD1/PB3 Z probe analog input

// Digital pin number to turn the IR LED on (high) or off (low)
const Pin Z_PROBE_MOD_PIN = 58;											// Digital pin number to turn the IR LED on (high) or off (low) on Duet v0.6 and v1.0 (PD26)

// COOLING FANS
const size_t NUM_FANS = 2;
const Pin COOLING_FAN_PINS[NUM_FANS] = { 16, 15 };
const Pin COOLING_FAN_RPM_PIN = NoPin;

// SD cards
const size_t NumSdCards = 1;
const Pin SdCardDetectPins[NumSdCards] = { 41 };						// PD9
const Pin SdWriteProtectPins[NumSdCards] = { NoPin };
const Pin SdSpiCSPins[1] = {56};

// M42 and M208 commands now use logical pin numbers, not firmware pin numbers.
// This next definition defines the highest one.
// This is the mapping from logical pins 60+ to firmware pin numbers
const Pin SpecialPinMap[] =
{
	0, 1, 2, 23, 24, 25, 31	, 37, 43, 44, 45						   	// We allow CS5-CS8 to be used because few users need >4 thermocouples or RTDs
};
const int HighestLogicalPin = 70;										// highest logical pin number on this electronics

// SAM4E Flash locations (may be expanded in the future)
const uint32_t IAP_FLASH_START = 0x00470000;
const uint32_t IAP_FLASH_END = 0x0047FBFF;

// Duet pin numbers to control the WiFi interface
const Pin EspResetPin = 69;				// PD28; Low on this in holds the WiFi module in reset (ESP_RESET)
const Pin EspEnablePin = 61;			// PD29; High to enable the WiFi module, low to power it down (ESP_CH_PD)
const Pin EspTransferRequestPin = 63;	// PD31; Input from the WiFi module indicating that it wants to transfer data (ESP GPIO0)
const Pin SamTfrReadyPin = 62;			// PD30; Output from the SAM to the WiFi module indicating we can accept a data transfer (ESP GPIO4 via 7474)
const Pin SamCsPin = 11;				// PA11; SPI NPCS pin, input from WiFi module

// Timer allocation (no network timer on DuetNG)
// TC0 channel 0 is used for FAN2
// TC0 channel 1 is currently unused (may use ift for a heater or a fan)
// TC0 channel 2 is available for us to use
#define STEP_TC				(TC0)
#define STEP_TC_CHAN		(2)
#define STEP_TC_IRQN		TC2_IRQn
#define STEP_TC_HANDLER		TC2_Handler

#endif
