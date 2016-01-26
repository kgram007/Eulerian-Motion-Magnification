//////////////****  Eulerian Motion Magnification  ****////////////////
//
//	File Name:	 Eulerian_MotionMag.cpp
//	Author:		 Ramsundar K G
//	Date:		 8 July 2015
//
//	Description: This is The C++ implementation of the following paper
//				 using the OpenCV library: "Eulerian Video Magnification
//				 for Revealing Subtle Changes in the World"
//
//////////////////////////////////////////////////////////////////////

/*************************  Includes  *******************************/
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <list>
#include "cv.h"			// Computer Vision Lib Header
#include "highgui.h"	// HighGUI Vision Lib Header
/********************************************************************/

using namespace cv;
using namespace std;

// Change the file/path definitions to actual files/path names
#define INPUT_FILE	"Videos\\Video_Input.mp4"
#define OUTPUT_FILE	"Videos\\Video_Magnified.avi"
#define OUT_WINDOW	"Output Window"

/*************************  Variables  *******************************/
float fl = 0.05, fh = 0.4;
float lambda_c = 80;
float alpha = 50, chromAttenuation = 0.1;
float exaggeration_factor = 2.0;
float delta = 0;
float lambda = 0;
int levels = 5;

std::vector<cv::Mat> lowpass1;
std::vector<cv::Mat> lowpass2;
int curLevel = 0;
/********************************************************************/


Mat LaplacianPyr(Mat img)
{
	Mat down, up, lap;
	pyrDown(img, down);
	pyrUp(down, up);
	lap = img - up;
	return lap;
}
	

bool buildLaplacianPyramid(const Mat &img, const int levels, vector<Mat> &pyramid)
{
    if (levels < 1)
	{
        perror("Levels should be larger than 1");
        return false;
    }
    pyramid.clear();
    Mat currentImg = img;
    for (int l=0; l<levels; l++)
	{
        Mat down,up;
        pyrDown(currentImg, down);
        pyrUp(down, up, currentImg.size());
        Mat lap = currentImg - up;
        pyramid.push_back(lap);
        currentImg = down;
    }
    pyramid.push_back(currentImg);
    return true;
}


void reconImgFromLaplacianPyramid(const vector<Mat> &pyramid, const int levels, Mat &dst)
{
    Mat currentImg = pyramid[levels];
    for (int l=levels-1; l>=0; l--)
	{
        Mat up;
        pyrUp(currentImg, up, pyramid[l].size());
        currentImg = up + pyramid[l];
    }
    dst = currentImg.clone();
}


void temporalIIRFilter(const Mat &src, Mat &dst)
{
    cv::Mat temp1 = (1-fh)*lowpass1[curLevel] + fh*src;
    cv::Mat temp2 = (1-fl)*lowpass2[curLevel] + fl*src;
    lowpass1[curLevel] = temp1;
    lowpass2[curLevel] = temp2;
    dst = lowpass1[curLevel] - lowpass2[curLevel];
}


void amplify(const Mat &src, Mat &dst)
{
    float currAlpha;
    //compute modified alpha for this level
    currAlpha = lambda/delta/8 - 1;
    currAlpha *= exaggeration_factor;
    if (curLevel==levels || curLevel==0)     // ignore the highest and lowest frequency band
        dst = src * 0;
    else
        dst = src * cv::min(alpha, currAlpha);
}


void attenuate(Mat &src, Mat &dst)
{
    Mat planes[3];
    split(src, planes);
    planes[1] = planes[1] * chromAttenuation;
    planes[2] = planes[2] * chromAttenuation;
    merge(planes, 3, dst);
}


void main()
{
	VideoCapture cap( INPUT_FILE );
	if(!cap.isOpened())
	{
		cout << "Error!! Unable to open input video file" << std::endl;
		getchar();
		return;
	}

	cvNamedWindow(OUT_WINDOW, CV_WINDOW_AUTOSIZE);
	cvMoveWindow( OUT_WINDOW, 20, 100 );

	cvSetMouseCallback(OUT_WINDOW, mouseEvent);
	
	Mat org, frame;
	Mat motion;
	Mat output;
	vector<Mat> pyramid;
    vector<Mat> filtered;

	Size czpSz = Size( cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT) );
	//Size czpSz = Size(320, 240);
	VideoWriter Out_Video;
	Out_Video.open( OUTPUT_FILE, // filename
					CV_FOURCC('M', 'J', 'P', 'G'), // codec to be used
					cap.get(CV_CAP_PROP_FPS),      // frame rate of the video
					czpSz // frame size
				  );
				  
	if (!Out_Video.isOpened())
	{
		cout << "Error!! Unable to create output video file" << std::endl;
		getchar();
		return;
	}

	int f_num = 0;
	while(1)
	{	
		cap >> org;
		if(org.empty())
			break;
		
		frame = org.clone();
			frame.convertTo(frame, CV_32FC3, 1.0/255.0f);
			cvtColor(frame, frame, CV_BGR2Lab);

		Mat s = frame.clone();
		buildLaplacianPyramid(s, levels, pyramid);

		if(f_num == 0)
		{
			lowpass1 = pyramid;
			lowpass2 = pyramid;
			filtered = pyramid;
		}
		else
		{
			for (int i=0; i<levels; ++i) 
			{
				curLevel = i;
				temporalIIRFilter(pyramid.at(i), filtered.at(i));
			}

			// amplify each spatial frequency bands
            // according to Figure 6 of paper            
            cv::Size filterSize = filtered.at(0).size();
            int w = filterSize.width;
            int h = filterSize.height;

            delta = lambda_c/8.0/(1.0+alpha);
            // the factor to boost alpha above the bound
            // (for better visualization)
            exaggeration_factor = 2.0;

            // compute the representative wavelength lambda
            // for the lowest spatial frequency band of Laplacian pyramid
            lambda = sqrt( (float)(w*w + h*h) ) / 3;  // 3 is experimental constant

            for (int i=levels; i>=0; i--)
			{
                curLevel = i;
                amplify(filtered.at(i), filtered.at(i));

                // go one level down on pyramid
                // representative lambda will reduce by factor of 2
                lambda /= 2.0;
            }
		}

		// 4. reconstruct motion image from filtered pyramid
        reconImgFromLaplacianPyramid(filtered, levels, motion);

        // 5. attenuate I, Q channels
        attenuate(motion, motion);

        // 6. combine source frame and motion image
        if (f_num > 0)    // don't amplify first frame
            s += motion;

        // 7. convert back to rgb color space and CV_8UC3
        output = s.clone();
			cvtColor(output, output, CV_Lab2BGR);
			output.convertTo(output, CV_8UC3, 255.0, 1.0/255.0);

		imshow(OUT_WINDOW, output);
		Out_Video.write(output);
		cout<< f_num++;
		
		char c = waitKey(1);
		if(c == 27)
			break;
	}
}

