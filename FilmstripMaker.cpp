//***************FilmstripMaker.cpp*************
//Author: Ethan Reker
//Date: 08/11/2015
//
//Purpose:
//This is a simple program that allows you to read several images and output them
//verticall y as a single strip. I designed this for use in gui applications 
//(primarily in audio plugins where I need to have a single image contain several frames)
//

//#include "stdafx.h"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"

#include <iostream>
#include <vector>
#include <queue>
//#include <Windows.h>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	int numImages;

	String version = "1.0";
	String file;
	String outputFileName = "filmStrip.jpg";
	String windowName = "Film Strip Maker v" + version;
	//SetConsoleTitle(TEXT("Filmstrip Maker"));

	Mat finalImage;

	cout << "Enter Number Of Images To Be Read: ";
	cin >> numImages;
	cout << endl;

	
	
	for (int i = 0; i < numImages; i++){
		cout << "Enter File name To Be Appended: ";
		cin >> file;
		cout << endl;

		cout <<"File To Be Read: " << file << endl;
		Mat img = imread(file, -1);

		if (img.empty()) //check whether the image is loaded or not
		{
			cout << "Error : Failed to load Image: " << file << endl;
			cout << "Check spelling and try again..." << endl;
			i = i - 1;

		}

		else
		{
			cout << file << " was succesfully loaded and added as Frame " << i + 1 << "." << endl<<endl;
			finalImage.push_back(img);
		}
		

	}


	imwrite(outputFileName, finalImage);

	cout << endl << "The Filmstrip was created and stored as " << outputFileName << endl << endl;

	system("pause"); //Wait for a key to be pressed to exit.

	/*
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	imshow(windowName, finalImage);

	
	waitKey(0);
	destroyWindow(windowName); //destroy the window with the name, "MyWindow"
	*/

	return 0;
}

