# Print Utils

Simple and practical **C utility library** for formatting text in the Windows console.  
Provides functions to **center**, **right-align**, and format text with professional-looking layouts.

## ✨ Features

- ✅ **Center text** – Single or multi-line text centered in the console (`printCentered`, `printc`)
- ✅ **Right-align text** – Align text to the right side of the console (`printr`)
- ✅ **Windows Console API** – Uses `GetConsoleScreenBufferInfo` and `SetConsoleCursorPosition` for accurate positioning
- ✅ **UTF-8 support** – Works with box-drawing characters, emojis, and international text
- ✅ **Inline functions** – Everything in the header file, no compilation needed
- ✅ **Lightweight** – Single header file, zero dependencies

## 📋 Requirements

- **OS**: Windows (uses `windows.h`)
- **Compiler**: GCC (MinGW), MSVC, Clang, or any C compiler supporting Windows API
- **C Standard**: C99 or later
- **Headers**: `windows.h`, `stdio.h`, `string.h` (standard libraries)

## 📦 Installation

### Method 1: Copy to Your Project

1. **Download** `print_utils.h` and `print_utils.c` from the repository
2. **Place both files** in your project folder (same directory as your `.c` files)
3. **Include** in your C program:
```c
#include "print_utils.h"
```
4. **Compile** normally:
```bash
gcc main.c print_utils.c -o myapp.exe
```

### Method 2: Copy Only Header

If you don't have `print_utils.c`, you can just copy `print_utils.h` since functions are defined inline. The compilation command remains the same.

## 🔧 API Functions

### 1. `void printCentered(const char* text);`

Center a **single line** horizontally in the console.

**What it does:**
- Gets the console width using `GetConsoleScreenBufferInfo`
- Calculates text length with `strlen`
- Prints padding spaces, then the text

**Example:**
```c
#include <windows.h>
#include "print_utils.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);  // Enable UTF-8 for special characters
    
    printCentered("Welcome!");
    printCentered("Press any key to continue...");
    
    return 0;
}
```

---

### 2. `void printc(const char* bigText, int fixed_width);`

Center a **multi-line block** of text.  
Each line is centered independently using the same width.

**Parameters:**
- `bigText` – Text with newlines (`\n`) separating lines
- `fixed_width` – Visual width of each line (count manually, especially for box characters)

**What it does:**
- Splits text on `\n` characters
- Centers each line individually
- Uses the same algorithm as `printCentered`

**Example:**
```c
#include <windows.h>
#include "print_utils.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    const char* banner =
    "┌─────────────────────────────┐\n"
    "│   GAMING SCORE BOARD        │\n"
    "│   Player: John              │\n"
    "│   Score: 9,850 points       │\n"
    "│   Level: 5                  │\n"
    "└─────────────────────────────┘";
    
    printc(banner, 31);  // 31 characters wide
    
    return 0;
}
```

---

### 3. `void printr(const char* text, int line_length);`

Right-align text or multi-line blocks in the console.

**Parameters:**
- `text` – Text to align (can have multiple lines with `\n`)
- `line_length` – Visual width of the text

**What it does:**
- Gets console width with `GetConsoleScreenBufferInfo`
- Calculates right-aligned position: `console_width - line_length`
- Uses `SetConsoleCursorPosition` to place the cursor
- Prints each line at the right position

**Example:**
```c
#include <windows.h>
#include "print_utils.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    printf("Product List:\n");
    printf("Apple ..................... 2.50 DH\n");
    printf("Orange .................... 1.75 DH\n");
    printf("Banana .................... 1.25 DH\n");
    printf("\n");
    
    printr("Total: 5.50 DH", 14);
    printr("Tax: 15%", 8);
    
    return 0;
}
```

---

## 🧪 Complete Examples


### Login Screen

```c
#include <windows.h>
#include <stdio.h>
#include "print_utils.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    
    system("cls");
    
    printCentered("═════════════════════════════════════");
    printCentered("        USER LOGIN PORTAL");
    printCentered("═════════════════════════════════════");
    printf("\n");
    
    char username[50];
    printf("Username: ");
    scanf("%s", username);
    
    char password[50];
    printf("Password: ");
    scanf("%s", password);
    
    printf("\n");
    printCentered("✓ Login successful!");
    
    return 0;
}
```

---

## 💻 Compilation Examples

### Using MinGW (Windows)

```bash
# Compile and create executable
gcc main.c print_utils.c -o myapp.exe

# Run the program
myapp.exe
```

### Using MSVC (Visual Studio)

```bash
# Compile
cl main.c print_utils.c

# Run
main.exe
```

### Using Code::Blocks or IDE

1. Create a new C project
2. Add `main.c`, `print_utils.h`, and `print_utils.c` to your project
3. Build the project (your IDE will handle compilation)

---

## 📝 How to Use - Step by Step

### Step 1: Create Your Project Folder
```
my_project/
├── main.c
├── print_utils.h
└── print_utils.c
```

### Step 2: Include the Header
```c
#include <windows.h>
#include <stdio.h>
#include "print_utils.h"

int main() {
    // Your code here
    return 0;
}
```

### Step 3: Enable UTF-8 (Recommended)
```c
int main() {
    SetConsoleOutputCP(CP_UTF8);  // Add this at the start
    
    // Now you can use special characters
    printCentered("Hello 世界 🌍");
    
    return 0;
}
```

### Step 4: Compile and Run
```bash
gcc main.c print_utils.c -o app.exe
app.exe
```

---

## ⚙️ Technical Details

### How `printCentered` Works
1. Calls `GetConsoleScreenBufferInfo` to get console dimensions
2. Uses `strlen()` to measure text length
3. Calculates: `padding = (console_width - text_length) / 2`
4. Prints spaces for padding, then the text

### How `printc` Works
1. Splits input text at each `\n` newline
2. For each line:
   - Extracts the line content
   - Calls the centering logic with `fixed_width`
   - Advances to next line

### How `printr` Works
1. Gets console width with `GetConsoleScreenBufferInfo`
2. Calculates: `column = console_width - line_length`
3. Uses `SetConsoleCursorPosition` to move cursor to that column
4. Prints the text at that position

---

**Author**: Yassine Abouayyoub  
**Country**: Morocco  
**Made for**: Applied Computer Science students and developers
