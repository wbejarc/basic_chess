#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mChess = new Chess(ui->graphicsView, this);
    setCentralWidget(ui->graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionIniciar_triggered()
{
    mChess->startGame();
}

void MainWindow::on_actionTerminar_triggered()
{
    mChess->stopGame();
    close();
}
