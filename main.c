#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EMPLOYEE_FILE "employees.csv"
#define ATTENDANCE_FILE "attendance.csv"
#define LEAVE_FILE "leaves.csv"
#define SALARY_FILE "salary.csv"

typedef struct {
  int id;
  char name[50];
  int age;
  char department[30];
  float salary;
  char role[10];
  char username[30];
  char password[30];
} Employee;

typedef struct {
  int employee_id;
  char date[15];
  char status[10];
} Attendance;

typedef struct {
  int id;
  int employee_id;
  char start_date[15];
  char end_date[15];
  char status[10]; 
} LeaveRequest;


void login();
void adminMenu();
void employeeMenu();
void addEmployee();
void viewEmployees();
void modifyEmployee();
void deleteEmployee();
void markAttendance();
void viewAttendance();
void applyLeave();
void approveLeave();
void calculateSalary();
void viewSalaryBreakdown();
int generateEmployeeID();
int generateLeaveID();
void removeEmployeeRecords(int empID);
void viewLeaveHistory();
int isUsernameUnique(const char *username, int excludeID);

char loggedInUser[30];
char userRole[10];

int main() {
  login(); 
  return 0;
}

void login() {
  char username[30], password[30];
  int found;
  FILE *file;

  while (1) { 
    found = 0;
    file = fopen(EMPLOYEE_FILE, "r");

    if (file == NULL) {
      printf("No employees found! Please add an admin first.\n");
      return;
    }

    printf("\n===== Employee Management System Login =====\n");
    printf("Enter Username(Enter exit to exit the code): ");
    if (scanf("%s", username) != 1)
      return;

    if (strcmp(username, "exit") == 0) {
      exit(0);
    }

    printf("Enter Password: ");
    if (scanf("%s", password) != 1)
      return;

    Employee emp;
    while (fscanf(file, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                  emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                  emp.username, emp.password) != EOF) {
      if (strcmp(emp.username, username) == 0 &&
          strcmp(emp.password, password) == 0) {
        strcpy(loggedInUser, emp.username);
        strcpy(userRole, emp.role);
        found = 1;
        break;
      }
    }
    fclose(file);

    if (found) {
      printf("Login successful! Welcome, %s (%s)\n", loggedInUser, userRole);
      break; 
    } else {
      printf("Invalid username or password! Please try again.\n");
    }
  }

  if (strcmp(userRole, "Admin") == 0) {
    adminMenu();
  } else {
    employeeMenu();
  }
}

void adminMenu() {
  int choice;
  do {
    printf("\n===== Admin Menu =====\n");
    printf("1. Add Employee\n");
    printf("2. View Employees\n");
    printf("3. Modify Employee\n");
    printf("4. Delete Employee\n");
    printf("5. Approve Leave Requests\n");
    printf("6. Calculate Salary\n");
    printf("7. View Salary Breakdown\n");
    printf("8. Logout\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input! Try again.\n");
      while (getchar() != '\n')
        ; // Clear input buffer
      continue;
    }

    switch (choice) {
    case 1:
      addEmployee();
      break;
    case 2:
      viewEmployees();
      break;
    case 3:
      modifyEmployee();
      break;
    case 4:
      deleteEmployee();
      break;
    case 5:
      approveLeave();
      break;
    case 6:
      calculateSalary();
      break;
    case 7:
      viewSalaryBreakdown();
      break;
    case 8:
      printf("Logging out...\n");
      login();
      return; 
    default:
      printf("Invalid choice! Try again.\n");
    }
  } while (1);
}

void employeeMenu() {
  int choice;
  do {
    printf("\n===== Employee Menu =====\n");
    printf("1. Mark Attendance\n");
    printf("2. View Attendance\n");
    printf("3. Apply for Leave\n");
    printf("4. View Leave History\n");
    printf("5. View Salary Breakdown\n");
    printf("6. Logout\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input! Try again.\n");
      while (getchar() != '\n')
        ; 
      continue;
    }

    switch (choice) {
    case 1:
      markAttendance();
      break;
    case 2:
      viewAttendance();
      break;
    case 3:
      applyLeave();
      break;
    case 4:
      viewLeaveHistory();
      break;
    case 5:
      viewSalaryBreakdown();
      break;
    case 6:
      printf("Logging out...\n");
      login();
      return; // Exit the menu
    default:
      printf("Invalid choice! Try again.\n");
    }
  } while (1);
}

