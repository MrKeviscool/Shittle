void runEditor();

#ifdef _WIN32
int WinMain(){
    runEditor();
}
#else
int main(){
    runEditor();
}
#endif