#include <ArduinoBuzzerSoundsRG.h>

/* ###############  BuzzerSoundsRgBase ############### */

// Constructor
BuzzerSoundsRgBase::BuzzerSoundsRgBase(int buzzerPin) {
  _buzzerPin = buzzerPin;
  pinMode(_buzzerPin, OUTPUT);    // Set Pin for Buzzer as output
}

// destructor
BuzzerSoundsRgBase::~BuzzerSoundsRgBase() {
	// Destructor-Logic to be placed here if needed
}


// public methods
// method to play a sound based on enum type
void BuzzerSoundsRgBase::playSound(SoundType sound) {
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

		case SoundType::SOS:
			sos_sound();
			break;
		case SoundType::SMS:
			sms_sound();
			break;
		case SoundType::Ok:
			ok_sound();
			break;	
		default:
			// nothing
	}
}

// privat methods
void BuzzerSoundsRgBase::db_read_error_sound() {
	// DiDitDah
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
}


void BuzzerSoundsRgBase::no_auth_sound() {
	// DiDiDiDiDitDah
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
}


void BuzzerSoundsRgBase::auth_ok_sound() {
	// ditdah
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
}

void BuzzerSoundsRgBase::sos_sound() {
	// didididahdahdahdididit
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);

	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);	
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
	pause(MorseCodeTiming::DitLength);	
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
	pause(MorseCodeTiming::DitLength);	

	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
	pause(MorseCodeTiming::DitLength);		
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);

	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 	
}

void BuzzerSoundsRgBase::sms_sound() {
	// dididit dahdah dididit
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);

	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DahLength);	
	
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
	pause(MorseCodeTiming::DitLength);	
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
	pause(MorseCodeTiming::DahLength);	


	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);

	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
}

void BuzzerSoundsRgBase::ok_sound() {
	// dahdahdah dahditdah
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);

	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DahLength);
	
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);	
	
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW); 
	pause(MorseCodeTiming::DitLength);

	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW); 
}

/* ###############  BuzzerSoundsRgNonRtos ############### */
// protected methods
// Implementierung für Nicht-Rtos Umgebung -> Überschreiben der Abstrakten Pause Methode
void BuzzerSoundsRgNonRtos::pause(int time_in_ms) {
    delay(time_in_ms); // Standard Arduino delay
}
