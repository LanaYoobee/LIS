#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QDialog>

namespace Ui {
class mainscreen;
}

class mainscreen : public QDialog
{
    Q_OBJECT

public:
    explicit mainscreen(QString user, int admin, QWidget *parent = nullptr);
    ~mainscreen();

private slots:
    void on_quitButton_clicked();

private:
    Ui::mainscreen *ui;
};

#endif // MAINSCREEN_H
