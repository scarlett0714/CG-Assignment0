#include "openglwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    OpenGLWindow window;
    window.resize(250, 250);  // 창 크기 설정
    window.show();
    return app.exec();
}
