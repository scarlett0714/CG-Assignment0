#include "openglwindow.h"
#include <QMouseEvent>
#include <QOpenGLFunctions>

OpenGLWindow::OpenGLWindow(QWidget *parent)
    : QOpenGLWidget(parent), timer(new QTimer(this)) {

    // connect(발신자, SIGNAL(이벤트), 수신자, SLOT(처리 함수));
    connect(timer, &QTimer::timeout, this, [this]() {
        spin += 2.0f; // 회전 각도 증가 (누적)
        if (spin > 360.0f) spin -= 360.0f;
        update(); // 화면 갱신
    });

    // 색상 변경 버튼
    colorButton = new QPushButton("Change Color", this); // 생성
    connect(colorButton, &QPushButton::clicked, this, &OpenGLWindow::changeColor); //함수 연결

    // 레이아웃 설정 (UI 파일 없이 버튼 추가)
    layout = new QVBoxLayout();
    layout->addWidget(colorButton); // 버튼 추가
    layout->setAlignment(Qt::AlignTop); // 상단 정렬
    setLayout(layout); // 레이아웃 적용

}

OpenGLWindow::~OpenGLWindow() {
    delete timer;
}

void OpenGLWindow::initializeGL() { //프로그램이 시작될 때 자동으로 실행됨
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0); // 배경색
}

void OpenGLWindow::resizeGL(int w, int h) { //창 크기가 변경될 때마다 자동으로 실행됨 (reshape)
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWindow::paintGL() { // 창이 처음 생성될 때, 창이 다시 그려져야 할 때, 애니메이션이 필요할 때 자동 실행됨, (display)
    glClear(GL_COLOR_BUFFER_BIT);

    // matrix stack (push-pop)
    glPushMatrix();
    glRotatef(spin, 0.0f, 0.0f, 1.0f);
    glColor3f(red, green, blue); //사각형 색상 변경
    glRectf(-25.0f, -25.0f, 25.0f, 25.0f);
    glPopMatrix();

    // pop하면 stack에서 matrix가 사라지기 때문에 다시 회전각도 0부터 시작
    // 하지만, spin변수에 각도가 누적이 되고 있으므로, 0 -> 2 -> 4 -> 6 ... 씩 회전
}

void OpenGLWindow::mousePressEvent(QMouseEvent *event) { //사용자가 마우스를 클릭하면 자동 실행됨 (mouse)
    if (event->button() == Qt::LeftButton) {
        startRotation(); // 좌클릭 시 회전 시작
    } else if (event->button() == Qt::RightButton) {
        stopRotation(); // 우클릭 시 회전 멈춤
    }

    // else : 아무 동작도 하지 않을 때는 코드 생략 가능
}

// 함수 기능 정의
void OpenGLWindow::startRotation() {
    if (!timer->isActive()) {
        timer->start(16); // 60 FPS
    }
}

void OpenGLWindow::stopRotation() {
    if (timer->isActive()) {
        timer->stop();
    }
}

void OpenGLWindow::changeColor() {
    // 색상 순환 (흰색 → 빨강 → 초록 → 파랑 → 반복)
    if (red == 1.0f && green == 1.0f && blue == 1.0f) {
        red = 1.0f; green = 0.0f; blue = 0.0f; // 빨강
    } else if (red == 1.0f && green == 0.0f && blue == 0.0f) {
        red = 0.0f; green = 1.0f; blue = 0.0f; // 초록
    } else if (red == 0.0f && green == 1.0f && blue == 0.0f) {
        red = 0.0f; green = 0.0f; blue = 1.0f; // 파랑
    } else {
        red = 1.0f; green = 1.0f; blue = 1.0f; // 기본 흰색
    }
    update(); // 화면 갱신
}
