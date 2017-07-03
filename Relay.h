/*
 * Relay.h
 *
 *  Created on: 4 Jan 2017
 *      Author: v
 */

#ifndef RELAY_H_
#define RELAY_H_

class Relay{
 	uint8_t pinIndex;
 	boolean state;
public:
 	static const boolean initialState = 1;

 	Relay(uint8_t in_pinIndex) {
 		 		pinIndex = in_pinIndex;
 		 		state = initialState;
 	};

 	bool init(){
 		pinMode(pinIndex,OUTPUT);
	 	setState(initialState);
 		return true;
 	};

 	void setState(boolean in_state){
 		state = in_state;
 		digitalWrite(pinIndex,state);
 	}


 	bool getState(){
 		return state;
 	}

 	uint8_t getPinIndex(){
 		return pinIndex;
 	}
};



#endif /* RELAY_H_ */
