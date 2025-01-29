#pragma once

#include <vector>
#include "./logger/logger.hh"

//* Executable Class
class MyClass {
    private:
        int value = 42;
		std::vector<int> numbers;

    public:
        int Add (int value) {
            this->value += value;

            LOG_DEBUG ("Called: MyClass::Add (" << value << ")");
			LOG_DEBUG ("  ==> value: " << this->value);

            return this->value;
        }

		void PushNumber (int value) {
			this->numbers.push_back (value);

			LOG_DEBUG ("Called: MyClass::PushNumber (" << value << ")");
			LOG_DEBUG ("  -> current numbers: " << this->numbers.size());
		}
};

//* AE Definition
struct MyClassDef {
	int (MyClass::*Add) (int);
	void (MyClass::*PushNumber) (int);
};

class FunctionPointerMenager {
	private:
		MyClass *target;
		MyClassDef functions;

	public:
		FunctionPointerMenager (MyClass *obj, MyClassDef &funcs) : target(obj), functions(funcs) { }

		int executeAdd (int x) {
			if (target && functions.Add) {
				return (target->*functions.Add)(x);
			}

			return -1;
		}

		void executePushNumber (int x) {
			if (target && functions.PushNumber) {
				return (target->*functions.PushNumber)(x);
			}
		}
};

//* Main
class MyClassRunner {
	public:
		void run() {
			MyClass instance;
			MyClassDef classDef;

			classDef.Add = &MyClass::Add;
			classDef.PushNumber = &MyClass::PushNumber;
			FunctionPointerMenager manager (&instance, classDef);

			manager.executeAdd (5);  // 42 + 5 => 47
			manager.executeAdd (3);  // 47 + 3 => 50

			manager.executePushNumber (1);  // 1
			manager.executePushNumber (2);  // 2
			manager.executePushNumber (3);  // 3
		}
};
