#ifndef FLAPPYBIRD_CONSTANTS
#define FLAPPYBIRD_CONSTANTS

/**
 * All numbers in the source code that are not 0 or 1 should probably be given
 * names and moved into here.
 */

// Bird constants.
const float BIRD_X_POS = 200.0;
const int BIRD_FRAMES_IN_COMPLETE_ANIMATION = 14;
const float BIRD_FRAME_DURATION = 0.025f;
const float GRAVITY = 3000;
const float BIRD_JUMP_VELOCITY = -700.f;
const float BIRD_MAX_Y = 0;
const float BIRD_FRAME_SIZE_X = 110.2f;
const float BIRD_FRAME_SIZE_Y = 101.3f;
const float BIRD_JUMP_ANIMATION_TIMER = BIRD_FRAME_DURATION * BIRD_FRAMES_IN_COMPLETE_ANIMATION * 1.0;

// Game constants.

// Pipes constants.
const int NUMBER_OF_PIPES = 2;
const int PIPE_SPAWN_POSITION = 900;
const int PIPE_RESET_POSITION = 1400;
const int DISTANCE_BETWEEN_PIPES = 500;
const int DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPES = 200;
const float PIPES_FRAME_DURATION = 0.01f;
const float PIPES_VELOCITY = 600.f;
const float PIPES_SPEED_BONUS = 0.85;
const float PIPES_DECELERATION = PIPES_VELOCITY * PIPES_SPEED_BONUS * 2.0;

#endif
