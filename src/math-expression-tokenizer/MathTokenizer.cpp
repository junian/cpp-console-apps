#include <iostream>

using namespace std;

bool isAlphabet(char chr)
{
    return ((chr >= 'a' && chr <= 'z') ||
            (chr >= 'A' && chr <= 'Z') ||
            chr == '$' || chr == '_');
}

bool isNumber(char chr)
{
    return (chr >= '0' && chr <= '9');
}

bool isOperator(char chr)
{
    return (chr == '+' || chr == '-' || chr == '/' || chr == '*' || chr == '^');
}

bool isBranch(char chr)
{
    return (chr == '(' || chr == ')');
}

bool isNull(char chr)
{
    return chr == '\0';
}

bool isSpace(char chr)
{
    return chr == ' ';
}

typedef struct MathTokenizer
{
    // the expression string
    string str;
    // pointer of char of expression
    char *pointer;

    // reset pointer to the first character of the expression
    void reset()
    {
        pointer = &str.at(0);
    }

    // get token from expression
    string getToken()
    {
        string result = "";

        // if pointer is null then end this process
        if (isNull(*pointer))
        {
            return "";
        }
        // if pointer is space then check next
        // ignore spaces
        else if (isSpace(*pointer))
        {
            pointer++;
            while (true)
            {
                if (isNull(*pointer))
                {
                    return "";
                }
                else if (isSpace(*pointer))
                {
                    pointer++;
                }
                else
                {
                    break;
                }
            }
        }

        // if operator or branch
        if (isOperator(*pointer) || isBranch(*pointer))
        {
            result = *pointer;
            pointer++;
        }
        // if variable / alphabet
        else if (isAlphabet(*pointer))
        {
            result = *pointer;
            pointer++;
            while (true)
            {
                if (isAlphabet(*pointer) || isNumber(*pointer))
                {
                    result += *pointer;
                }
                else
                {
                    break;
                }
                pointer++;
            }
        }
        // if number
        else if (isNumber(*pointer))
        {
            result = *pointer;
            pointer++;
            while (true)
            {
                if (isNumber(*pointer))
                {
                    result += *pointer;
                }
                else
                {
                    break;
                }
                pointer++;
            }
        }

        return result;
    }
} MathTokenizer;

int main()
{
    MathTokenizer exp;
    string s;

    while (true)
    {

        // input expression
        getline(cin, exp.str);
        exp.reset();

        // show tokens
        while ((s = exp.getToken()) != "")
        {
            cout << s << endl;
        }
    }

    return 0;
}
