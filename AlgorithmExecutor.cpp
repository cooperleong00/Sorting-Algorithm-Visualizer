#include "pch.h"
#include "AlgorithmExecutor.h"

AlgorithmExecutor::AlgorithmExecutor(Visualizer *myVs):CompareTime(0),SwapTime(0)
{
	myVisualizer = myVs;
}

BubbleSort::BubbleSort(Visualizer *myVs):AlgorithmExecutor(myVs)
{
}

void BubbleSort::Execute() {
	for (int loop1 = myVisualizer->myRects->rects.size()-1; loop1 >= 0; loop1--) {
		myVisualizer->HighLightRect(loop1 ,DEEPSKY_BLUE);	
		for (int loop2 = 0; loop2 < loop1;loop2++ ) {
			myVisualizer->HighLightRect(loop2, DEEPSKY_BLUE);		
			if (myVisualizer->myRects->position[loop2] > myVisualizer->myRects->position[loop2 + 1]) {		
				myVisualizer->SwapRect(loop2, loop2+1);
				SwapTime++;
				myVisualizer->UnHighLightRect(loop2);
				myVisualizer->UnHighLightRect(loop2+1);
			}
			CompareTime++;
			myVisualizer->UnHighLightRect(loop2);
		}
		myVisualizer->UnHighLightRect(loop1);
	}
	SDL_Delay(3000);
}

SelectionSort::SelectionSort(Visualizer * myVs) :AlgorithmExecutor(myVs)
{
}

void SelectionSort::Execute()
{
	for (int loop1 = 0; loop1 < myVisualizer->myRects->rects.size() - 1; loop1++) {
		size_t Min = myVisualizer->myRects->position[loop1];
		size_t MinStep = loop1;
		myVisualizer->HighLightRect(loop1, DEEPSKY_BLUE);
		for (int loop2 = loop1; loop2 < myVisualizer->myRects->rects.size() ; loop2++) {
			myVisualizer->HighLightRect(loop2, DEEPSKY_BLUE);
			if (Min > myVisualizer->myRects->position[loop2]) {
				Min = myVisualizer->myRects->position[loop2];
				MinStep = loop2;
			}
			CompareTime++;
			myVisualizer->UnHighLightRect(loop2);
		}
		myVisualizer->SwapRect(loop1, MinStep);
		SwapTime++;
		myVisualizer->UnHighLightRect(loop1);
		myVisualizer->UnHighLightRect(MinStep);
	}
	SDL_Delay(3000);
}

InsertionSort::InsertionSort(Visualizer * myVs) :AlgorithmExecutor(myVs)
{
}

void InsertionSort::Execute()
{
	for (int loop1 = 1; loop1 < myVisualizer->myRects->rects.size(); loop1++) {
		for (int loop2 = loop1; loop2 > 0 && myVisualizer->myRects->position[loop2] < myVisualizer->myRects->position[loop2 - 1]; loop2--) {
			myVisualizer->SwapRect(loop2, loop2 - 1);
			SwapTime++;
			myVisualizer->UnHighLightRect(loop2);
			myVisualizer->UnHighLightRect(loop2 - 1);
		}
		CompareTime++;
	}
	SDL_Delay(3000);
}



QuickSort::QuickSort(Visualizer * myVs) :AlgorithmExecutor(myVs)
{

}

void QuickSort::Execute() {
	this->Execute(0, myVisualizer->myRects->RectAmount -1);
	SDL_Delay(3000);
}

void QuickSort::Execute(size_t left, size_t right)
{
	if (left >= right)
		return;
	size_t first = left;
	size_t last = right;
	int temp = myVisualizer->myRects->position[first];
	while (first<last)
	{
		CompareTime++;
		while (first < last&&myVisualizer->myRects->position[last] >= temp) {
			CompareTime++;
			myVisualizer->HighLightRect(last, DEEPSKY_BLUE);
			myVisualizer->UnHighLightRect(last);
			--last;

		}
		myVisualizer->SwapRect(last, first);
		SwapTime++;
		myVisualizer->UnHighLightRect(last);
		myVisualizer->UnHighLightRect(first);
		
		while (first < last&&myVisualizer->myRects->position[first] < temp) {
			CompareTime++;
			myVisualizer->HighLightRect(first, DEEPSKY_BLUE);
			myVisualizer->UnHighLightRect(first);
				++first;

		}
		myVisualizer->SwapRect(last, first);
		SwapTime++;
		myVisualizer->UnHighLightRect(last);
		myVisualizer->UnHighLightRect(first);
	}
	this->Execute(left, first );
	this->Execute(first+1 , right);
}

ShellSort::ShellSort(Visualizer * myVs) :AlgorithmExecutor(myVs)
{

}

void ShellSort::Execute() {
	int length = myVisualizer->myRects->RectAmount;
	for (int div = length / 2; div >= 1; div /= 2) {
		for (int loop1 = 0; loop1 < div; loop1++) {
			myVisualizer->HighLightRect(loop1, DEEPSKY_BLUE);
			
			for (int loop2 = loop1; loop2 < length - div; loop2 += div) {
				myVisualizer->HighLightRect(loop2, DEEPSKY_BLUE);
				
				for (int loop3 = loop2; loop3 < length; loop3 += div) {
					myVisualizer->HighLightRect(loop3, DEEPSKY_BLUE);
					
					if (myVisualizer->myRects->rects[myVisualizer->myRects->position[loop2]].h > myVisualizer->myRects->rects[myVisualizer->myRects->position[loop3]].h) {
						myVisualizer->SwapRect(loop2, loop3);
						SwapTime++;
						myVisualizer->UnHighLightRect(loop2);
						myVisualizer->UnHighLightRect(loop3);
						
					}
					CompareTime++;
					myVisualizer->UnHighLightRect(loop3);
					
				}
				CompareTime++;
				myVisualizer->UnHighLightRect(loop2);
				
			}
			CompareTime++;
			myVisualizer->UnHighLightRect(loop1);
			
		}
	}
	SDL_Delay(3000);
}

