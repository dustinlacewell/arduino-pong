#pragma once

#include "globals.h"
#include "ball.h"
#include "paddle.h"
#include "audioPlayer.h"
#include <cmath>
#include <algorithm>
#include <limits>

enum class PaddleSide
{
    LEFT,
    RIGHT
};

// Helper function to clamp value between min and max
float clamp(float value, float min, float max)
{
    return std::max(min, std::min(max, value));
}

void checkNaN(Ball& ball, const char *msg, float ballNextX, float closestX, float distanceX, float distanceSquared, float distance, float normalX, float ballNextY, float closestY, float distanceY, float normalY)
{
    if (isnan(ball.y))
    {
        Serial.print("NaN: ");
        Serial.println(msg);
        Serial.println("Ball y is NAN");
        Serial.print("ballNextY: ");
        Serial.println(ballNextY);
        Serial.print("closestY: ");
        Serial.println(closestY);
        Serial.print("distanceY: ");
        Serial.println(distanceY);
        Serial.print("distanceSquared: ");
        Serial.println(distanceSquared);
        Serial.print("distance: ");
        Serial.println(distance);
        Serial.print("normalY: ");
        Serial.println(normalY);
        while (1)
            delay(10);
    }

    if (isnan(ball.x))
    {
        Serial.print("NaN: ");
        Serial.println(msg);
        Serial.println("Ball x is NAN");
        Serial.print("ballNextX: ");
        Serial.println(ballNextX);
        Serial.print("closestX: ");
        Serial.println(closestX);
        Serial.print("distanceX: ");
        Serial.println(distanceX);
        Serial.print("distanceSquared: ");
        Serial.println(distanceSquared);
        Serial.print("distance: ");
        Serial.println(distance);
        Serial.print("normalX: ");
        Serial.println(normalX);

        while (1)
            delay(10);
    }
}

class Collision
{
public:
    // Check for collision between ball and paddle and resolve if needed
    static void checkAndResolveCollision(Ball &ball, Paddle &paddle, PaddleSide side)
    {
        bool movingTowardsPaddle = (side == PaddleSide::LEFT && ball.dx < 0) || (side == PaddleSide::RIGHT && ball.dx > 0);

        // Additional check to see if the ball has already passed the paddle
        bool ballPassedPaddle = (side == PaddleSide::LEFT && ball.x < paddle.x + paddle.width / 2) ||
                                (side == PaddleSide::RIGHT && ball.x > paddle.x - paddle.width / 2);

        if (!movingTowardsPaddle)
        {
            // The ball is not moving towards the paddle, or it has already passed the paddle
            // No collision possible, so return early
            return;
        }

        // Calculate the ball's next position
        float ballNextX = ball.x + ball.dx;
        float ballNextY = ball.y + ball.dy;

        // Find the closest point on the paddle to the ball's next position
        float closestX = clamp(ballNextX, paddle.x, paddle.x + paddle.width);
        float closestY = clamp(ballNextY, paddle.y, paddle.y + paddle.height);

        // Calculate the distance from the closest point to the ball's center
        float distanceX = ballNextX - closestX;
        float distanceY = ballNextY - closestY;

        // Ensure distanceSquared is not negative
        float distanceSquared = std::max(0.0f, distanceX * distanceX + distanceY * distanceY);

        // Check if the distance is less than the ball's radius squared
        if (distanceSquared <= ball.radius * ball.radius && movingTowardsPaddle && !ballPassedPaddle)
        {
            // Collision detected, now resolve it

            // Normalize the distance vector
            float distance = std::sqrt(distanceSquared);
            float normalX = 0.0f;
            float normalY = 0.0f;
            if (distance > std::numeric_limits<float>::epsilon())
            {
                normalX = distanceX / distance;
                normalY = distanceY / distance;
            }
            else
            {
                // If distance is zero, the ball is exactly on the closest point
                // You can choose how to handle this case. For example:
                normalX = 0.0f;
                normalY = (ball.dy > 0) ? -1.0f : 1.0f; // Reflect directly vertically
            }

            // Calculate how much the ball has penetrated into the paddle
            float overlap = ball.radius - distance;

            // Move the ball out of the paddle by the overlap amount
            ball.x += normalX * overlap;
            ball.y += normalY * overlap;

            checkNaN(ball, "collision update", ballNextX, closestX, distanceX, distanceSquared, distance, normalX, ballNextY, closestY, distanceY, normalY);

            audio.play(TomSound);

            // Handle collisions with the top and bottom of the paddle
            if (closestX > paddle.x && closestX < paddle.x + paddle.width)
            {
                ball.dy = -ball.dy; // Reflect the Y velocity
            }
            else
            {
                // Side collisions reflect on the X
                ball.dx = -ball.dx;

                // Calculate the Y component based on where the ball hits the paddle
                float relativeIntersectY = (paddle.y + (paddle.height / 2)) - ball.y;
                float normalizedRelativeIntersectionY = (relativeIntersectY / (paddle.height / 2));
                float bounceAngle = normalizedRelativeIntersectionY * 0.55f; // Max 55% Y component

                // Adjust the Y velocity based on the bounce angle
                ball.dy = -ball.maxSpeed * bounceAngle;
            }

            // Calculate the new speed based on the paddle's wiggle
            float speedMultiplier = 0.5f + (abs(paddle.wiggle) / (float)paddle.wiggleRoom) * 0.5f;
            float newSpeed = ball.maxSpeed * speedMultiplier;

            // Ensure newSpeed is not zero to avoid multiplying by zero
            newSpeed = std::max(newSpeed, std::numeric_limits<float>::epsilon());

            // Normalize the ball's velocity to apply the new speed
            float velocityMagnitude = std::sqrt(ball.dx * ball.dx + ball.dy * ball.dy);

            // Ensure velocityMagnitude is not zero or too small
            if (velocityMagnitude > std::numeric_limits<float>::epsilon())
            {
                ball.dx = (ball.dx / velocityMagnitude) * newSpeed;
                ball.dy = (ball.dy / velocityMagnitude) * newSpeed;
            }
            else
            {
                // Handle the case where velocityMagnitude is too small or zero
                // Perhaps reset the ball or apply a minimal velocity to avoid getting stuck
                ball.dx = ball.maxSpeed * (ball.dx > 0 ? 1 : -1);
                ball.dy = ball.maxSpeed * (ball.dy > 0 ? 1 : -1);
            }

            switch (stage) {
                case Stage::TopBottomShrink:
                    top += 1;
                    bottom -= 1;
                    if (top > maxTop) {
                        stage = Stage::WallShrink;
                    }
                    break;
                case Stage::WallShrink:
                    wall -= 1;
                    if (wall <= g_width * wallPauseRatio) {
                        stage = Stage::TopBottomExpand;
                    }
                    break;
                case Stage::TopBottomExpand:
                    top -= 1;
                    bottom += 1;
                    if (top < 1) {
                        stage = Stage::FinalWallShrink;
                    }
                    break;
                case Stage::FinalWallShrink:
                    wall -= 1;
                    break;
            }
        }
    }
};