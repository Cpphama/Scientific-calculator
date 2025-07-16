#pragma once
#include <string>


namespace input
{
    namespace constants
    {
        constexpr const char pi    = 0;
        constexpr const char g     = 1;
        constexpr const char euler = 2;
    }
    namespace function
    {
        constexpr const char log = 0;
        constexpr const char ln  = 1;
        constexpr const char squreRoot = 17;
        namespace trig
        {
            constexpr const char sin = 2;
            constexpr const char sinsq = 3;
            constexpr const char sinh = 4;
            constexpr const char asin = 5;
            constexpr const char asinsq = 6;

            constexpr const char cos   = 7;
            constexpr const char cossq = 8;
            constexpr const char cosh  = 9;
            constexpr const char acos = 10;
            constexpr const char acossq = 11;  

            constexpr const char tan = 12;
            constexpr const char tansq= 13;
            constexpr const char tanh = 14;
            constexpr const char atan = 15;
            constexpr const char atansq = 16; 

        }
    
    }
    namespace parenthesis
    {
       constexpr const char openingPar = 0;
       constexpr const char closingPar = 1; 
    }

    namespace oprands
    {
        constexpr const char clear          = 0;
        constexpr const char point          = 1;
        constexpr const char addition       = 2;
        constexpr const char subtraction    = 3;
        constexpr const char multiplication = 4;
        constexpr const char division       = 5;
        constexpr const char model          = 6;
        constexpr const char backspace      = 7;
        constexpr const char equals         = 8;
        constexpr const char power          = 9;
    }
    
}


struct InputBuffer
{
    InputBuffer() : 
    buffer{""},alreadyUsedPoint{false}{}
    
    ~InputBuffer() = default;
    std::string buffer;
    bool alreadyUsedPoint;
};





class LogicParser
{
    public:
    LogicParser() = default;
    ~LogicParser() = default;
    
    void pushNumber(const char * input);
    void pushOperand(const char input);
    void pushConstants(const char input);
    void pushparenthesis(const char input);
    void pushFunction(const char input);

    std::string returnEqAndInter();
    
    
    std::string equation ="";
    std::string result   ="";
    bool ismodeDeg = true; // ture for deg false for rad
    
    private:
    
    InputBuffer m_intermidateBuffer;
    int  m_numsOfRightParenthesis{0};
    int  m_numsOfLeftParenthesis {0};
    bool m_theTailIsTroublesome      = false;
    bool m_lockInputAfterSyntaxError = false;
    
    
    
   void sanatizeEquationTail();
   void dumpBufferToEquation();
   void evaluteResult();
   void log();
   
};

