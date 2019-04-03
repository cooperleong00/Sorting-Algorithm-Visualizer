// AlgorithmVIsualizer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "AlgorithmExecutor.h"
#include <string>
#include <iostream>
#include <ctime>
#include <thread>
using namespace std;



int main(int argc, char* args[])
{
	SDL_Event e;
	//根据当前时间获取随机种子
	srand(time(NULL));
	//用户输入的 窗口宽度，窗口高度，矩形数量，算法选择
	int res_x,res_y,rectamount,AlgoSelection;
	Visualizer *v = nullptr;
	AlgorithmExecutor *sort1 = nullptr;
	while (v == nullptr) {
		cout << "请输入可视化窗口大小：" << endl;
		cout << "(建议16：9，如1280x720等，输入用空格分隔)" << endl;
		while (cin >> res_x >> res_y) {
			if (res_x < 5 || res_x>1920 || res_y < 5 || res_y>1080) {
				cout << "请输入合法的数据"<<endl;
				continue;
			}
			else {
				cout << "请输入随机数据数量：" << endl;
				cout << "（范围：2 - " << res_x / 2 << ")" << endl;
				while (cin >> rectamount) {
					if (rectamount<2||rectamount>(res_x/2)) {
						cout << "请输入合法的数据" << endl;
						continue;
					}
					else {
						v = new Visualizer(res_x, res_y, rectamount,&e);
						
						cout << "请输入序号选择进行可视化的排序算法：" << endl;
						cout << "1. 冒泡排序" << endl;
						cout << "2. 选择排序" << endl;
						cout << "3. 插入排序" << endl;
						cout << "4. 希尔排序" << endl;
						cout << "5. 快速排序" << endl;
						while (cin >> AlgoSelection) {
							switch (AlgoSelection)
							{
							case 1:
								sort1 = new BubbleSort(v);
								break;
							case 2:
								sort1 = new SelectionSort(v);
								break;
							case 3:
								sort1 = new InsertionSort(v);
								break;
							case 4:
								sort1 = new ShellSort(v);
								break;
							case 5:
								sort1 = new QuickSort(v);
								break;
							default:
								sort1 = nullptr;
								break;
							}
							if (sort1 == nullptr) {
								cout << "请输入合法的数据" << endl;
								continue;
							}
							else {
								sort1->Execute();
								cout << "比较次数：" << sort1->CompareTime << "交换次数：" << sort1->SwapTime << endl << endl;
								delete v;
								v = nullptr;
								delete sort1;
								sort1 = nullptr;
								break;
							}
						}
						break;
					}
				}
				break;
			}
		}		
	}
	return 0;
}

