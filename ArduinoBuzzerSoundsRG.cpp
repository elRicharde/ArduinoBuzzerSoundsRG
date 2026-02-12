#include "ArduinoBuzzerSoundsRG.h"

/* ###############  BuzzerSoundsRgBase ############### */

// Constructor
BuzzerSoundsRgBase::BuzzerSoundsRgBase(int buzzerPin) : _buzzerPin(buzzerPin) {
	pinMode(_buzzerPin, OUTPUT);    // Set Pin for Buzzer as output
}

// Destructor
BuzzerSoundsRgBase::~BuzzerSoundsRgBase() {
	digitalWrite(_buzzerPin, LOW);
}


// public methods
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
		case SoundType::OK:
			ok_sound();
			break;
	}
}

// private methods
void BuzzerSoundsRgBase::dit() {
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DitLength);
	digitalWrite(_buzzerPin, LOW);
}

void BuzzerSoundsRgBase::dah() {
	digitalWrite(_buzzerPin, HIGH);
	pause(MorseCodeTiming::DahLength);
	digitalWrite(_buzzerPin, LOW);
}

void BuzzerSoundsRgBase::db_read_error_sound() {
	// U = dit-dit-dah
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dah();
}

void BuzzerSoundsRgBase::no_auth_sound() {
	// Custom pattern: 5x dit + dah
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dah();
}

void BuzzerSoundsRgBase::auth_ok_sound() {
	// A = dit-dah
	dit(); pause(MorseCodeTiming::DitPause);
	dah();
}

void BuzzerSoundsRgBase::sos_sound() {
	// S = dit-dit-dit, O = dah-dah-dah, S = dit-dit-dit
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit();
	pause(MorseCodeTiming::DahPause); // letter gap S -> O
	dah(); pause(MorseCodeTiming::DitPause);
	dah(); pause(MorseCodeTiming::DitPause);
	dah();
	pause(MorseCodeTiming::DahPause); // letter gap O -> S
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit();
}

void BuzzerSoundsRgBase::sms_sound() {
	// S = dit-dit-dit, M = dah-dah, S = dit-dit-dit
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit();
	pause(MorseCodeTiming::DahPause); // letter gap S -> M
	dah(); pause(MorseCodeTiming::DitPause);
	dah();
	pause(MorseCodeTiming::DahPause); // letter gap M -> S
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit();
}

void BuzzerSoundsRgBase::ok_sound() {
	// O = dah-dah-dah, K = dah-dit-dah
	dah(); pause(MorseCodeTiming::DitPause);
	dah(); pause(MorseCodeTiming::DitPause);
	dah();
	pause(MorseCodeTiming::DahPause); // letter gap O -> K
	dah(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dah();
}

/* ###############  BuzzerSoundsRgNonRtos ############### */
void BuzzerSoundsRgNonRtos::pause(BuzzerSoundsRgBase::MorseCodeTiming pause) {
	delay(static_cast<int>(pause)); // Standard Arduino delay
}
