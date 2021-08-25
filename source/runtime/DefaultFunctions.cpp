class PrintFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, vector<Value*> &arguments) override {
        RuntimeContext* parentContext = environment.getContext();
        RuntimeContext context = RuntimeContext(parentContext, arguments);

        if (context.hasArgument())
            cout << context.getArgument()->toString();

        while (context.hasArgument())
            cout << " " << context.getArgument()->toString();

        return nullptr;
    }
};