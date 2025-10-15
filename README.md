# 🌈 Joie Arts - Filter Application

A C++ Object-Oriented **Image Filter Application** that allows users to choose between '26 Options' to apply multiple photo filters, transformations, and effects interactively.  
Developed as part of **CS213 - Assignment 1**, this project demonstrates image processing, filter design, and software collaboration principles.

---

## 🖼️ Overview

**Joie Arts** is a console-based image processing program that supports a wide range of filters such as grayscale, blur, resizing, rotation, old TV effects, oil painting, and much more.

Users can:
- Load and save images.
- Apply various filters and transformations.
- Undo and redo applied filters.
- Combine multiple filters for creative results.

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
- **Sharpen** ← *(new basic enhancement)*  


### 🌟 Artistic & Advanced Filters
- **Red Scale Filter** – creates a warm reddish tone with inverted highlights  
- **Purpling Filter** – gives a violet aesthetic through channel balance  
- **Skew Filter** – tilts the image diagonally for a 3D-like visual  
- **Glitch Filter** – introduces random RGB channel shifts for digital distortion  
- **Fish-Eye & Vignette Filter** – combines radial distortion with dark corners for a cinematic look  
- **Cel Shading Filter** – converts photo colors into cartoon-like quantized tones 
- **Pixel Art Filter** – scales down and up to produce a pixelated retro effect  
- **Emboss Filter** – highlights edges for a relief-style 3D effect
- **Film Frame Effect:** Highlights edges and adds a customizable border for a classic film-style frame.
- **Midnight Effect:** Creates a moody night look by darkening tones, adding purplish-red hues, and inverting colors for a cinematic feel.
- **Oil Painting Effect**  
- **Old TV Effect**  
- **Natural Sunlight Filter**  
- **Edge Detection**  
- **Frame Addition**  
- **Darken / Lighten Adjustment**  
- **Merge Two Images**

🧩 *Total Filters:* **26**, combining both fundamental and artistic enhancements.

### 🧭 Utility Features
- Load and save images with `.jpg`, `.png`, `.bmp`, `.jpeg`
- Undo / Redo operations for filters
- Robust input validation for user choices

---

## 🧮 Filter Categories Summary

| Category | Example Filters | Description |
|-----------|----------------|--------------|
| **Color & Tone** | Red Scale, Purpling, Invert, Black & White | Adjust image colors and tones |
| **Artistic** | Oil Painting, Cel Shading, Pixel Art, Midnight  Effect | Creative transformations with visual styles |
| **Distortion & Geometry** | Skew, Fish-Eye | Warps image geometry using math transformations |
| **Detail Enhancement** | Sharpen, Emboss, Edge Detection, Film Frame | Enhances or highlights image features |
| **Effects & Simulation** | Glitch, Old TV, Sunlight, Vignette | Adds cinematic or retro visual effects |

---

## 🧩 Technical Details

### 💻 Language
- **C++**

## 🧠 Concepts Used

- **Object-Oriented Programming (OOP)** — classes, encapsulation, modularity, abstraction  
- **Image Processing Algorithms** — pixel manipulation, kernel-based operations  
- **Matrix Convolution Filters** (e.g., sharpen, emboss, blur, edge detection)  
- **Color Channel Transformations** — used in red scale, purpling, and glitch filters  
- **Geometric Transformations** — used in skew and fish-eye filters  
- **Quantization Techniques** — used in cel shading  
- **Resampling & Nearest Neighbor Resizing** — used in pixel art filter  
- **File I/O Operations**  
- **Stack-based Undo/Redo System**  
- **Error Handling and Input Validation**  
- **Math & Trigonometry Functions** — used for distortion, skewing, and angular effects  


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
