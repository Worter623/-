#include <iostream>
#include <opencv.hpp>
#include <vector>
#include <math.h>
#include <time.h>
using namespace std;
using namespace cv;

/*������빫ʽ�е�m*/
const int m = 10;

/*��ʼ����Ҫ�õ��������*/
const double inf = 1e9;

/*��ʾһ�����صĽṹ��*/
struct pixel_cor {
	int l;
	int a;
	int b;
	int x;
	int y;
};

/*��ʼ������������ԭͼ��labɫ�ʿռ��ͼ��*/
Mat Initialize(Mat& image, vector<vector<int>>& l_image, vector<vector<double>>& d_image, vector <pixel_cor>& center, int S)
{
	if (image.empty())
	{
		cout << "image input initialize empty" << endl;
		return image;
	}
	int height = image.rows;
	int width = image.cols;
	struct pixel dot;

	/*��ͼƬ��RGB�ռ�ת��ΪLab�ռ�*/
	Mat lab_image;
	cvtColor(image, lab_image, COLOR_BGR2Lab);

	/*��ʼ��ÿ���������ڵľ�������Ϊ-1*/
	vector<int> c;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			c.push_back(-1);
		}
		l_image.push_back(c);
		vector<int>().swap(c);
	}
	/*����ΪS�������ؽ��г�ʼ�����������ɾ�������*/
	for (int i = 0; i < height; i += S)
	{
		dot.y = i + S / 2;
		if (dot.y >= height)
			continue;
		uchar* ptr = lab_image.ptr<uchar>(dot.y);
		for (int j = 0; j < width; j += S)
		{
			dot.x = j + S / 2;
			if (dot.x > width)
				continue;
			dot.l = *(ptr + dot.x * 3);
			dot.a = *(ptr + dot.x * 3 + 1);
			dot.b = *(ptr + dot.x * 3 + 2);
			center.push_back(dot);
		}
	}

	/*�����������ƶ���3��3�������ݶ���С��λ��*/
	Mat sobelx, sobely, sobel;
	Sobel(lab_image, sobelx, CV_64F, 0, 1, 3);
	Sobel(lab_image, sobely, CV_64F, 1, 0, 3);
	addWeighted(sobelx, 0.5, sobely, 0.5, 0, sobel);
	int width_s = sobel.cols;
	int height_s = sobel.rows;
	for (int i = 0; i < center.size(); i++)
	{
		dot = center[i];
		if (dot.x - 1 < 0 || dot.x + 1 >= width_s || dot.y - 1 < 0 || dot.y + 1 >= height_s)
		{
			cout << "center " << i << "is on boundary thus cannot move" << endl;
			continue;
		}
		double min = inf;
		struct pixel temp;
		for (int j = -1; j < 2; j++)
		{
			double* ptr_s = sobel.ptr<double>(dot.y + j);
			for (int n = -1; n < 2; n++)
			{
				temp.l = *(ptr_s + (dot.x + n) * 3);
				temp.a = *(ptr_s + (dot.x + n) * 3 + 1);
				temp.b = *(ptr_s + (dot.x + n) * 3 + 2);
				double gradient = pow(temp.l, 2) + pow(temp.a, 2) + pow(temp.b, 2);
				if (gradient < min)
				{/*��¼�ݶ���С��λ��*/
					min = gradient;
					temp.y = j;
					temp.x = n;
				}
			}
		}
		uchar* ptr_i = lab_image.ptr<uchar>(dot.y);
		center[i].x += temp.x;
		center[i].y += temp.y;
		center[i].l = *(ptr_i + dot.x * 3);
		center[i].a = *(ptr_i + dot.x * 3 + 1);
		center[i].b = *(ptr_i + dot.x * 3 + 2);
	}
	return lab_image;
}

/*��ʼ��ÿ�����صľ���Ϊinf*/
void DistanceInit(vector<vector<double>>& d_image, int height, int width)
{
	vector<double> d;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			d.push_back(inf);
		}
		d_image.push_back(d);
		vector<double>().swap(d);
	}
}

/*�����������ص�֮��ľ���*/
double ComputeDistance(struct pixel_cor& c, struct pixel_cor& temp, int S)
{
	double d_c = pow(temp.l - c.l, 2) + pow(temp.a - c.a, 2) + pow(temp.b - c.b, 2);
	double d_s = pow(temp.x - c.x, 2) + pow(temp.y - c.y, 2);
	return d_c + d_s / S * m * m;
}

