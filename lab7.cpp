#include "lab7.h"
#include "lab5.h"
#include "stdafx.h"
#include "common.h"
#include <chrono>

Mat grayscale2binary(Mat img, int threshold);

void dilatare() {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;

		Mat dst(height, width, CV_8UC1, Scalar(255));

		//src = dst;

		char* di = (char*)calloc(8, sizeof(char));
		char* dj = (char*)calloc(8, sizeof(char));

		di[0] = 0, dj[0] = 1;
		di[1] = -1, dj[1] = 1;
		di[2] = -1, dj[2] = 0;
		di[3] = -1, dj[3] = -1;
		di[4] = 0, dj[4] = -1;
		di[5] = 1, dj[5] = -1;
		di[6] = 1, dj[6] = 0;
		di[7] = 1, dj[7] = 1;

		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				if (src.at<uchar>(i, j) == 0) {
					for (int k = 0; k < 8; k++) {
						dst.at<uchar>(i + di[k], j + dj[k]) = 0;
					}
				}
			}
		}
	
		imshow("Original", src);
		imshow("Dilatare", dst);
		waitKey(0);
	}

}

void eroziune() {
	
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		src = grayscale2binary(src, 200);
		int height = src.rows;
		int width = src.cols;

		Mat dst(height, width, CV_8UC1, Scalar(255));

		char* di = (char*)calloc(8, sizeof(char));
		char* dj = (char*)calloc(8, sizeof(char));

		di[0] = 0, dj[0] = 1;
		di[1] = -1, dj[1] = 1;
		di[2] = -1, dj[2] = 0;
		di[3] = -1, dj[3] = -1;
		di[4] = 0, dj[4] = -1;
		di[5] = 1, dj[5] = -1;
		di[6] = 1, dj[6] = 0;
		di[7] = 1, dj[7] = 1;

		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				int s = 0;
				for (int k = 0; k < 8; k++) {
					s += src.at<uchar>(i + di[k], j + dj[k]);
				}
				if (s == 0)
					dst.at<uchar>(i, j) = 0;
			}
		}

		imshow("Original", src);
		imshow("Eroziune", dst);
		waitKey(0);
	}
}

void deschidere();

void inchidere();

void dilatare_n(int n);

void eroziune_n(int n);

void deschidere_n(int n);

void inchidere_n(int n);

void border_tracing_morpho();

void region_filling();