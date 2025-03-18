#include "BMPViewer.h"

std::string getInputBMPFile(){
    std::string path;
    std::cout << "Enter input BMP file path: ";
    std::cin >> path;
    return path;
}

int main() {
    BMPViewer viewer;
    std::string path = getInputBMPFile();
    viewer.read(path);
    viewer.show();
    return 0;
}
