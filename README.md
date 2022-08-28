## Syra-uOS
It is a software framework that helps microcontroller programmers to write simple and powerful applications for microcontrollers.

It is designed to work with small microcontrollers such as 8Bit AVR Xmega, tinyAVR and also 32Bit ARM SAM devices.

It is free, lightweight, easy to use and written in C language.


## How it work?

The main goal of this framework is to make microcontroller programming easy as programming in operating systems environment.

the framework initialize the system and run the user tasks in the main system loop.

Programmers do not need to think about the framework, and they only have to focus on their tasks.

So just write your task function, define it in the system, and let the framework run it .


## Quick start
1- Copy framework files into project folder.

2- Edit the default Main_Task in the main.c file or add a new task.

3- Compile and run the code.


## Basic Example
### A Simple Task
Task is defined as a normal function, but it does not take any input data. Also It does not return any data.

The statements inside the task being executed repeatedly as any infinite loop.

This example for an XMega AVR Microcontroller. This task change the status of PIN0 of PORTA , then it wait for 1000ms before next execution.

```c
void task1_app()
{
    // toggle the status of pin 0
     PORTA_OUTTGL = PIN0_bm;
     
     // wait for 1sec before next execution
     TaskWait(1000);
}
```

### Setup The Task
Before start executing the task there is a need to do some configurations or define some variables and set their initial values.

Here is an example of Setup function that set the direction of PIN0 of PORTA as an output.

This setup function will be executed before running the task in the system loop.

```c
void task1_Setup()
{
    // Define Pin 0 of Port A as output
    PORTA_DIRSET = PIN0_bm;
    
}
```

### Register The Task
To run your task, you need to register it in the system.

The best place to register your task is in the OnBoot method. because the framework execute this method before running tasks.

also in this method we call all setup functions for all tasks.

Registering task is done by calling the method Sys_CreateTask.

As in the example we pass the task name as a parameter.

If you need to execute additional tasks just repeat the previous steps.

```c
/*
// This section is part of the file main.c
//
*/
void OnBoot()
{
    // calling the setup function
    task1_Setup();
    
    // Registering Task 1 in the system
    Sys_CreateTask(task1_app);
    
    
    // Registering additional tasks
    Sys_CreateTask(task2_app);
    Sys_CreateTask(task3_app);
    Sys_CreateTask(task4_app);
    .
    .
    .
        
}
```

### That's it.


## How can we support you?
- Star our repository :star:
- For more information please visit the official website https://syrasys.com/
- We're always happy to receive your feedback!

## License

This project is licenced under the [LGPLv3 License](https://opensource.org/licenses/LGPL-3.0).



