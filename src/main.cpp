#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main()
{
    //    ofSetupOpenGL(1024,768,OF_WINDOW);			// <--------
    //    setup the GL context

    CGDisplayCount displayCount;
    CGDirectDisplayID displays[32];

    // Grab the active displays
    CGGetActiveDisplayList(32, displays, &displayCount);
    int numDisplays = displayCount;

    // If two displays present, use the 2nd one. If only one, use the first
    int whichDisplay = numDisplays - 1;

    int displayHeight = CGDisplayPixelsHigh(displays[whichDisplay]);
    int displayWidth = CGDisplayPixelsWide(displays[whichDisplay]);

    CGRect displayBounds = CGDisplayBounds(displays[whichDisplay]);

    // Setup the GL context
    //    ofSetupOpenGL(displayWidth, displayHeight, OF_WINDOW);
    ofSetupOpenGL(displayWidth, displayHeight, OF_FULLSCREEN);

    // OF_FULLSCREEN makes the window as big as the primary display, but we want
    // it to be as big as whichever we're using
    ofSetWindowShape(displayWidth, displayHeight);

    // Move onto our display
    ofSetWindowPosition(displayBounds.origin.x, displayBounds.origin.y);

    // Print display info (if in debug scheme, see
    // http://madcity.at/2013/ofLog-debug-release/)
    //#ifdef IS_DEBUG
    cout << numDisplays << " display(s) detected." << endl
         << "Using display " << whichDisplay << " (" << displayWidth << "x"
         << displayHeight << ")." << endl;
    //#endif

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
