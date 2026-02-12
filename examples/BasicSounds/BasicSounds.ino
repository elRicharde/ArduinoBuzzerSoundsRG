/*
  BasicSounds - ArduinoBuzzerSoundsRG Example

  Plays all available buzzer sound patterns in sequence.
  Connect a passive buzzer to the defined BUZZER_PIN.
*/

#include <ArduinoBuzzerSoundsRG.h>

const int BUZZER_PIN = 4;

// Create a buzzer instance for non-RTOS Arduino
BuzzerSoundsRgNonRtos buzzer(BUZZER_PIN);

void setup() {
	Serial.begin(9600);
	Serial.println("ArduinoBuzzerSoundsRG - BasicSounds Example");
}

void loop() {
	Serial.println("Playing: DB Read Error");
	buzzer.playSound(BuzzerSoundsRgBase::SoundType::DbReadError);
	delay(1000);

	Serial.println("Playing: No Auth");
	buzzer.playSound(BuzzerSoundsRgBase::SoundType::NoAuth);
	delay(1000);

	Serial.println("Playing: Auth OK");
	buzzer.playSound(BuzzerSoundsRgBase::SoundType::AuthOk);
	delay(1000);

	Serial.println("Playing: SOS");
	buzzer.playSound(BuzzerSoundsRgBase::SoundType::SOS);
	delay(1000);

	Serial.println("Playing: SMS");
	buzzer.playSound(BuzzerSoundsRgBase::SoundType::SMS);
	delay(1000);

	Serial.println("Playing: OK");
	buzzer.playSound(BuzzerSoundsRgBase::SoundType::OK);
	delay(3000);

	Serial.println("--- Restarting ---");
}
