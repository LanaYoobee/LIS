#ifndef MEMBERMAIN_H
#define MEMBERMAIN_H

#include <QDialog>

namespace Ui {
class memberMain;
}

class memberMain : public QDialog
{
    Q_OBJECT

public:
    explicit memberMain(QString user, QWidget *parent = nullptr);
    ~memberMain();

private:
    Ui::memberMain *ui;
    QString userFirstName;
};

#endif // MEMBERMAIN_H
