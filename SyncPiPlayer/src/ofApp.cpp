#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	udpConnection.Create();
	udpConnection.Bind(11999);
	udpConnection.SetNonBlocking(true);

	ofSetLogLevel(OF_LOG_VERBOSE);
	
	string videoPath = ofToDataPath("data/A.mp4", true);
	
	ofxOMXPlayerSettings settings;
	settings.videoPath = videoPath;
	settings.enableAudio = false;		//save resources by disabling
	settings.useHDMIForAudio = false;	
	settings.enableTexture = false;		
	settings.enableLooping = false;		
	omxPlayer.setup(settings);

	myTextFile.open("text" + ofGetTimestampString() + ".txt", ofFile::WriteOnly);

	pause = true;
	play = false;
	saved = false;
	t = ofGetElapsedTimeMillis();
}



//--------------------------------------------------------------
void ofApp::update()
{
	fRate = ofToString(ofGetFrameRate(), 2);
	aFrame = ofToString(omxPlayer.getCurrentFrame(), 2);
	mediaTimeLocal = omxPlayer.getMediaTime();
	strATime =  ofToString(mediaTimeLocal, 2); //TODO VER ESSE 2

	char udpMessage[1000];
	udpConnection.Receive(udpMessage, 1000);
	string msg = udpMessage;
	if (msg.size() > 0) readMessage(msg);

	//cout << msg << " play: " << play << endl;
	
	if (pause)
	{
		pause = false;
		omxPlayer.togglePause();
		isPlaying = false;
	}

	if (play)
	{
		play = false;
		if (!isPlaying) {
			omxPlayer.togglePause();
			isPlaying = true;
		}
	}
	/*
	if (doSeek) {
		omxPlayer.seekToTimeInSeconds(seek); // TODO
		seek = 0;
		doSeek = false;
		nSeek++;
	}
	*/
	if(isPlaying){
		if (increase) {
			omxPlayer.increaseSpeed();
			fSeek++;
			sStatus += fRate + ", " + ofToString(mediaTimeLocal, 2) + ", " + ofToString(mediaTimeGlobal, 2) + ", " + ofToString(bSeek, 2) + ", " + ofToString(fSeek, 2) + ", " + ofGetTimestampString() + "; ";
			if (mediaTimeLocal >= mediaTimeGlobal) {
				omxPlayer.setNormalSpeed();
				increase = false;
			}
		} 
		if (decrease) {
			omxPlayer.decreaseSpeed();
			bSeek++;
			sStatus += fRate + ", " + ofToString(mediaTimeLocal, 2) + ", " + ofToString(mediaTimeGlobal, 2) + ", " + ofToString(bSeek, 2) + ", " + ofToString(fSeek, 2) + "," + ofGetTimestampString() + "; ";
			if (mediaTimeLocal <= mediaTimeGlobal) {
				omxPlayer.setNormalSpeed();
				decrease = false;
			}
		}
		//cout << fRate << " mTLocal: " << mediaTimeLocal
		//	<< " mTGlobal: " << mediaTimeGlobal <<" diff: "<< difference <<" pulos +: " << fSeek <<"pulos -" << bSeek << endl;
		if (t + 1000 < ofGetElapsedTimeMillis()) {
			t = ofGetElapsedTimeMillis();
			sStatus += fRate + ", " + ofToString(mediaTimeLocal,2) + ", " + ofToString(mediaTimeGlobal,2) + ", " + ofToString(bSeek,2) + ", " + ofToString(fSeek,2) + ", " + ofGetTimestampString() + "; ";
		}
		//cout << sStatus;
		if (!saved && (omxPlayer.getMediaTime() / 1000000) >= omxPlayer.getDurationInSeconds()) {
			isPlaying = false;
			myTextFile << sStatus;
			cout << "acabou!!! \n" << sStatus << endl;
			saved = true;
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
	omxPlayer.draw(0, 0, 1920, 1080);
}

//--------------------------------------------------------------
void ofApp::readMessage(string msg) { //TODO
	//localTime = ofGetTimestampString();
	//time(&now);
	vector<string> messageStr = ofSplitString(msg, " ");
	video = messageStr[0];
	mediaTimeGlobal = ofToInt(messageStr[1]);
	mediaTimeLocal = omxPlayer.getMediaTime();
	
	difference = mediaTimeGlobal - mediaTimeLocal;
	increase = difference > 1;
	decrease = difference < -200000;

	//seek = (mediaTimeLocal + difference)/1000000f;
	
	if (video == "a") play = true;
	//if (seek >= 0.9) doSeek = true;
	
	//auxClock = messageStr[2];
	//calculaDiferenca(auxClock);
	
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	//ofLog(OF_LOG_VERBOSE, "%c keyPressed", key);
	switch (key)
	{

		case 'p':
		{
			message = "p" + strATime;
			pause = true;
			break;
		}
		
		case 's':
		{
			//seek = float(mediaTimeLocal/1000000) + 15.f;
			//doSeek = true;
			omxPlayer.increaseSpeed();
			break;
		}
		case 'd':
		{
			//seek = float(mediaTimeLocal/1000000) + 15.f;
			//doSeek = true;
			omxPlayer.decreaseSpeed();
			break;
		}

		case 'f':
		{
			//seek = float(mediaTimeLocal/1000000) + 15.f;
			//doSeek = true;
			omxPlayer.setNormalSpeed();
			break;
		}

		case 'a':
		{
			play = true;
			message = "a" + strATime;
			break;
		}

		default:
		{
			break;
		}
	}
	//udpConnection.Send(message.c_str(), message.length());
}
/* 
//--------------------------------------------------------------
void ofApp::exit() {
	myTextFile << sStatus;
}

*/
