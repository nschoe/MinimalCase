#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customlink.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Create the scene
	QGraphicsScene *scene = new QGraphicsScene;
	scene->setSceneRect(0, 0, 1500, 900);

	// Add some element
	CustomLink *link = new CustomLink(30, 30, 800, 340);
	scene->addItem(link);

	// Create the view
	QGraphicsView *view = new QGraphicsView(scene);
	view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	view->setMouseTracking(true);
	view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	view->setDragMode(QGraphicsView::RubberBandDrag);

	setCentralWidget(view);
	view->show();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) {
		close();
	}
}
