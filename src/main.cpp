#include "BMPViewer.h"

std::string getInputBMPFile(){
    std::string path;
    std::cout << "Enter input BMP file path: ";
    std::cin >> path;
    return path;
}

void pause(){
    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    BMP::BMPViewer viewer;
    std::string path = getInputBMPFile();
    viewer.read(path);
    viewer.show();
    pause();

    return 0;
}
