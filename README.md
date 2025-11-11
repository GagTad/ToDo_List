# ToDo List Application for Microchip

This is a simple ToDo List management application developed in C++ using the Qt framework, as a technical task for the C++ Software Engineer Intern position at Microchip.

## Design and Architecture

The application is built upon a multi-layered architecture to ensure a clear separation of concerns, high maintainability, and testability. The core logic is completely decoupled from the UI.

- **Command Processing Pipeline:** User input is processed through a compiler-like pipeline:
  1.  **Lexer:** Breaks the raw string input into a stream of typed `Tokens`.
  2.  **Parser:** Validates the syntactic correctness of the token stream and produces a structured `ParsedCommand` object.
  3.  **Executor:** Performs semantic validation on the `ParsedCommand`, executes the command by calling the `TaskManager`, and returns a raw `ExecutionResult`.
  4.  **ResponseFormatter:** A presentation-layer class that formats the raw `ExecutionResult` into a user-friendly string.

- **Core Logic:**
  - **TaskManager:** The central class responsible for all business logic (adding, removing, completing tasks). It uses an `std::map` for efficient, name-based task management.

- **GUI:**
  - A minimal **Qt Widgets** interface is used strictly for presentation and user input, as per the requirements. The UI is updated by querying the state of the `TaskManager` after each command.

## How to Build and Run

### Prerequisites
*   Qt 6.x (The project was developed and tested with Qt 6)
*   A C++17 compatible compiler (e.g., MinGW, MSVC, GCC).

### Steps
1.  Clone the repository:
    ```
    git clone <your-repository-link>
    ```
2.  Open the `ToDoApp.pro` file using **Qt Creator**.
3.  Configure the project by selecting an appropriate Kit (e.g., Desktop Qt MinGW).
4.  From the menu, select **Build -> Run qmake**.
5.  Press the **Run** button (the green triangle icon) to build and start the application.

## How to Use the Application

Enter commands into the input field at the bottom and press "Execute". The supported commands are:

*   `add_task -name {task name}`
*   `remove_task -name {task name}`
*   `complete_task -name {task name}`
*   `list_tasks`
*   `execute_file -file_path {C:/path/to/your/file.txt}`

## Known Issues or Limitations

*   Task names containing curly braces (`{` or `}`) are not supported due to the simple string literal parsing.
*   The checkboxes in the task list are for display only. Marking a task as complete must be done via the `complete_task` command.
