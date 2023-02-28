#include <opencv.hpp>
#include <opencv2\highgui.hpp>
#include <stdio.h>
#include <time.h>
#include <iostream>

#define MAXNUM 200

using namespace cv;
using namespace std;

/*ͼ����³ߴ磬���û�����*/
int new_height, new_width;

/*��ʼ��������չʾͼƬ����ʾ�û�����ͼ���³ߴ�*/
void InputImage(Mat& src, int height, int width)
{
	namedWindow("Original Image", 0);
	resizeWindow("Original Image", src.cols, src.rows );
	imshow("Original Image", src);
	waitKey(1000);
	cout << "the size of this picture is: " << height << " �� " << width << endl;
	cout << "please enter new height: " << endl;
	cin >> new_height;
	cout << "please enter new width" << endl;
	cin >> new_width;
}

/*��̬�滮������ͼ����������*/
void CalculateEnergy(Mat& grad_src, Mat& energy_src, Mat& trace_src, int height, int width)
{
	grad_src.copyTo(energy_src);
	for (int i = 1; i < height; i++)
	{
		//��һ��
		if (energy_src.at<float>(i - 1, 0) <= energy_src.at<float>(i - 1, 1))
		{
			energy_src.at<float>(i, 0) = grad_src.at<float>(i, 0) + energy_src.at<float>(i - 1, 0);
			//��¼��ǰλ�õ���һ��Ӧȡ�ĸ�λ�ã�����Ϊ0������1������Ϊ2
			trace_src.at<float>(i, 0) = 1;
		}
		else
		{
			energy_src.at<float>(i, 0) = grad_src.at<float>(i, 0) + energy_src.at<float>(i - 1, 1);
			trace_src.at<float>(i, 0) = 2;
		}
		//�м����
		for (int j = 1; j < width - 1; j++)
		{
			float dp[3];
			dp[0] = energy_src.at<float>(i - 1, j - 1);
			dp[1] = energy_src.at<float>(i - 1, j);
			dp[2] = energy_src.at<float>(i - 1, j + 1);

			int index = 0;
			if (dp[1] < dp[0])
				index = 1;
			if (dp[2] < dp[index])
				index = 2;
			energy_src.at<float>(i, j) = grad_src.at<float>(i, j) + energy_src.at<float>(i - 1, j - 1 + index);
			trace_src.at<float>(i, j) = index;
		}
		//���һ��
		if (energy_src.at<float>(i - 1, grad_src.cols - 1) <= energy_src.at<float>(i - 1, grad_src.cols - 2))
		{
			energy_src.at<float>(i, grad_src.cols - 1) = grad_src.at<float>(i, grad_src.cols - 1) + energy_src.at<float>(i - 1, grad_src.cols - 1);
			trace_src.at<float>(i, grad_src.cols - 1) = 1;
		}
		else
		{
			energy_src.at<float>(i, grad_src.cols - 1) = grad_src.at<float>(i, grad_src.cols - 1) + energy_src.at<float>(i - 1, grad_src.cols - 2);
			trace_src.at<float>(i, grad_src.cols - 1) = 0;
		}
	}
}

/*ͨ����̬�滮������ͼ�ҵ�������С��seam*/
void FindSeam(Mat& grad_src, Mat& minTrace, int height, int width)
{
	//�ۼ���������
	Mat energy_src(height, width, CV_32F, cv::Scalar(0));
	//������С�켣����
	Mat trace_src(height, width, CV_32F, cv::Scalar(0));

	//��̬�滮
	CalculateEnergy(grad_src, energy_src, trace_src, height, width);

	int row_count = energy_src.rows - 1;
	//������С�����켣�����������ͼ���е��б�
	int index = 0;

	//���index�������������Сֵ��λ��
	for (int i = 1; i < energy_src.cols; i++)
		if (energy_src.at<float>(row_count, i) < energy_src.at<float>(row_count, index))
			index = i;

	//����������С�켣���󣬵õ�������С�켣�����е���С��һ���Ĺ켣��minTrace�Ƕ���һ�о���
	minTrace.at<float>(row_count, 0) = index;
	int temp_Index = index;

	for (int i = row_count; i > 0; i--)
	{
		int temp = trace_src.at<float>(i, temp_Index);
		if (temp == 0)
			temp_Index = temp_Index - 1;
		else if (temp == 2)
			temp_Index = temp_Index + 1;
		minTrace.at<float>(i - 1, 0) = temp_Index;
	}
}

