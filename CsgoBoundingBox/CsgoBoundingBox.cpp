#define _CRT_SECURE_NO_WARNINGS
#include "CsgoBoundingBox.h"
#include "qapplication.h"
#include "qprocess.h"
#include "qwindow.h"
#include "qthread.h"
#include "windows.h"
#include "iostream"

CsgoBoundingBox::CsgoBoundingBox(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

CsgoBoundingBox::~CsgoBoundingBox()
{}
