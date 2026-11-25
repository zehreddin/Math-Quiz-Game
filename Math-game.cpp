#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
using namespace std;

struct stQuestionInf
{
    short Number1InQues;
    short Number2InQues;
    short Optyp;
    short UserAnswer;
    short QuesLevel;
};

struct stQuestionInfoAndCounters
{
    short NumberOfQuestion;
    short CorrcetAnwer = 0;
    short WrongAnswer = 0;
    short QuestionCountr = 0;
    stQuestionInf QuestionInf[10];
};

enum enOperationType
{
    Add = 1,
    Subtract = 2,
    Multiply = 3,
    Divide = 4,
    OpMix = 5
};

enum enQuestionLevel
{
    Easy = 1,
    Medium,
    Hard,
    QuMix
};

// Random Number

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

// Read Number

int ReadNumberFromTo(string Message, int From, int To)
{
    int Number;

    do
    {
        cout << Message;
        cin >> Number;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            Number = From - 1;
        }

        if (Number < From || Number > To)
        {
            cout << "Please enter a number from "
                << From << " to " << To << ".\n";
        }

    } while (Number < From || Number > To);

    return Number;
}

// Read Yes Or No

bool ReadYesNo(string Message)
{
    char Answer;

    do
    {
        cout << Message;
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
            return true;

        if (Answer == 'n' || Answer == 'N')
            return false;

        cout << "Please enter Y or N.\n";

    } while (true);
}

// Get Question Level

enQuestionLevel GetQuestionLevel(int number)
{
    switch (number)
    {
    case 1:
        return Easy;
    case 2:
        return Medium;
    case 3:
        return Hard;
    case 4:
        return QuMix;
    }

    return QuMix;
}

// Get Operation Type

enOperationType GetOperationType(int number)
{
    switch (number)
    {
    case 1:
        return Add;
    case 2:
        return Subtract;
    case 3:
        return Multiply;
    case 4:
        return Divide;
    case 5:
        return OpMix;
    }

    return OpMix;
}

// Mix Operation Type

enOperationType MixOpTyp(int AskOP)
{
    if (AskOP == OpMix)
    {
        return (enOperationType)RandomNumber(Add, Divide);
    }

    return GetOperationType(AskOP);
}

// Concepts Question Level

int ConceptsQuestionLevel(int AskQUSLevel)
{
    switch (GetQuestionLevel(AskQUSLevel))
    {
    case Easy:
        return RandomNumber(1, 10);

    case Medium:
        return RandomNumber(10, 50);

    case Hard:
        return RandomNumber(50, 100);

    case QuMix:
        return RandomNumber(1, 100);
    }

    return RandomNumber(1, 100);
}

// Generate Question

stQuestionInf GenerateQuestion(int AskQUSLevel, enOperationType AskOP)
{
    stQuestionInf QuestionInfo = {};

    QuestionInfo.QuesLevel = GetQuestionLevel(AskQUSLevel);

    QuestionInfo.Number1InQues = ConceptsQuestionLevel(AskQUSLevel);

    QuestionInfo.Number2InQues = ConceptsQuestionLevel(AskQUSLevel);

    QuestionInfo.Optyp = MixOpTyp(AskOP);

    return QuestionInfo;
}

// Read Questions Information

void ReadQuestionInfo(stQuestionInfoAndCounters& QuestionInfoAndCounters)
{
    short AskQUSLevel, AskOP;

    QuestionInfoAndCounters.NumberOfQuestion =
        ReadNumberFromTo("How many questions do you want? ", 1, 10);

    AskQUSLevel =
        ReadNumberFromTo(
            "Choose question level (1: Easy, 2: Medium, 3: Hard, 4: Mixed): ", 1, 4);

    AskOP =
        ReadNumberFromTo(
            "Choose operation type (1: Add, 2: Subtract, 3: Multiply, 4: Divide, 5: Mixed): ", 1, 5);

    for (short i = 0; i < QuestionInfoAndCounters.NumberOfQuestion; i++)
    {
        QuestionInfoAndCounters.QuestionInf[i] =
            GenerateQuestion(AskQUSLevel, (enOperationType)AskOP);
    }
}

