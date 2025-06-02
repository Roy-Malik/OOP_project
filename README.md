# C++ Cafeteria Management System 🚀

A console-based cafeteria management system written in C++, developed as a final OOP project. The application supports admin and student roles, providing full functionality for order placement, stock management, complaint handling, and notifications.

## 🧠 Key Features

- 👨‍🎓 Student and 👨‍💼 Employee logins
- 🍔 Place and view food orders
- 📦 Stock tracking with live updates
- 🗂️ Complaint registration and admin resolution
- 🔔 Real-time notifications
- 🔐 Role-based access control (admin vs. student)

## 🛠️ Technologies Used

- C++ (OOP principles)
- File handling (`.txt` and `.dat` files)
- Simple terminal UI

## 📁 Project Structure

- `main.cpp` – Entry point for the application
- `admin.cpp/h` – Admin role logic (stock, orders, complaints)
- `student.cpp/h` – Student role logic (ordering, complaints)
- `employee.cpp/h` – Employee-side management
- `user.cpp/h` – Abstract user handling
- `cart.txt`, `orders.txt`, `complains.txt` – Persistent storage
- `main.exe` – Compiled executable for Windows

## 📸 Screenshots

> You can add terminal screenshots of login, order placement, and admin panel here.

## 🏁 How to Run

1. Clone the repository
2. Compile using any C++ compiler (e.g., `g++ main.cpp *.cpp -o cafeteria.exe`)
3. Run the compiled `.exe` or output binary
4. Use provided login files (`Login_emp.txt`, `login_std.txt`) to log in

## ✅ Future Improvements

- GUI using Qt or C++
- Database integration (MySQL/SQLite)
- Web-based frontend with Flask/C++ backend

## 🧑‍💻 Author

Developed by Muhammad Ammar Shahid – Cybersecurity Student @ FAST, Pakistan.

