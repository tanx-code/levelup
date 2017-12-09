#pragma once

//就是把按键记录到数组里，函数里传进去的参数正好是整数，每个整数对应一个按键，摁下了就置true
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
};

