# Library Information System (LIS)

Desktop application for a Library Management System

## Tools

* All code was written in Qt Creator.
* All data is stored in a SQLite database.
* Password protection is from https://github.com/andreybutov/qt-bcrypt

## Usage

Once logged in, **members** can: 
* Browse Catalogue 
   * Select a book to get its details.  
   * Reserve the book if it is already borrowed. 
   * Borrow the book. 
   * Return the book if it is borrowed by the logged in user. 
* Search for a Book 
   * Select a book to get its details.  
   * Reserve the book if it is already borrowed. 
   * Borrow the book. 
   * Return the book if it is borrowed by the logged in user.  
* View their account
   * View details of the account. 
   * Update details and click the save icon. 
   * View the list of the books they have borrowed and perform the same functions as above (reserve, borrow, return). 

Once logged in, **administrators** can do the functions same as users and: 
* Maintain users 
  * Add new user 
  * Delete an existing user 
  * View books borrowed by another user and return them on their behalf 
* Maintain books 
  * Add new books 
  * Modify existing books 
  * Delete books (cannot delete borrowed books, must return them first)

## Login 
* admin account: user admin and password admin123
* member account: user Sunshine1 and password Sunshine1
