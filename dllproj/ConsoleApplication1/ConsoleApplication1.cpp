#include <windows.h>
#include <iostream>
class Dog {
public:
	Dog();

	~Dog();
	// 成员函数：发出狗叫声
	void Bark();
};

// 为了动态调用函数，先定义函数指针类型
typedef void (*PFN_ShowMessage)();
// 构造函数：接受 this 指针
typedef void (*ConstructorFunc)(void*, int xx);
// 析构函数：接受 this 指针
typedef void (*DestructorFunc)(void*);
// 成员函数：接受 this 指针
typedef void (*BarkFunc)(void*);

class testClass {
public:
	testClass(int n): nn(n) {

	}
	~testClass() {

	}
private:
	int nn;
};
int main()
{
	std::cout << "正在加载 DLL" << std::endl;

	// 加载 DLL
	HMODULE hDLL = LoadLibrary(L"dllproj.dll");
	if (hDLL == NULL) {
		std::cerr << L"加载 DLL 失败！错误代码：" 
			<< GetLastError() << std::endl;
		return -1;
	}

	// 获取 ShowMessage 函数的地址
	PFN_ShowMessage ShowMessage = (PFN_ShowMessage)
		GetProcAddress(hDLL, "ShowMessage");

	if (ShowMessage == NULL) {
		std::cerr << L"获取 ShowMessage 地址失败！错误代码：" 
			<< GetLastError() << std::endl;

		FreeLibrary(hDLL);
		return -1;
	}

	// 调用 ShowMessage 函数
	ShowMessage();

	ConstructorFunc Constructor = (ConstructorFunc)
		GetProcAddress(hDLL, "??0Dog@@QEAA@H@Z");
	DestructorFunc  Destructor = (DestructorFunc)
		GetProcAddress(hDLL, "??1Dog@@QAE@XZ");
	BarkFunc        Bark = (BarkFunc)
		GetProcAddress(hDLL, "?Bark@Dog@@QEAAXXZ");

	// 正确的内存分配，确保对齐
	void* dogMemory = ::operator new(sizeof(Dog));

	// 4. 调用构造函数，初始化对象（此时 this 指针就是 dogMemory）
	Constructor(dogMemory, 10);

	// 5. 使用对象，调用成员函数
	Bark(dogMemory);

	// 6. 调用析构函数，销毁对象
	Destructor(dogMemory);

	// 7. 释放内存
	::operator delete(dogMemory);

	// 8. 卸载 DLL
	FreeLibrary(hDLL);
	return 1;
}