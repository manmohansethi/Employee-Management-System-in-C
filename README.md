
# 🏢 Employee Management System in C  

![GitHub repo size](https://img.shields.io/github/repo-size/manmohansethi/Employee-Management-System-in-C?color=blue&style=flat)  
![GitHub contributors](https://img.shields.io/github/contributors/manmohansethi/Employee-Management-System-in-C?color=green)  
![GitHub license](https://img.shields.io/github/license/manmohansethi/Employee-Management-System-in-C?color=yellow)  

A **Command-Line Employee Management System** built in **C**, using **CSV files** for data storage. This system allows **Admins** to manage employees, approve leave, and calculate salaries, while **Employees** can mark attendance and request leave.  

🌟 **GitHub Repository:** [Employee-Management-System-in-C](https://github.com/manmohansethi/Employee-Management-System-in-C)  

---

## 🚀 Features  

### 🔹 **Admin Features**  
✅ Add, view, modify, and delete employee records  
✅ Approve or reject leave requests  
✅ Calculate and store employee salaries  
✅ View salary breakdown of employees  

### 🔹 **Employee Features**  
✅ Mark attendance (prevents duplicate entries)  
✅ View personal attendance records  
✅ Apply for leave and check leave history  
✅ View salary breakdown  

---

## 🛠️ Installation  

### 1️⃣ **Clone the repository**  
```bash
git clone https://github.com/manmohansethi/Employee-Management-System-in-C.git
cd Employee-Management-System-in-C
```

### 2️⃣ **Compile the code**  
```bash
gcc -o employee_system main.c
```

### 3️⃣ **Run the program**  
```bash
./employee_system
```

---

## 📜 Usage  

🔹 The system starts with a **Login Screen**  
🔹 **Admins** can **manage employees, approve leave, and calculate salaries**  
🔹 **Employees** can **mark attendance, request leave, and check salary breakdown**  
🔹 **Type `exit`** anytime to quit the program  

---

## 💻 Technologies Used  

- **Programming Language:** C  
- **Storage:** CSV files (instead of a database)  
- **File Handling:** Used for reading/writing employee, attendance, leave, and salary data  
- **Authentication:** Simple username/password validation  

---

## ⚡ Challenges & Solutions  

| Challenge | Solution |
|-----------|----------|
| Storing employee data persistently | Used CSV files instead of a database |
| Preventing duplicate usernames | Implemented unique username validation |
| Avoiding duplicate attendance entries | Checked previous records before marking attendance |
| Securing employee deletion | Added confirmation prompts to prevent accidental deletion |

---

## 🚀 Future Enhancements  

✨ Encrypt passwords for better security  
✨ Add a graphical UI for better usability  
✨ Implement database integration (**MySQL**)  
✨ Implement role-based access control (RBAC)  

---

## 🤝 Contributing  

We welcome contributions! To contribute:  

1️⃣ **Fork** the repository  
2️⃣ Create a **new branch**  
3️⃣ Make your changes and **commit**  
4️⃣ **Push** your changes and submit a **Pull Request**  

---

## 🧑‍💻 Author  

👤 **Manmohan Sethi**  
📌 GitHub: [@manmohansethi](https://github.com/manmohansethi)  

---

## 📜 License  

🔹 This project is **open-source** and free to use under the **MIT License**.  
