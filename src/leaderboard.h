#pragma once

#include <Arduino.h>

#include "files.h"

#define HIGHSCORE_FILE "/highscores.bin"
#define MAX_HIGHSCORES 5

class LeaderboardManager
{
public:
    LeaderboardManager()
    {
        
    }

    int submitScore(uint8_t newScore)
    {
        // Initially assume the new score is not a high score
        bool isHighScore = false;

        // Find the position for the new score
        int pos;
        for (pos = 0; pos < MAX_HIGHSCORES; pos++)
        {
            if (newScore > highscores[pos])
            {
                isHighScore = true;
                break;
            }
        }

        // If it's a high score
        if (isHighScore)
        {
            // Shift lower scores down to make room for the new score
            for (int i = MAX_HIGHSCORES -1; i > pos; --i)
            {
                highscores[i] = highscores[i - 1];
            }

            // Insert the new score
            Serial.println("Inserting new score" + String(newScore) + " at position " + String(pos));
            highscores[pos] = newScore;

            // Save the updated scores
            saveScores();
        } else {
            pos = -1;
        }

        return pos;
    }

    void resetScores()
    {
        for (int i = 0; i < MAX_HIGHSCORES; ++i)
        {
            highscores[i] = 0;
        }

        Serial.println("Highscores reset.");
        Serial.println("Highscores:");
        for (int i = 0; i < MAX_HIGHSCORES; ++i)
        {
            Serial.println(highscores[i]);
        }

        saveScores();
    }    

    const uint8_t *getHighScores() const
    {
        return highscores;
    }

    void loadScores()
    {
        // Read the binary high score data
        if (files.readBinaryFile(HIGHSCORE_FILE, highscores, sizeof(this->highscores)))
        {
            // print scores to serial
            Serial.println("High scores:");
            for (int i = 0; i < MAX_HIGHSCORES; ++i)
            {
                Serial.println(highscores[i]);
            }
        } else {
            Serial.println("Failed to load high scores!");
        }
    }

private:
    uint8_t highscores[MAX_HIGHSCORES] = {0};

    void saveScores()
    {
        if (files.writeBinaryFile(
            HIGHSCORE_FILE, 
            highscores, 
            sizeof(highscores)
        )) {
            Serial.println("Highscores saved.");
        } else {
            Serial.println("Failed to save high scores!");
        };
    }
};