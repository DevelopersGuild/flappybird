#import <Cocoa/Cocoa.h>
#include <string>

std::string GetAssetPath(std::string asset)
{
    NSString *nsAsset = [NSString stringWithUTF8String:asset.c_str()];
    NSBundle *thisBundle = [NSBundle mainBundle];
    NSString *path = [thisBundle pathForResource:nsAsset ofType:nil];
    return std::string([path UTF8String]);
}
