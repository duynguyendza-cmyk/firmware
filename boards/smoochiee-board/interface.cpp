#include "core/bus_HAL.h"
#include "core/powerSave.h"

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description:   initial setup for the device
***************************************************************************************/



void _setup_gpio() {

    pinMode(UP_BTN, INPUT_PULLUP);
    pinMode(DW_BTN, INPUT_PULLUP);


    pinMode(CC1101_SS_PIN, OUTPUT);
    pinMode(NRF24_SS_PIN, OUTPUT);

    digitalWrite(CC1101_SS_PIN, HIGH);
    digitalWrite(NRF24_SS_PIN, HIGH);
    // Starts SPI instance for CC1101 and NRF24 with CS pins blocking communication at start

    bruceConfigPins.rfModule = CC1101_SPI_MODULE;
    bruceConfigPins.irRx = RXLED;
}
bool isCharging() {
        return false;
        }

int getBattery() {
        return 100;
        }


/*********************************************************************
** Function: setBrightness
** location: settings.cpp
** set brightness value
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    if (brightval == 0) {
        analogWrite(TFT_BL, brightval);
    } else {
        int bl = MINBRIGHT + round(((255 - MINBRIGHT) * brightval / 100));
        analogWrite(TFT_BL, bl);
    }
}

/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler() {
        static bool upLast = false, dwLast = false;
            static bool upLong = false, dwLong = false;
                static uint32_t upTime = 0, dwTime = 0;
                    static uint32_t lastUpEvent = 0, lastDwEvent = 0;

                        bool up = (digitalRead(UP_BTN) == BTN_ACT);
                            bool dw = (digitalRead(DW_BTN) == BTN_ACT);

                                if (up || dw) {
                                        if (!wakeUpScreen())
                                                    AnyKeyPress = true;
                                                            else
                                                                        return;
                                                                            }

                                                                                // ===== UP =====
                                                                                    if (up != upLast && millis() - lastUpEvent > 40) {
                                                                                            lastUpEvent = millis();
                                                                                                    upLast = up;

                                                                                                            if (up) {
                                                                                                                        upTime = millis();
                                                                                                                                    upLong = false;
                                                                                                                                            } else {
                                                                                                                                                        if (!upLong) {
                                                                                                                                                                        UpPress = true;
                                                                                                                                                                                    }
                                                                                                                                                                                            }
                                                                                                                                                                                                }

                                                                                                                                                                                                    if (up && !upLong && millis() - upTime >= 350) {
                                                                                                                                                                                                            EscPress = true;
                                                                                                                                                                                                                    upLong = true;
                                                                                                                                                                                                                        }

                                                                                                                                                                                                                            // ===== DOWN =====
                                                                                                                                                                                                                                if (dw != dwLast && millis() - lastDwEvent > 40) {
                                                                                                                                                                                                                                        lastDwEvent = millis();
                                                                                                                                                                                                                                                dwLast = dw;

                                                                                                                                                                                                                                                        if (dw) {
                                                                                                                                                                                                                                                                    dwTime = millis();
                                                                                                                                                                                                                                                                                dwLong = false;
                                                                                                                                                                                                                                                                                        } else {
                                                                                                                                                                                                                                                                                                    if (!dwLong) {
                                                                                                                                                                                                                                                                                                                    DownPress = true;
                                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                                                                            }

                                                                                                                                                                                                                                                                                                                                                if (dw && !dwLong && millis() - dwTime >= 350) {
                                                                                                                                                                                                                                                                                                                                                        SelPress = true;
                                                                                                                                                                                                                                                                                                                                                                dwLong = true;
                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                    }


/*********************************************************************
** Function: powerOff
** location: mykeyboard.cpp
** Turns off the device (or try to)
**********************************************************************/
void powerOff() {
        return;
        }

/*********************************************************************
** Function: checkReboot
** location: mykeyboard.cpp
** Btn logic to turn off the device (name is odd btw)
*******************************************************************/

void checkReboot() {
        return;
        }

