#ifndef ALGORITHMECECUTOR_H
#define ALGORITHMEXECUTOR_H
#include "visualizer.h"
class AlgorithmExecutor {
public:
/*
	AlgorithmExecutor的构造函数
	myVs：指向Visualizer的指针
	绑定一个Visualizer来根据算法的执行控制矩形的变化
*/
	AlgorithmExecutor(Visualizer *myVs);
/*
	Execute：子类排序算法必须实现的函数
	其中实现算法的实行与矩形的控制
*/
	virtual void Execute() = 0 ;

	//绑定的Visualizer
	Visualizer *myVisualizer;
	//比较的次数
	size_t CompareTime;
	//交换的次数
	size_t SwapTime;
};


class BubbleSort:public AlgorithmExecutor {
public:
	BubbleSort(Visualizer *myVs);
	void Execute();
};

class SelectionSort :public AlgorithmExecutor {
public:
	SelectionSort(Visualizer *myVs);
	void Execute();
};

class InsertionSort :public AlgorithmExecutor {
public:
	InsertionSort(Visualizer *myVs);
	void Execute();
};

class ShellSort :public AlgorithmExecutor {
public:
	ShellSort(Visualizer *myVs);
	void Execute();
};

class QuickSort :public AlgorithmExecutor {
public:
	QuickSort(Visualizer *myVs);
	void Execute();
private:
	void Execute(size_t left, size_t right);
};
#endif // !ALGORITHMECECUTOR_H

