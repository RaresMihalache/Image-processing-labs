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

void RGB2HSV_components() {

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
				uchar R = px[2];
				uchar G = px[1];
				uchar B = px[0];

				float r = (float)R / 255;
				float g = (float)G / 255;
				float b = (float)B / 255;

				float M = max(r, g);
				M = max(M, b);
				float m = min(r, g);
				m = min(m, b);

				float C = M - m;
				float V = M;
				float S = 0;
				float H = 0;

				if (V != 0)
					S = C / V;

				if (C != 0) {
					if (M == r)
						H = 60 * (g - b) / C;
					if (M == g)
						H = 120 + 60 * (b - r) / C;
					if (M == b)
						H = 240 + 60 * (r - g) / C;
				}
				else
					H = 0;

				if (H < 0)
					H = H + 360;

				float H_norm = H * 255 / 360;
				float S_norm = S * 255;
				float V_norm = V * 255;

				dst[0].at<uchar>(i, j) = H_norm;
				dst[1].at<uchar>(i, j) = S_norm;
				dst[2].at<uchar>(i, j) = V_norm;
			}
		}

		imshow("H", dst[0]);
		imshow("S", dst[1]);
		imshow("V", dst[2]);
		waitKey(0);
	}
}

int isInside(Mat img, int i, int j) {
	
	int height = img.rows;
	int width = img.cols;

	if (i < height && j << width)
		return 1;
	return 0;
}