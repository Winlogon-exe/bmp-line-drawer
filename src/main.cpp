#include "BMPViewer.h"

int main() {
    BMPViewer viewer;
    std::string path;
    std::cout << "Enter input BMP file path: ";
    std::cin >> path;

    viewer.read(path);
    viewer.show();
    return 0;
}
