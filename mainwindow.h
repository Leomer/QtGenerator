#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QListWidgetItem"
#include <string>
#include <memory>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void start();
    void actionWidgetGame(QListWidgetItem *item, std::shared_ptr<std::map<std::string, std::string>>, std::shared_ptr<std::vector<std::string>>, QListWidget*);
    void insert(std::string, std::shared_ptr<std::vector<std::string>>, QListWidget*);
    void clearWidgets();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
