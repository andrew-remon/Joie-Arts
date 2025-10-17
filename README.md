# 🎨 Joie Arts - GUI Filter Application

A modern **C++ / Qt-based Image Filter Application** that provides an interactive, slider-driven interface for image editing, transformations, and artistic effects.  
Developed as part of **CS213 - OOP Project**, this GUI version brings all the console features — and more — into an intuitive, visual experience.

---

## 🖼️ Overview

**Joie Arts (GUI Edition)** transforms the original console application into a **fully interactive desktop tool** built using **Qt 6.9.2 (MSVC 2022, x86_64)**.

Users can now:
- Apply over **25 creative filters** through **panels and sliders**  
- Preview image changes in real-time  
- Control brightness, contrast, noise, and more dynamically  
- Save, compare, and merge images visually  

---

## 🖼️ Application Gallery

Below are snapshots of the application in action:

### 🖼️ Interface Previews

<p align="center">
  <img src="Joie_Arts_App/App%20Snapshots/1.jpeg" width="250">
  <img src="Joie_Arts_App/App%20Snapshots/2.jpeg" width="250">
  <img src="Joie_Arts_App/App%20Snapshots/3.jpeg" width="250">
</p>

### 🎨 Filter Previews

<p align="center">
  <img src="Joie_Arts_App/App%20Snapshots/4.jpeg" width="200">
  <img src="Joie_Arts_App/App%20Snapshots/5.jpeg" width="200">
  <img src="Joie_Arts_App/App%20Snapshots/6.jpeg" width="200">
  <img src="Joie_Arts_App/App%20Snapshots/7.jpeg" width="200">
  <img src="Joie_Arts_App/App%20Snapshots/8.jpeg" width="200">
  <img src="Joie_Arts_App/App%20Snapshots/9.jpeg" width="200">
  <img src="Joie_Arts_App/App%20Snapshots/10.jpeg" width="200">
</p>


