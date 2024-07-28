# Project-Hypercar

Welcome to the **Hypercar Project**! This DIY initiative is dedicated to engineering a groundbreaking vehicle that represents the zenith of automotive innovation and performance. Our mission is to push the boundaries of high-speed, high-efficiency driving through pioneering aerodynamics, advanced propulsion systems, and cutting-edge technology.

## Table of Contents
1. Project Overview
2. Getting Started
    - Install Arduino CLI
    - Clone the Repository
    - Navigate to the Project Directory
    - Run the Project
3. Standards
    - Commit Standards
    - Coding Standards
4. Contribute

## Project Overview

The Hypercar Project aims to create a high-performance vehicle by integrating:

- **Advanced Aerodynamics**: Optimizing airflow to enhance speed, stability, and efficiency.
- **Innovative Propulsion Systems**: Exploring state-of-the-art propulsion technologies for superior acceleration and energy efficiency.
- **High-Tech Components**: Utilizing the latest advancements in automotive technology to achieve unparalleled performance and reliability.

## Getting Started

Follow these steps to get started with the Hypercar Project:

### Install Arduino CLI (Prerequisite)

Follow the installation instructions on the [Arduino CLI GitHub page](https://arduino.github.io/arduino-cli/0.19/installation/).

### Clone the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/your-username/Project-Hypercar.git
```

### Navigate to the Project Directory

Change your working directory to the project folder:

```bash
cd Project-Hypercar/software
```

### Project Structure

PROJECT-HYPERCAR
|-

### Run The Project
#### Verify the Project PCB Code

Compile the program to see the current progress and test features:

```bash
make verify
```

#### Upload the Project PCB Code

Upload the program to see the current progress and test features:

```bash
make
```

#### Run The Interface and Telemetry

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
### Standards
#### Commit Standards

To maintain a clean and organized history in our version control, we follow these commit standards:

##### Commit Message Structure

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

##### Commit Message Body

- Provide additional context about what and why the change was made.
- Include any relevant issue numbers or links.

##### Types of Commit Messages

- **feat**: A new feature
- **fix**: A bug fix
- **docs**: Documentation only changes
- **style**: Changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc.)
- **refactor**: A code change that neither fixes a bug nor adds a feature
- **test**: Adding missing tests or correcting existing tests
- **chore**: Changes to the build process or auxiliary tools and libraries such as documentation generation

#### Coding Standards

To ensure code quality and maintainability, please adhere to the following coding standards:

##### General Guidelines

- Follow the Google C++ Style Guide for C++ code.
- Use descriptive variable and function names.
- Write clear and concise comments where necessary.

##### Formatting

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

##### Naming Conventions

- **Classes and Structs**: Use PascalCase.
- **Functions and Methods**: Use camelCase.
- **Variables**: Use camelCase.
- **Constants**: Use UPPER_SNAKE_CASE.

##### Code Review

- All code changes should be submitted through pull requests.
- Pull requests should be reviewed by at least one other team member.
- Ensure that all checks pass before merging.

### Contribute

We welcome contributions! Here's how you can help:

- **Report Bugs**: If you find any issues, please report them in the Issues section.
- **Suggest Features**: We are open to new ideas and feature requests.
- **Submit Pull Requests**: Feel free to fork the repository, make improvements, and submit a pull request.

###

Thank you for being part of the Hypercar Project! Together, we can push the boundaries of automotive technology and create something truly extraordinary.