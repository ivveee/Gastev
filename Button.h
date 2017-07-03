/*
 * Button.h
 *
 *  Created on: 4 Jan 2017
 *      Author: v
 */

#ifndef BUTTON_H_
#define BUTTON_H_




class  Button{
	 	uint8_t pinIndex;
	 	uint8_t lastState;
	 public:
	 	Button(uint8_t in_pinIndex) {
	 		pinIndex = in_pinIndex;
	 		lastState = 0;
	 	};

	 	bool getState(){
	 		return digitalRead(pinIndex);
	 	}

	 	bool getStateChange(){
	 		bool state = getState();
	 		bool change = (state != lastState);
	 		lastState =state;
	 		return change;
	 	}

	 	bool getLastState(){
	 		return lastState;
	 	}


	 	bool init(){
	 		pinMode(pinIndex,INPUT_PULLUP);
	 		getStateChange();
	 		return true;
	 	}

	 	uint8_t getPinIndex(){
	 		return pinIndex;
	 	}

 };



#endif /* BUTTON_H_ */
