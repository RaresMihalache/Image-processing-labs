#include "lab3.h"
#include "stdafx.h"
#include "common.h"
#include <chrono>
#include <string.h>

void showHistogram(const std::string& name, int* hist, const int hist_cols, const int hist_height);

int get_height(const std::string& name) {

	Mat src = imread(name, -1);
	int height = src.rows;

	return height;
}

int get_width(const std::string& name) {

	Mat src = imread(name, -1);
	int width = src.cols;

	return width;
}

void histogram() {

	int* hist = (int*)calloc(256, sizeof(int));
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				hist[src.at<uchar>(i, j)] ++;
			}
		}

		for (int i = 0; i < 256; i++) {
			std::cout << "[" << i << "]: " << hist[i] << "\n";
		}
		showHistogram("histogram", hist, 256, 300);
		imshow("image", src);
		waitKey(0);
	}
}

int* histogram_values(const std::string& name) {

	int* values = (int*)calloc(256, sizeof(int));
	Mat src = imread(name, IMREAD_GRAYSCALE);
	int height = src.rows;
	int width = src.cols;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			values[src.at<uchar>(i, j)]++;
		}
	}

	return values;
}

void fdp() {

	int* hist = (int*)calloc(256, sizeof(int));
	float* fdp = (float*)calloc(256, sizeof(float));
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		int no_pixels = height * width;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				hist[src.at<uchar>(i, j)]++;
			}
		}

		for (int i = 0; i < 256; i++) {
			fdp[i] = (float)hist[i] / no_pixels;
			std::cout << "[" << i << "]: " << fdp[i] << "\n";
		}

		imshow("fdp_values", src);
		waitKey(0);
	}
}

void histogram_acumm(int m) {

	int* hist = (int*)calloc(m, sizeof(int));
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		Mat dst = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int h_value = m * src.at<uchar>(i, j) / 256;

				dst.at<uchar>(i, j) = h_value;
				hist[h_value]++;
			}
		}

		imshow("Image with acummulators", dst);
		showHistogram("histogram", hist, m, 300);
		waitKey(0);
	}
}

void showHistogram(const std::string& name, int* hist, const int hist_cols, const int hist_height) {

	Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255)); // constructs a white image

	// computes histogram maximum
	int max_hist = 0;
	for (int i = 0; i < hist_cols; i++) {
		if (hist[i] > max_hist)
			max_hist = hist[i];
	}

	double scale = 1.0;
	scale = (double)hist_height / max_hist;
	int baseline = hist_height - 1;

	for (int x = 0; x < hist_cols; x++) {
		Point p1 = Point(x, baseline);
		Point p2 = Point(x, baseline - cvRound(hist[x] * scale));
		line(imgHist, p1, p2, CV_RGB(255, 0, 255)); // histogram bins colored in magenta
	}

	imshow(name, imgHist);
}