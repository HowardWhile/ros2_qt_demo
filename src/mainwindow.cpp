#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // -------------------------------------
    // ROS node 初始化
    // -------------------------------------
    rclcpp::init(0, nullptr);
    node_ = rclcpp::Node::make_shared("demo");
    // -------------------------------------

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    // -------------------------------------
    // ROS node 釋放
    // -------------------------------------
    rclcpp::shutdown();
    // -------------------------------------
}


void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    std::cout<<text.toStdString()<<std::endl;
}

