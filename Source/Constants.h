#ifndef FLAPPYBIRD_CONSTANTS
#define FLAPPYBIRD_CONSTANTS

/**
 * All numbers in the source code that are not 0 or 1 should probably be given
 * names and moved into here.
 */

#define PI 3.1415926535897932; //Overkill? I think not!

//Game constants.
const int NUMBER_OF_POPUPS = 3;
// Bird constants.
const float GRAVITY = 3000; //How fast the bird falls.
const float BIRD_JUMP_VELOCITY = -750.f; //How high the bird jumps.
const float BIRD_FRAME_DURATION = 0.025f; //How fast the bird flaps its wings.

const float BIRD_X_POS = 200.0;
const int BIRD_FRAMES_IN_COMPLETE_ANIMATION = 14;
const float BIRD_MAX_Y = 0;
const float BIRD_FRAME_SIZE_X = 110.2f;
const float BIRD_FRAME_SIZE_Y = 101.3f;
const float BIRD_JUMP_ANIMATION_TIMER = (float)(BIRD_FRAME_DURATION * BIRD_FRAMES_IN_COMPLETE_ANIMATION * 1.0);

// Game constants.

// Pipes constants.
const int NUMBER_OF_PIPES = 2;
const float DISTANCE_BETWEEN_PIPES = 500.f;
const float DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPES = 200.f;

const float PIPE_SPAWN_POSITION = 900.f;
const float PIPE_RESET_POSITION = 1400.f;
const float PIPES_FRAME_DURATION = 0.01f;
const float PIPES_VELOCITY = 600.f;
const float PIPES_SPEED_BONUS = 0.85f;
const float PIPES_DECELERATION = (float)(PIPES_VELOCITY * PIPES_SPEED_BONUS * 2.0);

// Ground constants
const int NUMBER_OF_GROUND_SPRITES = 2;
const float GROUND_VELOCITY = PIPES_VELOCITY;
const float GROUND_SPEED_BONUS = PIPES_SPEED_BONUS;
const float GROUND_DECELERATION = PIPES_DECELERATION;

#endif
