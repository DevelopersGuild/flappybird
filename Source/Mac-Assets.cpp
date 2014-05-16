#include <CoreFoundation/CoreFoundation.h>
#include <iostream>

#include "Assets.h"

using std::cerr;
using std::endl;

static void GAPError(string directory, string asset, string error)
{
    cerr << "Error from GetAssetPath(\"" << directory << "\", \"" << asset << "\"): " << error << endl;
}

string GetAssetPath(string directory, string asset)
{
    enum {
        MAX_PATH = 4096,
    };
    
    Boolean result = FALSE;
    int dot;
    string name_str;
    string type_str;
    CFStringRef name;
    CFStringRef type;
    CFStringRef dir;
    CFBundleRef bundle;
    CFURLRef bundleUrl;
    CFURLRef assetUrl;
    UInt8 buffer[MAX_PATH];
    
    dot = asset.find('.');
    if (dot == string::npos) {
        GAPError(directory, asset, "file name didn't include an extention");
        goto dotFail;
    }

    name_str = asset.substr(0, dot);
    type_str = asset.substr(dot + 1);
    name = CFStringCreateWithCString(NULL, name_str.c_str(), kCFStringEncodingUTF8);
    type = CFStringCreateWithCString(NULL, type_str.c_str(), kCFStringEncodingUTF8);
    dir = CFStringCreateWithCString(NULL, directory.c_str(), kCFStringEncodingUTF8);

    bundle = CFBundleGetMainBundle();
    if (bundle == nullptr) {
        GAPError(directory, asset, "bundle is null");
        goto bundleFail;
    }

    bundleUrl = CFBundleCopyBundleURL(bundle);
    if (bundleUrl == nullptr) {
        GAPError(directory, asset, "bundleUrl is null");
        goto bundleUrlFail;
    }

    assetUrl = CFBundleCopyResourceURLInDirectory(bundleUrl, name, type, dir);
    if (assetUrl == nullptr) {
        GAPError(directory, asset, "file not found in bundle");
        goto assertUrlFail;
    }

    result = CFURLGetFileSystemRepresentation(assetUrl, TRUE, buffer, sizeof(buffer));
    if (result == FALSE) {
        GAPError(directory, asset, "result is false");
    }

    CFRelease(assetUrl);
assertUrlFail:
    CFRelease(bundleUrl);
bundleUrlFail:
    CFRelease(bundle);
bundleFail:
    CFRelease(dir);
    CFRelease(type);
    CFRelease(name);
dotFail:

    if (result) {
        return string((char *)buffer);
    }
    else {
        return string();
    }
}
