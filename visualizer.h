/*
	visualizer.h
	���ӻ�������������������
	�������ԵĴ��棬���������
*/
#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <SDL.h>
#include <vector>
using namespace std;

//��������ɫ
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
	vRectangles��Ĭ�Ϲ��캯�����������ɹ�����εľ��μ�
	Ĭ������10������
*/
	vRectangles();
/*
	vRectangles�Ĺ��캯�����������ɹ�����εľ��μ�
	RectAmount��size_t ���ͣ�Ҫ���ɵľ��ε�����
*/
	vRectangles(size_t RectAmount);

/*
	���ƹ��캯��
*/
	//vRectangles()

/*
	���캯��3
*/
/*
	Rectmount�����ε�����	
*/
	size_t RectAmount;
/*
	rects���������SDL_Rect������
	���ÿ�����ζ�Ӧ�Ŀ�w���ߣ�h����λ�ã�x��y��
*/
	vector<SDL_Rect> rects;
/*
	position����Ŷ�Ӧλ�õľ�����ŵ�����
	������ÿ���±�����ʾ�ڴ����ϵľ��εĴ������������λ��
	ÿ���±��Ӧ��� ���ε����
	�磺position[1]��ֵΪ4���ʾ�����������ĵ�2��������rect�����еĵ�5������
*/
	vector<size_t> position;
/*
		rectColors����Ŷ�Ӧλ�õľ�����ɫ��ŵ�����
		���ÿ��λ���϶�Ӧ���ε���ɫ
*/
	vector<CommonColor> rectColors;
private:
/*
	RandomInt�����ɴ�0��ʼ���������
	randomMax��size_t���ͣ�����Ŀ��ܵ�����������������
*/
	size_t RandomInt(size_t randomMax);
	
};

class Visualizer {
public:
/*
	Visualizer ��Ĭ�Ϲ��캯��
	Ĭ�����ɿ��Ϊ640���߶�480����������Ϊ10�Ŀ��ӻ�������
*/
	Visualizer(SDL_Event *e);
/*
	Visualizer�Ĺ��캯������ʼ������һ�����������
	width��size_t���ͣ����ڵĿ��
	height��size_t���ͣ����ڵĸ߶�
	rectsAcount��size_t���ͣ���������ľ�������
*/
	Visualizer(size_t width, size_t height, size_t rectsAcount,SDL_Event *e);
	~Visualizer();
/*
	SwapRect ����������
	pos1��size_t ���ͣ�Ҫ�����ĵ�һ�����ε�λ��
	pos2��size_t ���ͣ�Ҫ���һ�����ν����ľ��ε�λ��
*/
	void SwapRect(size_t pos1, size_t pos2);
/*
	 HighLightRect����������
	 pos��ϣ�������ľ��ε�λ��-1��position�����е��±꣩
	 ccolor����������ɫ
*/
	void HighLightRect(size_t pos, CommonColor ccolor);
/*
	UnHighLightRect��ȡ�����θ���
	 pos��ϣ��ȡ�������ľݾ��ε�λ��-1��position�����е��±꣩
*/
	void UnHighLightRect(size_t pos);

	//�봰�ڰ󶨵ľ��μ�
	vRectangles *myRects;
	//�����¼�
	
private:
/*
	WindowInit,��ʼ������,�����Ƿ�ɹ�
	width��size_t���ͣ����ڵĿ��
	height��size_t���ͣ����ڵĸ߶�
*/
	bool WindowInit(size_t width, size_t height);
/*
	WindowQuit,�˳�����
*/
	void WindowQuit();
/*
	Update�����ݾ��ε�������Ⱦ���»���
*/
	void Update();
	//������
	SDL_Window *MainWindow;
	//�������ڰ󶨵���Ⱦ��
	SDL_Surface *MainSurface;
	//��Ⱦ��
	SDL_Renderer *MainRenderer;
	SDL_Event *myevent;
	//������ӳٵ�ʱ�䣬Ϊ���㲻���û�����
	size_t DelayTime;
};



#endif // !VISUALIZER_H
