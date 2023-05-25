#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

private:
    // -------------------------------------
    // ros
    // -------------------------------------
    // node
    rclcpp::Node::SharedPtr node_;
    // pub
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;   
    // sub 
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
    // -------------------------------------

};
#endif // MAINWINDOW_H
