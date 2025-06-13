void runEditor();

#if defined(_WIN32) && (defined(NDEBUG) && !defined(_DEBUG))
#include <Windows.h>
int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
    runEditor();
}
#else
int main(){
    runEditor();
}
#endif