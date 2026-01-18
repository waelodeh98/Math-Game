#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

enum en_Questions_Level { Easy_Level = 1, Med_Level = 2, Hard_Level = 3, Mix = 4 };

enum en_Operation_Type { Add = 1, Sub = 2, Mult = 3, Div = 4, Mix_OP = 5 };

struct st_Question {
	int Number_One = 0;
	int Number_Two = 0;
	en_Operation_Type Operation_Type;
	en_Questions_Level Question_Level;
	int Correct_Answer = 0;
	int Player_answer = 0;
	bool Answer_Result = false;
};

struct st_Quizz {
	st_Question Question_List[100];
	short Number_Of_Questions;
	en_Questions_Level Questions_Level;
	en_Operation_Type Op_Type;
	short Number_Of_Wrong_Answers = 0;
	short Number_Of_Right_Answers = 0;
	bool Is_Pass = false;
};

short Read_How_Many_Questions() {
	short Number_Of_Questions = 0;
	do {
		cout << "How Many Questions Do You Want To Answer ? ";
		cin >> Number_Of_Questions;
	} while (Number_Of_Questions < 1 || Number_Of_Questions > 10);
	return Number_Of_Questions;
}

en_Questions_Level Read_Questions_Level() {
	short Question_Level = 0;
	do {
		cout << "Enter Question Level [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
		cin >> Question_Level;
	} while (Question_Level < 1 || Question_Level > 4);
	return (en_Questions_Level)Question_Level;
}

en_Operation_Type Read_Operation_Type() {
	short Operation_Type = 0;
	do {
		cout << "Enter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix ? ";
		cin >> Operation_Type;
	} while (Operation_Type < 1 || Operation_Type > 5);
	return (en_Operation_Type)Operation_Type;
}

int Random_Number(int From, int To) {
	return rand() % (To - From + 1) + From;
}

en_Operation_Type Get_Random_Operation_Type() {
	int Operation_Type = Random_Number(1, 4);
	return (en_Operation_Type)Operation_Type;
}

int Simple_Calculator(int Number_One, int Number_Two, en_Operation_Type Operation_Type) {
	switch (Operation_Type) {
	case en_Operation_Type::Add:
		return Number_One + Number_Two;
	case en_Operation_Type::Sub:
		return Number_One - Number_Two;
	case en_Operation_Type::Mult:
		return Number_One * Number_Two;
	case en_Operation_Type::Div:
		return Number_One / Number_Two;
	defualt:
		return Number_One + Number_Two;
	}
}

st_Question Generate_Question(en_Questions_Level Question_Level, en_Operation_Type Operation_Type) {
	st_Question Question;
	if (Question_Level == en_Questions_Level::Mix) {
		Question_Level = (en_Questions_Level)Random_Number(1, 3);
	}
	if (Operation_Type == en_Operation_Type::Mix_OP) {
		Operation_Type = Get_Random_Operation_Type();
	}

	Question.Operation_Type = Operation_Type;

	switch (Question_Level) {
	case en_Questions_Level::Easy_Level:
		Question.Number_One = Random_Number(1, 10);
		Question.Number_Two = Random_Number(1, 10);

		Question.Correct_Answer = Simple_Calculator(Question.Number_One, Question.Number_Two, Question.Operation_Type);
		Question.Question_Level = Question_Level;
		return Question;

	case en_Questions_Level::Med_Level:
		Question.Number_One = Random_Number(10, 50);
		Question.Number_Two = Random_Number(10, 50);

		Question.Correct_Answer = Simple_Calculator(Question.Number_One, Question.Number_Two, Question.Operation_Type);
		Question.Question_Level = Question_Level;
		return Question;
	case en_Questions_Level::Hard_Level:
		Question.Number_One = Random_Number(50, 100);
		Question.Number_Two = Random_Number(50, 100);

		Question.Correct_Answer = Simple_Calculator(Question.Number_One, Question.Number_Two, Question.Operation_Type);
		Question.Question_Level = Question_Level;
		return Question;
	}
	return Question;
}

void Generate_Quiz_Questions(st_Quizz& Quiz) {
	for (short Question = 0; Question < Quiz.Number_Of_Questions; Question++) {
		Quiz.Question_List[Question] = Generate_Question(Quiz.Questions_Level, Quiz.Op_Type);
	}
}