int generateEmployeeID() {
  FILE *file = fopen(EMPLOYEE_FILE, "r");
  if (file == NULL)
    return 1; // If file doesn't exist, start from 1

  int id, maxID = 0;
  char buffer[200];

  while (fgets(buffer, sizeof(buffer), file)) {
    sscanf(buffer, "%d,", &id);
    if (id > maxID)
      maxID = id;
  }

  fclose(file);
  return maxID + 1; // Return next available ID
}

void addEmployee() {
  FILE *file = fopen(EMPLOYEE_FILE, "a");
  if (file == NULL) {
    printf("Error opening file!\n");
    return;
  }

  Employee emp;
  emp.id = generateEmployeeID(); // Auto-generate Employee ID
  printf("\nGenerated Employee ID: %d\n", emp.id);

  getchar(); // Clear newline character from buffer
  printf("Enter Name: ");
  if (fgets(emp.name, sizeof(emp.name), stdin) == NULL) {
    printf("Error reading name!\n");
    return;
  }
  emp.name[strcspn(emp.name, "\n")] = 0; // Remove newline

  printf("Enter Age: ");
  if (scanf("%d", &emp.age) != 1)
    return;

  printf("Enter Department: ");
  if (scanf("%s", emp.department) != 1)
    return;

  printf("Enter Salary: ");
  if (scanf("%f", &emp.salary) != 1)
    return;

  printf("Enter Role (Admin/Employee): ");
  if (scanf("%s", emp.role) != 1)
    return;

  printf("Enter Username: ");
  if (scanf("%s", emp.username) != 1)
    return;

  printf("Enter Password: ");
  if (scanf("%s", emp.password) != 1)
    return;

  fprintf(file, "%d,%s,%d,%s,%.2f,%s,%s,%s\n", emp.id, emp.name, emp.age,
          emp.department, emp.salary, emp.role, emp.username, emp.password);

  fclose(file);
  printf("Employee added successfully!\n");
}

void viewEmployees() {
  FILE *file = fopen(EMPLOYEE_FILE, "r");
  if (file == NULL) {
    printf("No employees found!\n");
    return;
  }

  Employee emp;
  printf("\n%-5s %-20s %-5s %-15s %-10s %-10s\n", "ID", "Name", "Age",
         "Department", "Salary", "Role");
  printf("---------------------------------------------------------------------"
         "--\n");

  while (fscanf(file, "%d,%49[^,],%d,%29[^,],%f,%9[^,],%29[^,],%29[^\n]\n",
                &emp.id, emp.name, &emp.age, emp.department, &emp.salary,
                emp.role, emp.username, emp.password) == 8) {
    printf("%-5d %-20s %-5d %-15s %-10.2f %-10s\n", emp.id, emp.name, emp.age,
           emp.department, emp.salary, emp.role);
  }

  fclose(file);
}

int isUsernameUnique(const char *username, int excludeID) {
  FILE *file = fopen(EMPLOYEE_FILE, "r");
  if (file == NULL)
    return 1; // If file doesn't exist, no duplicate exists

  Employee emp;
  while (fscanf(file, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                emp.username, emp.password) != EOF) {
    if (strcmp(emp.username, username) == 0 && emp.id != excludeID) {
      fclose(file);
      return 0; // Username is already taken
    }
  }
  fclose(file);
  return 1; // Username is unique
}