/*������벢����*/
void Cluster(vector<pixel_cor>& center, int S, Mat& lab_image, vector<vector<double>>& d_image, vector<vector<int>>& l_image)
{
	struct pixel_cor temp_dot;
	for (int count = 0; count < center.size(); count++)
	{
		struct pixel_cor dot = center[count];
		for (int i = dot.y - S; i < dot.y + S; i++)
		{
			//cout << lab_image.rows<<" "<<lab_image.cols<<endl;
			if (i < 0 || i >= lab_image.rows)
				continue;
			uchar* ptr_i = lab_image.ptr<uchar>(i);
			for (int j = dot.x - S; j < dot.x + S; j++)
			{
				if (j < 0 || j >= lab_image.cols)
					continue;
				temp_dot.x = j;
				temp_dot.y = i;
				temp_dot.l = *(ptr_i + j * 3);
				temp_dot.a = *(ptr_i + j * 3 + 1);
				temp_dot.b = *(ptr_i + j * 3 + 2);
				double D = ComputeDistance(dot, temp_dot, S);
				if (D < d_image[i][j])
				{
					d_image[i][j] = D;
					l_image[i][j] = count + 1;
				}
			}
		}
	}
}

/*�����µľ�������*/
void Update( vector<pixel_cor>& center, int S, Mat& lab_image, vector<vector<int>>& l_image)
{
	for (int count = 0; count < center.size(); count++)
	{
		struct pixel_cor dot = center[count];
		int sumc = 0; double sumx = 0; double sumy = 0;
		double suml = 0; double suma = 0; double sumb = 0;
		for (int i = dot.y - S; i < dot.y + S; i++)
		{
			if (i < 0 || i >= lab_image.rows)
				continue;
			uchar* ptr_i = lab_image.ptr<uchar>(i);
			for (int j = dot.x - S; j < dot.x + S; j++)
			{
				if (j < 0 || j >= lab_image.cols)
					continue;
				if (l_image[i][j] == count + 1)
				{
					sumx += j;
					sumy += i;
					suml += *(ptr_i + j * 3);
					suma += *(ptr_i + j * 3 + 1);
					sumb += *(ptr_i + j * 3 + 2);
					sumc++;
				}
			}
		}
		center[count].x = sumx / sumc;
		center[count].y = sumy / sumc;
		center[count].l = suml / sumc;
		center[count].a = suma / sumc;
		center[count].b = sumb / sumc;
	}
}

/*ʹ����ͨ��������һЩorphan pixel�������޸ĺ�ĳ����ؿ�����*/
void ConnectOrphanPixel(int S, int height, int width, vector<vector<int>>& l_image,vector<pixel_cor>& center, Mat& lab_image)
{
	int label = 1;
	int adjlabel = 1;
	/*����ԭ����ʵ�֣������ڽ�����Ϊ4-�ڽ�*/
	const int dx4[4] = { -1,  0,  1,  0 };
	const int dy4[4] = { 0, -1,  0,  1 };
	vector<vector<int>> new_label;
	vector <int> temp;

	/*��ʼ��һ���µı�ǩ����¼ÿ�����������ĸ���ǩ*/
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			temp.push_back(-1);
		}
		new_label.push_back(temp);
		vector<int>().swap(temp);
	}

	/*������ͨ����*/
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (new_label[i][j] == -1)
			{
				new_label[i][j] == label;
				struct pixel dot;
				dot.x = j; dot.y = i;
				vector<pixel> queue;
				queue.push_back(dot);
				/*4-������������Ѿ���������ģ���׼���ϲ�*/
				for (int k = 0; k < 4; k++)
				{
					int x = j + dx4[k];
					int y = i + dy4[k];
					if (x >= 0 && x < width && y >= 0 && y < height)
						if (new_label[i][j] >= 0)
							adjlabel = new_label[i][j];
				}
				int count = 1;
				/*���㳬���ؿ������صĸ���*/
				for (int k = 0; k < count; k++)
				{
					for (int n = 0; n < 4; n++)
					{
						int x = queue[k].x + dx4[n];
						int y = queue[k].y + dy4[n];
						if (x >= 0 && x < width && y >= 0 && y < height)
							if (new_label[y][x] == -1 && l_image[y][x] == l_image[i][j])
							{
								dot.x = x; dot.y = y;
								queue.push_back(dot);
								new_label[y][x] = label;
								count++;
							}
					}
				}
				/*�����ؿ������ظ���̫�٣��ͺϲ�*/
				if (count <= S / 2)
				{
					for (int k = 0; k < count; k++)
						new_label[queue[k].y][queue[k].x] = adjlabel;
					label--;
				}
				label++;
				vector<pixel_cor>().swap(queue);
			}
		}
	}
	//l_image = new_label;
}

