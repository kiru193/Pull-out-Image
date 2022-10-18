#include <opencv2/opencv.hpp>
#include <filesystem>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	int x_max, y_max, x_min, y_min;

	Mat readimage = imread("BB.bmp");
	String filename;
	if (readimage.empty() != 0) {
		printf("image was not found\n");
	}

	printf("image cols is %d \nimage rows is %d \n", readimage.cols, readimage.rows);
	x_max = y_max = 0;
	x_min = readimage.cols;
	y_min = readimage.rows;

	for (int i = 0; i < readimage.cols; i++) {
		for (int m = 0; m < readimage.rows; m++) {
			if (readimage.at<Vec3b>(m, i)[0] != 0) {
				x_min > i ? x_min = i : x_min;
				y_min > m ? y_min = m : y_min;
				x_max < i ? x_max = i : x_max;
				y_max < m ? y_max = m : y_max;
			}
		}
	}

	printf("x max is %d \nx min is %d \ny max is %d \ny min is %d \n", x_max, x_min, y_max, y_min);
	
	Mat writeimage = Mat::zeros(y_max - y_min, x_max - x_min, CV_8UC3);
	for (int i = 0; i < x_max - x_min; i++) {
		for (int m = 0; m < y_max - y_min; m++) {
			for (int n= 0; n < 3; n++) {
				writeimage.at<Vec3b>(m, i)[n] = readimage.at<Vec3b>(m+y_min, i+x_min)[n];
			}
		}
	}
	
	imshow("", writeimage);
	waitKey(0);
	printf("Please input file name! \n");
	cin >> filename;
	imwrite(filename + ".bmp", writeimage);

}