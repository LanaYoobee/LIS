#include "login.h"
#include "ui_login.h"
#include "qtbcrypt.h"
#include "mainscreen.h"


login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)

{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

//user authentication into the application
void login::on_passwordEntry_returnPressed()
{
    db_connect();

    //set up variables needed for authentication
    QSqlQuery qry;
    QString enteredUser, user, enteredPassword, storedPassword, storedSalt;
    int admin;

    //collect user input from the mainwindow
    enteredUser = ui->usernameEntry->text();
    enteredPassword = ui->passwordEntry->text();

    ui->centralwidget->releaseKeyboard();
    //prepare the query. bindValue is used to guard against sql injections

    qry.prepare("select username, password, admin, first_name from users where username= :username");
    qry.bindValue(":username", enteredUser);
    qry.exec();


    if(!qry.first()) //check if there were any results for this username
    {
        QMessageBox::critical(this, "LIS", "Incorrect username or password");
    }
    else //if there was such a username, we need to check if the password is correct
    {
        storedPassword = qry.value(1).toString(); //the developer does not know what the password is as it's stored hasshed and salted
        storedSalt = storedPassword.first(29); //the first 29 digits of the hashed password is the salt

        QString hashedPassword = QtBCrypt::hashPassword(enteredPassword, storedSalt); //run the same hashing algorithm but using this username's salt so we can compare the hashes

        //if the hash of the entered password with our stored salt matches our stored hashed password, then it must be the same, so we can let the user in.
        if (hashedPassword == storedPassword)
        {
            admin = qry.value(2).toInt(); //once we've let the user in, we need to know if they're an admin (value stored in the db)
            user = qry.value(3).toString(); //we also need to know their name, so we can greet them

            this->hide(); //we can close the login window once we've let the user in

            mainscreen *ms = new mainscreen(user, admin, this); //pass their first name and the admin status to the main screen window
            ms->show(); //show the main screen window



        }
        else QMessageBox::critical(this, "LIS", "Incorrect username or password");
    }

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);

}



//function for creating new users, to be moved to an admin screen later
void login::on_pushButton_clicked()

{

    //    QSqlDatabase db;
    //    db = QSqlDatabase::addDatabase("QSQLITE");
    //    db.setDatabaseName("../LIS/db.sqlite");

    //    if(!db.open())
    //    {
    //        qDebug()<<"problem opening database";
    //    }

    //    QSqlQuery qry;
    //    QString salt = QtBCrypt::generateSalt();
    //    QString hashedPassword = QtBCrypt::hashPassword("sillyPassword", salt);

    //    qry.prepare("INSERT INTO users(ID, username, password, first_name, surname, phone, admin) VALUES(1,'newUser',:password,:salt,'Admin','secondAdmin',1232132,'Y');");
    //    qry.bindValue(":password", hashedPassword);
    //    qry.bindValue(":salt", salt);
    //    qry.exec();

}


void login::on_login_destroyed()
{
    QApplication::closeAllWindows();
}

