#include "logic.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <cstdint>
#include <stack>
#include <cmath>
#include <fstream>

template<typename T> void print(T && info)
{
    std::cout << '\n' << info << "\n";
}

template<typename T,typename J> void print(T&& info, J&& secondinfo)
{
    std::cout << '\n' << info << " " << secondinfo << "\n";
}








struct Token
{
    enum Type{NUMBER,OPERATOR,CONSTANT,FUNCTION,RIGHTPARENTHESIS,LEFTPARENTHESIS,UNARY_MINUS,INVALID};
    Type type;
    std::string value;
};










std::vector<Token> tokenzieEquation(const std::string & equation);
bool checkForSyntaxError(const std::vector<Token>& tokens);
std::vector<Token> toPostfix(const std::vector<Token>& tokens);
std::string evaluatePostfix(const std::vector<Token>& tokens,const bool& mod);
std::string getResult(const std::vector<Token>& tokens,const bool& mod);
int getPrecedence(const Token& type);
bool checkForPi(const std::string& equatio,size_t howManyBytesBack);
std::string replacePi(const std::string&  equation);
bool checkForFunctions(const std::string& equation);
void logResult(const std::string& equation);


bool isOddDenominatorFraction(double exp)
{
    constexpr double eps = 1e-10;
    // Check if exp ≈ n/d where d is odd (simplified)
    // Try small odd denominators (1, 3, 5, 7, 9)
    for (int d : {1, 3, 5, 7, 9}) {
        double n = exp * d;
        double n_rounded = std::round(n);
        if (std::abs(n - n_rounded) < eps) {
            return true;  // exp ≈ n_rounded/d, and d is odd
        }
    }
    return false;
}



std::string LogicParser::returnEqAndInter()
{
    return (equation + m_intermidateBuffer.buffer);
}




void LogicParser::pushNumber(const char * input)
{
    if(m_lockInputAfterSyntaxError)return;
    if(!result.empty()){result.clear();equation.clear();}
    m_intermidateBuffer.buffer.append(input);
    log(); 
}



void LogicParser::pushConstants(const char input)
 {
    if(m_lockInputAfterSyntaxError)return;
    if(m_intermidateBuffer.alreadyUsedPoint)return;
    if(!result.empty()){result.clear();equation.clear();}
    if(input == input::constants::euler){m_intermidateBuffer.buffer.append("e");}
    if(input == input::constants::g){m_intermidateBuffer.buffer.append("g");}
    if(input == input::constants::pi){m_intermidateBuffer.buffer.append("π");}
    log();
 }




