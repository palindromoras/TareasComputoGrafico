#pragma once
#include "BaseApplication.h"

class Application:public BaseApplication
{
public:
	int angle;
	void setup() override;
	void update() override;
	void draw() override;
	Application();
	~Application();


};

