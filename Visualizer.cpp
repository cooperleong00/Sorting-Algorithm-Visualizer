#include "pch.h"
#include "visualizer.h"
#include <iostream>


using namespace std;


Visualizer::Visualizer(SDL_Event *event)
{
	Visualizer(640, 480, 10, event);
}


Visualizer::Visualizer(size_t width, size_t height, size_t rectsAmount,SDL_Event *event)
{
	myRects = new vRectangles(rectsAmount);
	myevent = event;
	//矩形数量大于100时动画延迟设为1ms
	if (rectsAmount > 100)
		DelayTime = 1;
	else
		DelayTime = static_cast<size_t>(750/rectsAmount + 1 );
	if (myRects == NULL)
		cout << "矩形初始化失败" << endl;
	else {
		//均分矩形宽度，每个矩形向右预留1像素作为间隙
		size_t rectwidth = (width - rectsAmount) / rectsAmount;
		for (int i = 0; i < rectsAmount; i++) {
			myRects->rects[i].w = rectwidth ;
			//排序好后的第一个矩形为正方形，其余矩形高度差距相等
			myRects->rects[i].h = rectwidth + i*(height - rectwidth)/(rectsAmount-1);
		}
		for (int i = 0; i < rectsAmount; i++) {
			myRects->rects[myRects->position[i]].x = i*rectwidth+i;
			myRects->rects[i].y = height - myRects->rects[i].h;
		}
		
	}
	if (WindowInit(width,height)) {
		Update();
		cout << "矩形初始化成功" << endl;
	}
	else 
		cout << "可视化界面初始化失败" << endl;
}


Visualizer::~Visualizer()
{
	WindowQuit();
	free(myRects);
}

void Visualizer::SwapRect(size_t pos1, size_t pos2)
{
	//将要交换的两个矩形高亮成橙色
	HighLightRect(pos1, RED);
	HighLightRect(pos2, RED);
	//交换对应位置对应矩形的x坐标
	size_t tempX = myRects->rects[myRects->position[pos1]].x;
	myRects->rects[myRects->position[pos1]].x = myRects->rects[myRects->position[pos2]].x;
	myRects->rects[myRects->position[pos2]].x = tempX;
	//在位置容器中交换对应位置的矩形序号
	size_t temp = myRects->position[pos1];
	myRects->position[pos1] = myRects->position[pos2];
	myRects->position[pos2] = temp;
	//重新高亮矩形
	HighLightRect(pos1, RED);
	HighLightRect(pos2, RED);
}

bool Visualizer::WindowInit(size_t width = 640, size_t height = 480) {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Visual Window Init Failed:" << SDL_GetError() << endl;
		success = false;
	}
	else {
		//初检测无错误后，创建主窗口
		MainWindow = SDL_CreateWindow("AlgorithmVisualize", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		if (MainWindow == NULL) {
			cout << "Main Window Create Failed:" << SDL_GetError() << endl;
			success = false;
		}

		else {
			//获取和初始化窗体关联的surface
			MainSurface = SDL_GetWindowSurface(MainWindow);
			if (MainSurface == NULL) {
				cout << "Main Surface Create Failed:" << SDL_GetError() << endl;
				success = false;
			}
			else {
				//创建与窗体关联的渲染器
				MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
				if (MainRenderer == NULL) {
					cout << "Main Renderer Create Failed:" << SDL_GetError() << endl;
					success = false;
				}
				else{
					//SDL_FillRect(MainSurface, NULL,0x000000);
					//更新填充信息
					SDL_UpdateWindowSurface(MainWindow);
				}
			}
		}
	}
	//SDL_AddEventWatch(this->mySDL_EventFilter, this); //尝试使用这个来异步获取event失败了 12/4/16：25

	return success;	
}

//释放窗体，退出操作
void Visualizer::WindowQuit(){
	SDL_DestroyWindow(MainWindow);
	MainWindow = NULL;	
	SDL_DestroyRenderer(MainRenderer);
	MainRenderer = NULL;
	SDL_Quit();
}




