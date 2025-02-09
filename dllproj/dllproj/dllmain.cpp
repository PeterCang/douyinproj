#include "pch.h"

// ------------------------------
// 导出一个 C 风格的函数
#ifdef __cplusplus
extern "C" {
#endif
	// 此函数会弹出一个消息框，表明该函数已被调用
	__declspec(dllexport) void ShowMessage()
	{
		MessageBox(NULL, L"这是一个从 DLL 导出的函数", 
			L"DLL Message", MB_OK);
	}

#ifdef __cplusplus
}
#endif

// ------------------------------
// 导出一个 C++ 类（狗狗类）
class __declspec(dllexport) Dog {
public:
	// 构造函数
	Dog(int xx): x (xx){
	}
	// 析构函数
	~Dog() {
	}
	// 成员函数：发出狗叫声
	void Bark() {
		wchar_t buf[100];
		wsprintf(buf, L"%d", x);

		//MessageBox(NULL, L"汪汪！", L"Dog Bark", MB_OK);
		MessageBox(NULL, buf, L"Dog Bark", MB_OK);
	}
private:
	int x;
};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

