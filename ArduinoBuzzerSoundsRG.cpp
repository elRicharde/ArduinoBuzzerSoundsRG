#include <CoolCarLib.h>

/* ###############  BuzzerSoundsRgBase ############### */

// Constructor
BuzzerSoundsRgBase(int buzzerPin) {
  _buzzerPin = buzzerPin;
  pinMode(_buzzerPin, OUTPUT);    // Set Pin for Buzzer as output
}

// virtual destructor
virtual ~BuzzerSoundsRgBase() {
	// Destructor-Logic to be placed here if needed
}


// public methods
// method to play a sound based on enum type
void playSound(SoundType sound) {
	switch (sound) {
		case SoundType::DbReadError:
			db_read_error_sound();
			break;
		case SoundType::NoAuth:
			no_auth_sound();
			break;
		case SoundType::AuthOk:
			auth_ok_sound();
			break;
		default:
			// nothing
	}
}
uint8_t CoolCarBasic::getMaxPassengers(){    
    return maxPassengers;
}

uint16_t CoolCarBasic::getSpeed(){    
    return speed;
}

void CoolCarBasic::setSpeed(uint16_t sp){    
    speed = sp;
}

void CoolCarBasic::hoot(){
    Serial.println("beep! beep! beep!");
}

/* #################  CoolCar ################ */

/**********  Public Functions **********/

void CoolCar::init(){    
    currentSpeed = 0;
    airConLevel = CC_AC_OFF;
}

uint8_t CoolCar::getMaxPassengers(){    
    return maxPassengers;
}

uint16_t CoolCar::getMaxSpeed(){    
    return maxSpeed;
}

float CoolCar::getLengthInMeters(){
    return length;
}

uint16_t CoolCar::getCurrentSpeed(){
    return currentSpeed;
}

void CoolCar::hoot(){
    Serial.println("beep! beep! beep!");
}

bool CoolCar::accelerate(uint16_t accVal){
    bool noLimitViolation = true;
    uint16_t newSpeed = static_cast<uint16_t>(calculateNewSpeed(accVal));
    if(newSpeed > maxSpeed){
        currentSpeed = maxSpeed;
        noLimitViolation = false;
    }
    else{
        currentSpeed = newSpeed;
    }
    return noLimitViolation;
}

void CoolCar::brake(uint16_t brakeVal){
    int16_t newSpeed = calculateNewSpeed(brakeVal * (-1));
    if(newSpeed <= 0){
        currentSpeed = 0;
    }
    else{
        currentSpeed = (uint16_t)newSpeed;
    }
}

void CoolCar::setAirConLevel(cc_ac_level level){
    airConLevel = level;
}

cc_ac_level CoolCar::getAirConLevel(){
    return airConLevel;
}
        
/*********  Private Functions *********/

int16_t CoolCar::calculateNewSpeed(int16_t value){
    int16_t speed = currentSpeed + value;
    return speed;   
}


//#############################################################################
#ifndef ARDUINO_BUZZER_SOUNDS_RG_H
#define ARDUINO_BUZZER_SOUNDS_RG_H

#include <Arduino.h> // will not hurt, as it contains guards against multiple definition


/* ###############  BuzzerSoundsRgBase ############### */

class BuzzerSoundsRgBase {  // Class Declaration
	public: 
	
		// Definition of Morse Code timings and sound-types
		enum class MorseCodeTiming {
			// International Morse code is composed of five elements:
			//   short mark, dot or dit ( . ): "dit duration" is one time unit long
			//   long mark, dash or dah ( _ ): three time units long
			//   inter-element gap between the dits and dahs within a character: one dot duration or one unit long
			//   short gap (between letters): three time units long
			//   medium gap (between words): seven time units long	
			
			DitLength = 100,     // short signal
			DitPause = 100,      // break between signals/signs
			DahLength = 300,     // long signal = Dah = 3xDit
			DahPause = 300,      // break between characters in a word
			WordPause = 700      // break between words
		};

		// Definition of SoundTypes
		enum class SoundType {
			DbReadError,
			NoAuth,
			AuthOk
			SOS
			SMS
		};

