#pragma once

#define TEENSYDUINO 153

#include <Audio.h>

#include "globals.h"
#include "files.h"

#include "sounds/kick.h"
#include "sounds/tom.h"
#include "sounds/gong.h"
#include "sounds/lose.h"

class SimpleAudioPlayer {
private:
    AudioPlayMemory player;
    AudioOutputAnalogStereo audioOut;
    AudioConnection patchCord;

public:
    SimpleAudioPlayer() : patchCord(player, 0, audioOut, 0) {
        AudioMemory(10);
    }

    void play(const unsigned int *sample) {
        if (player.isPlaying()) {
            player.stop();
        }

        player.play(sample);
    }

    void stop() {
        player.stop();
    }
};

SimpleAudioPlayer audio = SimpleAudioPlayer();

class MuteManager {
private:
    bool muted;
public:
    void toggle() {
        this->setMute(!muted);
    }

    bool getMute() {
        return muted;
    }

    void setMute(bool muted) {
        this->muted = muted;
        arcada.enableSpeaker(muted);
        this->persistMute();
    }

    void update() {
        if (buttons.pressed(ARCADA_BUTTONMASK_SELECT)) {
            toggle();
        }
    }

    void loadMute() {
        uint8_t mutedArray[1];

        if (files.readBinaryFile("/mute.bin", mutedArray, sizeof(mutedArray))) {
            this->setMute(mutedArray[0] == 1 ? true : false);
        } else {
            Serial.println("Failed to load mute state!");
        }
    }

    void persistMute() {
        uint8_t t = 1;
        uint8_t f = 0;
        uint8_t mutedArray[1] = { this->muted ? t : f };

        if (files.writeBinaryFile("/mute.bin", mutedArray, sizeof(mutedArray))) {
            Serial.println("Mute state saved.");
        } else {
            Serial.println("Failed to save mute state!");
        }
    }
};

MuteManager muteManager = MuteManager();