void Visualizer::HighLightRect(size_t pos, CommonColor ccolor)
{
	//对应位置的颜色容器中的颜色修改
	myRects->rectColors[pos] = ccolor;
	Update();
}

void Visualizer::UnHighLightRect(size_t pos)
{
	//对应位置的颜色容器中的颜色修改成白色，默认颜色
	myRects->rectColors[pos] = WHITE;
	Update();
}

void Visualizer::Update()
{
	//处理SDL事件，如鼠标对窗口的操作等，移动会造成暂停
	if (SDL_PollEvent(myevent) != 0) {
		//暂时只能通过关闭命令行来关闭程序
		//使用右上角叉叉关闭目前会造成不可预料的影响
		//if (myevent->type == SDL_QUIT) {
		//	delete this;
		//	return;
		//}
	}
	
		//清空渲染器，清空屏幕渲染等待重新渲染
		SDL_RenderClear(MainRenderer);
		//设置渲染器的渲染颜色为黑色
		SDL_SetRenderDrawColor(MainRenderer, 0x00, 0x00, 0x00, 0xFF);
		//渲染整个窗口的颜色为黑色，即设置背景颜色为黑
		SDL_RenderFillRect(MainRenderer, NULL);
		//遍历渲染全部的矩形
		for (int i = 0; i < this->myRects->RectAmount; i++) {
			//根据不同矩形的颜色渲染矩形
			switch (myRects->rectColors[i])
			{
			case WHITE:
				SDL_SetRenderDrawColor(MainRenderer, 0xF8, 0xF8, 0xFF, 0xFF);
				SDL_RenderFillRect(MainRenderer, &myRects->rects[myRects->position[i]]);
				break;
			case RED:
				SDL_SetRenderDrawColor(MainRenderer, 0xFF, 0x45, 0x00, 0xFF);
				SDL_RenderFillRect(MainRenderer, &myRects->rects[myRects->position[i]]);
				break;
			case DEEPSKY_BLUE:
				SDL_SetRenderDrawColor(MainRenderer, 0x00, 0xBF, 0xFF, 0xFF);
				SDL_RenderFillRect(MainRenderer, &myRects->rects[myRects->position[i]]);
				break;
			default:
				//默认渲染为白色
				SDL_SetRenderDrawColor(MainRenderer, 0xF8, 0xF8, 0xFF, 0xFF);
				SDL_RenderFillRect(MainRenderer, &myRects->rects[myRects->position[i]]);
				break;
			}

		}
		//将渲染器中的内容渲染上窗口
		SDL_RenderPresent(MainRenderer);
		//延迟delayTime毫秒
		SDL_Delay(DelayTime);
	
}



vRectangles::vRectangles()
{
	//默认设置10个矩形
	vRectangles(10);
}


vRectangles::vRectangles(size_t RectAmount)
{
	this->RectAmount = RectAmount;
	//将矩形集，对应位置的矩形序号集，对应位置的矩形颜色序号集，重新根据用户输入的矩形数量设置大小
	//大小与输入的矩形数量相同
	rects.resize(RectAmount);
	position.resize(RectAmount);
	rectColors.resize(RectAmount);
	//遍历将对应位置的矩形序号集 和 对应位置的矩形颜色序号集 ，设置默认值
	//矩形序号集默认从1到RectAmount
	//矩形颜色序号集默认全为白色
	for (int i = 0; i < RectAmount ; i++) {
		position[i] = i;
		rectColors[i] = WHITE;
	}
	//打乱对应位置矩形序号集的顺序
	//实现矩形位置的随机
	for (int i = 0,r = 0,temp = 0; i < RectAmount ; i++) {
		r = RandomInt(RectAmount-1);
		temp = position[i];
		position[i] = position[r];
		position[r] = temp;
	}
	//输出随机数据
	for (int i = 0, r = 0, temp = 0; i < RectAmount; i++) {
		cout << position[i] << " ";
	}
	cout << endl;
}


size_t vRectangles::RandomInt(size_t randomMax)
{
	//从0到randomMax间的随机整数
	return (size_t)(rand()%(randomMax+1));
}


