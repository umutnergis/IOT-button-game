#include <Arduino.h>


#define led 8
#define piston 3
#define reset 12
#define black A0
#define red A1 
#define blue A2
#define green A3 

#define blackValue 1
#define redValue 2
#define blueValue 3
#define greenValue 4

int order[10] = {};

// Button order 
int correctOrder[10] = {1, 1, 1, 1, 2, 2, 3, 4, 4, 4};


 
#define DEBUG_MODE
//#define PRINT_MODE


void setup()
{
    #ifdef DEBUG_MODE
    Serial.begin(9600);
    Serial.println("DEBUG MODE");
    #endif
    #ifdef PRINT_MODE
    Serial.begin(9600);
    Serial.println("PRINT MODE");
    #endif
    digitalWrite(reset,HIGH);
    pinMode(reset,OUTPUT);
    pinMode(piston, OUTPUT);
    pinMode(buzzer,OUTPUT);
}

void loop()
{

    #ifdef PRINT_MODE
    while (true)
    {
        Serial.print("A0: ");
        Serial.print(analogRead(black));
        Serial.print(" A1: ");
        Serial.print(analogRead(red));
        Serial.print(" A2: ");
        Serial.print(analogRead(blue));
        Serial.print(" A3: ");
        Serial.println(analogRead(green));
        delay(300);
    }
    #endif


    int blackv = analogRead(black);
    int redv = analogRead(red);
    int bluev = analogRead(blue);
    int greenv = analogRead(green);

    if (blackv >= 1000 || redv >= 1000 || bluev >= 1000 || greenv >= 1000) {
        digitalWrite(buzzer, HIGH);
        delay(150);
        digitalWrite(buzzer, LOW);
        if (blackv >= 1000) {
            addValue(blackValue);
            #ifdef DEBUG_MODE
            Serial.println(" Black added ");
            # endif
            while (analogRead(black) >= 1000) {delay(100);}
        }
        if (redv >= 1000) {
            addValue(redValue);
            #ifdef DEBUG_MODE
            Serial.println(" Red added ");
            #endif
            while (analogRead(red) >= 1000) {delay(100);}
        }
        if (bluev >= 1000) {
            addValue(blueValue);
            #ifdef DEBUG_MODE
            Serial.println(" Blue added ");
            #endif
            while (analogRead(blue) >= 1000) {delay(100);}
        }
        if (greenv >= 1000) {
            addValue(greenValue);
            #ifdef DEBUG_MODE
            Serial.println(" Green added ");
            #endif
            while (analogRead(green) >= 1000) {delay(100);}
        }

        if (checkOrder()) {
            #ifdef DEBUG_MODE
            Serial.println("Sıra doğru");
            #endif
            digitalWrite(piston, HIGH);
            delay(1000);
            digitalWrite(piston,LOW);
            digitalWrite(reset,LOW);
        }
        #ifdef DEBUG_MODE
        printOrder();
        #endif
    }
    delay(150);
}


void addValue(int value) {
    // shift order array by one to left
    for (int i = 0; i < 9; i++) {
        order[i] = order[i + 1];
    }
    // add new value to the last position
    order[9] = value;
}

bool checkOrder () {
    for (int i = 0; i < 10; i++) {
        if (order[i] != correctOrder[i]) {
            return false;
        }
    }
    return true;
}

void printOrder () {
    for (int i = 0; i < 10; i++) {
        Serial.print(order[i]);
        Serial.print(" ");
    }
    Serial.println();
}
