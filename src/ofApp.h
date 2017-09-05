#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include "./timer.h"

class ofApp : public ofBaseApp {
    ofxOscReceiver osc_in_;
    ofVideoPlayer vp_;
    float vol_;
    int fade_;
    Timer timer_;
    bool show_timer_;

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    void play();
};
