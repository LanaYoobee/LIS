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

    //set up variables needed for authentication
    QSqlQuery qry;
    QString enteredUser, user, enteredPassword, storedPassword, storedSalt;
    int admin, user_id;

    //collect user input from the mainwindow
    enteredUser = ui->usernameEntry->text();
    enteredPassword = ui->passwordEntry->text();

    //prepare the query. bindValue is used to guard against sql injections

    qry.prepare("select username, password, admin, first_name, id from users where username= :username");
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
            user_id = qry.value(4).toInt(); //we need the user_id for other functions
            admin = qry.value(2).toInt(); //once we've let the user in, we need to know if they're an admin (value stored in the db)
            user = qry.value(3).toString(); //we also need to know their name, so we can greet them

            this->user_id = user_id;
            this->close(); //we can close the login window once we've let the user in

            mainscreen *ms = new mainscreen(user, admin, user_id, this); //pass their first name and the admin status to the main screen window
            ms->show(); //show the main screen window
        }
        else QMessageBox::critical(this, "LIS", "Incorrect username or password");
    }

}