/*��ʾ�������ÿ�������ؿ����������ص�l��a��bֵ��ֵΪ���������ĵ��l��a��bֵ*/
void ShowResult(Mat& lab_image, vector<pixel_cor>center, int S, vector<vector<int>>& l_image)
{
	Mat temp = lab_image.clone();
	for (int count = 0; count < center.size(); count++)
	{
		struct pixel dot = center[count];
		for (int i = dot.y - S; i < dot.y + S; i++)
		{
			if (i < 0 || i >= lab_image.rows)
				continue;
			uchar* ptr_i = temp.ptr<uchar>(i);
			for (int j = dot.x - S; j < dot.x + S; j++)
			{
				if (j < 0 || j >= lab_image.cols)
					continue;
				if (l_image[i][j] == count + 1)
				{
					*(ptr_i + j * 3) = center[count].l;
					*(ptr_i + j * 3 + 1) = center[count].a;
					*(ptr_i + j * 3 + 2) = center[count].b;
				}
			}
		}
	}
	cvtColor(temp, temp, cv::COLOR_Lab2BGR);
	namedWindow("SLICresult", 0);
	imshow("SLICresult", temp);
}

/*��ʾ����������������أ��������ؿ���������ظ�ֵΪ��ɫ*/
void ShowBoundary(Mat& image, vector<vector<int>>& l_image)
{
	Mat temp = image.clone();
	for (int i = 0; i < image.rows - 1; i++)
	{
		uchar* ptr = temp.ptr<uchar>(i);
		for (int j = 0; j < image.cols - 1; j++)
		{
			if (l_image[i][j] != l_image[i][j + 1])
			{
				*(ptr + 3 * j) = 0;
				*(ptr + 3 * j + 1) = 0;
				*(ptr + 3 * j + 2) = 0;
			}
			else if (l_image[i][j] != l_image[i + 1][j])
			{
				*(ptr + 3 * j) = 0;
				*(ptr + 3 * j + 1) = 0;
				*(ptr + 3 * j + 2) = 0;
			}
		}
	}
	namedWindow("SLICboundary", 0);
	imshow("SLICboundary", temp);
}

/*��ָ��·����ͼƬִ��SLIC�㷨������k�������ؿ�
	RGBͼ��洢��ʽ: 64FC3
	����;������ļ�¼ͼ��洢��ʽ: 64FC1
	LABͼ��洢��ʽ: 8UC3*/
void SLIC(string IPath, int k)
{
	Mat image = imread(IPath);
	vector<vector<int>> l_image;//��¼ÿ�����������ĸ���������
	vector<vector<double>> d_image;//��¼ÿ�����صľ���
	vector<pixel_cor> center;//��¼��������
	const int threshold = 10;//k-means��������

	/*���㳬���ؿ�����֮��ľ���*/
	int S = 0;
	int height = image.rows;
	int width = image.cols;
	float temp = sqrt(height * width / k);
	S = round(temp);
	cout << "the size of this picture is: " << height << " �� " << width << endl;
	cout << "the rough size of superpixels would be: " << S << endl;
	cout << "iteration times would be: " << threshold << endl;

	/*��ʼ��*/
	clock_t start = clock();//����ʼʱ��
	Mat lab_image = Initialize(image, l_image, d_image, center, S);

	/*k-means����������Ϊ����threshould*/
	for (int times = 0; times < threshold; times++)
	{
		/*��ʼ��ÿ�����صľ���Ϊinf*/
		DistanceInit(d_image, height, width);
		/*������벢����*/
		Cluster(center, S, lab_image, d_image, l_image);
		/*�����µľ�������*/
		Update(center, S, lab_image, l_image);
	}

	/*ʹ����ͨ�����㷨����һЩorphan pixel*/
	ConnectOrphanPixel(S,height,width,l_image,center,lab_image);
	Update(center, S, lab_image, l_image);

	clock_t finish = clock();
	cout << "SLIC finish in: " << finish - start << " miliseconds" << endl;

	/*��ʾ���*/
	ShowResult(lab_image, center, S, l_image);
	ShowBoundary(image, l_image);

	/*�������ESC�����˳�*/
	int key = waitKey();
	if (key == 27)
		return;
}

int main()
{
	string path = "1_16_s.bmp";
	int k = 200;
	SLIC(path, k);
}