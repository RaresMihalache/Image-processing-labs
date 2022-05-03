#include "lab5.h"
#include "lab2.h"
#include "stdafx.h"
#include "common.h"
#include <chrono>
#include <queue>
#include <random>

Mat grayscale2binary(Mat img, int threshold) {

	int height = img.rows;
	int width = img.cols;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (img.at<uchar>(i, j) < threshold)
				img.at<uchar>(i, j) = 0;
			else
				img.at<uchar>(i, j) = 255;
		}
	}

	return img;
}

void BFS_component_labeling(int neighbor_type) {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;

		Mat binary_image = grayscale2binary(src, 200);
		Mat labels = Mat::zeros(height, width, CV_8UC1);
		int label = 0;

		int* di;
		int* dj;
		uchar* neighbors;

		if (neighbor_type == 0) {
			di = (int*)calloc(4, sizeof(int));
			dj = (int*)calloc(4, sizeof(int));
			neighbors = (uchar*)calloc(4, sizeof(uchar));

			di[0] = -1, dj[0] = 0;
			di[1] = 0, dj[1] = -1;
			di[2] = 1, dj[2] = 0;
			di[3] = 0, dj[3] = 1;
		}
		else if (neighbor_type == 1) {
			di = (int*)calloc(8, sizeof(int));
			dj = (int*)calloc(8, sizeof(int));
			neighbors = (uchar*)calloc(8, sizeof(uchar));

			di[0] = -1, dj[0] = 0;
			di[1] = -1, dj[1] = -1;
			di[2] = 0, dj[2] = -1;
			di[3] = 1, dj[3] = -1;
			di[4] = 1, dj[4] = 0;
			di[5] = 1, dj[5] = 1;
			di[6] = 0, dj[6] = 1;
			di[7] = -1, dj[7] = 1;
		}
		else {
			std::cout << "Error. Neighbor_type must be either 0 or 1!\n";
			return;
		}

		int no_neighbors = sizeof(neighbors) / sizeof(neighbors[0]);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (binary_image.at<uchar>(i, j) == 0 && labels.at<uchar>(i, j) == 0) {
					label++;
					std::queue<std::pair<int, int>> Queue;
					labels.at<uchar>(i, j) = label;
					Queue.push(std::pair<int, int>(i, j));
					while (!Queue.empty()) {
						std::pair<int, int> q = Queue.front();
						Queue.pop();
						for (int k = 0; k < no_neighbors; k++) {
							if (q.first + di[k] >= 0 && q.first + di[k] < height && q.second + dj[k] >= 0 && q.second + dj[k] < width) {
								neighbors[k] = binary_image.at<uchar>(q.first + di[k], q.second + dj[k]);
								if (neighbors[k] == 0 && labels.at<uchar>(q.first + di[k], q.second + dj[k]) == 0) {
									labels.at<uchar>(q.first + di[k], q.second + dj[k]) = label;
									Queue.push(std::pair<int, int>(q.first + di[k], q.second + dj[k]));
								}
							}

						}
					}
				}
			}
		}

		std::cout<<label;
		imshow("grayscale2binary", binary_image);
		waitKey(0);
	}
}