// Get Operation Symbol

string GetOperationSymbol(short Optyp)
{
    switch (Optyp)
    {
    case Add:
        return "+";

    case Subtract:
        return "-";

    case Multiply:
        return "*";

    case Divide:
        return "/";
    }

    return "";
}

// Print Question

void PrintQuestion(const stQuestionInfoAndCounters& QuestionInfoAndCounters,
    short QuestionNumber)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << "]\n\n";

    cout << QuestionInfoAndCounters.QuestionInf[QuestionNumber].Number1InQues;

    cout << " " << GetOperationSymbol(
        QuestionInfoAndCounters.QuestionInf[QuestionNumber].Optyp) << " ";

    cout << QuestionInfoAndCounters.QuestionInf[QuestionNumber].Number2InQues;

    cout << " = ";
}

// Get Correct Answer

int GetCorrectAnswer(const stQuestionInfoAndCounters& QuestionInfoAndCounters,
    short QuestionNumber)
{
    short Number1 =
        QuestionInfoAndCounters.QuestionInf[QuestionNumber].Number1InQues;

    short Number2 =
        QuestionInfoAndCounters.QuestionInf[QuestionNumber].Number2InQues;

    short Optyp =
        QuestionInfoAndCounters.QuestionInf[QuestionNumber].Optyp;

    switch (Optyp)
    {
    case Add:
        return Number1 + Number2;

    case Subtract:
        return Number1 - Number2;

    case Multiply:
        return Number1 * Number2;

    case Divide:
        return Number1 / Number2;
    }

    return 0;
}

// Check Answer

bool CheckAnswer(const stQuestionInfoAndCounters& QuestionInfoAndCounters,
    short QuestionNumber)
{
    return QuestionInfoAndCounters.QuestionInf[QuestionNumber].UserAnswer ==
        GetCorrectAnswer(QuestionInfoAndCounters, QuestionNumber);
}

// Print Wrong Answer

void PrintWrongAnswer(const stQuestionInfoAndCounters& QuestionInfoAndCounters,
    short QuestionNumber)
{
    cout << "\033[31m";

    cout << "Wrong Answer!";
    cout << "\nThe Correct Answer is: "
        << GetCorrectAnswer(QuestionInfoAndCounters, QuestionNumber);

    cout << "\033[0m" << endl;
}

// Read User Answer

void ReadUserAnswer(stQuestionInfoAndCounters& QuestionInfoAndCounters,
    short QuestionNumber)
{
    QuestionInfoAndCounters.QuestionInf[QuestionNumber].UserAnswer =
        ReadNumberFromTo("", -10000, 10000);
}

// Update Answer Counters

void UpdateAnswerCounters(stQuestionInfoAndCounters& QuestionInfoAndCounters,
    short QuestionNumber)
{
    if (CheckAnswer(QuestionInfoAndCounters, QuestionNumber))
    {
        QuestionInfoAndCounters.CorrcetAnwer++;
    }
    else
    {
        QuestionInfoAndCounters.WrongAnswer++;
    }

    QuestionInfoAndCounters.QuestionCountr++;
}

// Print Answer Result

void PrintAnswerResult(const stQuestionInfoAndCounters& QuestionInfoAndCounters,
    short QuestionNumber)
{
    if (CheckAnswer(QuestionInfoAndCounters, QuestionNumber))
    {
        cout << "\033[32mCorrect Answer!\033[0m\n";
    }
    else
    {
        PrintWrongAnswer(QuestionInfoAndCounters, QuestionNumber);
    }
}

// Print Final Result Header

void PrintFinalResultHeader()
{
    cout << "\n================================\n";
    cout << "          Final Result          ";
    cout << "\n================================\n";
}

// Print Question Statistics

