# ToDo List Application for Microchip

This is a simple command-line driven ToDo List management application developed in C++17 with a minimal Qt 6 GUI. The project was created as a technical task for the C++ Software Engineer Intern position at Microchip.

## Core Architectural Principles & Design

The application's architecture was designed with a strong emphasis on **modularity, scalability, and separation of concerns**. The core business logic is completely decoupled from the presentation layer (the Qt GUI), making the system highly maintainable and testable.

### Command Processing Pipeline
Instead of a simple `if/else` structure, user input is processed through a robust, compiler-inspired pipeline. This approach provides excellent flexibility and powerful error handling.

1.  **Lexer (`Lexer` class):** The raw input string is first tokenized into a stream of typed `Tokens` (e.g., COMMAND, KEYWORD, STRING_LITERAL). This stage is only concerned with recognizing "words".

2.  **Parser (`Parser` class):** The token stream is then fed into the Parser, which validates its syntactic correctness against the command grammar. If the syntax is valid, it produces a structured `ParsedCommand` object, representing the user's intent. Any grammatical errors (e.g., a missing argument) are caught here.

3.  **Executor (`Executor` class):** This class acts as the bridge between the parsed command and the business logic.
    *   **Semantic Validation:** It first performs semantic checks on the `ParsedCommand` (e.g., ensuring `list_tasks` has no arguments).
    *   **Execution:** It then calls the appropriate methods on the `TaskManager`, passing the validated arguments.
    *   **Result Generation:** It returns a raw, structured `ExecutionResult` object, containing the status of the operation and any relevant data.

4.  **Response Formatter (`ResponseFormatter` class):** This is the final presentation layer component. It takes the `ExecutionResult` and formats it into a user-friendly, display-ready string, including color-coding for errors using HTML.

### Technology Stack
*   **Language:** C++17
*   **Framework:** Qt 6
*   **Build System:** qmake
*   **Core Data Structures:** `std::map` for efficient O(log n) task lookups, `std::vector`, `std::string`, `std::optional`.

### A Note on AI/LLM Collaboration
In the spirit of modern development and transparency, it's worth noting that an AI assistant (Large Language Model) was used as a collaborative partner in this project. Its role was primarily in:
*   Generating documentation and explanatory text (including significant portions of this README).
*   Assisting in debugging and identifying subtle errors.



## Test Results

Here are a few screenshots demonstrating the application's functionality, including correct command execution and handling of various errors.

<img width="250" height="200" alt="image" src="https://github.com/user-attachments/assets/09d01a7d-a48b-4999-ac01-6135808ec20c" />
<img width="260" height="200" alt="image" src="https://github.com/user-attachments/assets/a67b1403-2de4-4463-9532-61a57e562be2" />
<img width="250" height="200" alt="image" src="https://github.com/user-attachments/assets/cfc21df3-aae2-49a4-a606-9b8d7c7671a9" />




**Placeholder for Test Result Image 1**
**Placeholder for Test Result Image 2**
**Placeholder for Test Result Image 3**

## How to Build and Run

### Prerequisites
*   Qt 6.x (The project was developed and tested with Qt 6)
*   A C++17 compatible compiler (e.g., MinGW, MSVC, GCC).
*   Qt Creator IDE
  
### Steps

* Download the Project Files:
* On the main page of this GitHub repository, click the green < > Code button.
* Select Download ZIP from the dropdown menu.
* Extract the ZIP Archive:
* Find the downloaded ToDo_List-main.zip (or similar) file on your computer.
* Extract its contents to a convenient location (e.g., your Desktop or a projects folder). You will now have a folder named ToDo_List-main containing all the project files (.cpp, .h, .pro, .ui).
* Open the Project in Qt Creator:
* Launch the Qt Creator IDE.
* Go to the menu: File > Open File or Project...
* Navigate into the ToDo_List-main folder that you just extracted.
* Select the ToDoApp.pro file and click "Open". This .pro file is the main project file for Qt.
* Configure the Project:
* A "Configure Project" dialog will appear.
* Select a compatible Kit from the list (e.g., Desktop Qt 6.x.x MinGW 64-bit). A Kit defines the compiler, Qt version, and debugger to use.
* Click the "Configure Project" button.
* Build the Project:
* Once the project is configured and opened, build it by pressing Ctrl+B or clicking the Build icon (a hammer) in the bottom-left panel.
* Wait for the build process to complete. You can monitor the progress in the "Compile Output" tab.
* Run the Application:
* After a successful build, run the application by pressing Ctrl+R or clicking the Run icon (a green triangle).
* The ToDo List Manager application window should now appear on your screen.


## Future Enhancements

The current architecture is highly extensible. Here are some potential features for future development:

1.  **Task Priority & Deadlines:**
    *   Extend the `Task` class to include priority levels (e.g., Low, Medium, High) and optional `QDateTime` deadlines.
    *   The `list_tasks` command could then be enhanced with sorting capabilities (e.g., `list_tasks -sort by_priority`, `list_tasks -sort by_deadline`).

2.  **Interactive UI:**
    *   Implement logic to handle user interaction directly from the GUI. For example, connecting the `QListWidget::itemChanged` signal to a slot that calls `complete_task` when a user clicks a checkbox. This would require careful state management to avoid conflicts with the command-line input.

3.  **Data Persistence:**
    *   Implement functionality to save the current task list to a file (e.g., JSON or XML) when the application closes and load it back on startup. This would make the application state persistent across sessions.



## Known Issues or Limitations

*   Task names containing curly braces (`{` or `}`) are not supported due to the simple parsing logic for string literals.
