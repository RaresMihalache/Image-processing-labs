#include "lab6.h"
#include "lab5.h"
#include "stdafx.h"
#include "common.h"
#include <chrono>
#include <queue>
#include <stack>
#include <random>

Mat grayscale2binary(Mat img, int threshold);

void border_tracing() {
	
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		Mat binary_image = grayscale2binary(src, 200);
		Mat border_image = binary_image;

		char* di = (char*)calloc(8, sizeof(char));
		char* dj = (char*)calloc(8, sizeof(char));

		// int dir = 0; -> vecinatate de 4
		int dir = 7; // folosim vecinatate de 8

		di[0] = 0, dj[0] = 1;
		di[1] = -1, dj[1] = 1;
		di[2] = -1, dj[2] = 0;
		di[3] = -1, dj[3] = -1;
		di[4] = 0, dj[4] = -1;
		di[5] = 1, dj[5] = -1;
		di[6] = 1, dj[6] = 0;
		di[7] = 1, dj[7] = 1;
		
		std::vector<std::pair<int, int>> border_pixels;
		std::pair<int, int> start_point = std::make_pair(-1, -1);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (binary_image.at<uchar>(i, j) == 0) { // object px detected
					start_point = std::make_pair(i, j);
					border_pixels.push_back(start_point);
					break;
				}
			}
			if (start_point.first != -1)
				break;
		}

		while (border_pixels.size() == 1 || border_pixels[0] != border_pixels[border_pixels.size() - 1]) {
			std::pair<int, int> previous_px = border_pixels[border_pixels.size() - 1];

			if (dir % 2 == 0)
				dir = (dir + 7) % 8;
			else
				dir = (dir + 6) % 8;

			for (int k = 0; k < 8; k++) {
				dir = (dir + k) % 8;

				if (binary_image.at<uchar>(previous_px.first + di[dir], previous_px.second + dj[dir]) == 0 &&
					border_image.at<uchar>(previous_px.first + di[dir], previous_px.second + dj[dir] != 1)) {

					std::pair<int, int> px = std::make_pair(previous_px.first + di[dir], previous_px.second + dj[dir]);
					border_image.at<uchar>(px.first, px.second) = 1;
					border_pixels.push_back(px);
					break;
				}
			}
		}

		for (int i = 0; i < border_pixels.size(); i++) {
			std::pair<int, int> px = border_pixels[i];
			border_image.at<uchar>(px.first, px.second) = 150;
		}
		
		imshow("border_tracing", border_image);
		waitKey(0);
	}
}

void construct_chain_code() {

}

void construct_derivative() {

}

void construct_border(int starting_point, uchar* chain_code) {

}