#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_showAllContactsButton_clicked();

    void on_addContactButton_clicked();

    void on_addNumberPushButton_clicked();

    void on_saveContactsButton_clicked();

    void on_deleteAllContactsButton_clicked();

    void on_sortButton_clicked();

    void on_searchContactButton_clicked();

    void on_deleteContactButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
