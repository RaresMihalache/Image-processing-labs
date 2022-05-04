#include "lab5.h"
#include "lab2.h"
#include "stdafx.h"
#include "common.h"
#include <chrono>
#include <queue>
#include <stack>
#include <random>

void colored_labels(Mat labeled_image);

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

Mat BFS_component_labeling(int neighbor_type) {

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
			return labels;
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

		std::cout<<"No. of components: " << label; // no. of labels
		imshow("grayscale2binary", binary_image);
		waitKey(0);
		return labels;
	}
}

Mat DFS_component_labeling(int neighbor_type) {

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
			std::cout << "Error. Neighbor_type must be either 0 or 1.\n";
			return labels;
		}

		int no_neighbors = sizeof(neighbors) / sizeof(neighbors[0]);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (binary_image.at<uchar>(i, j) == 0 && labels.at<uchar>(i, j) == 0) {
					label++;
					std::stack<std::pair<int, int>> Stack;
					labels.at<uchar>(i, j) = label;
					Stack.push(std::pair<int, int>(i, j));
					while (!Stack.empty()) {
						std::pair<int, int> q = Stack.top();
						Stack.pop();
						for (int k = 0; k < no_neighbors; k++) {
							if (q.first + di[k] >= 0 && q.first + di[k] < height && q.second + dj[k] >= 0 && q.second + dj[k] < width) {
								neighbors[k] = binary_image.at<uchar>(q.first + di[k], q.second + dj[k]);
								if (neighbors[k] == 0 && labels.at<uchar>(q.first + di[k], q.second + dj[k]) == 0) {
									labels.at<uchar>(q.first + di[k], q.second + dj[k]) = label;
									Stack.push(std::pair<int, int>(q.first + di[k], q.second + dj[k]));
								}
							}
						}
					}
				}
			}
		}

		std::cout << "No. of components: " << label; // no. of labels
		imshow("grayscale2binary", binary_image);
		waitKey(0);
		return labels;
	}
}

void two_pass_labeling() {
	
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;

		Mat binary_image = grayscale2binary(src, 200);
		Mat labels = Mat::zeros(height, width, CV_8UC1);
		int label = 0;
		std::vector<std::vector<uchar>> edges(1000);

		int* di = (int*)calloc(4, sizeof(int));
		int* dj = (int*)calloc(4, sizeof(int));
		std::pair<int, int>* neighbors = (std::pair<int, int>*)calloc(4, sizeof(std::pair<int , int>));

		di[0] = -1, dj[0] = -1;
		di[1] = -1, dj[1] = 0;
		di[2] = -1, dj[2] = 1;
		di[3] = 0, dj[3] = -1;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (binary_image.at<uchar>(i, j) == 0 && labels.at<uchar>(i, j) == 0) {
					std::vector<uchar> L;
					for (int k = 0; k < 4; k++) {
						neighbors[k] = std::make_pair(i + di[k], j + dj[k]); // position of neighbors: (x, y) format: (
						if (labels.at<uchar>(i + di[k], j + dj[k]) > 0) {
							std::pair<int, int> x = std::make_pair(1, 2);
							L.push_back(labels.at<uchar>(neighbors[k].first, neighbors[k].second));
						}
					}
					if (L.size() == 0) { // assign new label
						label++;
						labels.at<uchar>(i, j) = label;
					}
					else {
						uchar minim = 255;
						for (int i = 0; i < L.size(); i++) {
							minim = min(minim, L[i]);
						}
						
						labels.at<uchar>(i, j) = minim;
						for (int i = 0; i < L.size(); i++) {
							if (L[i] != minim) {
								edges[minim].push_back(L[i]);
								edges[L[i]].push_back(minim);
							}
						}
					}
				}
			}
		}

		// prima parcurgere:
		//printf("Prima parcurgere\n");
		colored_labels(labels);

		int newlabel = 0;
		int* newlabels = (int*)calloc(label + 1, sizeof(int));

		for (int i = 1; i < label; i++) {
			if (newlabels[i] == 0) {
				newlabel++;
				std::queue<int> Q;
				newlabels[i] = newlabel;
				Q.push(i);

				while (!Q.empty()) {
					int x = Q.front();
					Q.pop();
					for (int i = 0; i < edges[x].size(); i++) {
						if (newlabels[i] == 0) {
							newlabels[i] = newlabel;
							Q.push(i);
						}
					}
				}

			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				labels.at<uchar>(i, j) = newlabels[labels.at<uchar>(i, j)];
			}
		}

		//printf("A doua parcurgere.\n");
		colored_labels(labels);

	}
}

void colored_labels(Mat labeled_image) {
	
	int height = labeled_image.rows;
	int width = labeled_image.cols;

	Mat dst = Mat::zeros(height, width, CV_8UC3);
	Vec3b* labels = (Vec3b*)calloc(256, sizeof(Vec3b));
	int k = 0; // index that indicates the no. of labels in the image

	std::default_random_engine gen;
	std::uniform_int_distribution<int> d(1, 255);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (labeled_image.at<uchar>(i, j) != 0) {
				Vec3b px;
				uchar r = d(gen); px[2] = r;
				uchar g = d(gen); px[1] = g;
				uchar b = d(gen); px[0] = b;
				
				if (labels[labeled_image.at<uchar>(i, j)][0] == 0 &&
					labels[labeled_image.at<uchar>(i, j)][1] == 0 &&
					labels[labeled_image.at<uchar>(i, j)][2] == 0) { // white color
					
					labels[labeled_image.at<uchar>(i, j)] = px;
				}

				dst.at<Vec3b>(i, j) = labels[labeled_image.at<uchar>(i, j)];
			}
		}
	}

	imshow("colored_labels", dst);
	waitKey(0);
}
