#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // -------------------------------------
    // ROS 初始化
    // -------------------------------------
    rclcpp::init(0, nullptr);
    // create node
    this->node_ = rclcpp::Node::make_shared("demo");
    // create topic pub
    this->publisher_ = this->node_->create_publisher<std_msgs::msg::String>("pub_topic", 10);
    // create topic sub
    this->subscriber_ = node_->create_subscription<std_msgs::msg::String>(
        "sub_topic", 10,
        [&](const std_msgs::msg::String::SharedPtr msg)
        {
            // 處理訂閱到的消息
            QString receivedMsg = QString::fromStdString(msg->data);
            std::cout << msg->data << std::endl;
            ui->textBrowser->append(receivedMsg);
        });
    this->initSpin();
    // -------------------------------------
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    // -------------------------------------
    // ROS 釋放
    // -------------------------------------
    this->spin_timer_.stop();
    rclcpp::shutdown();
    // -------------------------------------
}

void MainWindow::initSpin(void)
{
    this->spin_timer_.setInterval(1); // 1 ms
    QObject::connect(&this->spin_timer_, &QTimer::timeout, [&]()
                     { rclcpp::spin_some(node_); });
    this->spin_timer_.start();
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    std::cout << text.toStdString() << std::endl;

    std_msgs::msg::String msg;
    msg.data = text.toStdString();
    publisher_->publish(msg);
}
