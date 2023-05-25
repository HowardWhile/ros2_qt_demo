#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QTimer>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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
        [this](const std_msgs::msg::String::SharedPtr msg) {
            // 处理订阅到的消息
            QString receivedMsg = QString::fromStdString(msg->data);
            std::cout<<msg->data<<std::endl;

            // 其他处理逻辑
            ui->textBrowser->append(receivedMsg);
        });    
    // -------------------------------------
    // 创建定时器
    static QTimer timer;

    // 设置定时器间隔，单位为毫秒
    int interval = 1; // 1 ms
    timer.setInterval(interval);

    // 连接定时器的timeout信号到槽函数
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        // 在定时器触发时执行的操作
        rclcpp::spin_some(node_);
    });

    // 启动定时器
    timer.start();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    // -------------------------------------
    // ROS 釋放
    // -------------------------------------
    rclcpp::shutdown();
    // -------------------------------------
}


void MainWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    std::cout<<text.toStdString()<<std::endl;

    std_msgs::msg::String msg;
    msg.data = text.toStdString();
    publisher_->publish(msg);
}

