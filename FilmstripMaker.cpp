//***************FilmstripMaker.cpp*************
//Author: Ethan Reker
//Date: 08/11/2015
//
//Purpose:
//This is a simple program that allows you to read several images and output them
//verticall y as a single strip. I designed this for use in gui applications 
//(primarily in audio plugins where I need to have a single image contain several frames)
//


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitching/stitcher.hpp"

#include <iostream>
#include <vector>
#include <queue>  

using namespace cv;
using namespace std;

/***************************************************************
Called for automatic reading of Images from the present working
directory. For this to work, the files must be numbered in 
order. (1.png, 2.png, 3.png, 4.png, etc...)
***************************************************************/
void getImagesAuto(int pNumImages, queue<Mat> &images){
	int startingIndex;
	string fExt;

	cout<<"Enter Number of the first image (if it's 0.png, enter 0): ";
	cin >> startingIndex;
	cout << "Enter file extension of the images: ";
	cin >> fExt;

	string fName;

	for(int i = startingIndex; i < pNumImages + 1; i++){

		fName = to_string(i);
		fName += fExt;

		cout << "Reading " << fName <<"...";

		images.push(imread(fName, -1));
		
		if(images.empty()){
			cout << "Error. Failed to open file.\n";
		}
		else
			cout << " Succesfully loaded!\n";
	}
}


/***************************************************************
Called for manual input of file names. It accepts file names
one at a time and then reads them and stores them in the
image Queue
***************************************************************/
void getImagesManual(int pNumImages, queue<Mat> &images){
		string fName;
		for (int i = 0; i < pNumImages; i++){
		cout << "\nEnter File name To Be Appended: ";
		cin >> fName;
		cout << endl;

		cout << "File To Be Read: " << fName << endl;
		images.push(imread(fName, -1));

		if(images.back().empty()){
			cout << "Error. Failed to open file.\n";
			cout << "Try entering file name again.\n";
			i--;
		}
		else
			cout <<" Succesfully loaded!\n";


	}
}

/***************************************************************
Recieves the queue of Mats that was created by either 
getImagesManual() or getImagesAuto() and combines them all
into one Mat and then returns it.
***************************************************************/
Mat compileImages(queue<Mat> images){
	Mat newMat;
	while(!images.empty()){
		newMat.push_back(images.front());
		images.pop();
	}	
	return newMat;	
}

/***************************************************************
Just a simple greeting with information about the program
***************************************************************/
void greeting(){
	String version = "1.1";
	cout << "\n\n************************************************\n"
	     << "Filmstrip Maker v"<< version << '\n'
	     << "Cut Through Recordings\n"
	     << "This software is free under the GPL v3 License.\n"
	     << "You are free to edit and redistribute this code\n"
	     << "as you like.\n"
	     << "************************************************\n";
	cout << "\nThis program is used for combining two or more\n"
		 << "images into a single strip of images. It is \n"
		 << "useful for audio plugin guis, particually for\n"
		 << "making meters.\n\n"
		 << "If you have any questions or want to contribute,\n"
		 << "you can email me at ctrecordingslive@gmail.com\n";
}

int main(int argc, const char** argv)
{
	greeting();
	int numImages;
	String outputFileName = "filmStrip.png";

	//Used for storing all the images
	queue<Mat> imageVector;

	//All images will be stitched together and stored here
	Mat finalImage;

	cout << "\nEnter Number Of Images To Be Read: ";
	cin >> numImages;
	cout << endl;

	cout << "Chose Mode:\n1.Auto Read: Reads files that already sorted by name, example(1.png,2.png,3.png..)";
	cout << "\n2.Manual Read: asks for file names one at a time.\n: ";
	int choice = 0;
	cin >> choice;

	switch(choice){
		//Auto Read
		case 1: 
			getImagesAuto(numImages, imageVector);
			break;
		//Manual Read
		case 2:
			getImagesManual(numImages, imageVector);
			break;
		//Error - Exit with code 1
		default:
			cout<<"\nError: Invalid choice.\n";
			return 1;
	}

	//Takes all images from the image queue and stitches them to
	//The final image
	finalImage = compileImages(imageVector);

	imwrite(outputFileName, finalImage);

	cout << endl << "The Filmstrip was created and stored as " << outputFileName << endl << endl;

	return 0;
}