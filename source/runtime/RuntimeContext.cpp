#include "../../header/runtime/RuntimeContext.h"

RuntimeContext::RuntimeContext(RuntimeContext* &parentContext, vector<Value*> &argumentList)
: parentContext(parentContext), argumentList(argumentList) {}

RuntimeContext::RuntimeContext(RuntimeContext* &parentContext) : parentContext(parentContext) {
    this->argumentList = vector<Value*>();
}

Field* RuntimeContext::accessField(vector<string> &accessedPath) {
    Field* accessedField = getField(accessedPath[0]);

    if (accessedField == nullptr) {
        if (parentContext == nullptr) return nullptr;
        return parentContext->accessField(accessedPath);
    }

    if (accessedPath.size() == 1) return accessedField;

    vector<string> accessedPath2 = { accessedPath.begin() + 1, accessedPath.end() };

    return accessedField->getValue()->accessField(accessedPath2);
}

Field* RuntimeContext::createField(string createdName, Value* createdValue) {
    Field* accessedField = getField(createdName);

    if (accessedField != nullptr) throw "FieldExists";

    Field* createdField = new Field(createdName, createdValue);

    fieldList.push_back(createdField);

    return createdField;
}

Field* RuntimeContext::getField(string fieldName) {
    for (Field* field : fieldList)
        if (field->getName() == fieldName) return field;

    return nullptr;
}

Value *RuntimeContext::getArgument() {
    if (argumentList.size() == 0)
        throw "NoArguments";

    Value* argument = argumentList[0];
    argumentList = { argumentList.begin() + 1, argumentList.end() };

    return argument;
}

bool RuntimeContext::hasArgument() {
    return !argumentList.empty();
}