void LogicParser::pushOperand(const char input)
{
    if(input != input::oprands::clear && m_lockInputAfterSyntaxError)return;
    
    switch(input)
    {
        case input::oprands::clear:
        {
            m_lockInputAfterSyntaxError = false;
            m_intermidateBuffer.buffer.clear();
            m_theTailIsTroublesome = false;
            result.clear();
            equation.clear();
            m_intermidateBuffer.alreadyUsedPoint = false;
            m_numsOfRightParenthesis= 0;
            m_numsOfLeftParenthesis = 0;
            return;
        }
        break;
        case input::oprands::point:
        {  
            char lastCharcter = m_intermidateBuffer.buffer.empty() ? '\0' : m_intermidateBuffer.buffer.back();
            if (!m_intermidateBuffer.alreadyUsedPoint && !m_intermidateBuffer.buffer.empty() && m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 1] != '.' &&
                (lastCharcter >= '0' && lastCharcter <= '9'))
            {
                
                m_intermidateBuffer.alreadyUsedPoint = true;
                m_intermidateBuffer.buffer.append(".");
                log();
            }
        }
        break;
        case input::oprands::model:
        {   
            
            if(!m_intermidateBuffer.buffer.empty()){dumpBufferToEquation();}
            bool hasAFuncBefore = checkForFunctions(equation);
            if(!result.empty()){equation.append(result);result.clear();}
            if(hasAFuncBefore)return;
            char lastCharcter = equation.back();
            if (((lastCharcter >= '0' && lastCharcter <= '9') 
            || (lastCharcter == 'g' || checkForPi(equation,0) || lastCharcter == 'e' || lastCharcter == ')')))
            {
                equation.append("%");
                log();
            }
        }
        break;
        case input::oprands::addition:
        {   
            if(!m_intermidateBuffer.buffer.empty()){dumpBufferToEquation();}
            bool hasAFuncBefore = checkForFunctions(equation);
            if(!result.empty()){equation.append(result);result.clear();}
            if(hasAFuncBefore)return;
            const char lastCharcter = equation.back();
            if (((lastCharcter >= '0' && lastCharcter <= '9') 
            || (lastCharcter == 'g' || checkForPi(equation,0) || lastCharcter == 'e' || lastCharcter == ')')))
            {
                equation.append("+");
                log();
            }
        }
        break;
        case input::oprands::subtraction:
        {   
            bool hasAFuncBefore = checkForFunctions(equation);
            if(hasAFuncBefore)return;
            if(!m_intermidateBuffer.buffer.empty()){dumpBufferToEquation();}
            if(!result.empty()){equation.append(result);result.clear();}
            
                equation.append("-");
                log();
            
        }
        break;
        case input::oprands::multiplication:
        {
            if(!m_intermidateBuffer.buffer.empty()){dumpBufferToEquation();}
            if(!result.empty()){equation.append(result);result.clear();}
            char lastCharcter = equation.back();
            if (((lastCharcter >= '0' && lastCharcter <= '9') 
            || (lastCharcter == 'g' || checkForPi(equation,0) || lastCharcter == 'e' || lastCharcter == ')')))
            {
                equation.append("x");
                log();
            }
        }
        break;
        case input::oprands::division:
        {
            if(!m_intermidateBuffer.buffer.empty()){dumpBufferToEquation();}
            if(!result.empty()){equation.append(result);result.clear();}
            char lastCharcter = equation.back();
            if (((lastCharcter >= '0' && lastCharcter <= '9') 
            || (lastCharcter == 'g' || checkForPi(equation,0) || lastCharcter == 'e' || lastCharcter == ')')))
            {
                equation.append("/");
                log();
            }
        }
        break;
        case input::oprands::backspace:
        {
            if(m_intermidateBuffer.buffer.empty() && equation.empty())return;
            
            if(!m_intermidateBuffer.buffer.empty())
            {
                char lastCharacter = m_intermidateBuffer.buffer.empty() ? '\0' : m_intermidateBuffer.buffer.back();
                if(lastCharacter == '.')
                {
                    m_intermidateBuffer.alreadyUsedPoint = false;
                    m_intermidateBuffer.buffer.pop_back();
                    log();
                    return;
                }else if(lastCharacter == 'e' || lastCharacter == 'g')
                {
                    if(m_intermidateBuffer.buffer.length()>= 3)
                    {
                        char secondlastCharacter = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                        if(secondlastCharacter == 'o')
                        {
                            m_intermidateBuffer.buffer.pop_back();m_intermidateBuffer.buffer.pop_back();
                            m_intermidateBuffer.buffer.pop_back();
                            m_theTailIsTroublesome = false;
                            log();return;
                        }
                    }
                    m_intermidateBuffer.buffer.pop_back();
                    log();
                    return;

                }else if(checkForPi(m_intermidateBuffer.buffer,0))
                {
                    m_intermidateBuffer.buffer.erase(m_intermidateBuffer.buffer.length() - 2, 2);   
                    log();
                    return;
                }
                else if(lastCharacter == '(')
                {
                    if (m_intermidateBuffer.buffer.length() != 1 && 
                    ((m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 1] == 'e') || 
                    (m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 1] == 'p') || 
                    (m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 1] == 'g')))
                    {
                        m_numsOfLeftParenthesis--;
                        m_intermidateBuffer.buffer.pop_back();
                        log();
                        return;
                    }
                    
                    if(!m_intermidateBuffer.buffer.empty())
                    {
                        m_numsOfLeftParenthesis--;
                        m_intermidateBuffer.buffer.pop_back();
                        log();
                    }
                }
                else if(lastCharacter == ')')
                {
                    m_numsOfRightParenthesis--;
                    m_intermidateBuffer.buffer.pop_back();
                    log();
                    return;
                }
                else if(lastCharacter == 'n')
                {
                    char secondLastChar =  m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                    if(secondLastChar == 'l')
                    {
                        m_intermidateBuffer.buffer.pop_back();m_intermidateBuffer.buffer.pop_back();
                        log();return;
                    }
                }
                else
                {
                    std::cout << " it hits here";
                    m_intermidateBuffer.buffer.pop_back();
                    log();
                    return;
                }
            }else if(!equation.empty())
            {
                char lastCharacter = equation.empty() ? '\0' : equation.back();
                if(lastCharacter == '.')
                {
                    m_intermidateBuffer.alreadyUsedPoint = false;
                    m_theTailIsTroublesome = false;
                    equation.pop_back();
                    log();
                    return;
                }else if(lastCharacter == 'e'  || lastCharacter == 'g')
                {
                    if(equation.length()>= 3)
                    {
                        char secondlastCharacter = equation[equation.length() - 2];
                        if(secondlastCharacter == 'o')
                        {
                            equation.pop_back();equation.pop_back();equation.pop_back();
                            log();
                            m_theTailIsTroublesome = false;return;
                        }
                    }
                    equation.pop_back();
                    log();
                    return;
                }
                else if(checkForPi(equation,0))
                {
                    equation.erase(equation.length() - 2, 2);
                    log();
                    return;
                }
                else if(lastCharacter == '(')
                {
                    m_numsOfLeftParenthesis--;
                    equation.pop_back();
                    log();
                    return;
                }
                else if(lastCharacter == ')')
                {
                    m_numsOfRightParenthesis--;
                    equation.pop_back();
                    log();
                    return;
                }
                else
                {
                    m_theTailIsTroublesome = false;
                    equation.pop_back();log();
                    return;
                    
                }
            }

        }break;
        case input::oprands::equals:
        {   
            dumpBufferToEquation();
            if(equation.empty())return;
            evaluteResult();
        }break;
        case input::oprands::power:
        {
            if(!m_intermidateBuffer.buffer.empty()){dumpBufferToEquation();}
            if(!result.empty()){equation.append(result);result.clear();}
            char lastCharcter = equation.back();
            if (((lastCharcter >= '0' && lastCharcter <= '9') 
            || (lastCharcter == 'g' || checkForPi(equation,0) || lastCharcter == 'e' || lastCharcter == ')')))
            {
                equation.append("^");
                log();
            }
        }
        default: return;
    }
     
 }