🎥 **YouTube Demo:**  
A full demonstration video showing the GUI workflow will be available in the repository:  
👉 [**Watch Application Demo**](https://youtu.be/k-BJtO6nvQo)

---

## 🧩 Filter Organization

### 🧭 **Panel Filters**
Accessible from the main toolbar — includes basic image operations:
- **Crop**
- **Resize**
- **Flip / Rotate**
- **Hue Options**
- **Edit Options** (Brightness, Contrast, etc.)

---

### ⚙️ **Edit Options Filters** *(with live sliders)*
Fine-tune image tone and quality dynamically:
- **Gamma**
- **Brightness**
- **Contrast**
- **Noise**
- **Vignette**

---

### 🎨 **Basic Filters**
Classic transformations and quick enhancements:
- **Grayscale**
- **Black & White**
- **Invert Colors**
- **Blur**

---

### 🌈 **Artistic & Advanced Filters**
Bring creativity and realism with complex, algorithmic effects:

| Filter | Description |
|--------|--------------|
| **InfraRed Filter** | Creates a warm reddish tone with inverted highlights |
| **Purplizing Filter** | Adds a violet aesthetic by adjusting RGB balance |
| **Skew Filter** | Tilts the image diagonally, giving a 3D-like perspective |
| **Glitch Filter** | Introduces random RGB channel shifts for a digital distortion effect |
| **Fish-Eye Filter** | Combines radial distortion with vignetting for a cinematic curve |
| **Nighty Effect Filter** | Blends cool hues, dark tones, and inversion for a surreal night look |
| **Cel Shading Filter** | Converts color regions into cartoon-like tones |
| **Pixel Art Filter** | Pixelates the image for a nostalgic retro effect |
| **Emboss Filter** | Highlights edges to create a relief-like 3D texture |
| **Sharpen** | Enhances image clarity by emphasizing edge details |
| **Oil Painting Effect** | Simulates brush strokes for a painted texture |
| **Old TV Effect** | Adds scanlines and static for a vintage analog feel |
| **Natural Sunlight Filter** | Brightens highlights with warm light simulation |
| **Edge Detection** | Detects and highlights prominent edges |
| **Frame Addition** | Adds artistic or cinematic frames |
| **Darken / Lighten Adjustment** | Modifies overall exposure levels |
| **Merge Two Images** | Combines two photos with blending techniques |

🧩 *Total Filters:* **25+**  
*(Now organized into functional panels and slider controls.)*

---

## 🧮 Filter Categories Summary

| Category | Example Filters | Description |
|-----------|----------------|--------------|
| **Color & Tone** | Gamma, Brightness, Contrast, InfraRed, Purplizing | Adjust image exposure and color balance |
| **Artistic** | Oil Painting, Cel Shading, Pixel Art, Nighty Effect | Creative transformations with stylized looks |
| **Distortion & Geometry** | Skew, Fish-Eye | Warps image shape for 3D or cinematic feel |
| **Detail Enhancement** | Sharpen, Emboss, Edge Detection | Highlights and refines texture details |
| **Effects & Simulation** | Glitch, Old TV, Vignette, Sunlight | Adds retro or cinematic visual effects |

---

## 🧠 Technical Details

### 💻 Language & Framework
- **C++17 / Qt 6.9.2 (MSVC 2022, x86_64)**  
- **OOP-based Architecture** from the console version  

### 🧱 Code Architecture
- `Image_Class.h` → Handles image I/O and pixel access  
- `Filter` Class → Implements all filter algorithms  
- `main.qml` → Main GUI interface file, defining the layout and user interactions  
- `CustomSlider.qml` (sub-folder) → Defines reusable slider components for real-time filter adjustments  
- `FilterManager` → Coordinates filter selection, preview updates, and communication between backend and UI  

### 🧩 Core Concepts
- **Signal–Slot Mechanism** for GUI responsiveness  
- **Real-time Image Preview** using QLabel and QPixmap  
- **Dynamic Sliders & Value Binding** (Qt widgets)  
- **Modular Filter Design** (easy to add or update filters)  
- **Undo / Redo Buffer System**  
- **File Handling** for `.png`, `.jpg`, `.bmp`, `.jpeg`  

---

## 👥 Team Members

| Name | ID | Section | Contributions |
|------|----|----------|----------------|
| **Ahmed Yasser** | 20240061 | S7-8 | Filters 1, 4, 7, 10  • GUI Implementation • GUI Panels • Testing |
| **Andrew Remon** | 20240094 | S7-8 | Filters 2, 5, 8, 11  • Class structure • Documentation • GitHub setup |
| **Joy Magdy** | 20240149 | S7-8 | Filters 2, 3, 5, 6, 8, 9, 1–15 • Advanced Filters • GUI Optimization  |

---

## 🚀 How to Run (GUI Version)

### 1. Open the project in Qt Creator
- Make sure **Qt 6.9.2 (MSVC 2022, x86_64)** is installed.  
- Open the `.pro` file or the `CMakeLists.txt` file directly in **Qt Creator**.

### 2. Configure the Kit
- Select the correct **Qt version** and **MSVC 2022** compiler in your build settings.

### 3. Build the project
- Click **Build ▶️** or use the shortcut `Ctrl + B`.

### 4. Run the application
- Press **Run ▶️** to launch the GUI.

### 5. Use the application
- Load an image using the **top menu bar**.  
- Experiment with different **panels and sliders** to apply filters in real time.  
- Save your result through **File → Save As**.

---

## 🏆 Acknowledgements
- Cairo University - Faculty of Computers and Artificial Intelligence
- CS213 - **OOP Course**
- Special Thanks to our **Dr. Mohamed Elramly** and his TAs for this opportunity to Level up our skills.

---

## 📜 License
This project is developed for academic and educational purposes under the supervision of Faculty of Computers and Artificial Intelligenct, Cairo University.
