#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "ofxUDPManager.h"

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void sendMessage();
		
		double mediaTime;
		string strMediaTime;
		string aFrame;
		string fRate;
		string video;

		ofxOMXPlayer omxPlayer;
		
		ofxUDPManager udpConnection;
		string message;
		string msgRecive;
		string timeS;

		bool pause;
		bool play;

		int sendTime = 30; 
};

