# EmployeeManagement
This project depicts simple Employee Management System software, which contains various functions that allow the user/company to keep track of its employees and store the details of its employees in a database. This project has been made using C language, and uses some important concepts, features and algorithms to accomplish the task. This software is entirely text based and could be run on any machine having C compiler (GCC, Turbo-C, Borland, etc.) through a Terminal window (LINUX), or Command Prompt (Windows).
HEADER FILES USED:
stdio.h
stdlib.h
string.h
ctype.h
termios.h

FUNCTIONS USED:

void head_disp( ) – This function displays the masthead of the Employee Management
Software program and is used as a header for displaying the Software name to all subparts of
the program. As indicated by its return type, it returns no value, and accepts no parameter.
void initTermios(int) – This function is used to set the terminal properties to its default
stage, and also it is used to implement getch() and getche() functions which are by default not
present in the standard C library, but are required for usage in some parts of the program.

void resetTermios( ) – This function resets the default state of the terminal which might
have been changed during implementation of getch() and getche() functions. The default
values to be used are stored in a structure variable named old.

char getch_(int) - This function takes an integer argument which is passed to it by, the

getch() and getche() functions, and according to the input passed to it, it instructs the

initTermios(int) function to implement those functions, and whether to echo the output on the
screen or not.

char getch( ) – This function takes a character from the standard input i.e. keyboard and
returns that character to a char type variable, but the value which is typed by the user on the
screen is not displayed. Also, getch() function does not wait for the user to press Enter key
after entering a character. The entered character is automatically used.

char getche( ) – This function takes a character from the standard input i.e. keyboard and
returns that character to a char type variable, and the value which is typed by the user is
displayed on the screen. Like getch() function, getche() function also does not wait for the
user to press Enter key after entering a character. The entered character is automatically used.NOTE- The employee database where information about all the employees will be stored is a
binary file, with name “employeeRecord.txt”. The program has been designed in such a
manner that it uses this file to work with all its functions. The software also analyzes and
checks if the file is present or not, and prompts the user for creating Employee database, if it
does not exists already.

void emp_append( ) – This function is used to add an Employee’s record in the existing
database.

void emp_delete( ) – This function is used for deleting the records of an employee present in
the database of the software.

void emp_modify( ) – This function is used to modify the records of the employees which
are present in the software’s database.

void emp_display( ) – This function takes Employee ID from the user, and displays all
information about that employee, from the database.

void emp_displayAll( ) – This function displays information about all the employees present
in the current software’s database.

void emp_search( ) – This function allows a user to search through the employee records
present in the database. User can search for employee either by Name or by Employee ID. If
found, the function displays the information about that employee to the user.

int main(void) – This function is the driving function of the program. The execution of the
software begins from this function, and it contains all the information about the database, and
it manages the control of execution of the program, by displaying user to choose what
operation which he wants to perform on the given database.

EMPLOYEE INFORMATION:

An employee has usually these details on which this software works on-
Name of Employee, Position of Employee in Company, Qualifications of Employee,
Certifications( if any) of Employees, Employee ID, Programming Languages known.
Personal Information of Employee including his/her Age, Phone number.
These values are stores in a structure personal.
