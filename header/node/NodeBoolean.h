//
// Created by Myles Harris on 8/23/21.
//

#ifndef CAMELCPP_NODEBOOLEAN_H
#define CAMELCPP_NODEBOOLEAN_H


class NodeBoolean: public Node {
private:
    bool value;

public:
    static NodeBoolean* parseBoolean(string);

    NodeBoolean(bool);

    Value * interpret(RuntimeEnvironment &, RuntimeContext &);

    bool getValue() { return value; }
};


#endif //CAMELCPP_NODEBOOLEAN_H