void PrintQuestionStatistics(
    const stQuestionInfoAndCounters& QuestionInfoAndCounters)
{
    cout << "\nTotal Questions: "
        << QuestionInfoAndCounters.NumberOfQuestion;

    cout << "\nQuestions Answered: "
        << QuestionInfoAndCounters.QuestionCountr;

    cout << "\nCorrect Answers: "
        << QuestionInfoAndCounters.CorrcetAnwer;

    cout << "\nWrong Answers: "
        << QuestionInfoAndCounters.WrongAnswer;
}

// Calculate Success Rate

double CalculateSuccessRate(
    const stQuestionInfoAndCounters& QuestionInfoAndCounters)
{
    return (double)QuestionInfoAndCounters.CorrcetAnwer /
        QuestionInfoAndCounters.NumberOfQuestion * 100;
}

// Print Success Rate

void PrintSuccessRate(
    const stQuestionInfoAndCounters& QuestionInfoAndCounters)
{
    cout << "\nSuccess Rate: "
        << CalculateSuccessRate(QuestionInfoAndCounters) << "%";
}

// Print Final Result Footer

void PrintFinalResultFooter()
{
    cout << "\n================================\n";
}

// Print Final Result

void PrintFinalResult(
    const stQuestionInfoAndCounters& QuestionInfoAndCounters)
{
    PrintFinalResultHeader();

    PrintQuestionStatistics(QuestionInfoAndCounters);

    PrintSuccessRate(QuestionInfoAndCounters);

    PrintFinalResultFooter();
}

// Read Question Number To Review

short ReadQuestionNumberToReview(
    const stQuestionInfoAndCounters& QuestionInfoAndCounters)
{
    return ReadNumberFromTo(
        "Enter question number to review: ",
        1, QuestionInfoAndCounters.QuestionCountr);
}

// Print Question Review

void PrintQuestionReview(
    const stQuestionInfoAndCounters& QuestionInfoAndCounters,
    short QuestionNumber)
{
    PrintQuestion(QuestionInfoAndCounters, QuestionNumber);

    cout << "\nYour Answer: "
        << QuestionInfoAndCounters.QuestionInf[QuestionNumber].UserAnswer;

    cout << "\nCorrect Answer: "
        << GetCorrectAnswer(QuestionInfoAndCounters, QuestionNumber);

    if (CheckAnswer(QuestionInfoAndCounters, QuestionNumber))
    {
        cout << "\n\033[32mCorrect Answer!\033[0m\n";
    }
    else
    {
        cout << "\n\033[31mWrong Answer!\033[0m\n";
    }
}

// Review Question

void ReviewQuestion(const stQuestionInfoAndCounters& QuestionInfoAndCounters)
{
    short QuestionNumber = ReadQuestionNumberToReview(QuestionInfoAndCounters);

    QuestionNumber--;

    PrintQuestionReview(QuestionInfoAndCounters, QuestionNumber);
}

// Clear Screen

void ClearScreen()
{
    system("cls");
}

// Play Questions

void PlayQuestions(stQuestionInfoAndCounters& QuestionInfoAndCounters)
{
    for (short i = 0;
        i < QuestionInfoAndCounters.NumberOfQuestion; i++)
    {
        PrintQuestion(QuestionInfoAndCounters, i);

        ReadUserAnswer(QuestionInfoAndCounters, i);

        UpdateAnswerCounters(QuestionInfoAndCounters, i);

        PrintAnswerResult(QuestionInfoAndCounters, i);
    }
}

// Play Game

void PlayGame()
{
    stQuestionInfoAndCounters QuestionInfoAndCounters = {};

    ReadQuestionInfo(QuestionInfoAndCounters);

    PlayQuestions(QuestionInfoAndCounters);

    PrintFinalResult(QuestionInfoAndCounters);

    if (ReadYesNo("\nDo you want to review a question? (Y/N): "))
    {
        ReviewQuestion(QuestionInfoAndCounters);
    }
}

// Ask To Restart Game

bool AskToRestartGame()
{
    if (!ReadYesNo("\nDo you want to restart the game? (Y/N): "))
        return false;

    ClearScreen();

    return true;
}

// Start Game

void StartGame()
{
    do
    {
        PlayGame();

    } while (AskToRestartGame());
}

// Main

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}