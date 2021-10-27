#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <fstream>

#define STACK_SIZE 8192
enum YBBInst :uint8_t {
    PtrRMov  = 1,   // > yyb  001
    PtrLMov  = 6,   // < bby  110
    PtrAdd   = 2,   // + yby  010 我真的好喜欢你啊，为了你  我要写YBB语言解释器
    PtrSub   = 5,   // - byb  101
    PtrPrint = 3,   // . ybb  011
    PtrInput = 4,   // , byy  100
    JmpNext  = 0,   // [ yyy  000
    JmpFirst = 7    // ] bbb  111
};

class YBBVirtualMachine {
    std::vector<int8_t>  registers;
    std::vector<YBBInst> instructions;
    std::map<uint, uint> jmpMap;
    uint ptrPos = 0;
    uint instrPos = 0;
public:
    bool parse(const std::string& input){
        // reset VM state
        registers.clear();
        instructions.clear();
        jmpMap.clear();
        ptrPos = 0;
        instrPos = 0;
        std::stack<uint> jmpStarters;
        uint8_t cnt = 0, inst = 0, instCnt = 0;

        for(char c : input){
            cnt++;
            switch (c) {
                case 'y':
                case 'Y':
                    inst += 0;
                    break;
                case 'b':
                case 'B':
                    inst += 1;
                    break;
                default:
                    cnt--;
                    break;
            }
            if(cnt == 3){
                // make a instruction and reset status
                switch (inst) {
                    case JmpNext:
                        jmpStarters.push(instCnt);
                        break;
                    case JmpFirst:
                        if (jmpStarters.empty()){
                            return false;
                        }
                        jmpMap[jmpStarters.top()] = instCnt;
                        jmpMap[instCnt] = jmpStarters.top();
                        jmpStarters.pop();
                        break;
                    default:
                        break;
                }

                instructions.push_back(YBBInst(inst));
                inst = 0;
                cnt = 0;
                instCnt++;
            } else {
                inst <<= 1;
            }
        }
        if (!jmpStarters.empty())
            return false;
        return true;
    }
    void run(){
        //
        registers.reserve(STACK_SIZE);
        while (instrPos < instructions.size()){
            switch (instructions[instrPos]) {
                case PtrRMov:
                    ptrPos++;
                    break;
                case PtrLMov:
                    ptrPos--;
                    break;
                case PtrAdd:
                    registers[ptrPos & (STACK_SIZE - 1)] += 1;
                    break;
                case PtrSub:
                    registers[ptrPos & (STACK_SIZE - 1)] -= 1;
                    break;
                case PtrPrint:
                    putchar(registers[ptrPos & (STACK_SIZE - 1)]);
                    break;
                case PtrInput:
                    registers[ptrPos & (STACK_SIZE - 1)] = getchar();
                    break;
                case JmpNext:
                    if (registers[ptrPos & (STACK_SIZE - 1)] == 0) {
                        instrPos = jmpMap[instrPos] + 1;
                        continue;
                    }
                    break;
                case JmpFirst:
                    instrPos = jmpMap[instrPos];
                    continue;
            }
            instrPos++;
        }
    }
};

void runProgram(const std::string& code) {
    YBBVirtualMachine vm;

    if (vm.parse(code)){
        vm.run();
    } else{
        std::cout << "Code wrong." << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, const char*argv[]) {
    if (argc >= 2){
        std::ifstream ifs(argv[1]);
        if (ifs.is_open()) {
            std::string content((std::istreambuf_iterator<char>(ifs)),
                                (std::istreambuf_iterator<char>()));
            runProgram(content);
        } else{
            std::cout << "File not found." << std::endl;
        }
        return 0;
    }

    std::cout << "Ybb language interpreter V0.1" << std::endl;
    while (true){
        std::string code;
        getline(std::cin, code);
        if (code.empty())
            break;

        runProgram(code);
    }
    return 0;
}
