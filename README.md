# Camel Programming Language in C++

Camel programming language c++ implementation.
Work in progress.

## Some Quick Documentation
Documentation is still being worked on. This should help you to be able to create simple Camel programs.

## Built-in Functions
Work in progress. More coming soon.
<br>`print(arguments...)`
<br>`printLine(arguments...)`

<br>`input()`
<br>`inputLine()`

<br>`int(argument)`
<br>`dec(argument)`
<br>`str(argument)`

### Variable Declaration
```
!variableName(variableExpression)
```

Example:
```
!bestProgrammingLanguage("Camel")
!someNumber(5 + 10)
```

### Function Declaration
```
!functionName {
    functionStatements    
}
```
In Camel, parameters are not implemented into the function signature. Instead you can access parameters iteratively using the `param` keyword.
Example:
```
!sayHello {
    print("Hello," param)
}
sayHello("Programmer")
```

### Variable Assignment
The same as variable declaration but without the `!`.
```
!variable(5)
variable(variable + 10)
```

### Function Invocation
The same as variable assignment!
```
print("Hello World!")
```

### Conditional Statements
Used to implement branch logic.
```
if (condition) then {

}
or if (condition) then {

}
or {

}
```

### Loop Statements
Used to implement while loops.
```
loop (condition) then {

}
```

### Classes
Classes are super simple! They are exactly the same except for a `return(self)`.
```
!Person {
    !name(param)

    !sayHello {
        print("Hello", name)
    }

    return(self)
}
!variablePerson(Person("Mastadons"))
variablePerson.sayHello()
```

### Static Blocks
Static fields do not exist in Camel. Instead you can declare a group of static fields with a static block. Static fields can be accessed without initializing an instaance.
```
!!FUNNY_STATIC_BLOCK {
    !funnyFunction {
        print("Funny!")
    }
}
FUNNY_STATIC_BLOCK.funnyFunction()
```

#### Enumerations
Static blocks can be used to create enumerations.
```
!Color {
    !r(param)
    !g(param)
    !b(param)

    return(self)
}

!!COLORS {
    !red(Color(255, 0, 0))
    !orange(Color(255, 165, 0))
    !green(Color(0, 255, 0))
}
```

### Format Strings
```
"Hello \{name}"
```