void LogicParser::pushFunction(const char input)
{

    switch(input)
    {   
        case input::function::log:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("log");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("log");
            log();
            
        }
            break;
        case input::function::ln:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("ln");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("ln");
            log();
        }
            break;
        case input::function::trig::sin:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("sin");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("sin");
            log();
        }
            break;
        case input::function::trig::sinsq:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("sinsq");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("sinsq");
            log();
        }
            break;
        case input::function::trig::asin:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("asin");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("asin");
            log();
        }
            break;
        case input::function::trig::asinsq:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("asinsq");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("asinsq");
            log();
        }
            break;
        case input::function::trig::sinh:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("sinh");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("sinh");
            log();
        }
            break;
        case input::function::trig::cos:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("cos");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("cos");
            log();
        }   
            break;
        case input::function::trig::cossq:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("cossq");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("cossq");
            log();
        }   
            break;
        case input::function::trig::acos:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("acos");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("acos");
            log();
        }   
            break;
        case input::function::trig::acossq:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("acossq");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("acossq");
            log();
        }   
            break;
        case input::function::trig::cosh:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("cosh");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("cosh");
            log();
        }   
            break;
        case input::function::trig::tan:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("tan");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("tan");
            log();
        }
            break;
        case input::function::trig::tansq:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("tansq");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("tansq");
            log();
        }
            break;
        case input::function::trig::atan:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("atan");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("atan");
            log();
        }
            break;
        case input::function::trig::atansq:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("atansq");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("atansq");
            log();
        }
            break;
        case input::function::trig::tanh:
        {
            char lastCharcter = m_intermidateBuffer.buffer.back();
            
            if(lastCharcter == '\0')
            {
                m_intermidateBuffer.buffer.append("tanh");
                return;
            }
            else if(m_intermidateBuffer.buffer.size() >= 3)
            {
                char secondLastChar = m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 2];
                if(lastCharcter == 'g' && secondLastChar == 'o')return;
                
            }
                if(lastCharcter == 'n')return;
                if(lastCharcter == 'h')return;
                if(lastCharcter == 's')return;
                if(lastCharcter == 'q')return;
            
            m_intermidateBuffer.buffer.append("tanh");
            log();
        }
            break;
        default:
            return;
    }
}






