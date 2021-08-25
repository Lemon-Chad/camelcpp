class PrintFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, RuntimeContext &context) {
        if (context.hasArgument())
            cout << context.getArgument()->toString();

        while (context.hasArgument())
            cout << " " << context.getArgument()->toString();

        return nullptr;
    }
};