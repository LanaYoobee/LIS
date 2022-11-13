#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H

#include <QDialog>

namespace Ui {
class BookDetails;
}

class BookDetails : public QDialog
{
    Q_OBJECT

    //QImage img, QString title,
public:
    explicit BookDetails(QImage img, QString title, QWidget *parent = nullptr);
    ~BookDetails();

private slots:
    void on_quitButton_clicked();

private:
    Ui::BookDetails *ui;
};

#endif // BOOKDETAILS_H
