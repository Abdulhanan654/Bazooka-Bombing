#pragma once


#include <fstream>
#include <iostream>
using namespace std;
class score {
	int Score;
public:
	// Constructor to initialize the score to 0
	score()
	{
		Score = 0;
	}
	//  function to get the current score
	int getScore() {
		return Score;
	}

	// Function to add a specified value to the score
	void AddScore(int x) {
		Score += x;
	}
};


class HighScores {
	int score1;
	int score2;
	int score3;
	int score4;
	int score5;
	ifstream read;
	ofstream write;
public:
	
	// Function to read high scores from a file
	void setHighscores() {
		read.open("Scoring.txt");
		read >> score1 >> score2 >> score3 >> score4 >> score5;
		read.close();
	}
	// Function to display high scores
	void getHighscores() {
		cout << score1 << endl;
		cout << score2 << endl;
		cout << score3 << endl;
		cout << score4 << endl;
		cout << score5 << endl;
	}
	// Function to update high scores based on the current game score
	void UpdateHighScore(int score) {
		if (score > score1) {
			score5 = score4;
			score4 = score3;
			score3 = score2;
			score2 = score1;
			score1 = score;
		}
		else if (score > score2) {
			score5 = score4;
			score4 = score3;
			score3 = score2;
			score2 = score;

		}
		else if (score > score3) {
			score5 = score4;
			score4 = score3;
			score3 = score;

		}
		else if (score > score4) {
			score5 = score4;
			score4 = score;

		}
		else if (score > score5) {
			score5 = score;
		}

		// Write the updated high scores to the file
		write.open("Scoring.txt", std::ios::trunc);
		write << score1 << endl << score2 << endl << score3 << endl << score4 << endl << score5 << endl;
		write.close();
	}

};
