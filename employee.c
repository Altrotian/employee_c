#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*<< Define the Employee structure >>*/

struct Employee
{
    int Employee_ID;
    char Employee_Name[50];
    int Salary;
    char Department[50];
};
/*<< Function to add a Employee >>*/
void addEmployee()
{
    struct Employee newEmployee;
    printf("Enter Employee ID: ");
    scanf("%d", &newEmployee.Employee_ID);

    printf("Enter Employee Name: ");
    scanf("%s", newEmployee.Employee_Name);

    printf("Enter Employee Salary: ");
    scanf("%d", &newEmployee.Salary);

    printf("Enter Department Name: ");
    scanf("%s", newEmployee.Department);

/*<< Open "Employee.txt" file in append mode >>*/

    FILE *file = fopen("Employee.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

/*<< Write employee details to the file >>*/

    fprintf(file, "%d %s %d %s\n", newEmployee.Employee_ID,
        newEmployee.Employee_Name, newEmployee.Salary,
        newEmployee.Department);

    fclose(file);
}

/*<< Function to list all employees >>*/

void listEmployee()
{
    FILE *file = fopen("Employee.txt", "r");
    if (file == NULL)
    {
        printf("No Employee available.\n");
        return;
    }

    struct Employee Employee;
    while (fscanf(file, "%d %s %d %s", &Employee.Employee_ID,
        Employee.Employee_Name, &Employee.Salary, Employee.Department) != EOF)
    {
        //Print Employee details.

    printf("ID: %d, Name: %s,Salary: %d, Dept: %s\n",
        Employee.Employee_ID, Employee.Employee_Name, Employee.Salary,
        Employee.Department);
    }

    fclose(file);
}

/*<< Function to delete an Employee based on ID >>*/

void deleteEmployee(int id)
{
    FILE *file = fopen("Employee.txt", "r");
    if (file == NULL)
    {
        printf("No Employee available.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    struct Employee Employee;
    while (fscanf(file, "%d %s %d %s", &Employee.Employee_ID,
    Employee.Employee_Name, &Employee.Salary,Employee.Department) != EOF)
    {
        if (Employee.Employee_ID != id)
        {   
            //Write employee details(except the one to be deleted) to temp file.

            fprintf(tempFile, "%d %s %d %s\n", Employee.Employee_ID,
                Employee.Employee_Name, Employee.Salary,Employee.Department);
        }
    }

    fclose(file);
    fclose(tempFile);

/*<< Replace original file with temp file >>*/

    remove("Employee.txt");
    rename("temp.txt", "Employee.txt");
}

/*<< Function to update employee details based on ID >>*/

void updateEmployee(int id)
{
    FILE *file = fopen("Employee.txt", "r");
    if (file == NULL)
    {
        printf("No Employee available.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    struct Employee employee;
    while (fscanf(file, "%d %s %d %s", &employee.Employee_ID,
        employee.Employee_Name, &employee.Salary, employee.Department) != EOF)
    {
        if (employee.Employee_ID == id)
        {
            // Prompt user for updated details.

            printf("Enter new Employee Name: ");
            scanf("%s", employee.Employee_Name);

            printf("Enter new Salary Of Employee: ");
            scanf("%d", &employee.Salary);

            printf("Enter new Department of Employee: ");
            scanf("%s", employee.Department);
        }
        // Write employee details to temp file.

        fprintf(tempFile, "%d %s %d %s\n", employee.Employee_ID,
            employee.Employee_Name, employee.Salary,employee.Department);
    }

    fclose(file);
    fclose(tempFile);

    //Replace original file with temp file.

    remove("Employee.txt");
    rename("temp.txt", "Employee.txt");
}

int main()
{
    int choice, id;

    while (1)
    {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. List Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Update Employee Details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addEmployee();
            break;
        case 2:
            listEmployee();
            break;
        case 3:
            printf("Enter Employee ID to delete: ");
            scanf("%d", &id);
            deleteEmployee(id);
            break;
        case 4:
            printf("Enter Employee ID to update: ");
            scanf("%d", &id);
            updateEmployee(id);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}