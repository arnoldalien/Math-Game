
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };

struct stQuizResults
{
	int NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	short RightAnswers = 0;
	short WrongAnswers = 0;
};

string GetStringLevel(enQuestionsLevel level)
{
	switch (level)
	{
	case Easy: return "Easy";
	case Med: return "Medium";
	case Hard: return "Hard";
	case MixLevel: return "Mix";
	default: return "Unknown";
	}
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;

	return randNum;
}

int ReadHowManyQuestions()
{
	short Questions = 0;

	cout << "How Many Questions do you want to answer ? ";
	cin >> Questions;

	return Questions;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short Level = 0;
	do
	{
		cout << "\nEnter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> Level;
	} while (Level < 1 || Level > 4);

	return (enQuestionsLevel)Level;
}

int LevelInQuestions(enQuestionsLevel QuizLevel)
{

	switch (QuizLevel)
	{
	case enQuestionsLevel::Easy:
		return RandomNumber(1, 10);
	case enQuestionsLevel::Med:
		return RandomNumber(10, 50);
	case enQuestionsLevel::Hard:
		return RandomNumber(50, 100);
	case enQuestionsLevel::MixLevel:
		return RandomNumber(1, 100);
	default:
		return RandomNumber(1, 100);
	}

}
enOperationType ReadOperationType()
{
	short operationType = 0;

	do
	{

		cout << "\nEnter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> operationType;

	} while (operationType < 1 || operationType > 5);

	return (enOperationType)operationType;

}

enOperationType GetRandomOperation()
{

	return (enOperationType)RandomNumber(1, 3);
}

int CalculateTheRound(enOperationType OP, int Number1, int Number2)
{
	switch (OP)
	{
	case Add: return Number1 + Number2;
	case Sub: return Number1 - Number2;
	case Mul: return Number1 * Number2;
	case Div: return (Number2 != 0) ? Number1 / Number2 : 0;
	default: return 0;
	}
}

string GetOperationName(enOperationType op)
{
	switch (op)
	{
	case Add: return "+";
	case Sub: return "-";
	case Mul: return "x";
	case Div: return "/";
	case Mix: return "Mix";
	default: return "Unknown";
	}
}

void ShowQuestion(enOperationType Op, int Number1, int Number2)
{

	cout << Number1 << endl;
	cout << Number2 << " " << GetOperationName(Op) << endl;
	cout << "__________" << endl;
}

void PassOrFail(short Right, short Wrong)
{
	if (Right > Wrong)
	{
		cout << "\n__________________________________\n\n";
		cout << " Final Result is PASS :-)\n\n";
		cout << "----------------------------------";
		system("color 2F");
	}
	else
	{
		cout << "\n__________________________________\n\n";
		cout << " Final Result is Fail :-)\n\n";
		cout << "----------------------------------";
		system("color 4F");
	}
}

stQuizResults PlayQuiz()
{

	stQuizResults Result;

	Result.NumberOfQuestions = ReadHowManyQuestions();
	Result.QuestionsLevel = ReadQuestionsLevel();
	Result.OperationType = ReadOperationType();


	for (int QuestionNumber = 1; QuestionNumber <= Result.NumberOfQuestions; QuestionNumber++)
	{
		cout << "\n\nQuestion [" << QuestionNumber << "/" << Result.NumberOfQuestions << "]\n\n";

		int Number1 = LevelInQuestions(Result.QuestionsLevel);
		int Number2 = LevelInQuestions(Result.QuestionsLevel);

		enOperationType Op = (Result.OperationType == Mix) ? GetRandomOperation() : Result.OperationType;

		int TrueAnswer = CalculateTheRound(Op, Number1, Number2);

		int Answer = 0;
		ShowQuestion(Op, Number1, Number2);
		cin >> Answer;

		if (Answer == TrueAnswer)
		{
			cout << "Right Answer :-)\n";
			system("color 2F");
			Result.RightAnswers++;
		}
		else
		{
			cout << "Wrong Answer :-(\n";
			cout << "The right answer is: " << TrueAnswer << endl;
			system("color 4F");
			cout << '\a';
			Result.WrongAnswers++;
		}
	}
	PassOrFail(Result.RightAnswers, Result.WrongAnswers);
	cout << "\nNumber Of Questions: " << Result.NumberOfQuestions << endl;
	cout << "Questions Level        : " << GetStringLevel(Result.QuestionsLevel) << endl;
	cout << "OpType                 : " << GetOperationName(Result.OperationType) << endl;
	cout << "Number of Right Answers: " << Result.RightAnswers << endl;
	cout << "Number of Wrong Answers: " << Result.WrongAnswers << endl << endl;
	cout << "__________________________________\n\n";
	return Result;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartQuiz()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stQuizResults QuizResult = PlayQuiz();
		cout << "Do you want  to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartQuiz();

	return 0;
}
