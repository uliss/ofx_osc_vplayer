#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowTitle("Crull Quest");
    ofSetEscapeQuitsApp(false);
    ofBackground(ofColor::black);

    osc_in_.setup(7878);
    vol_ = 0;
    fade_ = 0;
    show_timer_ = false;

    // vp_.load("krullfilmen.mov");
    vp_.setVolume(vol_);
    vp_.setLoopState(OF_LOOP_NONE);
}

void ofApp::update()
{
    vp_.update();

    try {
        while (osc_in_.hasWaitingMessages()) {
            ofxOscMessage m;
            osc_in_.getNextMessage(m);
            string addr = m.getAddress();
            if (addr == "/play") {
                play();
            } else if (addr == "/stop") {
                vp_.stop();
            } else if (addr == "/pause") {
                vp_.setPaused(!vp_.isPaused());
            } else if (addr == "/volume") {
                if (m.getNumArgs() > 0)
                    vp_.setVolume(m.getArgAsFloat(0));
            } else if (addr == "/skip") {
                if (m.getNumArgs() > 0)
                    vp_.setFrame(m.getArgAsFloat(0) * 25);
            } else if (addr == "/fade") {
                if (m.getNumArgs() > 0)
                    fade_ = std::min<int>(255, std::max<int>(0, m.getArgAsInt(0)));
            } else if (addr == "/load") {
                if (m.getNumArgs() > 0) {
                    std::string name = m.getArgAsString(0);
                    vp_.load(name);
                }
            } else {
                ofLog(OF_LOG_ERROR, "unknown message received: '%s'", addr.c_str());
            }
        }
    } catch (osc::Exception& exc) {
        ofLog(OF_LOG_ERROR, "%s", exc.what());
    }
}

void ofApp::draw()
{
    ofSetColor(255, 255, 255, fade_);
    ofEnableAlphaBlending();

    float h = ofGetHeight();
    float w = ofGetWidth();
    float scale = std::min(h / vp_.getHeight(), w / vp_.getWidth());
    float new_w = vp_.getWidth() * scale;
    float new_h = vp_.getHeight() * scale;

    vp_.draw((w - new_w) / 2, (h - new_h) / 2, new_w, new_h);

    if (show_timer_ && vp_.isPlaying()) {
        ofDrawBitmapString(timer_.current(), 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key) {
    case 'f':
        ofToggleFullscreen();
        break;
    case 'm':
        vol_ = vol_ < 1;
        vp_.setVolume(vol_);
        break;
    case ' ':
        if (vp_.isPlaying())
            vp_.setPaused(!vp_.isPaused());
        else
            vp_.play();
        break;
    case OF_KEY_ESC:
        vp_.stop();
        break;
    case OF_KEY_COMMAND | 'q':
        ofExit(0);
        break;
    case '+':
        fade_ = std::min(255, fade_ + 10);
        break;
    case '-':
        fade_ = std::max(0, fade_ - 10);
        break;
    case 't':
        show_timer_ = !show_timer_;
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

void ofApp::play()
{
    vp_.play();
    timer_.start();
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