void modifyEmployee() {
  FILE *file = fopen(EMPLOYEE_FILE, "r");
  if (file == NULL) {
    printf("No employees found!\n");
    return;
  }

  int empID, found = 0;
  Employee emp;
  FILE *tempFile = fopen("temp.csv", "w");
  if (tempFile == NULL) {
    printf("Error opening temporary file!\n");
    fclose(file);
    return;
  }

  // Check if it's Admin or Employee modifying their own profile
  if (strcmp(userRole, "Admin") == 0) {
    printf("\nEnter Employee ID to modify: ");
    if (scanf("%d", &empID) != 1) {
      printf("Invalid input! Try again.\n");
      fclose(file);
      fclose(tempFile);
      return;
    }
  } else {
    empID = -1; // Employees can only modify their own profile
  }

  while (fscanf(file, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                emp.username, emp.password) != EOF) {

    if ((strcmp(userRole, "Admin") == 0 && emp.id == empID) ||
        (strcmp(userRole, "Employee") == 0 &&
         strcmp(emp.username, loggedInUser) == 0)) {
      found = 1;

      // Display current details
      printf("\nCurrent Details:\n");
      printf("ID: %d\nName: %s\nAge: %d\nDepartment: %s\nSalary: %.2f\nRole: "
             "%s\nUsername: %s\n",
             emp.id, emp.name, emp.age, emp.department, emp.salary, emp.role,
             emp.username);

      // Get new details
      getchar(); // Clear input buffer
      printf("\nEnter New Name: ");
      fgets(emp.name, sizeof(emp.name), stdin);
      emp.name[strcspn(emp.name, "\n")] = 0;

      printf("Enter New Age: ");
      if (scanf("%d", &emp.age) != 1)
        return;

      printf("Enter New Department: ");
      if (scanf("%s", emp.department) != 1)
        return;

      printf("Enter New Salary (Admin Only): ");
      if (strcmp(userRole, "Admin") == 0 && scanf("%f", &emp.salary) != 1)
        return;

      if (strcmp(userRole, "Admin") == 0) {
        printf("Enter New Role (Admin/Employee): ");
        if (scanf("%s", emp.role) != 1)
          return;
      }

      do {
        printf("Enter New Username: ");
        if (scanf("%s", emp.username) != 1)
          return;

        if (!isUsernameUnique(emp.username, emp.id)) {
          printf("Error: Username already exists! Try again.\n");
        }
      } while (!isUsernameUnique(emp.username, emp.id));

      printf("Enter New Password: ");
      if (scanf("%s", emp.password) != 1)
        return;

      printf("\nEmployee details updated successfully!\n");
    }

    fprintf(tempFile, "%d,%s,%d,%s,%.2f,%s,%s,%s\n", emp.id, emp.name, emp.age,
            emp.department, emp.salary, emp.role, emp.username, emp.password);
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove(EMPLOYEE_FILE);
    rename("temp.csv", EMPLOYEE_FILE);
  } else {
    printf("Employee ID not found!\n");
    remove("temp.csv");
  }
}

void deleteEmployee() {
  FILE *file = fopen(EMPLOYEE_FILE, "r");
  if (file == NULL) {
    printf("No employees found!\n");
    return;
  }

  int empID, found = 0;
  char confirmation;
  Employee emp;
  FILE *tempFile = fopen("temp.csv", "w");

  if (tempFile == NULL) {
    printf("Error opening temporary file!\n");
    fclose(file);
    return;
  }

  printf("\nEnter Employee ID to delete: ");
  if (scanf("%d", &empID) != 1) {
    printf("Invalid input! Try again.\n");
    fclose(file);
    fclose(tempFile);
    return;
  }

  while (fscanf(file, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                emp.username, emp.password) != EOF) {

    if (emp.id == empID) {
      found = 1;

      // Prevent admin from deleting themselves
      if (strcmp(emp.username, loggedInUser) == 0) {
        printf("Error: You cannot delete yourself!\n");
        fprintf(tempFile, "%d,%s,%d,%s,%.2f,%s,%s,%s\n", emp.id, emp.name,
                emp.age, emp.department, emp.salary, emp.role, emp.username,
                emp.password);
        continue;
      }

      // Confirmation prompt
      printf("Are you sure you want to delete Employee %s (ID: %d)? (y/n): ",
             emp.name, emp.id);
      getchar(); // Clear input buffer
      scanf("%c", &confirmation);
      if (confirmation != 'y' && confirmation != 'Y') {
        fprintf(tempFile, "%d,%s,%d,%s,%.2f,%s,%s,%s\n", emp.id, emp.name,
                emp.age, emp.department, emp.salary, emp.role, emp.username,
                emp.password);
        printf("Deletion cancelled.\n");
        continue;
      }

      printf("\nEmployee %s (ID: %d) deleted successfully!\n", emp.name,
             emp.id);
      removeEmployeeRecords(empID); // Remove attendance and leave records
    } else {
      fprintf(tempFile, "%d,%s,%d,%s,%.2f,%s,%s,%s\n", emp.id, emp.name,
              emp.age, emp.department, emp.salary, emp.role, emp.username,
              emp.password);
    }
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove(EMPLOYEE_FILE);
    rename("temp.csv", EMPLOYEE_FILE);
  } else {
    printf("Employee ID not found!\n");
    remove("temp.csv");
  }
}

