// ifndef - define - endif
#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit OpenGLWindow(QWidget *parent = nullptr);
    ~OpenGLWindow();

protected:
    void initializeGL() override; // OpenGL 초기화
    void resizeGL(int w, int h) override; // 창 크기 변경
    void paintGL() override; // OpenGL 렌더링
    void mousePressEvent(QMouseEvent *event) override; // 마우스 이벤트

private slots: // connect로 연결 가능
    void startRotation(); // 회전 시작
    void stopRotation();  // 회전 멈춤
    void changeColor();   // 색상 변경

private:
    float spin = 0.0f; // 회전 각도
    QTimer *timer; // 애니메이션 타이머
    QPushButton *colorButton;  // 색상 변경 버튼 추가
    QVBoxLayout *layout;       // 버튼을 배치할 레이아웃
    float red = 1.0f, green = 1.0f, blue = 1.0f; // 사각형 색상
};

#endif // OPENGLWINDOW_H
