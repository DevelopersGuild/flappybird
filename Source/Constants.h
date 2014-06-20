#ifndef FLAPPYBIRD_CONSTANTS
#define FLAPPYBIRD_CONSTANTS


#define PI 3.1415926535897932; //Overkill? I think not!
const float GRAVITY = 4000;
const char CREDITS_TEXT[] =
    "Edwin Angkasa\n"
    "Ahmed Baki\n"
    "Anthony Bilic\n"
    "Vihan Chaudhry\n"
    "Alex Khouderchah\n"
    "Edwin Li\n"
    "Paul Merrill\n"
    "Akshay Shetty\n"
    "Brian Sonnenberg\n"
    "Alea \"Sabrina\" Suhair\n"
    "Ethan Wong"; // Last line has no \n

//Game constants.
const int NUMBER_OF_POPUPS = 3;

// Pipes constants.
const int NUMBER_OF_PIPES = 2;
const float DISTANCE_BETWEEN_PIPES = 500.0f;
const float DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPES = 200.0f;
const float PIPE_LENGTH = 500.0f;
const float PIPE_SPAWN_POSITION = 900.0f;
const float PIPE_RESET_POSITION = 1400.0f;
const float PIPES_VELOCITY = 600.0f;
const float PIPES_SPEED_BONUS = 0.85f;
const float PIPES_DECELERATION = (float)(PIPES_VELOCITY * PIPES_SPEED_BONUS * 2.0);

// Ground constants
const float GROUND_SPRITE_LENGTH = 400.0f;
const float GROUND_Y_POSITION = 650.0f;
const int NUMBER_OF_GROUND_SPRITES = 4;
const float GROUND_VELOCITY = PIPES_VELOCITY;
const float GROUND_SPEED_BONUS = PIPES_SPEED_BONUS;
const float GROUND_DECELERATION = PIPES_DECELERATION;

//Background constants.
const int NUMBER_OF_BACKGROUND_SPRITES = 2;
const float BACKGROUND_SPRITE_LENGTH = 1024.0f;
const float BACKGROUND_SPRITE_HEIGHT = 256.0f;
const float BACKGROUND_VELOCITY = 80.0f;
const float BACKGROUND_SPEED_BONUS = PIPES_SPEED_BONUS;
const float BACKGROUND_DECELERATION = float(BACKGROUND_VELOCITY * BACKGROUND_SPEED_BONUS * 2.0);

// Bird constants.
const float BIRD_JUMP_VELOCITY = -850.0f; //How high the bird jumps.
const float BIRD_FRAME_DURATION = 0.025f; //How fast the bird flaps its wings.
const float BIRD_X_POS = 200.0f;
const int BIRD_FRAMES_IN_COMPLETE_ANIMATION = 14;
const float BIRD_MAX_Y = 0.0f;
const float BIRD_FRAME_SIZE_X = 110.2f;
const float BIRD_FRAME_SIZE_Y = 101.3f;
const float BIRD_JUMP_ANIMATION_TIMER = (float)(BIRD_FRAME_DURATION * BIRD_FRAMES_IN_COMPLETE_ANIMATION * 1.0);

// Powerup constants
const float PU_RESET_POSITION = 2500.0f;
const float PU_FRAME_DURATION = 0.01f;
const float PU_VELOCITY = PIPES_VELOCITY/2;
const float PU_SPEED_BONUS = PIPES_SPEED_BONUS;
const float PU_DECELERATION = float(PU_VELOCITY * PU_SPEED_BONUS * 2.0);
const int NUMBER_OF_PU_TYPES = 1; //Add this as PU increases

#endif