/*ɾ��ԭͼ�е�һ��seam*/
void RemoveSeam(Mat& src, Mat& res, Mat& minTrace)
{
	for (int i = 0; i < res.rows; i++)
	{
		int k = minTrace.at<float>(i, 0);
		for (int j = 0; j < k; j++)
			res.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
		for (int j = k; j < res.cols - 1; j++)
			res.at<Vec3b>(i, j) = src.at<Vec3b>(i, j + 1);
	}
}

/*����һ���Ҷ�ͼÿ�����ص�������������������ͼ*/
void ComputeGradient(Mat& gray_src, Mat& grad_src, int height, int width)
{
	//ˮƽ�ݶȾ���
	Mat gradiant_H(height, width, CV_32F, cv::Scalar(0));
	//��ֱ�ݶȾ���
	Mat gradiant_V(height, width, CV_32F, cv::Scalar(0));
	//��ˮƽ�ݶ���ʹ�õľ����
	Mat kernel_H = (Mat_<float>(3, 3) << 0, 0, 0, 0, 1, -1, 0, 0, 0);
	//��ֱ�ݶ���ʹ�õľ����
	Mat kernel_V = (Mat_<float>(3, 3) << 0, 0, 0, 0, 1, 0, 0, -1, 0);

	filter2D(gray_src, gradiant_H, gradiant_H.depth(), kernel_H);
	filter2D(gray_src, gradiant_V, gradiant_V.depth(), kernel_V);

	//ˮƽ�봹ֱ�˲�����ľ���ֵ��ӣ����Եõ��ݶȴ�С
	add(abs(gradiant_H), abs(gradiant_V), grad_src);
}

/*����ͼ��������С��seam���Ծ�����ʽ��¼*/
Mat GetMinTrace(Mat& src, int height, int width)
{
	//��ɫͼ��ת��Ϊ�Ҷ�ͼ��
	Mat gray_src(height, width, CV_8U, cv::Scalar(0));
	cvtColor(src, gray_src, COLOR_BGR2GRAY);

	//����ͼ���ݶ�
	Mat grad_src(height, width, CV_32F, cv::Scalar(0));
	ComputeGradient(gray_src, grad_src, height, width);

	//ͨ����̬�滮������ͼ�ҵ�������С��seam
	Mat min_Trace(height, 1, CV_32F, cv::Scalar(0));
	FindSeam(grad_src, min_Trace, height, width);

	return min_Trace;
}

/*ɾ��һ��seam������flag = C����ɾ��һ����ֱ�����seam��flag = R����ɾ��һ��ˮƽ�����seam*/
void ShrinkSeam(Mat& src, char flag = 'C')
{
	int height = src.rows;
	int width = src.cols;

	//���ɾ��һ��ˮƽ�����seam����ͼ����ת90�ȴ�����
	if (flag == 'R')
	{
		transpose(src, src);
		flip(src, src, 1);
		height = src.rows;
		width = src.cols;
	}

	Mat min_Trace = GetMinTrace(src, height, width);

	//ɾ��ԭͼ�е�һ��seam
	Mat res(height, width - 1, src.type());
	RemoveSeam(src, res, min_Trace);

	if (flag == 'R')
	{
		transpose(res, res);
		flip(res, res, 0);
	}
	res.copyTo(src);
}

