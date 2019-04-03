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
	//������������100ʱ�����ӳ���Ϊ1ms
	if (rectsAmount > 100)
		DelayTime = 1;
	else
		DelayTime = static_cast<size_t>(750/rectsAmount + 1 );
	if (myRects == NULL)
		cout << "���γ�ʼ��ʧ��" << endl;
	else {
		//���־��ο�ȣ�ÿ����������Ԥ��1������Ϊ��϶
		size_t rectwidth = (width - rectsAmount) / rectsAmount;
		for (int i = 0; i < rectsAmount; i++) {
			myRects->rects[i].w = rectwidth ;
			//����ú�ĵ�һ������Ϊ�����Σ�������θ߶Ȳ�����
			myRects->rects[i].h = rectwidth + i*(height - rectwidth)/(rectsAmount-1);
		}
		for (int i = 0; i < rectsAmount; i++) {
			myRects->rects[myRects->position[i]].x = i*rectwidth+i;
			myRects->rects[i].y = height - myRects->rects[i].h;
		}
		
	}
	if (WindowInit(width,height)) {
		Update();
		cout << "���γ�ʼ���ɹ�" << endl;
	}
	else 
		cout << "���ӻ������ʼ��ʧ��" << endl;
}


Visualizer::~Visualizer()
{
	WindowQuit();
	free(myRects);
}

void Visualizer::SwapRect(size_t pos1, size_t pos2)
{
	//��Ҫ�������������θ����ɳ�ɫ
	HighLightRect(pos1, RED);
	HighLightRect(pos2, RED);
	//������Ӧλ�ö�Ӧ���ε�x����
	size_t tempX = myRects->rects[myRects->position[pos1]].x;
	myRects->rects[myRects->position[pos1]].x = myRects->rects[myRects->position[pos2]].x;
	myRects->rects[myRects->position[pos2]].x = tempX;
	//��λ�������н�����Ӧλ�õľ������
	size_t temp = myRects->position[pos1];
	myRects->position[pos1] = myRects->position[pos2];
	myRects->position[pos2] = temp;
	//���¸�������
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
		//������޴���󣬴���������
		MainWindow = SDL_CreateWindow("AlgorithmVisualize", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		if (MainWindow == NULL) {
			cout << "Main Window Create Failed:" << SDL_GetError() << endl;
			success = false;
		}

		else {
			//��ȡ�ͳ�ʼ�����������surface
			MainSurface = SDL_GetWindowSurface(MainWindow);
			if (MainSurface == NULL) {
				cout << "Main Surface Create Failed:" << SDL_GetError() << endl;
				success = false;
			}
			else {
				//�����봰���������Ⱦ��
				MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED);
				if (MainRenderer == NULL) {
					cout << "Main Renderer Create Failed:" << SDL_GetError() << endl;
					success = false;
				}
				else{
					//SDL_FillRect(MainSurface, NULL,0x000000);
					//���������Ϣ
					SDL_UpdateWindowSurface(MainWindow);
				}
			}
		}
	}
	//SDL_AddEventWatch(this->mySDL_EventFilter, this); //����ʹ��������첽��ȡeventʧ���� 12/4/16��25

	return success;	
}

//�ͷŴ��壬�˳�����
void Visualizer::WindowQuit(){
	SDL_DestroyWindow(MainWindow);
	MainWindow = NULL;	
	SDL_DestroyRenderer(MainRenderer);
	MainRenderer = NULL;
	SDL_Quit();
}




void Visualizer::HighLightRect(size_t pos, CommonColor ccolor)
{
	//��Ӧλ�õ���ɫ�����е���ɫ�޸�
	myRects->rectColors[pos] = ccolor;
	Update();
}

void Visualizer::UnHighLightRect(size_t pos)
{
	//��Ӧλ�õ���ɫ�����е���ɫ�޸ĳɰ�ɫ��Ĭ����ɫ
	myRects->rectColors[pos] = WHITE;
	Update();
}

void Visualizer::Update()
{
	//����SDL�¼��������Դ��ڵĲ����ȣ��ƶ��������ͣ
	if (SDL_PollEvent(myevent) != 0) {
		//��ʱֻ��ͨ���ر����������رճ���
		//ʹ�����Ͻǲ��ر�Ŀǰ����ɲ���Ԥ�ϵ�Ӱ��
		//if (myevent->type == SDL_QUIT) {
		//	delete this;
		//	return;
		//}
	}
	
		//�����Ⱦ���������Ļ��Ⱦ�ȴ�������Ⱦ
		SDL_RenderClear(MainRenderer);
		//������Ⱦ������Ⱦ��ɫΪ��ɫ
		SDL_SetRenderDrawColor(MainRenderer, 0x00, 0x00, 0x00, 0xFF);
		//��Ⱦ�������ڵ���ɫΪ��ɫ�������ñ�����ɫΪ��
		SDL_RenderFillRect(MainRenderer, NULL);
		//������Ⱦȫ���ľ���
		for (int i = 0; i < this->myRects->RectAmount; i++) {
			//���ݲ�ͬ���ε���ɫ��Ⱦ����
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
				//Ĭ����ȾΪ��ɫ
				SDL_SetRenderDrawColor(MainRenderer, 0xF8, 0xF8, 0xFF, 0xFF);
				SDL_RenderFillRect(MainRenderer, &myRects->rects[myRects->position[i]]);
				break;
			}

		}
		//����Ⱦ���е�������Ⱦ�ϴ���
		SDL_RenderPresent(MainRenderer);
		//�ӳ�delayTime����
		SDL_Delay(DelayTime);
	
}



vRectangles::vRectangles()
{
	//Ĭ������10������
	vRectangles(10);
}


vRectangles::vRectangles(size_t RectAmount)
{
	this->RectAmount = RectAmount;
	//�����μ�����Ӧλ�õľ�����ż�����Ӧλ�õľ�����ɫ��ż������¸����û�����ľ����������ô�С
	//��С������ľ���������ͬ
	rects.resize(RectAmount);
	position.resize(RectAmount);
	rectColors.resize(RectAmount);
	//��������Ӧλ�õľ�����ż� �� ��Ӧλ�õľ�����ɫ��ż� ������Ĭ��ֵ
	//������ż�Ĭ�ϴ�1��RectAmount
	//������ɫ��ż�Ĭ��ȫΪ��ɫ
	for (int i = 0; i < RectAmount ; i++) {
		position[i] = i;
		rectColors[i] = WHITE;
	}
	//���Ҷ�Ӧλ�þ�����ż���˳��
	//ʵ�־���λ�õ����
	for (int i = 0,r = 0,temp = 0; i < RectAmount ; i++) {
		r = RandomInt(RectAmount-1);
		temp = position[i];
		position[i] = position[r];
		position[r] = temp;
	}
	//����������
	for (int i = 0, r = 0, temp = 0; i < RectAmount; i++) {
		cout << position[i] << " ";
	}
	cout << endl;
}


size_t vRectangles::RandomInt(size_t randomMax)
{
	//��0��randomMax����������
	return (size_t)(rand()%(randomMax+1));
}


