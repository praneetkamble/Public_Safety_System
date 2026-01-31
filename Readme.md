# 🚨 Unified Public Safety & Civic Services System

A console-based, app-like public safety system built using the **C programming language**, designed to provide **quick access for citizens** and **centralized control for government authorities** through two separate applications sharing a common database.

---

## 📌 How It Works

- The **User Application** allows citizens to report emergencies or civic issues quickly
- Each report generates a **unique Case ID**
- All cases are stored permanently using **file handling**
- The **Government Application** accesses the same database to:
  - view all cases
  - update case status
  - generate analytics reports
- Every case follows a defined **lifecycle**:
  - Registered → Dispatched → In Progress → Resolved → Closed

---

## ✨ Features

- Two separate applications (User & Government)
- Shared database using binary files
- Emergency & civic issue reporting
- Case status tracking using Case ID
- Severity-based input validation (1–5 only)
- Human-readable status and case types
- Analytics report generation
- App-like console interface
- Robust input validation (no invalid values allowed)

---

## 🛠 Tech Stack

- C Programming Language
- File Handling
- Structures & Enums
- Modular Design
- system("cls") for screen control

---

## ▶ How to Run

1. Compile the programs:
   ```bash
   gcc user_app.c -o user_app
   gcc government_app.c -o government_app

   
2.Run the applications:

./user_app  
./government_app
