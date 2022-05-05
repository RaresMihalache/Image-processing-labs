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

void deschidere() {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		src = grayscale2binary(src, 200);
		int height = src.rows;
		int width = src.cols;

		Mat eroziune(height, width, CV_8UC1, Scalar(255));
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
					eroziune.at<uchar>(i, j) = 0;
			}
		}

		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				if (eroziune.at<uchar>(i, j) == 0) {
					for (int k = 0; k < 8; k++) {
						dst.at<uchar>(i + di[k], j + dj[k]) = 0;
					}
				}
			}
		}

		imshow("Original", src);
		imshow("Deschidere", dst);
		waitKey(0);
	}
}

void inchidere() {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		src = grayscale2binary(src, 200);
		int height = src.rows;
		int width = src.cols;

		Mat dilatare(height, width, CV_8UC1, Scalar(255));
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
				if (src.at<uchar>(i, j) == 0) {
					for (int k = 0; k < 8; k++)
						dilatare.at<uchar>(i + di[k], j + dj[k]) = 0;
				}
			}
		}

		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				int s = 0;
				for (int k = 0; k < 8; k++)
					s += dilatare.at<uchar>(i + di[k], j + dj[k]);
				if (s == 0)
					dst.at<uchar>(i, j) = 0;
			}
		}

		imshow("Original", src);
		imshow("Inchidere", dst);
		waitKey(0);
	}
}

void dilatare_n(int n) {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		src = grayscale2binary(src, 200);
		int height = src.rows;
		int width = src.cols;

		Mat dst(height, width, CV_8UC1, Scalar(255));
		Mat temp_img = src.clone();

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

		while (n) {
			for (int i = 1; i < height - 1; i++) {
				for (int j = 1; j < width - 1; j++) {
					if (temp_img.at<uchar>(i, j) == 0) {
						for (int k = 0; k < 8; k++)
							dst.at<uchar>(i + di[k], j + dj[k]) = 0;
					}
				}
			}

			temp_img = dst.clone();
			n--;
		}

		imshow("Original", src);
		imshow("Dilatare * n", dst);
		waitKey(0);
	}
}

void eroziune_n(int n) {
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		src = grayscale2binary(src, 200);
		int height = src.rows;
		int width = src.cols;

		Mat dst(height, width, CV_8UC1, Scalar(255));
		Mat temp_img = src.clone();

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

		while (n) {
			for (int i = 1; i < height - 1; i++) {
				for (int j = 1; j < width - 1; j++) {
					int s = 0;
					for (int k = 0; k < 8; k++)
						s += temp_img.at<uchar>(i + di[k], j + dj[k]);
					if (s == 0)
						dst.at<uchar>(i, j) = 0;
				}
			}

			temp_img = dst.clone();
			n--;
		}

		imshow("Original", src);
		imshow("Eroziune * n", dst);
		waitKey(0);
	}
}

void deschidere_n(int n) {
	
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		src = grayscale2binary(src, 200);
		int height = src.rows;
		int width = src.cols;

		Mat dst(height, width, CV_8UC1, Scalar(255));
		Mat temp_img = src.clone();

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

		while (n) {
			for (int i = 1; i < height - 1; i++) {
				for (int j = 1; j < width - 1; j++) {
					int s = 0;
					for (int k = 0; k < 8; k++)
						s += temp_img.at<uchar>(i + di[k], j + dj[k]);
					if (s == 0)
						dst.at<uchar>(i, j) = 0;
				}
			}

			temp_img = dst.clone();

			for (int i = 1; i < height - 1; i++) {
				for (int j = 1; j < width - 1; j++) {
					if (temp_img.at<uchar>(i, j) == 0) {
						for (int k = 0; k < 8; k++)
							dst.at<uchar>(i + di[k], j + dj[k]) = 0;
					}
				}
			}

			temp_img = dst.clone();

			n--;
		}

		imshow("Original", src);
		imshow("Deschidere * n", dst);
		waitKey(0);
	}
}

void inchidere_n(int n) {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		src = grayscale2binary(src, 200);
		int height = src.rows;
		int width = src.cols;

		Mat dst(height, width, CV_8UC1, Scalar(255));
		Mat temp_img = src.clone();

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

		while (n) {
			for (int i = 1; i < height - 1; i++) {
				for (int j = 1; j < width - 1; j++) {
					if (temp_img.at<uchar>(i, j) == 0) {
						for (int k = 0; k < 8; k++)
							dst.at<uchar>(i + di[k], j + dj[k]) = 0;
					}
				}
			}

			temp_img = dst.clone();

			for (int i = 1; i < height - 1; i++) {
				for (int j = 1; j < width - 1; j++) {
					int s = 0;
					for (int k = 0; k < 8; k++)
						s += temp_img.at<uchar>(i + di[k], j + dj[k]);
					if (s == 0)
						dst.at<uchar>(i, j) = 0;
				}
			}

			temp_img = dst.clone();

			n--;
		}

		imshow("Original", src);
		imshow("Inchidere * n", dst);
		waitKey(0);
	}
}

void border_tracing_morpho() {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
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

		// dilatare
		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				if (src.at<uchar>(i, j) == 0) {
					for (int k = 0; k < 8; k++) {
						dst.at<uchar>(i + di[k], j + dj[k]) = 0;
					}
				}
			}
		}

		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				if (src.at<uchar>(i, j) == 0 && dst.at<uchar>(i, j) == 0)
					dst.at <uchar>(i, j) = 255;
			}
		}

		imshow("Original", src);
		imshow("Border tracing", dst);
		waitKey(0);
	}
}

void region_filling() {

	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		src = grayscale2binary(src, 200);

		Mat dst(height, width, CV_8UC1, Scalar(255));
		Mat negative(height, width, CV_8UC1, Scalar(255));
		Mat temp_img = src.clone();

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

		// construct complementary image
		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < height - 1; j++) {
				if (src.at<uchar>(i, j) == 0)
					negative.at<uchar>(i, j) = 255;
				else if (src.at<uchar>(i, j) == 255)
					negative.at<uchar>(i, j) = 0;
			}
		}

		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				if (temp_img.at<uchar>(i, j) == 0) {
					for (int k = 0; k < 8; k++)
						dst.at<uchar>(i + di[k], j + dj[k]) = 0;
				}
			}
		}

		temp_img = dst.clone();

		for (int i = 1; i < height - 1; i++) {
			for (int j = 1; j < width - 1; j++) {
				if (temp_img.at<uchar>(i, j) != src.at<uchar>(i, j)) {
					dst.at<uchar>(i, j) = 255;
				}
			}
		}

		imshow("Original", src);
		imshow("Complementary", negative);
		imshow("Region filling", dst);
		waitKey(0);
	}
}