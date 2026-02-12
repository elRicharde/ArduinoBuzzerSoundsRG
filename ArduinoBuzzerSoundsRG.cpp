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

// Morse code building blocks — each produces a single beep without trailing pause.
// Pauses between elements (DitPause) and between letters (DahPause) are added
// explicitly in the sound methods to ensure correct Morse code timing.
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
	// Morse "U" (..-) — two short beeps followed by a long one.
	// Suitable for data/read errors: noticeable but not alarming.
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dah();
}

void BuzzerSoundsRgBase::no_auth_sound() {
	// Custom pattern (.....-) — five rapid short beeps + one long tone.
	// Not a standard Morse character. The insistent rapid beeping
	// followed by a long tone clearly signals "access denied".
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dah();
}

void BuzzerSoundsRgBase::auth_ok_sound() {
	// Morse "A" (.-) — one short + one long beep.
	// Quick and pleasant confirmation: "authentication successful".
	dit(); pause(MorseCodeTiming::DitPause);
	dah();
}

void BuzzerSoundsRgBase::sos_sound() {
	// Morse "SOS" (...---...) — the universal distress signal.
	// Use for critical system errors or emergencies that require immediate attention.
	// S (...)
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit();
	pause(MorseCodeTiming::DahPause); // letter gap S -> O
	// O (---)
	dah(); pause(MorseCodeTiming::DitPause);
	dah(); pause(MorseCodeTiming::DitPause);
	dah();
	pause(MorseCodeTiming::DahPause); // letter gap O -> S
	// S (...)
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit();
}

void BuzzerSoundsRgBase::sms_sound() {
	// Morse "SMS" (...--...) — the classic SMS notification pattern.
	// Use for incoming messages, notifications, or non-critical alerts.
	// S (...)
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit();
	pause(MorseCodeTiming::DahPause); // letter gap S -> M
	// M (--)
	dah(); pause(MorseCodeTiming::DitPause);
	dah();
	pause(MorseCodeTiming::DahPause); // letter gap M -> S
	// S (...)
	dit(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dit();
}

void BuzzerSoundsRgBase::ok_sound() {
	// Morse "OK" (-----.-) — acknowledgment/ready signal.
	// Use for successful operations, boot-up confirmation, or "system ready".
	// O (---)
	dah(); pause(MorseCodeTiming::DitPause);
	dah(); pause(MorseCodeTiming::DitPause);
	dah();
	pause(MorseCodeTiming::DahPause); // letter gap O -> K
	// K (-.- )
	dah(); pause(MorseCodeTiming::DitPause);
	dit(); pause(MorseCodeTiming::DitPause);
	dah();
}

/* ###############  BuzzerSoundsRgNonRtos ############### */
void BuzzerSoundsRgNonRtos::pause(BuzzerSoundsRgBase::MorseCodeTiming pause) {
	delay(static_cast<int>(pause)); // Standard Arduino delay
}