void removeEmployeeRecords(int empID) {
  FILE *attendanceFile = fopen(ATTENDANCE_FILE, "r");
  FILE *leaveFile = fopen(LEAVE_FILE, "r");

  if (attendanceFile != NULL) {
    FILE *tempAttendance = fopen("temp_attendance.csv", "w");
    Attendance att;

    while (fscanf(attendanceFile, "%d,%[^,],%s\n", &att.employee_id, att.date,
                  att.status) != EOF) {
      if (att.employee_id != empID) {
        fprintf(tempAttendance, "%d,%s,%s\n", att.employee_id, att.date,
                att.status);
      }
    }
    fclose(attendanceFile);
    fclose(tempAttendance);
    remove(ATTENDANCE_FILE);
    rename("temp_attendance.csv", ATTENDANCE_FILE);
  }

  if (leaveFile != NULL) {
    FILE *tempLeave = fopen("temp_leaves.csv", "w");
    LeaveRequest leave;

    while (fscanf(leaveFile, "%d,%d,%[^,],%[^,],%s\n", &leave.id,
                  &leave.employee_id, leave.start_date, leave.end_date,
                  leave.status) != EOF) {
      if (leave.employee_id != empID) {
        fprintf(tempLeave, "%d,%d,%s,%s,%s\n", leave.id, leave.employee_id,
                leave.start_date, leave.end_date, leave.status);
      }
    }
    fclose(leaveFile);
    fclose(tempLeave);
    remove(LEAVE_FILE);
    rename("temp_leaves.csv", LEAVE_FILE);
  }

  printf("All records related to Employee ID %d have been removed.\n", empID);
}

void viewAttendance() {
  FILE *file = fopen(ATTENDANCE_FILE, "r");
  if (file == NULL) {
    printf("No attendance records found!\n");
    return;
  }

  int empID, found = 0;
  Attendance att;
  Employee emp;

  if (strcmp(userRole, "Admin") == 0) {
    // Admin can view attendance for any employee
    printf("\nEnter Employee ID to view attendance: ");
    if (scanf("%d", &empID) != 1) {
      printf("Invalid input!\n");
      fclose(file);
      return;
    }
  } else {
    // Employees can only view their own attendance
    FILE *empFile = fopen(EMPLOYEE_FILE, "r");
    if (empFile == NULL) {
      printf("No employees found!\n");
      fclose(file);
      return;
    }

    while (fscanf(empFile, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                  emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                  emp.username, emp.password) != EOF) {
      if (strcmp(emp.username, loggedInUser) == 0) {
        empID = emp.id;
        found = 1;
        break;
      }
    }
    fclose(empFile);

    if (!found) {
      printf("Error: Employee record not found!\n");
      fclose(file);
      return;
    }
  }

  // Display attendance records
  printf("\n===== Attendance Records for Employee ID %d =====\n", empID);
  printf("Date\t\tStatus\n");
  printf("------------------------\n");

  found = 0;
  while (fscanf(file, "%d,%[^,],%s\n", &att.employee_id, att.date,
                att.status) != EOF) {
    if (att.employee_id == empID) {
      printf("%s\t%s\n", att.date, att.status);
      found = 1;
    }
  }

  if (!found) {
    printf("No attendance records found for Employee ID %d.\n", empID);
  }

  fclose(file);
}

void applyLeave() {
  FILE *file = fopen(LEAVE_FILE, "a");
  if (file == NULL) {
    printf("Error opening leave file!\n");
    return;
  }

  int empID, found = 0;
  char start_date[15], end_date[15];
  Employee emp;

  FILE *empFile = fopen(EMPLOYEE_FILE, "r");
  if (empFile == NULL) {
    printf("No employees found!\n");
    fclose(file);
    return;
  }

  // Find employee ID based on logged-in username
  while (fscanf(empFile, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                emp.username, emp.password) != EOF) {
    if (strcmp(emp.username, loggedInUser) == 0) {
      empID = emp.id;
      found = 1;
      break;
    }
  }
  fclose(empFile);

  if (!found) {
    printf("Error: Employee record not found!\n");
    fclose(file);
    return;
  }

  // Get leave details
  printf("\nEnter Start Date (YYYY-MM-DD): ");
  if (scanf("%s", start_date) != 1)
    return;

  printf("Enter End Date (YYYY-MM-DD): ");
  if (scanf("%s", end_date) != 1)
    return;

  fprintf(file, "%d,%d,%s,%s,Pending\n", generateLeaveID(), empID, start_date,
          end_date);
  fclose(file);

  printf("Leave request submitted successfully from %s to %s. Awaiting "
         "approval.\n",
         start_date, end_date);
}

