#ifndef FLAPPYBIRD_MAC_ASSETS
#define FLAPPYBIRD_MAC_ASSETS

#include <string>

using std::string;

/**
 * GetAssetPath
 *
 * Generate a file path that can be used to load a file successfully on both
 * Windows and Mac.
 *
 * Visual Studio and Xcode load files from different places, so in order to
 * accomodate both, use this function whenever you need a file path to load from.
 *
 * Example usage:
 *      ... a file exists at Flappy Bird/Assets/NewBird.png ...
 *
 *   	string birdPath = GetAssetPath("Assets", "NewBird.png");
 *      texture.loadFromFile(birdPath);
 * 
 * (It's kind of weird that there are two parameters: directory and filename.
 * We could probably do with only one.  Oh well.)
 */
string GetAssetPath(string directory, string filename);

#endif