void LogicParser::dumpBufferToEquation()
{
    if(!m_intermidateBuffer.buffer.empty())
    {
        equation.append(m_intermidateBuffer.buffer);
        m_intermidateBuffer.buffer.clear();
        m_intermidateBuffer.alreadyUsedPoint = false;
    }
    
}


void LogicParser::pushparenthesis(const char input)
{
    if(!result.empty()){result.clear();}
    if(m_lockInputAfterSyntaxError)return;
    switch (input)
    {
    case input::parenthesis::openingPar:
        m_intermidateBuffer.buffer.append("(");m_numsOfLeftParenthesis++;
        if(m_intermidateBuffer.buffer.length() != 1 && ((equation[equation.length() - 1] =='e') 
        || (m_intermidateBuffer.buffer[m_intermidateBuffer.buffer.length() - 1] =='p') || (equation[equation.length() - 1] =='g')))
        {
            log();
            
        }
    break;
    case input::parenthesis::closingPar:
        if(m_numsOfLeftParenthesis > m_numsOfRightParenthesis)
        {
            m_intermidateBuffer.buffer.append(")");m_numsOfRightParenthesis++;
            log();
        }
        
    break;
    }
    
}





void LogicParser::evaluteResult()
{
    if (m_numsOfRightParenthesis != m_numsOfLeftParenthesis)
    {
        m_lockInputAfterSyntaxError = true;
        m_intermidateBuffer.buffer.clear();
        equation = "Syntax Error";
        return;
    }
    else if (equation == "0+0")
    {
        m_lockInputAfterSyntaxError = true;
        m_intermidateBuffer.buffer.clear();
        equation = "Hello World!";
        return;
    }else if(equation == "69")
    {
        m_lockInputAfterSyntaxError = true;
        m_intermidateBuffer.buffer.clear();
        equation = "NICE";
        return;
    }
    else
    {
        
        
            sanatizeEquationTail();
            if (m_theTailIsTroublesome)
            return;
        
        // removing π and replacing it with p
        
      
        std::string temp = replacePi(equation);
        equation = std::move(temp);
            if(equation == "p"){equation = "π";return;}
            std::vector<Token> holder = tokenzieEquation(equation);

        
        if (!checkForSyntaxError(holder))
        {   print("\nissue happend in tokenization\n");
            m_lockInputAfterSyntaxError = true;
            m_intermidateBuffer.buffer.clear();
            equation = "Syntax Error";
            return;
        }
        
        result = getResult(holder,ismodeDeg);
        logResult(result);
        std::cout << "\n\n\n";
        for(const auto& token : holder)
        {
            std::cout << token.value;
            std::cout << "\t : \n";
        }
        equation.clear();
    }
}




