class PrintFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, RuntimeContext &context) {
        while (context.hasArgument())
            cout << context.getArgument()->toString();

        return nullptr;
    }
};