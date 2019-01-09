
#include "MSRCR.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <io.h>
#include <Windows.h>
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <direct.h>

using namespace cv;
using namespace std;


extern void SplitString(const string& s, vector<string>& v, const string& c);
extern int readDir(char *dirName, vector<string> &filesName);

struct imfo57
{
	string name;

	float ratiow;
	float ratioh;
	float wperh;
	int objw;
	int objh;
	int width;
	int height;
};


//升序
bool LessSortw(imfo57 a, imfo57 b)
{
	
	return (a.ratiow<b.ratiow);
}
//升序
bool LessSorth(imfo57 a, imfo57 b)
{
	return (a.ratioh<b.ratioh);
}
// 先写图片对应的txt，然后再画图
int test57_1(int argc, char *argv[])
{
	
	string imgpath = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5";

	string imgpath1 = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\labelsBOX1";
	mkdir(imgpath1.c_str());

	fstream finRead;
	string inputPathtxt = imgpath + "\\" + "frameAnnotationsBOX1.csv";
	finRead.open(inputPathtxt, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	

	

	map<string,int> mapclass;
	mapclass[string("go")] = 1;  mapclass[string("goLeft")] = 2; mapclass[string("stop")] = 3;
	mapclass[string("stopLeft")] = 4; mapclass[string("warning")] = 5; mapclass[string("warningLeft")] = 6; 
	
	string line; 
	getline(finRead, line);
	while (getline(finRead, line))
	{
		vector<string> vs;
		SplitString(line, vs, ";");

		int npos = vs[0].find_last_of('\\');
		int npos2 = vs[0].find_last_of('.');

		string name1 = vs[0].substr(npos + 1, npos2 - npos - 1);

		cout << name1.c_str()<<endl;
		string outputtxt = imgpath1 + "\\" + name1 + ".txt";
		fstream finWrite;
		finWrite.open(outputtxt, ios::app);

		if (!finWrite.is_open())
		{
			cout << "finRead2 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		
			
			int x1, y1, x2, y2, label;
			label = mapclass[vs[1]];
			x1 = atoi(vs[2].c_str());
			y1 = atoi(vs[3].c_str());
			x2 = atoi(vs[4].c_str());
			y2 = atoi(vs[5].c_str());

			finWrite << label << " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
		

		finWrite.close();

	}

	return 0;
}

// 先写图片对应的txt，然后再画图
int test57_2(int argc, char *argv[])
{

	string imgpath = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5";

	
	string imgpath2 = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\labelsBULB1";
	mkdir(imgpath2.c_str());

	

	fstream finRead2;
	string inputPathtxt2 = imgpath + "\\" + "frameAnnotationsBULB1.csv";
	finRead2.open(inputPathtxt2, ios::in);
	if (!finRead2.is_open())
	{
		cout << "finRead2 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	

	map<string, int> mapclass;
	mapclass[string("go")] = 1;  mapclass[string("goLeft")] = 2; mapclass[string("stop")] = 3;
	mapclass[string("stopLeft")] = 4; mapclass[string("warning")] = 5; mapclass[string("warningLeft")] = 6;

	string line;
	getline(finRead2, line);
	while (getline(finRead2, line))
	{
		vector<string> vs;
		SplitString(line, vs, ";");

		int npos = vs[0].find_last_of('\\');
		int npos2 = vs[0].find_last_of('.');

		string name1 = vs[0].substr(npos + 1, npos2 - npos - 1);

		cout << name1.c_str() << endl;
		string outputtxt = imgpath2 + "\\" + name1 + ".txt";
		fstream finWrite;
		finWrite.open(outputtxt, ios::app);

		if (!finWrite.is_open())
		{
			cout << "finRead2 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}



		int x1, y1, x2, y2, label;
		label = mapclass[vs[1]];
		x1 = atoi(vs[2].c_str());
		y1 = atoi(vs[3].c_str());
		x2 = atoi(vs[4].c_str());
		y2 = atoi(vs[5].c_str());

		finWrite << label << " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;


		finWrite.close();

	}

	return 0;
}

int test57_3(int argc, char *argv[])
{

	string imgpath = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\frames";
	string labelpath1 = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\labelsBOX1";
	string drawpath = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\drawBOX1";
	mkdir(drawpath.c_str());

	vector<string> v_img_;
	readDir((char*)imgpath.c_str(), v_img_);
	for (int i = 0; i < v_img_.size(); i++)
	{


		


		int npos = v_img_[i].find_last_of('\\');
		int npos2 = v_img_[i].find_last_of('.');
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());

		cout << name1 << endl;

		if (img.data == NULL)
		{

			printf("图像为空!\n");
			cout << v_img_[i].c_str() << endl;
			system("pause");
		}
		fstream finRead;
		string inputPathtxt = labelpath1 + "\\" + name1+".txt";
		finRead.open(inputPathtxt, ios::in);
		if (!finRead.is_open())
		{
			cout << "finRead1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string line; 
		while (getline(finRead, line))
		{
			stringstream str_s(line);
			int label, x1, y1, x2, y2;
			str_s >> label >> x1 >> y1 >> x2 >> y2;

			char text[10];
			sprintf(text,"%d",label);
			Point pt1, pt2;
			pt1.x = x1; pt1.y = y1;
			pt2.x = x2; pt2.y = y2;
			rectangle(img, pt1, pt2, Scalar(0, 0, 255));
			Point pt3; pt3.x = x1 ; pt3.y = y2+5 ;
			putText(img, text, pt3, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0));


			
		}

		

		string file = drawpath + "\\" + name1+".png";

		imwrite(file, img);

	}

	
	

	return 0;
}
int test57_4(int argc, char *argv[])
{

	string imgpath = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\frames";
	string labelpath2 = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\labelsBULB1";
	string drawpath = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\drawBULB1";
	mkdir(drawpath.c_str());

	vector<string> v_img_;
	readDir((char*)imgpath.c_str(), v_img_);
	for (int i = 0; i < v_img_.size(); i++)
	{





		int npos = v_img_[i].find_last_of('\\');
		int npos2 = v_img_[i].find_last_of('.');
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());

		cout << name1 << endl;

		if (img.data == NULL)
		{

			printf("图像为空!\n");
			cout << v_img_[i].c_str() << endl;
			system("pause");
		}
		

		fstream finRead2;
		string inputPathtxt2 = labelpath2 + "\\" + name1 + ".txt";
		finRead2.open(inputPathtxt2, ios::in);
		if (!finRead2.is_open())
		{
			cout << "finRead2 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string line2;
		while (getline(finRead2, line2))
		{
			stringstream str_s(line2);
			int label, x1, y1, x2, y2;
			str_s >> label >> x1 >> y1 >> x2 >> y2;

			char text[10];
			sprintf(text, "%d", label);
			Point pt1, pt2;
			pt1.x = x1; pt1.y = y1;
			pt2.x = x2; pt2.y = y2;
			rectangle(img, pt1, pt2, Scalar(0, 0, 255));
			Point pt3; pt3.x = x2 + 10; pt3.y = y2 + 10;
			putText(img, text, pt3, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0));
		}

		string file = drawpath + "\\" + name1 + ".png";

		imwrite(file, img);

	}




	return 0;
}

int test57_5(int argc, char *argv[])
{

	

	string imgpath = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\frames";
	string labelpath2 = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\labelsBULB1";
	string txtpathw = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\0-BULBperw.txt";
	string txtpathh = "E:\\LISA-Traffic-Light\\dayTraining\\dayClip5\\0-BULBperh.txt";

	fstream finWrite;
	finWrite.open(txtpathw, ios::out);
	if (!finWrite.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}


	fstream finWrite2;
	finWrite2.open(txtpathh, ios::out);
	if (!finWrite2.is_open())
	{
		cout << "finRead2 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}
	vector<string> v_img_; int num = 0;
	readDir((char*)imgpath.c_str(), v_img_);
	int short_size = 600; int max_long_size = 1000;

	float minw = 10000; float minh = 10000;
	float maxw = 0; float maxh = 0;
	vector<imfo57>vfo;
	for (int i = 0; i<v_img_.size(); i++)
	{
		int npos = v_img_[i].find_last_of('\\');
		int npos2 = v_img_[i].find_last_of('.');

		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{
			printf("img.data = NULL！\n");
			system("pause");
			continue;
		}


		
		cout << name1 << endl;
		

	


		string str = labelpath2 + "\\" + name1 + ".txt";
		fstream finRead1;
		finRead1.open(str, ios::in);
		if (!finRead1.is_open())
		{
			cout << "finRead3 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		string line; int num1 = 0;

		while (getline(finRead1, line))
		{

			if (line.empty())
			{
				break;
			}

			num1++;

			int label; int x1, y1, x2, y2;
			stringstream str_s(line);
			str_s >> label >> x1 >> y1 >> x2 >> y2;

			int objw = x2 - x1 + 1; int objh = y2 - y1 + 1;
			
			float objperw = objw*1.0 / img.cols;
			float objperh = objh*1.0 / img.rows;

			imfo57 vi;
			vi.name = name1;
			
			vi.ratiow= objperw;
			vi.ratioh = objperh;
			vi.wperh = objw*1.0 / objh;
			vi.objw = objw;
			vi.objh = objh;

			vfo.push_back(vi);


			if (objperw<minw)
			{
				minw = objperw;
			}
			if (objperh < minh)
			{
				minh = objperh;
			}

			if (objperw>maxw)
			{
				maxw = objperw;
			}
			if (objperh > maxh)
			{
				maxh = objperh;
			}

		}

		finRead1.close();

	}
	printf("perminw=%f,perminh=%f,permaxw=%f,permaxh=%f\n", minw, minh, maxw, maxh);

	sort(vfo.begin(), vfo.end(), LessSortw);//升序排列

	for (int j = 0; j < vfo.size(); j++)
	{
		imfo57 vi = vfo[j];
		finWrite << vi.name << " " << vi.ratiow << " " << vi.ratioh << " " << vi.wperh << " " << vi.objw << " " << vi.objh<< endl;
	}

	finWrite.close();


	sort(vfo.begin(), vfo.end(), LessSorth);//升序排列

	for (int j = 0; j < vfo.size(); j++)
	{
		imfo57 vi = vfo[j];
		finWrite2 << vi.name << " " << vi.ratiow << " " << vi.ratioh << " " << vi.wperh << " " << vi.objw << " " << vi.objh << endl;
	}

	finWrite2.close();

	return 0;
}
int test57_5val(int argc, char *argv[])
{



	string imgpath = "E:\\LISA-Traffic-Light\\dayTrainingall\\dayClip";
	
	
	

	string inputPathtxt = imgpath+"\\"+"test.txt";
	fstream finRead;
	finRead.open(inputPathtxt, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead1 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	

	

	
	map<int,vector<imfo57>>mvfo;
	
	string line;
	while (getline(finRead, line))
	{
		string str1, str2;
		stringstream str_s(line);
		str_s >> str1 >> str2;

		int npos = str1.find_last_of('/');
		
		string name1 = str1.substr(npos + 1, str1.size() - npos - 1);

		string imgfile = imgpath + "\\" + str1;
		Mat img = imread(imgfile);
		int width = img.cols; int height = img.rows;


		string outputtxt = imgpath + "\\" + str2;
		fstream fin1;
		fin1.open(outputtxt, ios::in);

		if (!fin1.is_open())
		{
			cout << "fin12 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}


		string line1;

		while (getline(fin1, line1))
		{
			int x1, y1, x2, y2, label;
			stringstream str_s(line1);
			str_s >> label >> x1 >> y1 >> x2 >> y2;
			
			int objw = x2 - x1 + 1; int objh = y2 - y1 + 1;

			float objperw = objw*1.0 / img.cols;
			float objperh = objh*1.0 / img.rows;

			imfo57 vi;
			vi.name = name1;

			vi.ratiow = objperw;
			vi.ratioh = objperh;
			vi.wperh = objw*1.0 / objh;
			vi.objw = objw;
			vi.objh = objh;
			vi.width = width;
			vi.height = height;
			mvfo[label].push_back(vi);

		}

		fin1.close();

	}

	finRead.close();

	map<int, vector<imfo57>>::iterator it = mvfo.begin();
	for (; it != mvfo.end();it++)
	{
		int label = it->first;
		char file[1024];
		sprintf(file,"%d",label);
		string txtpathw = imgpath + "\\" +file+ "perw.txt";
		fstream finWrite;
		finWrite.open(txtpathw, ios::out);
		if (!finWrite.is_open())
		{
			cout << "finRead1 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}
		vector<imfo57> vfo = it->second;
		sort(vfo.begin(), vfo.end(), LessSortw);//升序排列

		for (int j = 0; j < vfo.size(); j++)
		{
			imfo57 vi = vfo[j];
			finWrite << vi.name << " " << vi.ratiow << " " << vi.ratioh << " " << vi.wperh << " " << vi.objw << " " << vi.objh 
				<< " " << vi.width << " " << vi.height << endl;
		}

		finWrite.close();
	}
	

	

	
	map<int, vector<imfo57>>::iterator it1 = mvfo.begin();
	for (; it1 != mvfo.end(); it1++)
	{
		int label = it1->first;
		char file[1024];
		sprintf(file, "%d", label);
		string txtpathh = imgpath + "\\" +file+"perh.txt";
		fstream finWrite2;
		finWrite2.open(txtpathh, ios::out);
		if (!finWrite2.is_open())
		{
			cout << "finRead2 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}
		vector<imfo57> vfo = it1->second;
		sort(vfo.begin(), vfo.end(), LessSorth);//升序排列

		for (int j = 0; j < vfo.size(); j++)
		{
			imfo57 vi = vfo[j];
			finWrite2 << vi.name << " " << vi.ratiow << " " << vi.ratioh << " " << vi.wperh << " " << vi.objw << " " << vi.objh 
				<<" " << vi.width  << " " << vi.height<< endl;
		}

		finWrite2.close();
	}

	
	

	return 0;
}
int test57(int argc, char *argv[])
{

	/*test57_1(argc, argv);
	test57_2(argc, argv);
	test57_3(argc, argv);
	test57_4(argc, argv);*/
	
	//test57_5(argc, argv);

	//  验证集 目标占图像比例。
	test57_5val(argc, argv);

	return 0;
}