		// Constructor
		BuzzerSoundsRgBase(int buzzerPin) {
		  _buzzerPin = buzzerPin;
		  pinMode(_buzzerPin, OUTPUT);    // Set Pin for Buzzer as output
		}

		// virtual destructor
		virtual ~BuzzerSoundsRgBase() {
			// Destructor-Logic to be placed here if needed
		}

		// method to play a sound based on enum type
		void playSound(SoundType sound) {
			switch (sound) {
				case SoundType::DbReadError:
					db_read_error_sound();
					break;
				case SoundType::NoAuth:
					no_auth_sound();
					break;
				case SoundType::AuthOk:
					auth_ok_sound();
					break;
			}
		}
		
	private: 
		// attributes
		int _buzzerPin;
		
		// methods
		virtual void pause(int time_in_ms) = 0; // Reine virtuelle Methode  
		// this abstract method needs to be redefined depending on the usage with or without rtos:
		//
			// class BuzzerSoundsRgNonRtos : public BuzzerSoundsRgBase {
			// public:
			//     // derived class constructor calls base class constructor
			//     BuzzerSoundsRgNonRtos(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}
			//
			//	   redefine abstract method into concrete implementation for use without rtos
			//     void pause(int time_in_ms) override {
			//         delay(time_in_ms); // Standard Arduino delay
			//     }
			// };
			//
			// class BuzzerSoundsRgRTOS : public BuzzerSoundsRgBase {
			// public:
			//     // derived class constructor calls base class constructor
			//     BuzzerSoundsRgRTOS(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}
			//
			//     redefine abstract method into concrete implementation for use with rtos
			//     void pause(int time_in_ms) override {
			//         vTaskDelay(pdMS_TO_TICKS(time_in_ms)); // RTOS delay
			//     }
			// };


		
		void db_read_error_sound() {
		// 2x lang 1x länger
		  digitalWrite(_buzzerPin, HIGH);
		  pause(MorseCodeTiming::DitLength);
		  digitalWrite(_buzzerPin, LOW); 
		  pause(140);
		  digitalWrite(_buzzerPin, HIGH);
		  pause(700);
		  digitalWrite(_buzzerPin, LOW); 
		  pause(140);
		  digitalWrite(_buzzerPin, HIGH);
		  pause(1400);
		  digitalWrite(_buzzerPin, LOW);  
		}


		void no_auth_sound() {
		// 5 kurz 1 lang
		  digitalWrite(_buzzerPin, HIGH);
		  pause(70);
		  digitalWrite(_buzzerPin, LOW); 
		  pause(70);
		  digitalWrite(_buzzerPin, HIGH);
		  pause(70);
		  digitalWrite(_buzzerPin, LOW); 
		  pause(70);
		  digitalWrite(_buzzerPin, HIGH);
		  pause(70);
		  digitalWrite(_buzzerPin, LOW); 
		  pause(70);
		  digitalWrite(_buzzerPin, HIGH);
		  pause(70);
		  digitalWrite(_buzzerPin, LOW); 
		  pause(70);
		  digitalWrite(_buzzerPin, HIGH);
		  pause(70);
		  digitalWrite(_buzzerPin, LOW); 
		  pause(70);
		  digitalWrite(_buzzerPin, HIGH);
		  pause(400);
		  digitalWrite(_buzzerPin, LOW);   
		}


		void auth_ok_sound() {
		// 1 kurz 1 lang    
		  digitalWrite(_buzzerPin, HIGH);
		  pause(100);
		  digitalWrite(_buzzerPin, LOW); 
		  pause(100);
		  digitalWrite(_buzzerPin, HIGH);
		  pause(100);
		  digitalWrite(_buzzerPin, LOW); 
		}

}


	class BuzzerSoundsRTOS : public BuzzerSoundsBase {
	public:
	// Abgeleitete Klasse Konstruktor ruft Basisklasse Konstruktor auf
	BuzzerSoundsRTOS(int buzzerPin) : BuzzerSoundsBase(buzzerPin) {}

	// Redefiniton der Pause-Methode
	void pause(int time_in_ms) override {
		vTaskDelay(pdMS_TO_TICKS(time_in_ms)); // RTOS delay
	}
	};
#endif // ARDUINO_BUZZER_SOUNDS_RG_H


