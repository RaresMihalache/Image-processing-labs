#include "lab1.h"
#include "stdafx.h"
#include "common.h"
#include <chrono>

void negative_image()
{ 
	Mat img = imread("Images/cameraman.bmp", IMREAD_GRAYSCALE);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			img.at<uchar>(i, j) = 255 - img.at<uchar>(i, j);
		}
	}
	imshow("negative image", img);
	waitKey(0);
}

void additive_factor(int factor) {
	char fname[MAX_PATH];
	while (openFileDlg(fname)) {
		Mat src = imread(fname, IMREAD_GRAYSCALE);
		Mat dst = imread(fname, IMREAD_GRAYSCALE);

		for (int i = 0; i < dst.rows; i++) {
			for (int j = 0; j < dst.cols; j++) {
				if (dst.at<uchar>(i, j) + factor <= 255) {
					dst.at<uchar>(i, j) += factor;
				}
			}
		}

		imshow("source image", src);
		imshow("processed image", dst);
		waitKey(0);
	}
}

void multiplicative_factor(float factor)
{
	Mat src = imread("Images/cameraman.bmp", IMREAD_GRAYSCALE);
		
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (src.at<uchar>(i, j) * factor < 255) {
				src.at<uchar>(i, j) *= factor;
			}
		}
	}
	imshow("processed image", src);
	waitKey(0);
	imwrite("Images/cameraman_multiplicative.bmp", src);
}

void quarters_image()
{
	Mat img(256, 256, CV_8UC3);
	int current_width = 0;
	int current_height = 0;
	for (int i = 0; i < img.rows; i++) {
		current_height = i;
		for (int j = 0; j < img.cols; j++) {
			current_width = j;
			Vec3b pixel = img.at<Vec3b>(current_height, current_width);
			unsigned char B = pixel[0];
			unsigned char G = pixel[1];
			unsigned char R = pixel[2];
			if (current_height < 128 && current_width < 128) {
				B = G = R = 255;
				pixel[0] = B;
				pixel[1] = G;
				pixel[2] = R;
			}
			else if (current_height < 128 && current_width >= 128) {
				B = G = 0;
				R = 255;
				pixel[0] = B;
				pixel[1] = G;
				pixel[2] = R;
			}
			else if (current_height >= 128 && current_width < 128) {
				B = R = 0;
				G = 255;
				pixel[0] = B;
				pixel[1] = G;
				pixel[2] = R;
			}
			else if (current_height >= 128 && current_width >= 128) {
				B = 0;
				G = R = 255;
				pixel[0] = B;
				pixel[1] = G;
				pixel[2] = R;
			}
			img.at<Vec3b>(i, j) = pixel;
		}
	}
	imshow("quarters image", img);
	waitKey(0);

}

void inverse_matrix()
{
	float vals[9] = { 2.5f, 3.2f, 4.0f, 3.0f, 3.9f, 4.0f, 2.0f, 3.2f, 4.5f };
	Mat m(3, 3, CV_32FC1, vals);

	printf("Matrice initiala:\n");
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			printf("%f ", m.at<float>(i, j));
		}
		printf("\n");
	}

	printf("Matrice inversata:\n");
	Mat m_inverse = m.inv();
	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			printf("%f ", m_inverse.at<float>(i, j));
		}
		printf("\n");
	}
	Sleep(5000);
}



