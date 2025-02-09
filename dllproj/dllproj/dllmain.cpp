#include "pch.h"

// ------------------------------
// ����һ�� C ���ĺ���
#ifdef __cplusplus
extern "C" {
#endif
	// �˺����ᵯ��һ����Ϣ�򣬱����ú����ѱ�����
	__declspec(dllexport) void ShowMessage()
	{
		MessageBox(NULL, L"����һ���� DLL �����ĺ���", 
			L"DLL Message", MB_OK);
	}

#ifdef __cplusplus
}
#endif

// ------------------------------
// ����һ�� C++ �ࣨ�����ࣩ
class __declspec(dllexport) Dog {
public:
	// ���캯��
	Dog(int xx): x (xx){
	}
	// ��������
	~Dog() {
	}
	// ��Ա����������������
	void Bark() {
		wchar_t buf[100];
		wsprintf(buf, L"%d", x);

		//MessageBox(NULL, L"������", L"Dog Bark", MB_OK);
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

