#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "ofxUDPManager.h"
#include <time.h>  

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void readMessage(string msg);
		//void exit();
		
		string strATime;
		string aFrame;
		string fRate;
		
		ofxOMXPlayer omxPlayer;
		ofxUDPManager udpConnection;
		ofFile myTextFile;

		string message;
		string msgRecive;
		string video;
		string localTime;
		string sStatus;
		
		float seek;

		//int millisMaster;
		//int millisLocal;

		int mediaTimeLocal;
		int mediaTimeGlobal;
		int difference;
		int fSeek;
		int bSeek;
		int t;
		/*
		time_t now;
		struct tm masterTime;
		int difClockTotal;
		double difSeconds;
		*/

		bool pause;
		bool play;
		bool isPlaying;
		bool doSeek;
		bool increase;
		bool decrease;
		bool saved;
};

