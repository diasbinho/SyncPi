#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	udpConnection.Create();
	udpConnection.SetEnableBroadcast(true);
	udpConnection.Connect("192.168.1.255", 11999); // broadcast ip
	udpConnection.Bind(11999); // porta da aplicacao
	udpConnection.SetNonBlocking(true);
	

	ofSetLogLevel(OF_LOG_VERBOSE);
	
	string videoPath = ofToDataPath("data/A.mp4", true);
	
	ofxOMXPlayerSettings settings;
	settings.videoPath = videoPath;
	settings.enableAudio = true;		
	settings.useHDMIForAudio = false;	
	settings.enableTexture = false;		
	settings.enableLooping = false;		
	omxPlayer.setup(settings);
	
	cout << "Digite P para iniciar o vídeo:" << endl;
	pause = true;
	video = "p"; //TODO APENAS TESTES INICIAIS
}



//--------------------------------------------------------------
void ofApp::update()
{
	fRate = " Frame Rate: " + ofToString(ofGetFrameRate(), 2);
	aFrame = " ActualFrame: " +  ofToString(omxPlayer.getCurrentFrame(), 2); 

	//envia a mensagem a cada 30 frames de aplicacao
	if (sendTime > 0) sendTime--;
	else {
		sendMessage();
		sendTime = 30;
	}
	cout << fRate << aFrame << " Media Time: " << ofToString(omxPlayer.getMediaTime(), 2) << " " << ofGetTimestampString() << endl;

	if (pause)
	{
		pause = false;
		omxPlayer.togglePause();
	}

	if (play)
	{
		play = false;
		omxPlayer.restartMovie();
	}

	
	/*
	msgRecive = udpMessage;
	if (msgRecive.compare("p")) {
		pause = true;
	} else if (msgRecive.compare("a")) {
		play = true;
	}
	*/
}


//--------------------------------------------------------------
void ofApp::draw(){
	
	omxPlayer.draw(0, 0, 1920, 1080);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
		case 'p':
		{
			video = "a";
			pause = true;
			break;
		}

		case 'a':
		{
			video = "a";
			play = true;
			break;
		}

		default:
		{
			break;
		}
	}
	sendMessage();
}

void ofApp::sendMessage() {
	timeS = ofGetTimestampString();
	mediaTime = omxPlayer.getMediaTime();
	strMediaTime = ofToString(mediaTime, 2);
	message = video + " " + strMediaTime + " " + timeS;
	udpConnection.Send(message.c_str(), message.length());
}



