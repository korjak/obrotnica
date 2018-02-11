#include <iostream>

using namespace std;

class Car {
public:
    int value;
    Car *next;
    Car(int value) {
        this->value = value;
    }
    void setNext(Car *next) {
        this->next = next;
    }
    Car* getNext() {
        return next;
    }
    int getValue() const {
        return value;
    }
};

class Stack {
    int stackSize;
    Car *topCar;
    Car *tempNew;
public:
    Stack()
    {
        this->stackSize = 0;
    }
    void pop() {
        if (stackSize > 1)
        {
            topCar = topCar->getNext();
        }
        else {
            topCar = nullptr;
        }
        stackSize--;
    }
    void push(Car value) {
        if(stackSize == 0) {
            topCar = new Car(value.value);
            topCar->setNext(nullptr);
        }
        else {
            tempNew = new Car(value.value);
            tempNew->setNext(topCar);
            topCar = tempNew;
        }
        stackSize++;
    }
    void push(int value) {
        if(stackSize == 0) {
            makeCar(value, &tempNew);
            topCar = tempNew;
            topCar->setNext(nullptr);
        }
        else {
            makeCar(value, &tempNew);
            tempNew->setNext(topCar);
            topCar = tempNew;
        }
        stackSize++;
    }
    bool empty() {
        if(stackSize==0) {
            return true;
        }
        else {
            return false;
        }
    }
    int size() {
        return stackSize;
    }
    Car top() {
        return *topCar;
    }
    void makeCar(int value, Car **tempNew) {
        *tempNew = new Car(value);
    }
};

ostream& operator<<(ostream& ostr, const Car& car) {
    ostr << car.getValue();
    return ostr;
}

int main() {
    int railsAmount, onRailAmount, tempCar, instructionsAmount, instructionValue;
    int turnPtr = 0;
    int iter = 0;
    int temp = 0;
    char comm;
    Stack turn;
    Stack tmp;
    cin >> railsAmount;
    Stack *rail = new Stack[railsAmount];
    for(int i = 0; i < railsAmount; i++) {
        cin >> onRailAmount;
        for(int j = 0; j < onRailAmount; j++) {
            cin >> tempCar;
            rail[i].push(tempCar);
        }
        while(!rail[i].empty()) {
            tmp.push(rail[i].top());
            rail[i].pop();
        }
        rail[i] = tmp;
        if(!tmp.empty()) {
            while(!tmp.empty()) {
                tmp.pop();
            }
        }
    }
    cin >> instructionsAmount;
    for(int i = 0; i < instructionsAmount; i++) {
        cin >> comm;
        switch(comm) {
            case 'z': {
                cin >> instructionValue;
                turnPtr += instructionValue % railsAmount;
                while(turnPtr >= railsAmount) {
                    turnPtr -= railsAmount;
                }
                break;
            }
            case 'o': {
                cin >> instructionValue;
                turnPtr -= instructionValue % railsAmount;
                if(turnPtr < 0) {
                    turnPtr += railsAmount;
                }
                break;
            }
            case 'w': {
                cin >> instructionValue;
                if(rail[turnPtr].size()==0) {
                    break;
                }
                else if(turn.size()==10) {
                    break;
                }
                else if(instructionValue > (10-turn.size())) {
                    while((!rail[turnPtr].empty())&&(turn.size()<10)) {
                        turn.push(rail[turnPtr].top());
                        rail[turnPtr].pop();
                    }
                    break;
                }
                else {
                    while((turn.size()<=10)&&(!rail[turnPtr].empty())&&(iter<instructionValue)) {
                        turn.push(rail[turnPtr].top());
                        rail[turnPtr].pop();
                        iter++;
                    }
                    iter = 0;
                    break;
                }
            }
            case 'j': {
                cin >> instructionValue;
                if(turn.size()==0) {
                    break;
                }
                else if(turn.size()<instructionValue) {
                    while(!turn.empty()) {
                        rail[turnPtr].push(turn.top());
                        turn.pop();
                    }
                    break;
                }
                else {
                    while(iter<instructionValue) {
                        rail[turnPtr].push(turn.top());
                        turn.pop();
                        iter++;
                    }
                    iter = 0;
                    break;
                }
            }
        }
    }
    cout << turn.size();
    while(!turn.empty()) {
        cout << " ";
        cout << turn.top();
        turn.pop();
    }
    cout << endl;
    temp = turnPtr;
    for(int i = 0; i < railsAmount; i++) {
        cout << rail[temp].size();
        while(!rail[temp].empty()) {
            cout << " ";
            cout << rail[temp].top();
            rail[temp].pop();
        }
        temp++;
        if(temp==railsAmount) {
            temp = 0;
        }
        cout << endl;
    }
    delete[] rail;
    return 0;
}