std::vector<Token> tokenzieEquation(const std::string& equation)
{
    std::vector<Token> tokens;
    tokens.reserve(20);
    size_t i{0};

    while(i < equation.length())
    { 
        char currentChar = equation[i];
        
       if(isdigit(currentChar) || currentChar == '.')
       {      
           bool skipImplicitMult = false;
            size_t end = i;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }
            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }

            
            

            while(isdigit(equation[end]) || equation[end]=='.')
            {
                end++;
            }

            const std::string strDouble = equation.substr(i, end);
            tokens.push_back(Token{Token::NUMBER,std::move(strDouble)});
            i+= (end - i);
            
        }
       else if(currentChar == 'g'  || currentChar == 'e')
        {
           
            bool skipImplicitMult = false;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }
            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }

            tokens.push_back(Token{Token::CONSTANT,std::string(1,currentChar)});
            i++;
        }
       else if (currentChar == '+' || currentChar == '/' ||
       currentChar == 'x' || currentChar == '^' || currentChar == '%') {
            tokens.push_back(Token{Token::OPERATOR, std::string(1, currentChar)});
            i++;
       }else if(currentChar == '-')
        {
            bool isUnary = false;
            if (i == 0)
            {
                isUnary = true;
            }
            else
            {
                char prevType = equation[i-1];
                if (prevType == '+' || prevType == '-' || prevType == '/' || prevType == '^' 
                    || prevType == '%' || prevType == 'x'|| prevType == '(' || prevType == 'q'
                    || prevType == 'h' || prevType == 'n' || prevType ==  's'
                )
                {
                    isUnary = true;
                }
            }

            if (isUnary)
            {
                tokens.push_back(Token{Token::UNARY_MINUS, "-"});
                i++;
            }
            else
            {
                tokens.push_back(Token{Token::OPERATOR, "-"});
                i++;
            }
        }
       else if(currentChar == '(')
       {
            bool skipImplicitMult = false;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }


            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }
            
            
            
            tokens.push_back(Token{Token::LEFTPARENTHESIS,std::string(1,currentChar)});
            i++;
       }
       else if(currentChar == ')')
       {
            tokens.push_back(Token{Token::RIGHTPARENTHESIS,std::string(1,currentChar)});
            i++;
       }else if(currentChar == 'p')
       {
           bool skipImplicitMult = false;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }


            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }
            tokens.push_back(Token{Token::CONSTANT,std::string(1,'p')});
            i++;
       }
       else if(currentChar == 'l')
       {
            
            bool skipImplicitMult = false;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }


            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }
        
        
        
        
        
            if(equation[i+1] == 'o')
            {
                print("\nhit here in the tokenier\n");
                        const char * mlog= "log";
                        tokens.push_back(Token{Token::FUNCTION,mlog});
                         i+=3;
                continue;
            }else if(equation[i+1] == 'n')
            {
                print("\nhit here in the tokenier\n");
                        const char * mln= "ln";
                        tokens.push_back(Token{Token::FUNCTION,mln});
                         i+=2;
                continue;
            }
       }
       else if(currentChar == 's')
       {
         bool skipImplicitMult = false;
            size_t end = i;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }
            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }


            while(equation[end] == 's' || equation[end] == 'i' || equation[end] == 'n' 
                || equation[end] == 'h' || equation[end] == 'q')
            {

             
                end++;
            }

            const std::string strDouble = equation.substr(i, end);
            tokens.push_back(Token{Token::FUNCTION,std::move(strDouble)});
            i+= (end - i);   
       }
       else if(currentChar == 'c')
       {
          bool skipImplicitMult = false;
            size_t end = i;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }
            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }


            while(equation[end] == 'c' || equation[end] == 'o' || equation[end] == 's' 
                || equation[end] == 'h' || equation[end] == 'q')
            {

             
                end++;
            }

            const std::string strDouble = equation.substr(i, end);
            tokens.push_back(Token{Token::FUNCTION,std::move(strDouble)});
            i+= (end - i); 
       }
       else if(currentChar == 't')
       {
              bool skipImplicitMult = false;
            size_t end = i;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }
            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }


            while(equation[end] == 't' || equation[end] == 'a' || equation[end] == 'n' 
                || equation[end] == 'h' || equation[end] == 'q' || equation[end] == 's')
            {
                end++;
            }

            const std::string strDouble = equation.substr(i, end);
            tokens.push_back(Token{Token::FUNCTION,std::move(strDouble)});
            i+= (end - i); 
       }
       else if (currentChar == 'a')
       {
              bool skipImplicitMult = false;
            size_t end = i;

            if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    skipImplicitMult = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    skipImplicitMult = true;
                }
            }
            if(i != 0 && skipImplicitMult == false && (isdigit(equation[i - 1]) 
            ||  equation[i - 1] == 'g'|| equation[i - 1] == 'e' || 
            equation[i - 1] == 'p' || equation[i - 1] == ')' ))
            {
                tokens.push_back(Token{Token::OPERATOR,std::string (1, 'x')});
            }


            while(equation[end]  == 'a' || equation[end] == 's' || equation[end] == 'i' 
                || equation[end] == 'n' || equation[end] == 'c' || equation[end] == 'o' 
                || equation[end] == 't'  || equation[end] == 'h' || equation[end] == 'q'
            )
            {
                end++;
            }

            const std::string strDouble = equation.substr(i, end);
            tokens.push_back(Token{Token::FUNCTION,std::move(strDouble)});
            i+= (end - i); 
       }
       else
       {
            tokens.push_back(Token{Token::INVALID,std::string(1,'?')});
            i++;
       }
    }    
    

    return tokens;
}












