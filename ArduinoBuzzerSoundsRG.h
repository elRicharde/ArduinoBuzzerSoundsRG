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
			AuthOk,
			SOS,
			SMS,
			OK
		};

		// Constructor
		explicit BuzzerSoundsRgBase(int buzzerPin);

		// virtual destructor
		virtual ~BuzzerSoundsRgBase();

		// method to play a sound based on enum type
		void playSound(SoundType sound);
				
	protected:
		// methods
		virtual void pause(int time_in_ms) = 0; // Reine virtuelle Methode  
		// this abstract method needs to be redefined depending on the usage with or without Rtos:
		//
			// class BuzzerSoundsRgNonRtos : public BuzzerSoundsRgBase {
			// public:
			//     // derived class constructor calls base class constructor
			//     BuzzerSoundsRgNonRtos(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}
			//
			//	   redefine abstract method into concrete implementation for use without Rtos
			//     void pause(int time_in_ms) override {
			//         delay(time_in_ms); // Standard Arduino delay
			//     }
			// };
			//
			// class BuzzerSoundsRgRtos : public BuzzerSoundsRgBase {
			// public:
			//     // derived class constructor calls base class constructor
			//     BuzzerSoundsRgRtos(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}
			//
			//     redefine abstract method into concrete implementation for use with Rtos
			//     void pause(int time_in_ms) override {
			//         vTaskDelay(pdMS_TO_TICKS(time_in_ms)); // Rtos delay
			//     }
			// };


	private: 
		// attributes
		int _buzzerPin;
		
		// methods
		void db_read_error_sound();

		void no_auth_sound();
		
		void auth_ok_sound();
		
		void sos_sound();
		
		void sms_sound();
		
		void ok_sound();
};

/* ###############  BuzzerSoundsRgRtos ############### */
// sollte in spezifischen Programmen abgeleitet werden, um hier die Abhängigkeit von Rtos zu vermeiden
// class BuzzerSoundsRgRtos : public BuzzerSoundsRgBase {
// 	public:
// 		// derived class constructor calls base class constructor
// 		BuzzerSoundsRgRtos(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}
// 	
// 		// redefine abstract method into concrete implementation for use with Rtos
// 		void pause(int time_in_ms) override {
// 			vTaskDelay(pdMS_TO_TICKS(time_in_ms)); // Rtos delay
// 		}
// };

/* ###############  BuzzerSoundsRgNonRtos ############### */
class BuzzerSoundsRgNonRtos : public BuzzerSoundsRgBase {
	public:
		// derived class constructor calls base class constructor
		BuzzerSoundsRgNonRtos(int buzzerPin) : BuzzerSoundsRgBase(buzzerPin) {}

	protected:
		// redefine abstract method into concrete implementation for use without Rtos
		void pause(int time_in_ms) override; // for Stadnard Arduino / c++ Delay
};

#endif // ARDUINO_BUZZER_SOUNDS_RG_H
