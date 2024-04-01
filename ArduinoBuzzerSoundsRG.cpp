#include <ArduinoBuzzerSoundsRG.h>

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
