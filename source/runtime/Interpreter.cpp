#include "../../header/runtime/Interpreter.h"
#include "Field.cpp"
#include "RuntimeEnvironment.cpp"
#include "RuntimeContext.cpp"
#include "../native/DefinedFunction.cpp"
#include "../native/Function.cpp"
#include "../native/Instance.cpp"
#include "../literal/Literal.cpp"
#include "DefaultFunctions.cpp"

void Interpreter::interpret(NodeCompoundStatement &statement) {
    RuntimeContext* parentContext = nullptr;
    RuntimeContext* context = new RuntimeContext(parentContext);

    RuntimeEnvironment environment = RuntimeEnvironment(context);

    Value* value = nullptr;
    context->createField("none", value);

    Function* printFunction = new PrintFunction();
    context->createField("print", reinterpret_cast<Value *&>(printFunction));

    Function* inputFunction = new InputFunction();
    context->createField("input", reinterpret_cast<Value *&>(inputFunction));

    Function* printLineFunction = new PrintLineFunction();
    context->createField("printLine", reinterpret_cast<Value *&>(printLineFunction));

    Function* inputLineFunction = new InputLineFunction();
    context->createField("inputLine", reinterpret_cast<Value *&>(inputLineFunction));

    Function* returnFunction = new ReturnFunction();
    context->createField("return", reinterpret_cast<Value *&>(returnFunction));

    Function* parseIntFunction = new ParseIntFunction();
    context->createField("int", reinterpret_cast<Value *&>(parseIntFunction));

    Function* parseDecFunction = new ParseDecFunction();
    context->createField("dec", reinterpret_cast<Value *&>(parseDecFunction));

    Function* parseStrFunction = new ParseStrFunction();
    context->createField("str", reinterpret_cast<Value *&>(parseStrFunction));

    statement.interpret(environment, context);
}