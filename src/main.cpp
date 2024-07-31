#include <Arduino.h>

void setup() {
// write your initialization code here
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
// write your code here
    //convert serial input text into morse code by using the morse code table and built in led
    String morseCode = "";
    String morseTable[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
        "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
    };
    if (Serial.available() > 0) {
        String input = Serial.readString();
        input.trim();
        //convert input to capital
        input.toUpperCase();

        if(input.length()<1){
            return;
        }
        for (int i = 0; i < input.length(); i++) {
            if (input[i] == ' ') {
                morseCode += " ";
            } else {
                morseCode += morseTable[input[i] - 'A'];
                morseCode += " ";
            }
        }
        String output = input + " : " + morseCode;
        Serial.println(output);
        Serial.println("STARTING MORSE CODE TRANSMISSION: CHECK LED");
        for (int i = 0; i < morseCode.length(); i++) {
            if (morseCode[i] == '.') {
                digitalWrite(LED_BUILTIN, HIGH);
                delay(100);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            } else if (morseCode[i] == '-') {
                digitalWrite(LED_BUILTIN, HIGH);
                delay(300);
                digitalWrite(LED_BUILTIN, LOW);
                delay(100);
            } else if (morseCode[i] == ' ') {
                delay(300);
            }
        }
        Serial.println("MORSE CODE TRANSMISSION COMPLETED");
        delay(1000);
    }

}