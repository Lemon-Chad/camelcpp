#include "../native/Function.cpp"

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

class PrintLineFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, vector<Value*> &arguments) override {
        RuntimeContext* parentContext = environment.getContext();
        RuntimeContext context = RuntimeContext(parentContext, arguments);

        if (context.hasArgument())
            cout << context.getArgument()->toString();

        while (context.hasArgument())
            cout << " " << context.getArgument()->toString();

        cout << endl;

        return nullptr;
    }
};

class InputFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, vector<Value*> &arguments) override {
        string input;
        cin >> input;

        return new LiteralString(input);
    }
};

class InputLineFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, vector<Value*> &arguments) override {
        string inputLine;
        getline (cin, inputLine);


        return new LiteralString(inputLine);
    }
};

class ReturnFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, vector<Value*> &arguments) override {
        return new LiteralReturn(arguments[0]);
    }
};

class ParseIntFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, vector<Value*> &arguments) override {
        return new LiteralInteger(stoi(arguments[0]->toString()));
    }
};

class ParseDecFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, vector<Value*> &arguments) override {
        return new LiteralDecimal(stof(arguments[0]->toString()));
    }
};

class ParseStrFunction: public Function {

public:
    Value* invokeFunction(RuntimeEnvironment &environment, vector<Value*> &arguments) override {
        return new LiteralString(arguments[0]->toString());
    }
};