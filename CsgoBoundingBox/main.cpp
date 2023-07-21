#include "CsgoBoundingBox.h"
#include <QtWidgets/QApplication>
#include "windows.h"
#include <QApplication>
#include <QWidget>
#include <QWindow>
#include <QResizeEvent>
#include <Windows.h>
#include <iostream>
#include <string>
#include <QPainter>

class CSOverlay : public QWidget {
public:
    explicit CSOverlay(HWND csgoWindow, QWidget* parent = nullptr)
        : QWidget(parent), csgoWindowHandle(csgoWindow) {
        // Set the overlay window as a transparent, borderless frame
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setAttribute(Qt::WA_NoSystemBackground, true);
        setAttribute(Qt::WA_TransparentForMouseEvents, true);

        // Adjust the size of the overlay window to match CSGO's initial size
        RECT rect;
        GetWindowRect(csgoWindowHandle, &rect);
        setGeometry(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);

        std::cout << "Found CSGO window. Initial size: " << rect.right - rect.left << "x" << rect.bottom - rect.top << std::endl;

        show();
    }

    void resizeEvent(QResizeEvent* event) override {
        // Enforce the maximum size when the overlay window is resized
        QSize newSize = event->size();
        QSize maxSize(2560, 1440); // Set your desired maximum size here
        if (newSize.width() > maxSize.width() || newSize.height() > maxSize.height()) {
            newSize = newSize.boundedTo(maxSize);
            setFixedSize(newSize);
        }

        // Resize the CSGO window to match the overlay window's size
        SetWindowPos(csgoWindowHandle, nullptr, 0, 0, newSize.width(), newSize.height(), SWP_NOMOVE | SWP_NOZORDER);
    }

    void mousePressEvent(QMouseEvent* event) override {
        // Forward mouse press event to CSGO window
        QMouseEvent newEvent(QEvent::MouseButtonPress, event->localPos(), event->windowPos(),
            event->screenPos(), event->button(), event->buttons(), event->modifiers());
        QApplication::sendEvent(QWindow::fromWinId((WId)csgoWindowHandle), &newEvent);
    }

    void mouseReleaseEvent(QMouseEvent* event) override {
        // Forward mouse release event to CSGO window
        QMouseEvent newEvent(QEvent::MouseButtonRelease, event->localPos(), event->windowPos(),
            event->screenPos(), event->button(), event->buttons(), event->modifiers());
        QApplication::sendEvent(QWindow::fromWinId((WId)csgoWindowHandle), &newEvent);
    }

    void mouseMoveEvent(QMouseEvent* event) override {
        // Forward mouse move event to CSGO window
        QMouseEvent newEvent(QEvent::MouseMove, event->localPos(), event->windowPos(),
            event->screenPos(), event->button(), event->buttons(), event->modifiers());
        QApplication::sendEvent(QWindow::fromWinId((WId)csgoWindowHandle), &newEvent);
    }

private:
    HWND csgoWindowHandle;

protected:
    void paintEvent(QPaintEvent* event) override {
        // Call the base class paintEvent function
        QWidget::paintEvent(event);

        // Draw the text in the top-left corner
        QPainter painter(this);
        painter.setPen(QPen(Qt::red, 1));

        // Set the font family and font size here
        QFont font("Arial", 32); 

        // Set the painter's font to the new QFont
        painter.setFont(font);

        painter.drawText(100, 100, "Bounding box active");
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CsgoBoundingBox w;
    w.show();

    HWND csgoWindow = FindWindowA(nullptr, "Counter-Strike: Global Offensive - Direct3D 9");

    if (csgoWindow) {
        CSOverlay overlay(csgoWindow);
        return a.exec();
    }

    else {
        return -1;
    }
}
