#include "../../header/runtime/Interpreter.h"
#include "Field.cpp"
#include "RuntimeEnvironment.cpp"
#include "RuntimeContext.cpp"
#include "../function/DefinedFunction.cpp"
#include "../function/Function.cpp"
#include "../function/Instance.cpp"
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

    statement.interpret(environment, *context);
}