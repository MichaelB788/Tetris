Subjects covered:
- Game Logic
    - Blocks
- Automation
    - [CMake](#cmake) 

# Game Logic

## Temp

Some text.

# Automation

## CMake

CMake is software which allows us to automate the compilation process of
our programs. This automation comes especially handy when we build programs
which implement **multiple libraries**, or if there are multiple **directory
hierarchies** in our program which we want to compile efficiently.

Block game originally utilized make, however with the expansion of this project
CMake seems to be more suitable and convienient. (Make wasn't going to compile
all my files unless I specified each one!)

Most of my notes will be based on the following [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html) 

Also, I used this repository as reference [cmake-examples](https://github.com/ttroy50/cmake-examples/tree/master/01-basic/A-hello-cmake) 

#### Initialization

CMake files are usually normal .txt files fittingly named `CMakeLists.txt`.

#### Minimum CMake Required
It is also standard for a CMake file to contain the line
`cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])`.
> <policy_max> is not strictly required.

#### Project

After set the minimum required version of CMake, we should go ahead and call
`project()`. Take a look at the syntax below. 

```CMake
project(<PROJECT-NAME> [<language-name>...])

project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```
> For this project, I imagine the former would be most appropriate.

#### Executable

Finally, we want to set the name of our executible through 
`add_executable(<name> <options>... <sources>...)` 

It's common practice to use the project name as the name of the executable.
Since project() creates a ${PROJECT-NAME} value, we can simply do the following;

```CMake
cmake_minimum_required(VERSION 2.6)
project (hello_cmake)
add_executable(${PROJECT_NAME} main.cpp)
```

#### Configure and build CMake

Once all that is done, configure cmake by simply calling `cmake` on the root
directory of your project.

Now when you want to build, call `cmake --build .` 