// Function to generate a unique Leave ID
int generateLeaveID() {
  FILE *file = fopen(LEAVE_FILE, "r");
  if (file == NULL)
    return 1; // If file doesn't exist, start from 1

  int id, maxID = 0;
  char buffer[200];

  while (fgets(buffer, sizeof(buffer), file)) {
    sscanf(buffer, "%d,", &id);
    if (id > maxID)
      maxID = id;
  }

  fclose(file);
  return maxID + 1; // Return next available Leave ID
}

void approveLeave() {
  FILE *file = fopen(LEAVE_FILE, "r");
  if (file == NULL) {
    printf("No leave requests found!\n");
    return;
  }

  int leaveID, found = 0;
  char decision;
  LeaveRequest leave;
  FILE *tempFile = fopen("temp_leaves.csv", "w");

  if (tempFile == NULL) {
    printf("Error opening temporary file!\n");
    fclose(file);
    return;
  }

  printf("\nEnter Leave ID to approve/reject: ");
  if (scanf("%d", &leaveID) != 1) {
    printf("Invalid input!\n");
    fclose(file);
    fclose(tempFile);
    return;
  }

  while (fscanf(file, "%d,%d,%[^,],%[^,],%s\n", &leave.id, &leave.employee_id,
                leave.start_date, leave.end_date, leave.status) != EOF) {

    if (leave.id == leaveID) {
      found = 1;
      printf("\nLeave Request:\nID: %d | Employee ID: %d | Start: %s | End: %s "
             "| Status: %s\n",
             leave.id, leave.employee_id, leave.start_date, leave.end_date,
             leave.status);

      printf("Approve (A) or Reject (R)? ");
      getchar(); // Clear input buffer
      scanf("%c", &decision);

      if (decision == 'A' || decision == 'a') {
        strcpy(leave.status, "Approved");
        printf("Leave approved!\n");
      } else if (decision == 'R' || decision == 'r') {
        strcpy(leave.status, "Rejected");
        printf("Leave rejected!\n");
      } else {
        printf("Invalid choice! Keeping status as Pending.\n");
      }
    }

    fprintf(tempFile, "%d,%d,%s,%s,%s\n", leave.id, leave.employee_id,
            leave.start_date, leave.end_date, leave.status);
  }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove(LEAVE_FILE);
    rename("temp_leaves.csv", LEAVE_FILE);
  } else {
    printf("Leave ID not found!\n");
    remove("temp_leaves.csv");
  }
}

void viewLeaveHistory() {
  FILE *file = fopen(LEAVE_FILE, "r");
  if (file == NULL) {
    printf("No leave records found!\n");
    return;
  }

  int empID, found = 0;
  LeaveRequest leave;
  Employee emp;

  // Find employee ID based on logged-in username
  FILE *empFile = fopen(EMPLOYEE_FILE, "r");
  if (empFile == NULL) {
    printf("No employees found!\n");
    fclose(file);
    return;
  }

  while (fscanf(empFile, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                emp.username, emp.password) != EOF) {
    if (strcmp(emp.username, loggedInUser) == 0) {
      empID = emp.id;
      found = 1;
      break;
    }
  }
  fclose(empFile);

  if (!found) {
    printf("Error: Employee record not found!\n");
    fclose(file);
    return;
  }

  // Display leave records
  printf("\n===== Leave History for Employee ID %d =====\n", empID);
  printf("Leave ID\tStart Date\tEnd Date\tStatus\n");
  printf("-------------------------------------------------\n");

  found = 0;
  while (fscanf(file, "%d,%d,%[^,],%[^,],%s\n", &leave.id, &leave.employee_id,
                leave.start_date, leave.end_date, leave.status) != EOF) {
    if (leave.employee_id == empID) {
      printf("%d\t\t%s\t%s\t%s\n", leave.id, leave.start_date, leave.end_date,
             leave.status);
      found = 1;
    }
  }

  if (!found) {
    printf("No leave records found for Employee ID %d.\n", empID);
  }

  fclose(file);
}

