#ifndef LIBRARYMAIN_H
#define LIBRARYMAIN_H

#include <QDialog>

namespace Ui {
class librarymain;
}

class librarymain : public QDialog
{
    Q_OBJECT

public:
    explicit librarymain(QWidget *parent = nullptr);
    ~librarymain();

private slots:
    void on_returnButton_clicked();

private:
    Ui::librarymain *ui;
};

#endif // LIBRARYMAIN_H
