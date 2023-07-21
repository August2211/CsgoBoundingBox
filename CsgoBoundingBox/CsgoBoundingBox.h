#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CsgoBoundingBox.h"

class CsgoBoundingBox : public QMainWindow
{
    Q_OBJECT

public:
    CsgoBoundingBox(QWidget *parent = nullptr);
    ~CsgoBoundingBox();

private:
    Ui::CsgoBoundingBoxClass ui;
};
