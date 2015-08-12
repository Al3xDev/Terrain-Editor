/*

Author: Stoica Alexandru ( Al3xDev )
Contact al3xdev@gmail.com
License: GPL v2.0, see LICENSE file

*/

#ifndef WIDGET_H
#define WIDGET_H
#include <iostream>
#include <QWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <cstdlib>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
public slots:
    void Create();
    void Load();
    void Save();
    void Positive_Strength();
    void Strength(double strength);
    void Ray(double ray);
private slots:
    void on_pushButton_clicked();
};

#endif // WIDGET_H
