#include <iostream>
#include <istream>
#include <conio.h>
#include <time.h>
#include <string>
#include <windows.h>

#include "../headers/Turn.h"
#include "../headers/Screens.h"

#define TWO 50
#define ESC 27

Screens<std::string, char*, int> S;

bool Turn::CheckTurn(bool check_over) {

	//Stress Check
	if (stress < 0) {
		stress = 0;
	}

	//Turn Check
	numOfActions--;
	if (numOfActions <= 0) {
		numOfActions = 2;
		numOfTurns++;
	}

	//Win & Loss Conditions
	if (numOfTurns == turnLimit) {
		//Loss by lack of turns
	}

	else if (amOfMarks < 0) {
		//Loss by lack of marks
	}

	else if (amOfMarks >= markGoal) {
		//Win by reaching goal
	}

	else {
		//Continue game
		return false;
	}
}

void Turn::InitSeed() {
	if (seed == 0) {
		srand(time(NULL));
	}
	else {
		srand(seed);
	}
}

//Job Option
void Turn::Job() {
	while (!err){
		S.Specialty("Please type in your perferred Job", "(Job title should be shorter than 40 characters)", "", "");
		Sleep(1000 * 2);

		std::getline(std::cin,career);

		if (career.size() > 40) {
			std::cout << "I said shorter than 40 characters.";
			system("PAUSE");
			continue;
		}
		err = true;
	}

	//Init jobs
	jobs = rand() % 10 + 1;
	randNumOfJobFound = rand() % jobs + 1;
	if (randNumOfJobFound > jobs / 2) {
		//Init Wage
		randWage = rand() % 1000 + 400; //Base wage
		randNumOfProm = rand() % jobs + 2 / 2 + 1; //amount of promotions
		randProm = rand() % 600 + 50; //mark promotion
		actsUntilProm = rand() % 10 + 5; //how many acts until a promotion
		wage = randWage;
		jobBool = true;

		//Stress
		randStress = rand() % 10; // Stress v
		stress -= randStress;

		S.Specialty("Congrats! You found a Job!", "Your starting wage is:", wage, "Your stress is reduced by:", randStress);
		system("PAUSE");
	}
	else { //fail to find job
		randStress = rand() % 14 + 1; //add stress
		stress += randStress;

		S.Specialty("Seems like you were not lucky enough to find a job.", "Your stress has been increased by:",randStress,"");

		//Reset job stats and add stress
		career = "Start a new Job";
		wage = 0;

		system("PAUSE");
	}
}

// Work Option
void Turn::Work() {
	if (jobBool) {
		amOfMarks += wage; //get paid

		//Stress
		randJobMood = rand() % 10;
		if (randJobMood < 3) {
			randStress = rand() % 4 + 1;
			stress -= randStress;

			S.Specialty("You work for the day! I had a great day today!", "Your balance is increased by: ", wage, "Your stress is reduced by: ", randStress);
			Sleep(1000);
			system("PAUSE");
		}
		else {
			randStress = rand() % 15 + 1;
			stress += randStress;
			S.Specialty("You work, although you had a pretty bad day.", "Your balance is increased by: ", wage, "Your stress is increased by: ", randStress);
			Sleep(1000);
			system("PAUSE");
		}

		//Promotions
		if (++promCount == actsUntilProm) {
			if (randNumOfProm <= 0) { //if no more promotions left
				S.Specialty((const char*)"This job isn't willing to give you anymore promotions", (const char*)"", (const char*)"", (const char*)"");
				Sleep(1000);
				system("PAUSE");
			}
			else if (randNumOfProm > 0) { //if promotions left
				randNumOfProm -= 1; //reduce num of promotions
				actsUntilProm = rand() % 10 + 5;
				promCount = 0;
				wage += randProm; //increase working wage
				S.Specialty("You got promoted!", "You now will earn an extra: ", randProm, "");
				Sleep(1000 * 2);
				system("PAUSE");
			}
		}
	}

	else { //dont have a job
		S.Specialty("You don't have a job.", "You walk around the city aimlessly.", "", "");
		stress += 10;
		system("PAUSE");
	}
}

void Turn::StrsRelief() {
	S.Specialty("You take time to calm the nerves","What would you like to do?", "", "");
	std::getline(std::cin, typeOfStrsR);
	randStress = rand() % 15 + 5;
	std::string strsType = "You " + typeOfStrsR;

	S.Specialty(strsType, "Your stress is reduced by: ", randStress, " ");
}