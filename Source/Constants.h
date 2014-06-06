#ifndef FLAPPYBIRD_CONSTANTS
#define FLAPPYBIRD_CONSTANTS

/**
 * All numbers in the source code that are not 0 or 1 should probably be given
 * names and moved into here.
 */

// Bird constants.
const float BIRD_X_POS = 400.0;
const int BIRD_FRAMES_IN_COMPLETE_ANIMATION = 14;
const float BIRD_FRAME_DURATION = 0.025f;
const float GRAVITY = 1650.f;
const float BIRD_JUMP_VELOCITY = -500.f;
const float BIRD_MAX_Y = 0;
const float BIRD_FRAME_SIZE_X = 110.2f;
const float BIRD_FRAME_SIZE_Y = 101.3f;
const float BIRD_JUMP_ANIMATION_TIMER = BIRD_FRAME_DURATION * BIRD_FRAMES_IN_COMPLETE_ANIMATION * 1.0;

// Game constants.

// Pipes constants.
const int NUMBER_OF_PIPES = 2;
const float PIPES_FRAME_DURATION = 0.01f;
const float PIPES_VELOCITY = 590.f; //Was 600.f
const float PIPES_SPEED_BONUS = 0.85;
const float PIPES_DECELERATION = PIPES_VELOCITY * PIPES_SPEED_BONUS * 2.0;

#endif