void calculateSalary() {
  FILE *file = fopen(EMPLOYEE_FILE, "r");
  if (file == NULL) {
    printf("No employees found!\n");
    return;
  }

  int empID, found = 0;
  float bonus, deductions, netSalary;
  Employee emp;

  printf("\nEnter Employee ID to calculate salary: ");
  if (scanf("%d", &empID) != 1) {
    printf("Invalid input!\n");
    fclose(file);
    return;
  }

  while (fscanf(file, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                emp.username, emp.password) != EOF) {
    if (emp.id == empID) {
      found = 1;
      break;
    }
  }
  fclose(file);

  if (!found) {
    printf("Employee ID not found!\n");
    return;
  }

  // Get salary details
  printf("\nBasic Salary: %.2f\n", emp.salary);
  printf("Enter Bonus Amount: ");
  if (scanf("%f", &bonus) != 1)
    return;

  printf("Enter Deductions: ");
  if (scanf("%f", &deductions) != 1)
    return;

  netSalary = emp.salary + bonus - deductions;
  printf("\nFinal Salary for %s (ID: %d) is: %.2f\n", emp.name, emp.id,
         netSalary);

  // Save salary record
  FILE *salaryFile = fopen(SALARY_FILE, "a");
  if (salaryFile == NULL) {
    printf("Error opening salary records file!\n");
    return;
  }

  fprintf(salaryFile, "%d,%s,%.2f,%.2f,%.2f,%.2f\n", emp.id, emp.name,
          emp.salary, bonus, deductions, netSalary);
  fclose(salaryFile);

  printf("Salary details saved successfully!\n");
}

void viewSalaryBreakdown() {
  FILE *file = fopen(SALARY_FILE, "r");
  if (file == NULL) {
    printf("No salary records found!\n");
    return;
  }

  int empID, found = 0;
  float baseSalary, bonus, deductions, netSalary;
  char name[50];

  // Find employee ID based on logged-in username
  FILE *empFile = fopen(EMPLOYEE_FILE, "r");
  if (empFile == NULL) {
    printf("No employees found!\n");
    fclose(file);
    return;
  }

  Employee emp;
  while (fscanf(empFile, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                emp.username, emp.password) != EOF) {
    if (strcmp(emp.username, loggedInUser) == 0) {
      empID = emp.id;
      found = 1;
      break;
    }
  }
  fclose(empFile);

  if (!found) {
    printf("Error: Employee record not found!\n");
    fclose(file);
    return;
  }

  // Display salary records
  printf("\n===== Salary Breakdown for Employee ID %d =====\n", empID);
  printf("Base Salary\tBonus\tDeductions\tNet Salary\n");
  printf("------------------------------------------------------\n");

  found = 0;
  while (fscanf(file, "%d,%[^,],%f,%f,%f,%f\n", &empID, name, &baseSalary,
                &bonus, &deductions, &netSalary) != EOF) {
    if (empID == emp.id) {
      printf("%.2f\t%.2f\t%.2f\t%.2f\n", baseSalary, bonus, deductions,
             netSalary);
      found = 1;
    }
  }

  if (!found) {
    printf("No salary records found for Employee ID %d.\n", empID);
  }

  fclose(file);
}


void markAttendance() {
  if (strcmp(userRole, "Admin") == 0) {
    printf("Admins cannot mark attendance!\n");
    return;
  }

  FILE *file = fopen(ATTENDANCE_FILE, "a+");
  if (file == NULL) {
    printf("Error opening attendance file!\n");
    return;
  }

  int empID, found = 0;
  char date[15];
  Attendance att;
  Employee emp;

  // Get current employee ID based on username
  FILE *empFile = fopen(EMPLOYEE_FILE, "r");
  if (empFile == NULL) {
    printf("No employees found!\n");
    fclose(file);
    return;
  }

  while (fscanf(empFile, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%s\n", &emp.id,
                emp.name, &emp.age, emp.department, &emp.salary, emp.role,
                emp.username, emp.password) != EOF) {
    if (strcmp(emp.username, loggedInUser) == 0) {
      empID = emp.id;
      found = 1;
      break;
    }
  }
  fclose(empFile);

  if (!found) {
    printf("Error: Employee record not found!\n");
    fclose(file);
    return;
  }

  // Fetch today's date automatically
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  snprintf(date, sizeof(date), "%04d-%02d-%02d", tm.tm_year + 1900,
           tm.tm_mon + 1, tm.tm_mday);

  // Check if attendance is already marked for today
  FILE *readFile = fopen(ATTENDANCE_FILE, "r");
  if (readFile != NULL) {
    while (fscanf(readFile, "%d,%[^,],%s\n", &att.employee_id, att.date,
                  att.status) != EOF) {
      if (att.employee_id == empID && strcmp(att.date, date) == 0) {
        printf("Attendance already marked for today!\n");
        fclose(readFile);
        fclose(file);
        return;
      }
    }
    fclose(readFile);
  }

  // Mark attendance
  fprintf(file, "%d,%s,Present\n", empID, date);
  fclose(file);
  printf("Attendance marked successfully for %s on %s.\n", emp.name, date);
}