/*����count��ô����seam������flag = C����������ֱ�����seam��flag = R��������ˮƽ�����seam*/
void EnlargeSeam(Mat& src, int count, char flag = 'C')
{
	Mat trace[MAXNUM];

	//�������ˮƽ�����seam����ͼ����ת90�ȴ�����
	if (flag == 'R')
	{
		transpose(src, src);
		flip(src, src, 1);
	}

	Mat res(src.rows, src.cols, src.type());
	src.copyTo(res);

	//�ҳ�count��������С��seam����¼��trace��
	for (int i = 0; i < count; i++)
	{
		int height = res.rows;
		int width = res.cols;

		Mat min_Trace = GetMinTrace(res, height, width);
		min_Trace.copyTo(trace[i]);

		//ɾ��res�е�����seam������Ѱ����һ��������С��seam
		Mat temp(height, width - 1, res.type());
		RemoveSeam(res, temp, min_Trace);
		temp.copyTo(res);
	}

	//����trace����ͼ��
	for (int c = 0; c < count; c++)
	{
		Mat res_add(src.rows, src.cols + 1, src.type());
		for (int i = 0; i < src.rows; i++)
		{
			int k = trace[c].at<float>(i, 0);
			for (int j = c; j < count; j++)
			{
				int value = trace[j].at<float>(i, 0);
				if (value >= k)
					trace[j].at<float>(i, 0) = value + 1;
			}
			for (int j = 0; j < k; j++)
				res_add.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
			res_add.at<Vec3b>(i, k) = src.at<Vec3b>(i, k);
			for (int j = k + 1; j < src.cols; j++)
				res_add.at<Vec3b>(i, j) = src.at<Vec3b>(i, j - 1);
		}
		res_add.copyTo(src);
	}

	if (flag == 'R')
	{
		transpose(src, src);
		flip(src, src, 0);
	}
}

/*�Ƚ��û�����ĳߴ���ԭʼͼƬ�ߴ磬��seam-carving�㷨����ͼƬ*/
void SeamCarving(Mat& src, int height, int width)
{
	//�ж��ǷŴ�����Сͼ�� �ȴ�����
	if (new_width < width)
		for (int i = 0; i < width - new_width; i++)
			ShrinkSeam(src, 'C');
	else
		EnlargeSeam(src, new_width - width, 'C');

	//������
	if (new_height < height)
		for (int i = 0; i < height - new_height; i++)
			ShrinkSeam(src, 'R');
	else
		EnlargeSeam(src, new_height - height, 'R');
}

int main()
{
	//��ͼƬ������ԭͼ�Ա�������¼���ߴ�
	string ImagePath = "test2.jpg";
	Mat origin = imread(ImagePath);

	int height = origin.rows;
	int width = origin.cols;
	Mat src;

	while (1)
	{
		origin.copyTo(src);
		//��ʼ��������չʾͼƬ����ʾ�û�����ͼ���³ߴ�
		InputImage(src, height, width);
		cout << "------start carving------" << endl;
		clock_t start = clock();	//����ʼʱ��

		//�Ƚ��û�����ĳߴ���ԭʼͼƬ�ߴ磬��seam-carving�㷨����ͼƬ
		Mat res;
		SeamCarving(src, height, width);
		bilateralFilter(src, res, 1, 5, 5);

		//�㷨���н������������ʱ������н�����������ESC�����˳����������κμ������ٴ�����ߴ�
		clock_t finish = clock();	//�������ʱ��
		cout << "------end carving------" << endl;
		cout << "algorithm finish in: " << finish - start << " miliseconds" << endl << endl;
		namedWindow("Result Image", 0);
		resizeWindow("Result Image", res.cols, res.rows);
		imshow("Result Image", res);
		int key = waitKey();
		if (key == 27)
			break;
		else
		{
			destroyWindow("Original Image");
			continue;
		}
	}
}
