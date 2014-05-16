#include "Assets.h"

/**
 * GetAssetPath
 * 
 * Returns the correct path to load images (and sounds, etc.) for those running
 * Flappy Bird from within the Visual Studio 2010 project included in the Git
 * repository.
 */
string GetAssetPath(string directory, string asset)
{
	return "..\\..\\" + directory + "\\" + asset;
}
