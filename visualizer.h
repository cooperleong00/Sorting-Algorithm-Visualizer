/*
	visualizer.h
	可视化界面的属性与操作函数
	矩形属性的储存，管理与操作
*/
#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <SDL.h>
#include <vector>
using namespace std;

//常见的颜色
typedef enum {
	DEFAULT,
	RED,
	DEEPSKY_BLUE,
	WHITE,
	BLACK,
	GREEN
}CommonColor;

class vRectangles {
public:
/*
	vRectangles的默认构造函数，用于生成管理矩形的矩形集
	默认生成10个矩形
*/
	vRectangles();
/*
	vRectangles的构造函数，用于生成管理矩形的矩形集
	RectAmount：size_t 类型，要生成的矩形的数量
*/
	vRectangles(size_t RectAmount);

/*
	复制构造函数
*/
	//vRectangles()

/*
	构造函数3
*/
/*
	Rectmount：矩形的数量	
*/
	size_t RectAmount;
/*
	rects：存放所有SDL_Rect的容器
	存放每个矩形对应的宽（w）高（h），位置（x，y）
*/
	vector<SDL_Rect> rects;
/*
	position：存放对应位置的矩形序号的容器
	容器中每个下标是显示在窗口上的矩形的从左到右数的序号位置
	每个下标对应存放 矩形的序号
	如：position[1]的值为4则表示：从左到右数的第2个矩形是rect容器中的第5个矩形
*/
	vector<size_t> position;
/*
		rectColors：存放对应位置的矩形颜色序号的容器
		存放每个位置上对应矩形的颜色
*/
	vector<CommonColor> rectColors;
private:
/*
	RandomInt，生成从0开始的随机整数
	randomMax：size_t类型，随机的可能的最大整数（会包括）
*/
	size_t RandomInt(size_t randomMax);
	
};

class Visualizer {
public:
/*
	Visualizer 的默认构造函数
	默认生成宽度为640，高度480，矩形数量为10的可视化控制器
*/
	Visualizer(SDL_Event *e);
/*
	Visualizer的构造函数，初始化生成一个窗口与矩形
	width：size_t类型，窗口的宽度
	height：size_t类型，窗口的高度
	rectsAcount：size_t类型，用于排序的矩形数量
*/
	Visualizer(size_t width, size_t height, size_t rectsAcount,SDL_Event *e);
	~Visualizer();
/*
	SwapRect 交换两矩形
	pos1：size_t 类型，要交换的第一个矩形的位置
	pos2：size_t 类型，要与第一个矩形交换的矩形的位置
*/
	void SwapRect(size_t pos1, size_t pos2);
/*
	 HighLightRect：高亮矩形
	 pos：希望高亮的矩形的位置-1（position容器中的下标）
	 ccolor：高亮的颜色
*/
	void HighLightRect(size_t pos, CommonColor ccolor);
/*
	UnHighLightRect：取消矩形高亮
	 pos：希望取消高亮的据矩形的位置-1（position容器中的下标）
*/
	void UnHighLightRect(size_t pos);

	//与窗口绑定的矩形集
	vRectangles *myRects;
	//窗口事件
	
private:
/*
	WindowInit,初始化窗口,返回是否成功
	width：size_t类型，窗口的宽度
	height：size_t类型，窗口的高度
*/
	bool WindowInit(size_t width, size_t height);
/*
	WindowQuit,退出窗口
*/
	void WindowQuit();
/*
	Update：根据矩形的属性渲染更新画面
*/
	void Update();
	//主窗口
	SDL_Window *MainWindow;
	//与主窗口绑定的渲染器
	SDL_Surface *MainSurface;
	//渲染器
	SDL_Renderer *MainRenderer;
	SDL_Event *myevent;
	//画面间延迟的时间，为方便不由用户控制
	size_t DelayTime;
};



#endif // !VISUALIZER_H
