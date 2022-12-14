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
    QString enteredUser, userFirstName, enteredPassword, storedPassword, storedSalt;
    int admin;

    //collect user input from the mainwindow
    enteredUser = ui->usernameEntry->text();
    enteredPassword = ui->passwordEntry->text();



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
            admin = qry.value(2).toInt();

            userFirstName = qry.value(3).toString(); //we also need to know their name, so we can greet them

            setUsername(enteredUser);
            setAdmin(admin);

            this->close(); //we can close the login window once we've let the user in

            mainscreen *ms = new mainscreen(userFirstName, admin, enteredUser, this); //pass their first name and the admin status to the main screen window
            ms->show(); //show the main screen window
        }
        else QMessageBox::critical(this, "LIS", "Incorrect username or password");
    }

}

void login::setUsername(QString username)
{
    this->loggedInUser = username;
}

QString login::getUsername()
{

    return this->loggedInUser;
}

void login::setAdmin(int admin)
{
    this->admin = admin;
}

int login::getAdmin()
{

    return this->admin;
}

