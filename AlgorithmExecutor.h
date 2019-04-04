#ifndef ALGORITHMECECUTOR_H
#define ALGORITHMEXECUTOR_H
#include "visualizer.h"
class AlgorithmExecutor {
public:
/*
	AlgorithmExecutor�Ĺ��캯��
	myVs��ָ��Visualizer��ָ��
	��һ��Visualizer�������㷨��ִ�п��ƾ��εı仯
*/
/*
	Construction of AlgorithmExecutor
	myVs��A pointer points to the Visualizer
	Which binds a Visualizer and controls the displayed rectangles with the running algorithm 
*/
	AlgorithmExecutor(Visualizer *myVs);
/*
	Execute�����������㷨����ʵ�ֵĺ���
	����ʵ���㷨��ʵ������εĿ���
*/
/*
	Execute��A virtual function which the subclass of the AlgorithmExecutor must implement
	Implement the exact sorting algorithm and change the status of rectangles
*/
	virtual void Execute() = 0 ;

	//binded Visualizer
	Visualizer *myVisualizer;
	//�ȽϵĴ���
	size_t CompareTime;
	//�����Ĵ���
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