void LogicParser::sanatizeEquationTail()
{
    char lastChar = equation.back();
    if (lastChar == '.' || lastChar == '+' || lastChar == '-' ||
        lastChar == '/' || lastChar == 'x' || lastChar == '%' || lastChar=='^')
    {
        m_theTailIsTroublesome = true;
        std::cout << "incomplete function remove " << lastChar << " from the end \n";
        log();
    }
    else{m_theTailIsTroublesome = false;}
    /*  if(checkForFunctions(equation) && (lastChar != ')' || !isdigit(lastChar) || lastChar != 'e'
        || ;))
    {
        std::cout << "incomplete equation the function must end with a number/constant/closeing par \n";
        m_theTailIsTroublesome = true;
    } */
    
}


void LogicParser::log()
{
    std::cout << equation << m_intermidateBuffer.buffer <<"\n";
}

bool checkForSyntaxError(const std::vector<Token>& tokens)
{
    for(const auto& token : tokens)
    {
        if(token.type == Token::INVALID)
        {
            std::cout << "invaild id happend \n";
            return false;
        }
    }
    return true;
}


std::string getResult(const std::vector<Token>& tokens, const bool& mod)
{   
   std::vector<Token> postFix = toPostfix(tokens);
   return (evaluatePostfix(postFix,mod));

}



int getPrecedence(const Token& type)
{
    switch (type.type)
    {
    case Token::FUNCTION:return 5;
    case Token::UNARY_MINUS: return 4;
    case Token::OPERATOR:
        if(type.value == "^")return 3;
        if(type.value == "x" || type.value == "/")return 2;
        else return 1; // + -
    default: return 0;
    }
}




