#include "../../header/formatstring/NodeFormatString.h"
#include "../formatstring/FormatStringComponent.cpp"

using namespace std;


NodeFormatString::NodeFormatString(vector<FormatStringComponent *> &componentList) : componentList(componentList) {}

Value* NodeFormatString::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    stringstream formatStringStream;

    for (auto & component : componentList)
        formatStringStream << component->interpret(environment, context);

    return new LiteralString(formatStringStream.str());
}
