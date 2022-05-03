#include "lab2.h"
#include "stdafx.h"
#include "common.h"
#include <chrono>

void RGB2grayscale_each_channel() {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_COLOR);
		Mat dst[3];
		int height = src.rows;
		int width = src.cols;

		for (int i = 0; i < 3; i++) {
			dst[i] = imread(fname, IMREAD_GRAYSCALE);
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Vec3b px = src.at<Vec3b>(i, j);
				
				dst[0].at<uchar>(i, j) = px[0]; // B component
				dst[1].at<uchar>(i, j) = px[1]; // G component
				dst[2].at<uchar>(i, j) = px[2]; // R component
			}
		}

		imshow("R image - graysclae", dst[2]);
		imshow("G image - graysclae", dst[1]);
		imshow("B image - graysclae", dst[0]);
		waitKey(0);
	}
}

void RGB2grayscale() {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_COLOR);
		Mat dst = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Vec3b px = src.at<Vec3b>(i, j);
				int median = (px[0] + px[1] + px[2]) / 3;
				dst.at<uchar>(i, j) = median;
			}
		}

		imshow("Graysclae image", dst);
		waitKey(0);
	}
}

void grayscale2binary(int threshold) {
	
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		Mat dst = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				uchar px = src.at<uchar>(i, j);

				if (px < threshold)
					dst.at<uchar>(i, j) = 0;
				else
					dst.at<uchar>(i, j) = 255;
			}
		}

		imshow("Binary image", dst);
		waitKey(0);
	}
}