string Get_Op_Type_Symbol(en_Operation_Type Operation_Type) {
	switch (Operation_Type) {
	case en_Operation_Type::Add:
		return "+";
	case en_Operation_Type::Sub:
		return "-";
	case en_Operation_Type::Mult:
		return "*";
	case en_Operation_Type::Div:
		return "/";
	default:
		return "Mix";
	}
}

void Print_The_Question(st_Quizz& Quiz, short Question_Number) {
	cout << '\n';
	cout << "Question [" << Question_Number + 1 << "/" << Quiz.Number_Of_Questions << "]\n\n";
	cout << Quiz.Question_List[Question_Number].Number_One << endl;
	cout << Quiz.Question_List[Question_Number].Number_Two << " ";
	cout << Get_Op_Type_Symbol(Quiz.Question_List[Question_Number].Operation_Type);
	cout << "\n__________" << endl;
}

int Read_Question_Answer() {
	int Question_Answer = 0;
	cin >> Question_Answer;
	return Question_Answer;
}

void Set_Screen_Color(bool Right_Answer) {
	if (Right_Answer)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << '\a';
	}
}

void Correct_The_Question_Answer(st_Quizz& Quiz, short Question_Number) {
	if (Quiz.Question_List[Question_Number].Player_answer != Quiz.Question_List[Question_Number].Correct_Answer) {
		Quiz.Question_List[Question_Number].Answer_Result = false;
		Quiz.Number_Of_Wrong_Answers++;
		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is : ";
		cout << Quiz.Question_List[Question_Number].Correct_Answer;
		cout << "\n";
	}
	else
	{
		Quiz.Question_List[Question_Number].Answer_Result = true;
		Quiz.Number_Of_Right_Answers++;
		cout << "Right Answer :-) \n";
	}
	cout << endl;
	Set_Screen_Color(Quiz.Question_List[Question_Number].Answer_Result);
}

void Ask_And_Correct_Question_List_Answer(st_Quizz& Quiz) {
	for (short Question_Number = 0; Question_Number < Quiz.Number_Of_Questions; Question_Number++) {
		Print_The_Question(Quiz, Question_Number);
		Quiz.Question_List[Question_Number].Player_answer = Read_Question_Answer();
		Correct_The_Question_Answer(Quiz, Question_Number);
	}
	Quiz.Is_Pass = (Quiz.Number_Of_Right_Answers >= Quiz.Number_Of_Wrong_Answers);
}

string Get_Final_Results_Text(bool Is_Pass) {
	if (Is_Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

string Get_Question_Level_Text(en_Questions_Level Questions_Level) {
	string Array_Questions_Level_Text[4] = { "Easy" , "Med" , "Hard" , "Mix" };
	return Array_Questions_Level_Text[Questions_Level - 1];
}

void Print_Quiz_Result(st_Quizz Quiz) {
	cout << "\n";
	cout << "________________________________\n\n";
	cout << "Final Results is " << Get_Final_Results_Text(Quiz.Is_Pass) << endl;
	cout << "________________________________\n\n";
	cout << "Number Of Questions  : " << Quiz.Number_Of_Questions << endl;
	cout << "Questions Level      : " << Get_Question_Level_Text(Quiz.Questions_Level) << endl;
	cout << "Operation Type       : " << Get_Op_Type_Symbol(Quiz.Op_Type) << endl;
	cout << "Number Of Right Answers : " << Quiz.Number_Of_Right_Answers << endl;
	cout << "Number Of Wrong Answers : " << Quiz.Number_Of_Wrong_Answers << endl;
	cout << "________________________________\n\n";
}

void Play_Math_Game() {
	st_Quizz Quiz;
	Quiz.Number_Of_Questions = Read_How_Many_Questions();
	Quiz.Questions_Level = Read_Questions_Level();
	Quiz.Op_Type = Read_Operation_Type();

	Generate_Quiz_Questions(Quiz);
	Ask_And_Correct_Question_List_Answer(Quiz);
	Print_Quiz_Result(Quiz);
}

void Reset_Screen() {
	system("cls");
	system("color 0F");
}

void Start_Game() {
	char Play_Again = 'y';
	do {
		Reset_Screen();
		Play_Math_Game();
		cout << "Do You Want To Play Again ? Y/N ? ";
		cin >> Play_Again;
	} while (Play_Again == 'Y' || Play_Again == 'y');
}

int main() {
	srand((unsigned)time(NULL));
	Start_Game();
	return 0;
}