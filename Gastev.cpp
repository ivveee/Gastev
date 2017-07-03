// Do not remove the include below
#include "Gastev.h"

const int buttonPin = 5;
const int ledPin = 3;
const int relayPin = 11;

#define NUM_ANALOG_USED  NUM_ANALOG_INPUTS // All
#define NUM_DIGITAL_USED 2
#define NUM_BUTTONS  NUM_ANALOG_USED + NUM_DIGITAL_USED
//uint8_t buttonAnalogPins[NUM_BUTTONS] = {A0,A1,A2,A3,A4,A5};

#define NUM_RELAY 4
uint8_t mp3SerialPinRX = 12;
uint8_t mp3SerialPinTX = 11;

Button buttons[NUM_BUTTONS] = {
		Button(PIN_A0),
		Button(PIN_A1),
		Button(PIN_A2),
		Button(PIN_A3),
		Button(PIN_A4),
		Button(PIN_A5),
		Button(2),
		Button(3)
};

Relay relays[NUM_RELAY] = {
		Relay(4),
		Relay(5),
		Relay(6),
		Relay(7),
};
void turnOffAllRelays(){
	DEBUG_PRINT("<all relays off>");
	for(int i=0;i<NUM_RELAY;i++){
		relays[i].setState(Relay::initialState);
	};
}

SoftwareSerial mp3Serial(mp3SerialPinRX, mp3SerialPinTX); // RX, TX
MP3 player(mp3Serial);

struct buttonTableRecord{
	uint16_t soundfileNum;
	uint32_t actionLength;
	uint8_t relayNum;
};

#define EMPTY 0xFF
buttonTableRecord table[NUM_BUTTONS]{
	1, 		55000, 	0, 			// A0 - pin4 55
	2, 		44000, 	1, 			// A1 - pin5 44
	3, 		66000, 	2, 			// A2 - pin6 66
	4, 		42000, 	3, 			// A3 -      42
	5, 		39000, 	EMPTY, 		// A4 - pin7 39
	6, 		47000, 	EMPTY, 		// A5 - pin8 47
	7, 		35000, 	EMPTY, 		// 2 - pin9  35
	8, 		53000, 	EMPTY  		// 3 -       53
};


void (*act)(uint32_t);
uint32_t curTime;
uint32_t whenToRelayReset = 0xFFFFFFFF;
uint32_t whenToStandbyReset = 0xFFFFFFFF;
const uint32_t deltaStandby = 15000;

void loop()
{
	uint32_t curTime = millis();
	if(curTime >= whenToRelayReset){
		turnOffAllRelays();
		whenToRelayReset = 0xFFFFFFFF;
	}
	act(curTime);
}

void standby(uint32_t curTime){
	if(curTime >= whenToStandbyReset)
		act = &waitButton;
}

void waitButton(uint32_t curTime){
	//DEBUG_PRINT("<wait>");
	for(int i=0;i<NUM_BUTTONS;i++){
		Button button = buttons[i];
		bool buttonStateChange = button.getStateChange();
		if(buttonStateChange && (button.getLastState()==0)){
			DEBUG_PRINT("<pressed button>");
			DEBUG_PRINT(button.getPinIndex());
			turnOffAllRelays();
			buttonTableRecord record = table[i];
			player.stop();
			if(record.soundfileNum != EMPTY){
				player.playSong(record.soundfileNum);
				DEBUG_PRINT("<playing file>");
				DEBUG_PRINT(record.soundfileNum);
			}
			if(record.relayNum != EMPTY){
				relays[record.relayNum].setState(0);
				DEBUG_PRINT("<turn on relay>");
				DEBUG_PRINT(relays[record.relayNum].getPinIndex());
			}
			DEBUG_PRINT("<sleep for>");
			DEBUG_PRINT(deltaStandby);
			whenToRelayReset = curTime + record.actionLength;
			whenToStandbyReset = curTime + deltaStandby;
			act = &standby;
			return;
		}
	};
}


void setup()
{
	Serial.begin(9600);
	delay(1000);

	for(int i=0;i<NUM_RELAY;i++){
		relays[i].init();
	};

	for(int i=0;i<NUM_BUTTONS;i++){
		buttons[i].init();
	};

	delay(3000);

	if(buttons[0].getState()==0){
		DEBUG_PRINT("<all relays are on>");
		act = &standby;
		for(int i=0;i<NUM_RELAY;i++){
			relays[i].setState(0);
		};
		return;
	}
	player.setMode(0x00);
	player.setVolume(0x1F);

	act = &waitButton;

	DEBUG_PRINT("<inited>");
}


