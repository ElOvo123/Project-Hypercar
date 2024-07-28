# Project-Hypercar

Welcome to the **Hypercar Project**! This DIY initiative is dedicated to engineering a groundbreaking vehicle that represents the zenith of automotive innovation and performance. Our mission is to push the boundaries of high-speed, high-efficiency driving through pioneering aerodynamics, advanced propulsion systems, and cutting-edge technology.

## Project Overview

The Hypercar Project aims to create a high-performance vehicle by integrating:

- **Advanced Aerodynamics**: Optimizing airflow to enhance speed, stability, and efficiency.
- **Innovative Propulsion Systems**: Exploring state-of-the-art propulsion technologies for superior acceleration and energy efficiency.
- **High-Tech Components**: Utilizing the latest advancements in automotive technology to achieve unparalleled performance and reliability.

## Getting Started

Follow these steps to get started with the Hypercar Project:

### 1. Install Arduino CLI (Prerequisite)

Follow the installation instructions on the [Arduino CLI GitHub page](https://arduino.github.io/arduino-cli/0.19/installation/).

### 2. Clone the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/your-username/Project-Hypercar.git
```

### 3. Navigate to the Project Directory

Change your working directory to the project folder:

```bash
cd Project-Hypercar/software
```

### 5. Run The Project
#### 5.1 Verify the Project PCB Code

Compile the program to see the current progress and test features:

```bash
make verify
```

#### 5.2 Upload the Project PCB Code

Upload the program to see the current progress and test features:

```bash
make
```

#### 5.3 Run The Interface and Telemetry

Compile and execute the program to see the current progress and features:

- **Interface**

```bash
make
./bin/interface
```

- **Telemetry**

```bash
make
./bin/telemetry
```
### 6. Standards
#### 6.1 Commit Standards

To maintain a clean and organized history in our version control, we follow these commit standards:

##### 6.1.1 Commit Message Structure

- **Type**: A short keyword that categorizes the commit (e.g., feat, fix, docs, style, refactor, test, chore).
- **Scope**: An optional component or module the change pertains to (e.g., aero, propulsion).
- **Description**: A brief, imperative-style summary of the change

```bash
<type>(<scope>): <description> 
```

Example:
```bash
feat(aero): improve airflow efficiency in front spoiler
```

##### 6.1.2 Commit Message Body

- **Provide additional context about what and why the change was made.
- **Include any relevant issue numbers or links.

##### 6.1.3 Types of Commit Messages

- **feat**: A new feature
- **fix**: A bug fix
- **docs**: Documentation only changes
- **style**: Changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc.)
- **refactor**: A code change that neither fixes a bug nor adds a feature
- **test**: Adding missing tests or correcting existing tests
- **chore**: Changes to the build process or auxiliary tools and libraries such as documentation generation

#### 6.2 Coding Standards

To ensure code quality and maintainability, please adhere to the following coding standards:

##### 6.2.1 General Guidelines

- **Follow the Google C++ Style Guide for C++ code.**
- **Use descriptive variable and function names.**
- **Write clear and concise comments where necessary.**

##### 6.2.1 Formatting

- **Indentation**: Use 4 spaces for indentation, no tabs.
- **Line Length**: Limit lines to 80 characters.
- **Braces**: Use K&R style for braces.

```cpp
if (condition) {
    // code
} else {
    // code
}
```

##### 6.2.1 Naming Conventions

- **Classes and Structs**: Use PascalCase.
- **Functions and Methods**: Use camelCase.
- **Variables**: Use camelCase.
- **Constants**: Use UPPER_SNAKE_CASE.

##### 6.2.1 Code Review

- **All code changes should be submitted through pull requests.**
- **Pull requests should be reviewed by at least one other team member.**
- **Ensure that all checks pass before merging.**

### 7. Contribute

We welcome contributions! Here's how you can help:

- **Report Bugs**: If you find any issues, please report them in the Issues section.
- **Suggest Features**: We are open to new ideas and feature requests.
- **Submit Pull Requests**: Feel free to fork the repository, make improvements, and submit a pull request.

###

Thank you for being part of the Hypercar Project! Together, we can push the boundaries of automotive technology and create something truly extraordinary.