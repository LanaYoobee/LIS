#ifndef DB_CLOSE_H
#define DB_CLOSE_H

#include <QObject>
#include <QtSql>

class db_close : public QObject
{
    Q_OBJECT
public:
    explicit db_close(QObject *parent = nullptr);

signals:

};

#endif // DB_CLOSE_H
