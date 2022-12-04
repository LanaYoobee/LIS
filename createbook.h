#pragma once

#include <QWidget>
#include "login.h"

namespace Ui {
class CreateBook;
}

class CreateBook : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateBook(QWidget *parent = nullptr);
    ~CreateBook();

private slots:
    void on_saveAccountButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::CreateBook *ui;
};
