# 🌈 Joy Animation App

A C++ Object-Oriented **Image Filter Application** that allows users to apply multiple photo filters, transformations, and effects interactively.  
Developed as part of **CS213 - Assignment 1**, this project demonstrates image processing, filter design, and software collaboration principles.

---

## 🖼️ Overview

**Joy Animation App** is a console-based image processing program that supports a wide range of filters such as grayscale, blur, resizing, rotation, old TV effects, oil painting, and much more.

Users can:
- Load and save images
- Apply various filters and transformations
- Undo and redo applied filters
- Combine multiple filters for creative results

This project also serves as a foundation for the **Grand Competition GUI version**, which is under development.

---

## 🎥 Demo & Documentation

A video demonstration, detailed documentation, and design diagrams are available on Google Drive:

👉 [**Project Drive Folder**](https://drive.google.com/drive/u/2/folders/1RGNOCiMWfK1G72d6raB_XjhekJpsMMff)

---

## 👥 Team Members

| Name | ID | Section | Contributions |
|------|----|----------|----------------|
| **Ahmed Yasser** | 20240061 | S7-8 | Filters 1, 4, 7, 10 • GitHub setup • GUI (in progress) |
| **Andrew Remon** | 20240094 | S7-8 | Filters 2, 5, 8, 11 • Menus • Class structure • Diagram • Linking GUI (in progress) |
| **Joy Magdy** | 20240149 | S7-8 | Filters 3, 6, 9, 12–15 • Menu • Advanced Filters (16–18 + bonus) • Optimization Testing |

---

## ⚙️ Features

### 🎨 Basic Filters
- **Grayscale**
- **Black & White**
- **Invert Colors**
- **Blur**
- **Crop**
- **Resize**
- **Flip / Rotate**

### 🌟 Artistic & Advanced Filters
- **Oil Painting Effect**
- **Old TV Effect**
- **Natural Sunlight Filter**
- **Edge Detection**
- **Frame Addition**
- **Darken / Lighten Adjustment**
- **Merge Two Images**

### 🧭 Utility Features
- Load and save images with `.jpg`, `.png`, `.bmp`, `.jpeg`
- Undo / Redo operations for filters
- Robust input validation for user choices

---

## 🧩 Technical Details

### 💻 Language
- **C++**

### 🧠 Concepts Used
- **Object-Oriented Design (OOP)** — classes, encapsulation, modularity, and abstraction  
- Image processing algorithms
- File I/O operations
- Stack-based undo/redo system
- Bicubic interpolation for resizing
- Kernel-based convolution (blur & edge detection)
- Class-based modular architecture

### 🧱 Code Structure
- `Image_Class.h` → Handles image loading, saving, and pixel access  
- `Filter` Class → Implements all filters and transformations  
- `InputValidation` Class → Ensures valid user input  
- `Main` Class → Manages the user menu and program workflow

---

## 🚀 How to Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/Joy-Animation-App.git
   cd Joy-Animation-App
2. **Compile the project**
   Make sure  you have a C++ compiler installed
   ```bash
   g++ -o JoyAnimationApp main.cpp
3. **Run the executable**
   ```bash
   ./JoyAnimationApp
4. **Follow the on-screen menu**
   - Load an image
   - Apply your desired filters
   - Save the output image

---

## 🏆 Acknowledgements
- Cairo University - Faculty of Computers and Artificial Intelligence
- CS213 - OOP Course
- Special Thans to our Dr. Mohamed Elramly and his TAs for this opportunity to Level up our skills.

---

## 📜 License
This project is developed for academic and educational purposes under the supervision of Faculty of Computers and Artificial Intelligenct, Cairo University.