std::vector<Token> toPostfix(const std::vector<Token>& tokens)
{
    std::vector<Token> output;
    std::stack<Token> opStack;

    for (const Token& token : tokens) {
        if (token.type == Token::NUMBER || token.type == Token::CONSTANT) {
            output.push_back(token);
        }else if(token.type == Token::UNARY_MINUS || token.type == Token::OPERATOR || token.type == Token::FUNCTION) {
            while (!opStack.empty() &&
                   getPrecedence(opStack.top()) >= getPrecedence(token)) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
        else if (token.type == Token::LEFTPARENTHESIS) {
            opStack.push(token);
        }
        else if (token.type == Token::RIGHTPARENTHESIS) {
            while (!opStack.empty() && opStack.top().type != Token::LEFTPARENTHESIS) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // pop the '('
        }
    }

    while (!opStack.empty()) {
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}

std::string evaluatePostfix(const std::vector<Token>& postfix,const bool& mod)
{
    std::stack<double> evalStack;

    for (const Token& token : postfix) {
        if (token.type == Token::NUMBER) {
            evalStack.push(std::stod(token.value));
        }
        else if (token.type == Token::CONSTANT) {
            if (token.value == "e") evalStack.push(2.718281828);// euler
            else if (token.value == "g") evalStack.push(9.80665); // gravity
            else if (token.value  == "p")evalStack.push(3.14159265); //pi
        }
        else if (token.type == Token::UNARY_MINUS)
        {
            if (evalStack.empty())
                return "Syntax Error";
            double value = evalStack.top();
            evalStack.pop();
            evalStack.push(-value);
        }
        else if (token.type == Token::OPERATOR) {
            if (evalStack.size() < 2) return "Syntax Error";
            double b = evalStack.top(); evalStack.pop();
            double a = evalStack.top(); evalStack.pop();

            if (token.value == "+") evalStack.push(a + b);
            else if (token.value == "-") evalStack.push(a - b);
            else if (token.value == "x" || token.value == "*") evalStack.push(a * b);
            else if (token.value == "/") {
                if (b == 0) return "Math Error";
                evalStack.push(a / b);
            }else if(token.value == "^")
            {
                

                if (a == 0 && b < 0)
                    return "Math Error"; // 0^-1 is undefined
                if (a < 0 && !isOddDenominatorFraction(b)) return "Math Error";
                
                bool isBaseNegative = a < 0 ? true : false;


                if(!isOddDenominatorFraction(b))
                {
                    if(isBaseNegative)
                    {
                        a *= -1;
                    }
                    double result = std::pow(a,b);

                    if(isBaseNegative)result*=-1;
                    
                    evalStack.push(std::move(result));
                    continue;
                }else
                {
                    print("hit here awwdawa");
                    if(isBaseNegative)
                    {
                        a *= -1;
                    }
                    double result = std::pow(a,b);
                    if(isBaseNegative)result*=-1;

                    evalStack.push(std::move(result));
                    continue;
                }
                
               

            }
            else if (token.value == "%") {
                evalStack.push(std::fmod(a, b));
            }
        }else if(token.type == Token::FUNCTION)
        {
            double value = evalStack.top();evalStack.pop();
            if(token.value == "log")
            {
                if(value <= 0)return "infinity";
                evalStack.push(std::log10(value));
            }else if(token.value =="ln")
            {
                if(value <= 0)return "infinity";
                evalStack.push(std::log(value));
            }else if(token.value == "sin")
            {
                if(mod == true)
                {
                    evalStack.push((std::sin(value / (180 / 3.14159265))) );//convert to deg
                }else if(mod == false)
                {
                    evalStack.push(std::sin(value));
                }
            }else if(token.value == "sinsq")
            {
               if(mod == true)
                {
                    evalStack.push(
                        (std::sin(value / (180 / 3.14159265)))
                        * (std::sin(value / (180 / 3.14159265)))
                    );//convert to deg
                }else if(mod == false)
                {
                    evalStack.push(
                        std::sin(value) * std::sin(value)
                           
                    );
                }
            }else if(token.value == "sinh")
            {
                evalStack.push(std::sinh(value));
        
            }else if(token.value == "asin")
            {
                if((value > 1) || (value < -1))
                {
                    return "Domain Error";
                }
                
                if(mod)
                {
                    evalStack.push(   (std::asin(value)) * (180 / 3.14159265));
                }else if(!mod)
                {
                    evalStack.push(std::asin(value));
                }

            }else if(token.value == "asinsq")
            {
                if(value > 1 || value < -1)
                {
                    return "Domain Error";
                }
                
                if(mod)
                {
                    evalStack.push(   ( (std::asin(value)) * (std::asin(value))) * (180 / 3.14159265));
                }else if(!mod)
                {
                    evalStack.push(( (std::asin(value)) * (std::asin(value))));
                    
                }
            }else if(token.value == "cos")
            {
                if(mod == true)
                {
                    evalStack.push((std::cos(value / (180 / 3.14159265))) );//convert to deg
                }else if(mod == false)
                {
                    evalStack.push(std::cos(value));
                }
            }else if(token.value == "cossq")
            {
                if(mod == true)
                {
                    evalStack.push(
                        (std::cos(value / (180 / 3.14159265)))
                        * (std::cos(value / (180 / 3.14159265)))
                    );//convert to deg
                }else if(mod == false)
                {
                    evalStack.push(
                        std::cos(value) * std::cos(value)
                           
                    );
                }
            }else if(token.value == "acos")
            {
                if(value > 1 || value < -1)
                {
                    return "Domain Error";
                }
                
                if(mod)
                {
                    evalStack.push(   (std::acos(value)) * (180 / 3.14159265));
                }else if(!mod)
                {
                    evalStack.push(std::acos(value));
                }
            }else if(token.value == "acossq")
            {
                if(value > 1 || value < -1)
                {
                    return "Domain Error";
                }
                
                if(mod)
                {
                    evalStack.push(   ( (std::acos(value)) * (std::acos(value))) * (180 / 3.14159265));
                }else if(!mod)
                {
                    evalStack.push(( (std::acos(value)) * (std::acos(value))));
                    
                }
            }else if(token.value == "cosh")
            {
                evalStack.push(std::cosh(value));
            }else if(token.value == "tan")
            {
                if(mod == true)
                {

                    if(std::fmod((std::abs(value)),180.0) == 90.0)
                    {
                        return "Math Error";
                    }
                    evalStack.push((std::tan(value / (180 / 3.14159265)))); // convert to deg
                }else if(mod == false)
                {
                    if(std::fmod((std::abs(value)),3.14159265) == 1.57079632)
                    {                                      
                        return "Math Error";
                    }
                    evalStack.push(std::tan(value));
                }
            }else if(token.value == "tansq")
            {
                if(mod == true)
                {

                    if(std::fmod((std::abs(value)),180.0) == 90.0)
                    {
                        return "Math Error";
                    }
                    evalStack.push(
                        (std::tan(value / (180 / 3.14159265)))
                        *  (std::tan(value / (180 / 3.14159265)))
                    ); // convert to deg
                }else if(mod == false)
                {
                    if(std::fmod((std::abs(value)),3.14159265) == 1.57079632)
                    {                                      
                        return "Math Error";
                    }
                    evalStack.push(std::tan(value) * std::tan(value));
                }
            }else if(token.value == "tanh")
            {
                evalStack.push(std::tanh(value));
            }else if(token.value == "atan")
            {
                if(mod == true)
                {
                    evalStack.push((std::atan(value / (180 / 3.14159265)))); // convert to deg
                }else if(mod == false)
                {
                    evalStack.push(std::atan(value));
                }
            }else if(token.value == "atansq")
            {
                if(mod == true)
                {
                    evalStack.push((std::atan2(value / (180 / 3.14159265),0.0))); // convert to deg
                }else if(mod == false)
                {
                    evalStack.push(std::atan2(value,0));
                }
            }


            /**/}   
    }

    if (evalStack.size() != 1) return "Syntax Error";


    std::string temp = std::to_string(evalStack.top());

    while(temp.back() == '0' || temp.back() == '.')
    {
        if(temp.back() == '0')temp.pop_back();
        else if(temp.back() == '.'){temp.pop_back();break;}
    }

    return temp;
}




bool checkForPi(const std::string& equation,size_t howManyBytesBack)
{
    if(howManyBytesBack < 2 && howManyBytesBack == 0){std::cout << "\n waring pi is 2 bytes big it must be 2 or more!\n";}
     if (equation.length() >= 2 + howManyBytesBack)
    {
        bool foundPi =  equation.substr(equation.length() - 2  - howManyBytesBack) == "π" ? true : false;
        return foundPi;
    }
    return false;
}



std::string replacePi(const std::string& equation)
{
    std::string temp;

    for(size_t i = 0; i < equation.length(); ) {
    // Check for π in UTF-8 (0xCF 0x80)
    if (static_cast<unsigned char>(equation[i]) == 0xCF && static_cast<unsigned char>(equation[i+1]) == 0x80) {
        temp += 'p';
        i += 2;
    } else {
        temp += equation[i++];
    }
}
    print("\ntemp is",temp);
    return temp;
}



bool checkForFunctions(const std::string& equation)
{
    bool foundFunc = false;
        size_t i = equation.length();    
        if(equation.length() >= 2)
            {
                if(equation[i - 1] == 'n' || equation[i - 1] == 'h' || 
                equation[i - 1] == 's' || equation[i - 1] == 'q')
                {
                    foundFunc  = true;
                }
            }
            if(equation.length() >= 3)
            {
                if(equation[i - 2] == 'o')
                {
                    foundFunc = true;
                }
            }
    return foundFunc;
}


void logResult(const std::string & result)
{
    std::ofstream outfile("result.txt",std::ios_base::app);
    if(result == "Math Error" || result == "Syntax Error")return;

    if(outfile)
    {
        outfile << "Result is = " << result << std::endl;
    }


}
