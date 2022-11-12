#ifndef DB_CONNECT_H
#define DB_CONNECT_H

#include <QObject>
#include <QtSql>

class db_connect : public QObject
{
    Q_OBJECT
public:
    explicit db_connect(QObject *parent = nullptr);

signals:

};

#endif // DB_CONNECT_H
