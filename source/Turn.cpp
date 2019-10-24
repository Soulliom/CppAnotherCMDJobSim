#include <iostream>
#include <istream>
#include <conio.h>
#include <time.h>
#include <string>
#include <windows.h>
#include <vector>

#include "../headers/Turn.h"
#include "../headers/Screens.h"

#define TWO 50
#define ESC 27

Screens S;

bool Turn::CheckTurn(bool check_over) {

	//Turn Check
	numOfActions--;
	if (numOfActions <= 0) {
		numOfActions = 2;
		numOfTurns++;

		if (wage != 0) {
			payment = rand() % (wage / 2) + (wage) * (1 + stress / stressCap);
			amOfMarks -= payment;

			S.Specialty("Payments are due.", "You pay: ", payment, "");
			system("PAUSE");
		}
	}
	//Stress Check
	if (stress < 0) {
		stress = 0;
	}
	if (stress >= stressCap) {
		StrsLimt();
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
	bool err = true;
	while (err){
		S.Specialty("Please type in your perferred Job.", "(Job title should be shorter than 40 characters).", "(Use underscores as spaces)");

		std::cin >> career;

		if (career.size() > 40) {
			std::cout << "Job Title is too long! Try again!\n";
			system("PAUSE");
			continue;
		}
		err = false;
	}

	//Init jobs
	rando = rand() % 10 + 1;
	randNumOfJobFound = rand() % rando + 1;
	if (randNumOfJobFound >= (rando / 2)) {
		//Init Wage
		randWage = rand() % 500 + 500; //Base wage
		randNumOfProm = rand() % rando + 2 / 2 + 1; //amount of promotions
		actsUntilProm = rand() % 5 + 5; //how many acts until a promotion
		wage = randWage;
		jobBool = true;

		//Stress
		randStress = rand() % 10; // Stress v
		stress -= randStress;

		S.Specialty("Congrats! You found a Job!", "Your starting wage is:", wage, "Your stress is reduced by:", randStress);
		system("PAUSE");
	}
	else { //fail to find job
		randStress = rand() % 10 + 5; //add stress
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

		//Job stress
		randJobMood = rand() % 10;
		if (randJobMood < 3) {
			randStress = rand() % 4 + 1;
			stress -= randStress;

			S.Specialty("You work for the day! I had a great day today!", "Your balance is increased by: ", wage, "Your stress is reduced by: ", randStress);
			system("PAUSE");
		}
		else {
			randStress =(rand() % 10 + 5) * (1 + stress/stressCap);
			stress += randStress;
			S.Specialty("You work, although you had a pretty bad day.", "Your balance is increased by: ", wage, "Your stress is increased by: ", randStress);
			system("PAUSE");
		}

		//Promotions counter/calculator
		if (++promCount == actsUntilProm) {
			if (randNumOfProm <= 0) { //if no more promotions left
				S.Specialty("This job isn't willing to give you anymore promotions.", "", "");
				system("PAUSE");
			}
			else if (randNumOfProm > 0) { //if promotions left
				randNumOfProm -= 1; //reduce num of promotions
				randProm = rand() % 800 + 200; //reset promotion earning
				actsUntilProm = rand() % 5 + 5; //reset acts until promotion
				promCount = 0; //reset promotion count
				wage += randProm; //increase working wage

				S.Specialty("You got promoted!", "You now will earn an extra: ", randProm, "");
				system("PAUSE");
			}
		}
	}

	else { //dont have a job
		S.Specialty("You don't have a job.", "You walk around the city aimlessly.", "Your stress is increased by: 10");
		system("PAUSE");

		stress += 10;
	}
}

void Turn::StrsRelief() {
	std::string opHob = "2. ";
	std::string youHob = "You ";
	
	opHob += sHobby;
	const char* tempOpHob = opHob.c_str();

	youHob += sHobby;
	const char* tempYouHob = youHob.c_str();


	S.Specialty("You decide to take your mind off things for a while.", "1. Start a new Hobby", tempOpHob);

	bool err = true;
	while (true) {
		switch (_getch()) {
		case ONE:
			while (err) {
				S.Specialty("What would you like to do as a hobby?", "(Hobby should be shorter than 20 characters).", "(Use underscores as spaces)");

				std::cin >> sHobby;

				if (sHobby.size() > 20) {
					std::cout << "Hobby name is too long! Try again!\n";
					system("PAUSE");
					continue;
				}
				isHobby = true;
				err = false;
			}
			rando = rand() % 5 + 5;
			hobbyStressR = rand() % (stressCap / rando) + 5;
			break;

		case TWO:
			if (!isHobby) {
				S.Specialty("You dont have a hobby, Please try starting one first","","");
				system("PAUSE");
				StrsRelief();
				break;
			}
			randStress = (rand() % hobbyStressR + hobbyStressR / 1.25) * (1 + (stress / stressCap));
			stress -= randStress;

			S.Specialty(tempYouHob, "Your stress is decreased by: ", randStress, "");
			system("PAUSE");
			break;

		default:
			continue;
			break;
		}
		break;
	}
}

void Turn::StrsLimt() {
	numOfTurns++;
	if (stress > stressCap) {
		stress = stressCap;
	}
	stress -= stressCap/4;

	S.Specialty("You've gone over your stress limit, a turn is skipped.", "You should find a way to decrease your stress.", "Your stress is decreased by: 15");
	system("PAUSE");
}